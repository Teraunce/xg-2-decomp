/**
 * boot.ld — Linker script for the XG2 boot region
 *
 * ROM:0x1000 → VRAM:0x8004B400
 * Covers: boot.s (func_8004B400 + func_8004B464)
 *         init.s (func_8004B498 = LZSS decompressor)
 *
 * BSS regions (both empty in shipped ROM, so start == end):
 *   D_80000400 = BSS 1 start/end  (range cleared by boot stub)
 *   D_80001000 = BSS 2 start/end
 */

OUTPUT_FORMAT("elf32-tradbigmips")
OUTPUT_ARCH(mips)
ENTRY(func_8004B400)

MEMORY {
    BOOT (rx) : ORIGIN = 0x8004B400, LENGTH = 0x98
    INIT (rx) : ORIGIN = 0x8004B498, LENGTH = 0x588
}

SECTIONS {
    /* Boot stub at exact VRAM address — 0x98 bytes */
    .boot 0x8004B400 : {
        *boot.o(.text)
    } > BOOT

    /* LZSS init at exact VRAM address — 0x588 bytes */
    .init 0x8004B498 : {
        *init.o(.text)
    } > INIT

    /DISCARD/ : {
        *(.reginfo)
        *(.pdr)
        *(.mdebug*)
        *(.comment)
        *(.note*)
    }

    /* BSS symbol definitions (both ranges are empty in this build) */
    D_80000400 = 0x80000400;
    D_80001000 = 0x80001000;

    /* Decompressed code entry (jal target in init.s) */
    D_8004BA20 = 0x8004BA20;
    D_2B588    = 0x0002B588;   /* compressed data size constant */
    D_8024BA20 = 0x8024BA20;   /* RDRAM mirror of decompressed code */
    D_8024BA28 = 0x8024BA28;   /* RDRAM mirror + 8 */
}
