#include "ultra64.h"
void guMtxF2L(char*, char*);                          /* extern */
void guScaleF(void *, f32, f32, s32);                  /* extern */
extern f32 gPitchMaxF;
extern Unk gTrigCoeffs;
extern f64 gPitchCoeffC;
extern f64 gPitchCoeffA;
extern f64 gPitchCoeffB;
extern f32 gPitchReturnF;
extern s32 gPitchTblPos;
extern s32 gPitchTblNeg;

/*
 * guScale — nonmatching.
 * arg2_ft4 is a float passed in non-standard register $f16 (SN64 quirk).
 */
void guScale(f32 arg1, s32 arg0, f32 arg2_ft4) {
    s32 sp18[16];

    guScaleF(&sp18, arg0, arg1, (s32) arg2_ft4);
    guMtxF2L(&sp18, arg0);
}

f32 sinf(f32 arg0) {
    f64 temp_fa0;
    f64 temp_fa0_2;
    f64 temp_fa1;
    f64 temp_fv0;
    f64 temp_fv0_2;
    f64 temp_fv1;
    f64 temp_fv1_2;
    f64 temp_fv1_3;
    s32 temp_t6;
    s32 var_v0;

    temp_t6 = ((s32) arg0 >> 0x16) & 0x1FF;
    if (temp_t6 < 0xFF) {
        temp_fv1_2 = (f64) arg0;
        if (temp_t6 >= 0xE6) {
            temp_fa0_2 = temp_fv1_2 * temp_fv1_2;
            return (f32) ((temp_fv1_2 * temp_fa0_2 * (gTrigCoeffs.unk8 + (((((gTrigCoeffs.unk20 * temp_fa0_2) + gTrigCoeffs.unk18) * temp_fa0_2) + gTrigCoeffs.unk10) * temp_fa0_2))) + temp_fv1_2);
        }
        return arg0;
    }
    if (temp_t6 < 0x136) {
        temp_fv1_3 = (f64) arg0;
        temp_fv0 = temp_fv1_3 * gPitchCoeffC;
        if (temp_fv0 >= 0.0) {
            var_v0 = (s32) (temp_fv0 + 0.5);
        } else {
            var_v0 = (s32) (temp_fv0 - 0.5);
        }
        temp_fv0_2 = (f64) var_v0;
        temp_fv1 = (temp_fv1_3 - (temp_fv0_2 * gPitchCoeffA)) - (temp_fv0_2 * gPitchCoeffB);
        temp_fa0 = temp_fv1 * temp_fv1;
        temp_fa1 = gTrigCoeffs.unk8 + (((((gTrigCoeffs.unk20 * temp_fa0) + gTrigCoeffs.unk18) * temp_fa0) + gTrigCoeffs.unk10) * temp_fa0);
        if (!(var_v0 & 1)) {
            return (f32) ((temp_fv1 * temp_fa0 * temp_fa1) + temp_fv1);
        }
        return -(f32) ((temp_fv1 * temp_fa0 * temp_fa1) + temp_fv1);
    }
    if (arg0 != arg0) {
        return gPitchMaxF;
    }
    return gPitchReturnF;
}

s16 sinInt(s32 arg0) {
    s16 var_v1;
    s32 temp_t8;

    temp_t8 = ((u32) (arg0 & 0xFFFF) >> 4) & 0xFFFF;
    if (temp_t8 & 0x400) {
        var_v1 = *(&gPitchTblNeg + -((temp_t8 & 0x3FF) * 2));
    } else {
        var_v1 = *(&gPitchTblPos + ((temp_t8 & 0x3FF) * 2));
    }
    if (temp_t8 & 0x800) {
        return (s16) (var_v1 * -1);
    }
    return var_v1;
}
