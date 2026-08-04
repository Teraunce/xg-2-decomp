/**
 * init.c — LZSS decompressor + OS init
 *
 * ROM:0x1098 → VRAM:0x8004B498
 *
 * Layout:
 *   func_8004B464  VRAM:0x8004B464  Icache flush (called just before jumping to
 *                                   decompressed code)
 *   func_8004B498  VRAM:0x8004B498  Main entry: reads PIF, DMA-copies compressed
 *                                   block to staging area, LZSS-decompresses back
 *                                   to 0x8004BA20, then jumps to decompressed code.
 *   func_8004B5B8  VRAM:0x8004B5B8  Back-reference copy inner loop (inlined by
 *                                   compiler into func_8004B498 but split by
 *                                   spimdisasm at a glabel boundary).
 *
 * LZSS parameters (Okumura variant):
 *   Ring buffer size:   4096 bytes (N=0x1000)
 *   Initial write pos:  0xFEE
 *   Ring fill value:    0x00
 *   Min match length:   3   ((k & 0xF) + 3 bytes output per back-ref)
 *   Bit convention:     1 = literal, 0 = back-reference
 *   Flag byte order:    LSB first; 0xFF00 sentinel signals 8 bits exhausted
 *   Termination:        output byte counter (output_size from header)
 *
 * Compressed block layout at VRAM:0x8004BA20 (ROM:0x1620):
 *   +0x00  u32   version   (= 1)
 *   +0x04  u32   pad       (= 0)
 *   +0x08  u32   hdr_size  (= 0x18 = 24)  ← used to locate compressed data
 *   +0x0C  u32   magic     (= 'LZSS' = 0x4C5A5353)
 *   +0x10  u32   out_size  (= 0x4AB20 = 305,952)  ← output byte counter
 *   +0x14  u32   in_size   (= 0x2B56F = 177,519)
 *   +0x18  u8[]  compressed data (177,519 bytes)
 *
 * Decompressor writes 305,952 bytes to VRAM:0x8004BA20, overwriting itself.
 * After decompression finishes, a icache flush is performed and the
 * decompressed code entry point (0x8004BA20) is called via jalr.
 */

#include "ultra64.h"

/* SI hardware register (Serial Interface status) */
#define SI_STATUS_REG  (*(volatile u32 *)0xA4800018)
/* PIF RAM control word */
#define PIF_RAM_CTRL   (*(volatile u32 *)0xBFC007FC)

/* Compressed block staging area (DMA copy destination, in upper RDRAM) */
extern u32 D_8024BA20;    /* staging area base — DMA destination */
extern u32 D_8024BA28;    /* staging area + 8 — header word at +8 (hdr_size) */

/* Source of LZSS compressed block (in the 1MB initial load) */
typedef void (*DecompEntryFn)(void);
extern DecompEntryFn D_8004BA20;  /* also the decompressor output address */

/* Copy word count (= 0x2B588 / 4 = 0xAD62 words — header + compressed data
   rounded up to 4 bytes). Used as loop limit for staging copy. */
extern u32 D_2B588;

/* Cache flush helper (invalidates icache over decompressed region) */
void func_8004B464(void);


/**
 * func_8004B498 — LZSS decompressor and OS init
 *
 * Never returns — jumps to decompressed code after finishing.
 */
