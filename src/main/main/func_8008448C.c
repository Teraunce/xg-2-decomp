#include "ultra64.h"
f64 frexp(f64, s32 *);                      /* extern */
extern f64 gAudioFreqScaleD;
extern f64 gAudioConvScaleD;
extern Unk gAudioNodeCfg;

s16 audioCalcRatio(f64 arg1, s32 arg0) {
    s16 *saved_reg_s1 = NULL; /* implicit $s1 set by caller — not saved/restored here */
    s32 spB0;
    s32 sp68[32];
    f64 temp_fa0;
    f64 temp_fs0;
    f64 temp_fv0;
    f64 temp_fv1;
    f64 var_fa1;
    f64 var_fv0;
    f64 var_fv1;
    s32 temp_ft3;
    s32 temp_t9;
    s32 var_s0;

    var_fa1 = arg1;
    if (arg0 == 0) {
        if ((s32)0.0 /* implicit $fs0/$f16 float from caller */ <= var_fa1) {
            *saved_reg_s1 = 0xFFFF;
            return 0x7FFF;
        }
        *saved_reg_s1 = 0;
        return 0;
    }
    if (var_fa1 < 1.0) {
        var_fa1 = 1.0;
    }
    if ((s32)0.0 /* implicit $fs0/$f16 float from caller */ <= 0.0) {

    }
    M2C_MEMCPY_ALIGNED(&sp68, &gAudioNodeCfg, 0x3C);
    temp_fs0 = (f64) 0x40000000;
    ((Unk*)&sp68)->unk3C = (s32) gAudioNodeCfg.unk3C;
    var_s0 = (s32) ((1.0 / (f64) arg0) * temp_fs0);
    var_fv1 = 1.0;
    var_fv0 = 1.0 + (((*(f32*)((char*)(((s32)sp68 + ((s32) (frexp(var_fa1 / (s32)0.0 /* implicit $fs0/$f16 float from caller */, &spB0) * (f64) 0x10) * 8)))) - 40)+ (f64) spB0) * gAudioFreqScaleD) / (1.0 * temp_fs0);

    if (var_s0 != 0) {
        do {
            temp_t9 = var_s0 >> 1;
            if (var_s0 & 1) {
                var_fv1 *= var_fv0;
            }
            var_fv0 *= var_fv0;
            var_s0 = temp_t9;
        } while (temp_t9 != 0);
    }
    temp_fv0 = var_fv1 * var_fv1;
    temp_fa0 = temp_fv0 * temp_fv0;
    temp_fv1 = temp_fa0 * temp_fa0;
    temp_ft3 = (s32) temp_fv1;
    *saved_reg_s1 = (s16) (s32) ((temp_fv1 - (f64) (f32) (s16) temp_ft3) * gAudioConvScaleD);
    return (s16) temp_ft3;
}
