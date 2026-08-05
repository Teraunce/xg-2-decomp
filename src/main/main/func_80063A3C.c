#include "ultra64.h"
#include "audio.h"

/*
 * sfxDispatchSample — SFX definition lookup and sample dispatch (nonmatching).
 * sfxGetFrameOutput — Return the current SFX frame output value (nonmatching).
 *
 * sfxDispatchSample(defIndex, volume):
 *   Reads gSfxDefTable[defIndex] (16-byte record) from the table whose
 *   base pointer lives at gSfxDefTable.  Dispatches on the four-CC tag
 *   at record[+0x04]:
 *
 *     'LHUF' / 0x4C485546 — full sample (Huffman):
 *         audioDecodeHufh(D_8004B658 + rec[0], volume, rec[2])   → returns 1
 *
 *     'COPY' / 0x434F5059 — copy/loop sample:
 *         audioPlayCopySample(D_8004B658 + rec[0], rec[2], volume)   → returns 1
 *
 *     'LZSS' / 0x4C5A5353 — LZSS compressed sample:
 *         func_8005AC70(D_8004B658 + rec[0], volume, rec[2], rec[3])  → returns 1
 *
 *     unknown tag — returns 0.
 *
 * 16-byte record layout (each field is one s32):
 *   +0x00  s32  bank byte-offset (added to D_8004B658 to get sample pointer)
 *   +0x04  u32  four-CC type tag
 *   +0x08  s32  sample length (bytes)
 *   +0x0C  s32  LZSS loop-end or repeat count (only used for 'LZSS')
 *
 * MIPS dispatch uses an unsigned compare (sltu) to sort the tag:
 *   tag == 0x4C485546  → HUFH
 *   tag  < 0x4C485546  → check for LZSS (0x4C5A5353 > HUFH, so falls to bnez path)
 *   tag  > 0x4C485546  → check for COPY (0x434F5059 < HUFH? no, 0x43 < 0x4C → less)
 *
 * Globals:
 *   gSfxDefTable   0x80092D38  void*  pointer to SFX def table base (main BSS)
 *   D_8004B658   0x8004B658  void*  sample bank base pointer (rodata, word-aligned)
 *   D_801823E0   0x801823E0  s32    current SFX frame output value (overlay BSS)
 */

extern void *gSfxDefTable;  /* 0x80092D38 — pointer to SFX def table base */
extern void *D_8004B658;  /* 0x8004B658 — sample bank base pointer */
extern s32   D_801823E0;  /* 0x801823E0 — current SFX frame output value */

/* Sample decoder prototypes — argument order confirmed from asm. */
s32 audioPlayCopySample(void *ptr, s32 length, s32 volume);
s32 func_8005AC70(void *ptr, s32 volume, s32 length, s32 loopEnd);
s32 audioDecodeHufh(void *ptr, s32 volume, s32 length);

/* Four-CC tags stored at record[+0x4] */
#define SFX_TAG_HUFH  0x4C485546u   /* 'LHUF' big-endian → Huffman full sample */
#define SFX_TAG_COPY  0x434F5059u   /* 'COPY' → copy/loop sample              */
#define SFX_TAG_LZSS  0x4C5A5353u   /* 'LZSS' → LZSS-compressed sample        */

/* -------------------------------------------------------------------------
 * sfxDispatchSample
 * Look up SFX def record by index and dispatch to the matching decoder.
 * Returns 1 on success, 0 for an unknown type tag.
 * nonmatching
 * ------------------------------------------------------------------------- */
s32 sfxDispatchSample(s32 defIndex, s32 volume) {
    /* Record pointer: *(base_ptr) + defIndex * 16 */
    s32  *rec    = (s32 *)((u8 *)gSfxDefTable + (defIndex << 4));
    void *bank   = D_8004B658;
    void *sample = (u8 *)bank + rec[0];   /* D_8004B658 + rec[0x0] */
    u32   tag    = (u32)rec[1];            /* four-CC at rec[0x4]  */
    s32   length = rec[2];                 /* rec[0x8]             */
    s32   loopEnd = rec[3];                /* rec[0xC] (LZSS only) */

    if (tag == SFX_TAG_HUFH) {
        audioDecodeHufh(sample, volume, length);
        return 1;
    }

    if (tag > SFX_TAG_HUFH) {
        /* 0x434F5059 'COPY': numerically > 0x4C485546?  No: 0x43 < 0x4C.
         * The sltu in the asm compares $a3 (0x4C485546) against $a0 (tag):
         *   sltu $v0, $a3, $a0  →  $v0 = (0x4C485546 < tag) = (tag > HUFH)
         * So bnez $v0 → .L80063A8C (LZSS check), which is the "tag > HUFH" path.
         * COPY (0x434F5059) < HUFH (0x4C485546), so COPY is reached via
         * the beq at 0x80063A7C (after failing the sltu). */
        if (tag == SFX_TAG_LZSS) {
            func_8005AC70(sample, volume, length, loopEnd);
            return 1;
        }
        return 0;
    }

    /* tag < SFX_TAG_HUFH: check for COPY */
    if (tag == SFX_TAG_COPY) {
        audioPlayCopySample(sample, length, volume);
        return 1;
    }

    return 0;
}

/* -------------------------------------------------------------------------
 * sfxGetFrameOutput
 * Return the current SFX frame output value stored in D_801823E0.
 * nonmatching (0x8 bytes in binary — only 2 instructions before fall-through)
 * ------------------------------------------------------------------------- */
s32 sfxGetFrameOutput(void) {
    return D_801823E0;
}