void func_8004B498(void) {
    /* Ring buffer lives on the stack (0x1000 bytes at sp+0x10).
       Allocated by the 0x1030-byte frame (addiu $sp,$sp,-0x1030). */
    s8 ring[0x1000];  /* at sp+0x10, zeroed below */

    /* --- Wait for SI controller ready, then enable 64-bit CIC mode --- */
    while (SI_STATUS_REG & 3) {}

    /* Read PIF command byte (initialises controller) */
    while (SI_STATUS_REG & 3) {}
    PIF_RAM_CTRL |= 8;

    /* --- Copy compressed block to staging area (word-by-word DMA) ---
     * Copies 0xAD62 words (0x2B588 bytes) from D_8004BA20 → D_8024BA20.
     * This moves the LZSS header + compressed data to a safe location
     * so the decompressor can write its output back to 0x8004BA20
     * without clobbering the source as it reads it.
     */
    {
        u32 *src  = (u32 *)&D_8004BA20;
        u32 *dst  = (u32 *)&D_8024BA20;
        s32  words = (u32)&D_2B588 / 4;   /* 0xAD62 */
        s32  i    = 0;
        while (i < words) {
            *dst++ = *src++;
            i++;
        }
    }

    /* --- Zero the ring buffer (4078 bytes, downward from &ring[0xFFD]) ---
     * Fills indices 0–4077 with 0x00 (indices 4078–4095 are uninitialised
     * stack — zeroed by RDRAM on emulator / undefined on real hardware).
     */
    {
        s8 *p = &ring[0xFFD];  /* sp + 0xFFD */
        s32  n = 0xFED;         /* count = 4077; loop runs 4078 times (n >= 0) */
        do {
            *p-- = 0;
        } while (--n >= 0);
    }

    /* --- Locate compressed data via the staged header ---
     *
     * Staging header at D_8024BA20:
     *   [0] = version (1)
     *   [1] = pad (0)
     *   [2] = hdr_size (0x18)   ← used here
     *   [3] = 'LZSS'
     *   [4] = out_size (0x4AB20) ← t3 counter
     *   [5] = in_size  (0x2B56F)
     *
     * a3 = &D_8024BA28 + D_8024BA28.hdr_size - 8
     *    = 0x8024BA28 + (0x18 - 8)
     *    = 0x8024BA38  ← first byte of compressed data
     */
    u8  *src_ptr   = (u8 *)((u32)&D_8024BA28 + *(u32 *)&D_8024BA28 - 8);
    s8  *out_ptr   = (s8 *)&D_8004BA20;  /* write output back to 0x8004BA20 */
    s32  out_left  = *((s32 *)&D_8024BA28 + 2);   /* header[+0x10] = out_size */
    s32  write_pos = 0xFEE;                         /* ring write position */
    s32  flags     = 0;                             /* flag shift register */

    /* --- LZSS main loop ---
     * flag register $t4:
     *   Loaded as flag_byte | 0xFF00.
     *   Bit 0 = current symbol type (1=literal, 0=backref).
     *   Shifted right after each symbol.
     *   When bit 8 becomes 0, load next flag byte.
     */
    if (out_left > 0) {
        flags = 0 >> 1;  /* initial pre-shift (no-op since flags=0) */
        do {
            s32 bit;
            if (flags & 0x100) {
                /* Sentinel still set — use existing bit */
                bit = flags & 1;
            } else {
                /* Fetch new flag byte, set sentinel at bit 8 via 0xFF00 */
                s32 fb = (s8)*src_ptr++;
                flags  = fb | 0xFF00;
                bit    = flags & 1;
            }

            if (bit != 0) {
                /* Literal: copy one byte directly */
                s8 byte       = (s8)*src_ptr++;
                ring[write_pos] = byte;
                write_pos       = (write_pos + 1) & 0xFFF;
                out_left--;
                *out_ptr++ = byte;
            } else {
                /* Back-reference: two-byte encoding
                 *   j = src[0]           (low 8 bits of 12-bit offset)
                 *   k = src[1]           (packed: high 4 bits of offset + 4-bit length)
                 *   offset = j | ((k & 0xF0) << 4)   (12-bit ring read position)
                 *   length = (k & 0x0F) + 3           (copy count, min 3)
                 */
                u8  j      = src_ptr[0];
                u8  k      = src_ptr[1];
                src_ptr   += 2;
                s32 offset = j | ((k & 0xF0) << 4);
                s32 length = (k & 0xF) + 2;   /* loop runs while copy_i <= length */
                s32 copy_i = 0;
                do {
                    s8 byte          = ring[(offset + copy_i) & 0xFFF];
                    ring[write_pos]  = byte;
                    write_pos        = (write_pos + 1) & 0xFFF;
                    out_left--;
                    *out_ptr++ = byte;
                    copy_i++;
                } while (length >= copy_i);  /* runs length+1 = (k&F)+3 times */
            }

            flags >>= 1;
        } while (out_left > 0);
    }

    /* Flush icache over decompressed region before jumping into it */
    func_8004B464();

    /* Jump to decompressed code entry at 0x8004BA20 (never returns) */
    D_8004BA20();
}


/**
 * func_8004B464 — Icache flush
 *
 * Invalidates the icache over [0x80000000, 0x80002000) using cache op 0x01
 * (Index Invalidate). Called just before jumping to the decompressed code
 * so the CPU sees fresh instruction words.
 */
void func_8004B464(void) {
    u32 addr = 0x80000000;
    u32 end  = 0x80001FF0;
    do {
        /* cache 0x01, 0(addr) — Index Invalidate Icache */
        __asm__ volatile ("cache 0x01, 0(%0)" :: "r"(addr));
        addr += 0x10;
    } while (addr <= end);
}
