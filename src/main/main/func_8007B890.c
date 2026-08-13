#include "ultra64.h"
#include "mtx.h"
f32 cosf(f32);                             /* cosf */
f32 sinf(f32);                             /* sinf */
extern f32 gMtxScaleOut;

/*
 * mtxEulerScaleF — build scaled Euler-angle (YXZ) rotation matrix (nonmatching).
 *
 * Called via GETTER preamble which loads a scale factor into $fv0/$f0.
 * At entry, arg2 ($fa1) and arg3 ($ft4/$f16, non-standard) are pre-multiplied
 * by scale_fv0, and scale_fv0 is stored to gMtxScaleOut.
 * scale_fv0 is not expressible as a standard C parameter.
 *
 * The matrix elements are all multiplied by arg4 (a uniform scale factor).
 * arg5/arg6/arg7 are stored to the translation column (unk30/unk34/unk38).
 */
void mtxEulerScaleF(Matrix4x4 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7 /*, f32 scale_fv0 */) {
    f32 sp40;
    f32 sp3C;
    f32 sp34;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fv0;

    /* arg2 *= scale_fv0; arg3 *= scale_fv0; gMtxScaleOut = scale_fv0; (at entry) */
    temp_fs0 = sinf(arg1);
    temp_fs1 = cosf(arg1);
    sp40 = sinf(arg2);
    sp34 = cosf(arg2);
    sp3C = sinf(arg3);
    temp_fv0 = cosf(arg3);
    arg0->unk0 = (f32) (sp34 * temp_fv0 * arg4);
    arg0->unk4 = (f32) (sp34 * sp3C * arg4);
    arg0->unkC = 0.0f;
    arg0->unk8 = (f32) (-sp40 * arg4);
    arg0->unk1C = 0.0f;
    temp_fa0 = temp_fs0 * sp40;
    arg0->unk10 = (f32) (((temp_fa0 * temp_fv0) - (temp_fs1 * sp3C)) * arg4);
    arg0->unk14 = (f32) (((temp_fa0 * sp3C) + (temp_fs1 * temp_fv0)) * arg4);
    arg0->unk18 = (f32) (temp_fs0 * sp34 * arg4);
    arg0->unk2C = 0.0f;
    temp_fa0_2 = temp_fs1 * sp40;
    arg0->unk20 = (f32) (((temp_fa0_2 * temp_fv0) + (temp_fs0 * sp3C)) * arg4);
    arg0->unk24 = (f32) (((temp_fa0_2 * sp3C) - (temp_fs0 * temp_fv0)) * arg4);
    arg0->unk28 = (f32) (temp_fs1 * sp34 * arg4);
    arg0->unk30 = arg5;
    arg0->unk34 = arg6;
    arg0->unk3C = 1.0f;
    arg0->unk38 = arg7;
}
