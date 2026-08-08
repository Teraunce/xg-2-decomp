#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of mtxEulerRotGetter (initial). */

f32 cosf(f32);                             /* cosf */
void guMtxIdent(Unk*);                           /* extern */
f32 sinf(f32);                             /* sinf */
extern f32 D_80189808;

/*
 * mtxEulerRotF — build Euler-angle (YXZ) rotation matrix (nonmatching).
 *
 * Called via GETTER preamble (mtxEulerRotGetter) which loads a scale factor into
 * $fv0/$f0. At function entry, arg2 and arg3 are pre-multiplied by scale_fv0
 * (via `mul.s $fa1,$fa1,$fv0` and `mul.s $ft4,$ft4,$fv0`), and scale_fv0 is
 * stored to D_80189808. scale_fv0 is not expressible as a standard C parameter.
 *
 * arg1 = yaw   ($fa0/$f12), unscaled
 * arg2 = pitch ($fa1/$f14), scaled at entry
 * arg3 = roll  ($ft4/$f16, non-standard register), scaled at entry
 */
void mtxEulerRotF(Unk *arg0, f32 arg1, f32 arg2, f32 arg3 /*, f32 scale_fv0 */) {
    f32 sin1 = sinf(arg1);
    f32 cos1 = cosf(arg1);
    f32 sin2 = sinf(arg2);
    f32 cos2 = cosf(arg2);
    f32 sin3 = sinf(arg3);
    f32 cos3 = cosf(arg3);

    guMtxIdent(arg0);
    arg0->unk8  = (f32) -sin2;
    arg0->unk0  = (f32) (cos2 * cos3);
    arg0->unk4  = (f32) (cos2 * sin3);
    arg0->unk10 = (f32) (((sin1 * sin2) * cos3) - (cos1 * sin3));
    arg0->unk18 = (f32) (sin1 * cos2);
    arg0->unk14 = (f32) (((sin1 * sin2) * sin3) + (cos1 * cos3));
    arg0->unk20 = (f32) (((cos1 * sin2) * cos3) + (sin1 * sin3));
    arg0->unk28 = (f32) (cos1 * cos2);
    arg0->unk24 = (f32) (((cos1 * sin2) * sin3) - (sin1 * cos3));
}

/*
 * mtxEulerRotGetter — GETTER_NOJR preamble for mtxEulerRotF.
 * Loads scale factor into $fv0, moves $a1/$a2/$a3 into float registers,
 * then falls through to mtxEulerRotF. Cannot be expressed in standard C.
 */
void mtxEulerRotGetter(s32 arg1, s32 arg2, s32 arg3) {
    guRotateDegF2L((f32)arg1, arg2);
}
