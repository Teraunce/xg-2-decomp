/*
 * func_8007A918 — unpack interleaved s32 pairs into floats (nonmatching).
 *
 * Reads from two arrays in arg1 (lo_array at arg1, hi_array at (char*)arg1+0x20),
 * reconstructs pairs of integers from their split 16-bit halves, converts to float,
 * and divides by scale_fv0, writing results to arg0.
 *
 * scale_fv0 is passed in $fv0/$f0 by the caller — non-standard, not a C parameter.
 */
#include "ultra64.h"
void func_8007A918(Unk *arg0, s32 *arg1 /*, f32 scale_fv0 */) {
    s32 sp4;
    s32 temp_a3;
    s32 var_a0;
    s32 var_a2;
    s32 *var_v0;
    u32 *var_v1;
    f32 *var_t1;
    f32 *var_t0;

    var_v0 = arg1;
    var_v1 = (u32 *)((char *)arg1 + 0x20);
    var_a2 = 0;
    var_t0 = (f32 *)arg0;
    do {
        var_a0 = 0;
        var_t1 = var_t0;
loop_2:
        var_a0 += 1;
        sp4    = (s32)(((*var_v1 >> 0x10) & 0xFFFF) | ((u32)*var_v0 & 0xFFFF0000));
        temp_a3 = (s32)((*var_v1 & 0xFFFF) | ((u32)(*var_v0 << 0x10) & 0xFFFF0000));
        var_v0 += 1;
        var_v1 += 1;
        var_t1 += 2;
        var_t1[-2] = (f32)sp4    /* / scale_fv0 */;
        var_t1[-1] = (f32)temp_a3 /* / scale_fv0 */;
        if (var_a0 != 2) {
            goto loop_2;
        }
        var_a2 += 1;
        var_t0 += 4;
    } while (var_a2 != 4);
}

void func_8007A9C8(Unk *arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    *arg4 = arg0->unk30 + ((arg0->unk0 * arg1) + (arg0->unk10 * arg2) + (arg0->unk20 * arg3));
    *arg5 = arg0->unk34 + ((arg0->unk4 * arg1) + (arg0->unk14 * arg2) + (arg0->unk24 * arg3));
    *arg6 = arg0->unk38 + ((arg0->unk8 * arg1) + (arg0->unk18 * arg2) + (arg0->unk28 * arg3));
}
