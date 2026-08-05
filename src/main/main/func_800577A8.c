#include "ultra64.h"
extern f32 D_8004BDA0;
extern f32 D_8004BDA4;
extern f32 D_8004BDA8;

void func_800577A8(Unk *arg0, Unk *arg1, Unk *arg2) {
    s32 spC;
    s32 sp0;
    s32 sp4;
    s32 sp8;
    Unk sp_buf[8];
    Unk *sp = sp_buf; /* $sp base — local stack byte-pointer */
    f32 *var_v1;
    f32 temp_ft0;
    s32 var_a3;
    s32 var_v0;
    Unk *var_a0;

    var_a0 = arg0;
    var_a3 = 0;
    var_v1 = sp;
    do {
        var_a3 += 1;
        temp_ft0 = (arg1->unk0 * var_a0->unk0) + (arg1->unk4 * var_a0->unk10) + (arg1->unk8 * var_a0->unk20) + var_a0->unk30;
        var_a0 += 4;
        *var_v1 = temp_ft0;
        var_v1 += 4;
    } while (var_a3 < 4);
    var_v0 = (s32) spC;
    if (var_v0 < 0) {
        var_v0 = -var_v0;
    }
    if ((f32) var_v0 < D_8004BDA0) {
        arg2->unk4 = 0.0f;
        arg2->unk0 = 0.0f;
        arg2->unk8 = (f32) D_8004BDA4;
        return;
    }
    arg2->unk0 = (f32) (sp0 / spC);
    arg2->unk4 = (f32) (sp4 / spC);
    arg2->unk8 = (f32) (sp8 / spC);
}

void guMtxScaleF2L(Unk *arg0, Unk *arg1) {
    s32 temp_ft3;
    s32 temp_ft3_10;
    s32 temp_ft3_11;
    s32 temp_ft3_12;
    s32 temp_ft3_13;
    s32 temp_ft3_14;
    s32 temp_ft3_15;
    s32 temp_ft3_16;
    s32 temp_ft3_2;
    s32 temp_ft3_3;
    s32 temp_ft3_4;
    s32 temp_ft3_5;
    s32 temp_ft3_6;
    s32 temp_ft3_7;
    s32 temp_ft3_8;
    s32 temp_ft3_9;

    temp_ft3 = (s32) (arg0->unk0 * D_8004BDA8);
    temp_ft3_2 = (s32) (arg0->unk4 * D_8004BDA8);
    temp_ft3_3 = (s32) (arg0->unk8 * D_8004BDA8);
    temp_ft3_4 = (s32) (arg0->unkC * D_8004BDA8);
    arg1->unk0 = (s32) ((temp_ft3 & 0xFFFF0000) | ((u32) temp_ft3_2 >> 0x10));
    arg1->unk4 = (s32) ((temp_ft3_3 & 0xFFFF0000) | ((u32) temp_ft3_4 >> 0x10));
    arg1->unk20 = (s32) ((temp_ft3 << 0x10) | (temp_ft3_2 & 0xFFFF));
    arg1->unk24 = (s32) ((temp_ft3_3 << 0x10) | (temp_ft3_4 & 0xFFFF));
    temp_ft3_5 = (s32) (arg0->unk10 * D_8004BDA8);
    temp_ft3_6 = (s32) (arg0->unk14 * D_8004BDA8);
    temp_ft3_7 = (s32) (arg0->unk18 * D_8004BDA8);
    temp_ft3_8 = (s32) (arg0->unk1C * D_8004BDA8);
    arg1->unk8 = (s32) ((temp_ft3_5 & 0xFFFF0000) | ((u32) temp_ft3_6 >> 0x10));
    arg1->unkC = (s32) ((temp_ft3_7 & 0xFFFF0000) | ((u32) temp_ft3_8 >> 0x10));
    arg1->unk28 = (s32) ((temp_ft3_5 << 0x10) | (temp_ft3_6 & 0xFFFF));
    arg1->unk2C = (s32) ((temp_ft3_7 << 0x10) | (temp_ft3_8 & 0xFFFF));
    temp_ft3_9 = (s32) (arg0->unk20 * D_8004BDA8);
    temp_ft3_10 = (s32) (arg0->unk24 * D_8004BDA8);
    temp_ft3_11 = (s32) (arg0->unk28 * D_8004BDA8);
    temp_ft3_12 = (s32) (arg0->unk2C * D_8004BDA8);
    arg1->unk10 = (s32) ((temp_ft3_9 & 0xFFFF0000) | ((u32) temp_ft3_10 >> 0x10));
    arg1->unk14 = (s32) ((temp_ft3_11 & 0xFFFF0000) | ((u32) temp_ft3_12 >> 0x10));
    arg1->unk30 = (s32) ((temp_ft3_9 << 0x10) | (temp_ft3_10 & 0xFFFF));
    arg1->unk34 = (s32) ((temp_ft3_11 << 0x10) | (temp_ft3_12 & 0xFFFF));
    temp_ft3_13 = (s32) (arg0->unk30 * D_8004BDA8);
    temp_ft3_14 = (s32) (arg0->unk34 * D_8004BDA8);
    temp_ft3_15 = (s32) (arg0->unk38 * D_8004BDA8);
    temp_ft3_16 = (s32) (arg0->unk3C * D_8004BDA8);
    arg1->unk18 = (s32) ((temp_ft3_13 & 0xFFFF0000) | ((u32) temp_ft3_14 >> 0x10));
    arg1->unk38 = (s32) ((temp_ft3_13 << 0x10) | (temp_ft3_14 & 0xFFFF));
    arg1->unk1C = (s32) ((temp_ft3_15 & 0xFFFF0000) | ((u32) temp_ft3_16 >> 0x10));
    arg1->unk3C = (s32) ((temp_ft3_15 << 0x10) | (temp_ft3_16 & 0xFFFF));
}
