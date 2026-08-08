#include "ultra64.h"
void midiDecodeEvent(Unk*, Unk*);                     /* extern */
extern f64 gAudioPeriodMul;
extern f64 gAudioPeriodScale;

void midiSeqStep(Unk *arg0, Unk *arg1, u32 arg2) {
    s16 sp50;
    s32 sp4C;
    u32 sp44;
    s16 sp3E;
    s16 var_s5;
    s32 var_s4;
    u32 var_s6;
    u32 var_v0;

    if (arg2 == 0) {
        arg1->unkC = 0;
        arg1->unk4 = 0U;
        arg1->unk8 = 0U;
        arg1->unk0 = (s32) arg0->unk4;
        return;
    }
    var_v0 = 0;
    sp4C = arg0->unk8;
    sp3E = arg0->unk1A;
    sp44 = arg0->unkC;
    arg0->unk1A = 0;
    arg0->unkC = 0U;
    arg0->unk8 = (s32) arg0->unk4;
loop_3:
    var_s4 = arg0->unk8;
    var_s5 = arg0->unk1A;
    var_s6 = var_v0;
    midiDecodeEvent(arg0, &sp50);
    if (sp50 == 4) {
        var_s4 = arg0->unk8;
        var_s5 = arg0->unk1A;
        var_s6 = arg0->unkC;
    } else {
        var_v0 = arg0->unkC;
        if (var_v0 < arg2) {
            goto loop_3;
        }
    }
    arg1->unk0 = var_s4;
    arg1->unkC = var_s5;
    arg1->unk4 = var_s6;
    arg1->unk8 = (u32) arg0->unkC;
    arg0->unk8 = sp4C;
    arg0->unk1A = sp3E;
    arg0->unkC = sp44;
}

s32 func_80081A20(Unk *arg0, f32 arg1, s32 arg2) {
    f64 temp_ft2;
    f64 var_ft1;
    s32 temp_ft4;

    var_ft1 = (f64) arg2;
    if (arg2 < 0) {
        var_ft1 += 4294967296.0;
    }
    temp_ft2 = ((f64) arg1 * gAudioPeriodMul * (f64) arg0->unk18) / var_ft1;
    temp_ft4 = (s32) temp_ft2;
    if (0 /* cfc1 $v0, $31: FCR31 FPU status */ & 0x78) {
        if (!(0 /* cfc1 $v0, $31: FCR31 FPU status */ & 0x78)) {
            return (s32) (temp_ft2 - 2147483648.0) | 0x80000000;
        }
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return -1;
    }
    if (temp_ft4 >= 0) {
        return temp_ft4;
    }
    return -1;
}

f32 func_80081B04(Unk *arg0, s32 arg1, s32 arg2) {
    f32 var_ft3;

    var_ft3 = (f32) arg2;
    if (arg2 < 0) {
        var_ft3 += 4294967296.0f;
    }
    return (f32) ((f64) ((f32) arg1 * var_ft3) / ((f64) (f32) arg0->unk18 * gAudioPeriodScale));
}
