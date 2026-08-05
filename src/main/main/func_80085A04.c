#include "ultra64.h"
/*
 * geomBufWrite — geometry buffer write dispatch (nonmatching).
 *
 * PERMANENTLY NONMATCHING — two reasons:
 * 1. Non-standard ABI: command type arrives in $v1, not $a0-$a3.
 *    In standard MIPS ABI $v1 is a return-value register, not an argument.
 *    No C declaration can pass an argument in $v1.
 * 2. jr dispatch through jtbl_8004CF78 (8 entries, index = $v1 & 7).
 *
 * arg0 ($a0) saved to $a3 = target object; $a2 = input buffer pointer.
 * Each case reads $a2[0], computes strip index = $v1 >> 3, and writes to
 * different fields of $a3->unk20[strip_index]:
 *   [0]→unk00  [1]→unk04  [2]→unk08  [3]→unk0A
 *   [4]→unk0C  [5]→unk0E  [6]→various  [7]→various
 * Function size: 0x258 bytes.
 */
s32 geomBufWrite(Unk *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    /* nonmatching: command in $v1 / index ($v1 & 7) — see asm stub */
    (void)arg1; (void)arg2; (void)arg3;
    return 0;
}

s32 audioNodeSetValue(s32 *arg0, s32 arg1, s32 arg2) {
    if (arg1 == 1) {
        *arg0 = arg2;
    }
    return 0;
}
