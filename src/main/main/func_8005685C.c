#include "ultra64.h"
#include "mtx.h"

f32 cosf(f32);                             /* cosf */
f32 sinf(f32);                             /* sinf */
extern f32 gMtxIdent00;
extern f32 gMtxIdent11;

/*
 * mtxRotXF — init X-axis rotation matrix (nonmatching).
 *
 * arg_ft1 and arg_fv0 are passed in non-standard float registers ($f7/$f0)
 * by the SN64 compiler; they are not expressible as normal C parameters.
 * Typically called via the getter mtxRotAxisFGetter which loads gMtxIdent11
 * into $fv0 and moves $a1 into $ft0 for the caller.
 *
 * The matrix written is a rotation around the X axis by angle (arg_ft1 * arg_fv0):
 *   [ D  0     0    0 ]
 *   [ 0  cos  -sin  0 ]
 *   [ 0  sin   cos  0 ]
 *   [ 0  0     0    D ]
 * where D = gMtxIdent00 (likely 1.0f).
 */
void mtxRotXF(Matrix4x4 *arg0 /*, f32 arg_ft1, f32 arg_fv0 */) {
    /* angle = arg_ft1 * arg_fv0  (mul.s $fs0, $ft1, $fv0) */
    f32 sin_val = sinf(0.0f /* angle */);
    f32 cos_val = cosf(0.0f /* angle */);

    arg0->unk0  = gMtxIdent00;
    arg0->unk4  = 0.0f;
    arg0->unk8  = 0.0f;
    arg0->unkC  = 0.0f;
    arg0->unk10 = 0.0f;
    arg0->unk14 = cos_val;
    arg0->unk18 = -sin_val;
    arg0->unk1C = 0.0f;
    arg0->unk20 = 0.0f;
    arg0->unk24 = sin_val;
    arg0->unk28 = cos_val;
    arg0->unk2C = 0.0f;
    arg0->unk30 = 0.0f;
    arg0->unk34 = 0.0f;
    arg0->unk38 = 0.0f;
    arg0->unk3C = gMtxIdent00;
}

/*
 * mtxRotAxisFGetter — GETTER_NOJR preamble for mtxRotAxisF.
 * Loads gMtxIdent11 into $fv0 and moves $a1 into $ft0, then falls through.
 * Cannot be expressed in standard C.
 */
f32 mtxRotAxisFGetter(s32 arg1) {
    (void)arg1;
    return gMtxIdent11;
}
