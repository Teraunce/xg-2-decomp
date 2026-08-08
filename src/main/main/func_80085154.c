#include "ultra64.h"
s32 osVirtualToPhysical(u32);                       /* extern */
extern f64 D_8004CF60;
extern f32 D_8004CF68;

s32 audioVoiceNodeCmd(Unk *arg0, s16 *arg1, s32 arg2, s32 arg4) {
    char *sp48;
    s16 sp46;
    char *sp28;
    f32 temp_fv0;
    Unk *temp_t1;
    s32 temp_ft2;
    char *temp_a1;
    Unk *temp_t8;
    Unk *temp_v0;
    Unk *temp_v0_2;
    char *var_a1;

    temp_t1 = arg0->unk0;
    sp46 = 0x140;
    if (arg2 == 0) {
        return arg4;
    }
    if (arg0->unk1C != 0) {
        temp_v0 = ((s32(*)())(s32)temp_t1->unk4)(temp_t1, &sp46, arg2, arg4);
        temp_v0->unk0 = (s32) ((sp46 & 0xFFFFFF) | 0x0A000000);
        var_a1 = temp_v0 + 8;
        temp_v0->unk4 = (s32) ((*arg1 << 0x10) | ((arg2 * 2) & 0xFFFF));
    } else {
        if (D_8004CF60 < (f64) arg0->unk18) {
            arg0->unk18 = (f32) D_8004CF68;
        }
        arg0->unk18 = (f32) (s32) (arg0->unk18 * 32768.0f);
        arg0->unk18 = (f32) (arg0->unk18 / 32768.0f);
        temp_fv0 = arg0->unk20 + (arg0->unk18 * (f32) arg2);
        temp_ft2 = (s32) temp_fv0;
        arg0->unk20 = (f32) (temp_fv0 - (f32) temp_ft2);
        temp_v0_2 = ((s32(*)())(s32)temp_t1->unk4)((s16 *)0x47000000, temp_t1, (s32) &sp46, temp_ft2, arg4);
        temp_v0_2->unk0 = (s32) ((sp46 & 0xFFFF) | 0x08000000);
        temp_t8 = temp_v0_2 + 8;
        temp_v0_2->unk4 = (s32) ((*arg1 << 0x10) | ((arg2 * 2) & 0xFFFF));
        sp28 = temp_t8;
        temp_v0_2->unk8 = (s32) (((arg0->unk24 & 0xFF) << 0x10) | 0x05000000 | ((s32) (arg0->unk18 * 32768.0f) & 0xFFFF));
        temp_a1 = temp_v0_2 + 0x10;
        sp48 = temp_a1;
        var_a1 = temp_a1;
        temp_t8->unk4 = osVirtualToPhysical(arg0->unk14);
        arg0->unk24 = 0;
    }
    return (s32) var_a1;
}

f32 audioTriOsc(Unk *arg0, s32 arg1) {
    f32 var_fv1;
    f64 temp_fv0;

    arg0->unk14 = (f32) (arg0->unk14 + (arg0->unk10 * (f32) arg1));
    temp_fv0 = (f64) arg0->unk14;
    if (temp_fv0 > 2.0) {
        arg0->unk14 = (f32) (temp_fv0 - 4.0);
    } else {
        arg0->unk14 = (f32) temp_fv0;
    }
    var_fv1 = arg0->unk14;
    if (var_fv1 < 0.0f) {
        var_fv1 = -var_fv1;
    }
    return arg0->unk1C * (f32) ((f64) var_fv1 - 1.0);
}
