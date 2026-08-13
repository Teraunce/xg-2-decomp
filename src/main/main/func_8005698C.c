#include "ultra64.h"
#include "mtx.h"

f32 cosf(f32);                             /* cosf */
f32 sinf(f32);                             /* sinf */
extern f32 gMtxIdent33;

/*
 * mtxRotZF — init Z-axis rotation matrix (nonmatching).
 *
 * arg_ft1 and arg_fv0 are passed in non-standard float registers ($f7/$f0)
 * by the SN64 compiler; not expressible as normal C parameters.
 * Called via getter mtxRotAxisFGetter2 which loads gMtxIdent22 into $fv0 and
 * moves $a1 into $ft1.
 *
 * The matrix written is a rotation around the Z axis by angle (arg_ft1 * arg_fv0):
 *   [ cos  -sin  0  0 ]
 *   [ sin   cos  0  0 ]
 *   [ 0     0    D  0 ]
 *   [ 0     0    0  D ]
 * where D = gMtxIdent33 (likely 1.0f).
 */
void mtxRotZF(Matrix4x4 *arg0 /*, f32 arg_ft1, f32 arg_fv0 */) {
    /* angle = arg_ft1 * arg_fv0  (mul.s $fs0, $ft1, $fv0) */
    f32 sin_val = sinf(0.0f /* angle */);
    f32 cos_val = cosf(0.0f /* angle */);

    arg0->unk0  = cos_val;
    arg0->unk4  = -sin_val;
    arg0->unk8  = 0.0f;
    arg0->unkC  = 0.0f;
    arg0->unk10 = sin_val;
    arg0->unk14 = cos_val;
    arg0->unk18 = 0.0f;
    arg0->unk1C = 0.0f;
    arg0->unk20 = 0.0f;
    arg0->unk24 = 0.0f;
    arg0->unk28 = gMtxIdent33;
    arg0->unk2C = 0.0f;
    arg0->unk30 = 0.0f;
    arg0->unk34 = 0.0f;
    arg0->unk38 = 0.0f;
    arg0->unk3C = gMtxIdent33;
}
