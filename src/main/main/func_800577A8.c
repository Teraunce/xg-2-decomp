#include "ultra64.h"
#include "mtx.h"
extern f32 gSfxDistThresh;
extern f32 gSfxVolInitF;
extern f32 gSfxVolDecay;

void mtxProjectVec(Matrix4x4 *arg0, Unk *arg1, Unk *arg2) {
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

    var_a0 = (Unk *)arg0;
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
    if ((f32) var_v0 < gSfxDistThresh) {
        arg2->unk4 = 0.0f;
        arg2->unk0 = 0.0f;
        arg2->unk8 = (f32) gSfxVolInitF;
        return;
    }
    arg2->unk0 = (f32) (sp0 / spC);
    arg2->unk4 = (f32) (sp4 / spC);
    arg2->unk8 = (f32) (sp8 / spC);
}

void guMtxScaleF2L(Matrix4x4 *arg0, Unk *arg1) {
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

    temp_ft3 = (s32) (arg0->unk0 * gSfxVolDecay);
    temp_ft3_2 = (s32) (arg0->unk4 * gSfxVolDecay);
    temp_ft3_3 = (s32) (arg0->unk8 * gSfxVolDecay);
    temp_ft3_4 = (s32) (arg0->unkC * gSfxVolDecay);
    arg1->unk0 = (s32) ((temp_ft3 & 0xFFFF0000) | ((u32) temp_ft3_2 >> 0x10));
    arg1->unk4 = (s32) ((temp_ft3_3 & 0xFFFF0000) | ((u32) temp_ft3_4 >> 0x10));
    arg1->unk20 = (s32) ((temp_ft3 << 0x10) | (temp_ft3_2 & 0xFFFF));
    arg1->unk24 = (s32) ((temp_ft3_3 << 0x10) | (temp_ft3_4 & 0xFFFF));
    temp_ft3_5 = (s32) (arg0->unk10 * gSfxVolDecay);
    temp_ft3_6 = (s32) (arg0->unk14 * gSfxVolDecay);
    temp_ft3_7 = (s32) (arg0->unk18 * gSfxVolDecay);
    temp_ft3_8 = (s32) (arg0->unk1C * gSfxVolDecay);
    arg1->unk8 = (s32) ((temp_ft3_5 & 0xFFFF0000) | ((u32) temp_ft3_6 >> 0x10));
    arg1->unkC = (s32) ((temp_ft3_7 & 0xFFFF0000) | ((u32) temp_ft3_8 >> 0x10));
    arg1->unk28 = (s32) ((temp_ft3_5 << 0x10) | (temp_ft3_6 & 0xFFFF));
    arg1->unk2C = (s32) ((temp_ft3_7 << 0x10) | (temp_ft3_8 & 0xFFFF));
    temp_ft3_9 = (s32) (arg0->unk20 * gSfxVolDecay);
    temp_ft3_10 = (s32) (arg0->unk24 * gSfxVolDecay);
    temp_ft3_11 = (s32) (arg0->unk28 * gSfxVolDecay);
    temp_ft3_12 = (s32) (arg0->unk2C * gSfxVolDecay);
    arg1->unk10 = (s32) ((temp_ft3_9 & 0xFFFF0000) | ((u32) temp_ft3_10 >> 0x10));
    arg1->unk14 = (s32) ((temp_ft3_11 & 0xFFFF0000) | ((u32) temp_ft3_12 >> 0x10));
    arg1->unk30 = (s32) ((temp_ft3_9 << 0x10) | (temp_ft3_10 & 0xFFFF));
    arg1->unk34 = (s32) ((temp_ft3_11 << 0x10) | (temp_ft3_12 & 0xFFFF));
    temp_ft3_13 = (s32) (arg0->unk30 * gSfxVolDecay);
    temp_ft3_14 = (s32) (arg0->unk34 * gSfxVolDecay);
    temp_ft3_15 = (s32) (arg0->unk38 * gSfxVolDecay);
    temp_ft3_16 = (s32) (arg0->unk3C * gSfxVolDecay);
    arg1->unk18 = (s32) ((temp_ft3_13 & 0xFFFF0000) | ((u32) temp_ft3_14 >> 0x10));
    arg1->unk38 = (s32) ((temp_ft3_13 << 0x10) | (temp_ft3_14 & 0xFFFF));
    arg1->unk1C = (s32) ((temp_ft3_15 & 0xFFFF0000) | ((u32) temp_ft3_16 >> 0x10));
    arg1->unk3C = (s32) ((temp_ft3_15 << 0x10) | (temp_ft3_16 & 0xFFFF));
}
