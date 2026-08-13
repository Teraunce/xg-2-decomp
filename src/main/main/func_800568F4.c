#include "ultra64.h"
#include "mtx.h"

f32 cosf(f32);                             /* cosf */
f32 sinf(f32);                             /* sinf */
extern f32 gMtxOneF;
extern f32 gMtxIdent22;

/*
 * mtxRotAxisF — init Y-axis rotation matrix (nonmatching).
 *
 * arg_ft0 and arg_fv0 are passed in non-standard float registers ($f8/$f0)
 * by the SN64 compiler; not expressible as normal C parameters.
 * Called via getter mtxRotAxisFGetter which loads gMtxOneF into $fv0 and
 * moves $a1 into $ft0.
 *
 * The matrix written is a rotation around the Y axis by angle (arg_ft0 * arg_fv0):
 *   [ cos  0  sin  0 ]
 *   [ 0    D  0    0 ]
 *   [-sin  0  cos  0 ]
 *   [ 0    0  0    D ]
 * where D = gMtxOneF (likely 1.0f).
 */
void mtxRotAxisF(Matrix4x4 *arg0 /*, f32 arg_ft0, f32 arg_fv0 */) {
    /* angle = arg_ft0 * arg_fv0  (mul.s $fs0, $ft0, $fv0) */
    f32 sin_val = sinf(0.0f /* angle */);
    f32 cos_val = cosf(0.0f /* angle */);

    arg0->unk0  = cos_val;
    arg0->unk4  = 0.0f;
    arg0->unk8  = sin_val;
    arg0->unkC  = 0.0f;
    arg0->unk10 = 0.0f;
    arg0->unk14 = gMtxOneF;
    arg0->unk18 = 0.0f;
    arg0->unk1C = 0.0f;
    arg0->unk20 = -sin_val;
    arg0->unk24 = 0.0f;
    arg0->unk28 = cos_val;
    arg0->unk2C = 0.0f;
    arg0->unk30 = 0.0f;
    arg0->unk34 = 0.0f;
    arg0->unk38 = 0.0f;
    arg0->unk3C = gMtxOneF;
}

/*
 * mtxRotAxisFGetter2 — GETTER_NOJR preamble for mtxRotZF.
 * Loads gMtxIdent22 into $fv0 and moves $a1 into $ft1, then falls through.
 * Cannot be expressed in standard C.
 */
f32 mtxRotAxisFGetter2(s32 arg1) {
    (void)arg1;
    return gMtxIdent22;
}
