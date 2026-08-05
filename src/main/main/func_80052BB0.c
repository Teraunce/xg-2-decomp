#include "ultra64.h"
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} UnkStruct_D_80173CC0;
typedef struct {
    /* 0x00 */ u8 pad00[0x30C];
    /* 0x30C */ s32 unk30C;
    /* 0x310 */ u8 pad310[0x140];
    /* 0x450 */ s32 unk450;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
} UnkStruct_temp_a0;
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
} UnkStruct_temp_a3;
typedef struct {
    /* 0x00 */ u8 pad00[0x588];
    /* 0x588 */ s32 unk588;
} UnkStruct_var_a0;

s32 heap_alloc_default(s32);                               /* extern */
extern f32 D_8004BC70;
extern f32 D_8004BC74;
extern f32 D_8004BC78;
extern s32 gTrackNodeCount;
extern s32 gSetupDisplayList;
extern s32 D_80170390;
extern s32 D_80170880;
extern s32 D_80173C18;
extern UnkStruct_D_80173CC0 *D_80173CC0;
extern u16 *D_80174720;
extern s32 D_8017CA44;
extern s32 D_80184580;

void func_80052BB0(void) {
    D_80170390 = heap_alloc_default(0x3EA90);
}

void func_80052BE0(void) {
    if (*D_80174720 != 0x40) {
        M2C_BREAK(0);
    }
}

s32 func_80052C04(UnkStruct_arg0 *arg0) {
    UnkStruct_var_a0 *var_a0;
    s32 var_v1;

    if ((arg0->unk30C > 0.0f) || (arg0->unk450 != 0) || (D_80184580 == 0xE)) {
        /* Duplicate return node #3. Try simplifying control flow for better match */
        return 0;
    }
    if (D_80184580 == 0xB) {
        var_v1 = 0;
        if (gTrackNodeCount > 0) {
            var_a0 = &D_80170880;
loop_7:
            var_v1 += 1;
            if ((u32) (var_a0->unk588 - 4) >= 2U) {
                var_a0 += 0x668;
                if (var_v1 >= gTrackNodeCount) {
                    /* Duplicate return node #9. Try simplifying control flow for better match */
                    return 1;
                }
                goto loop_7;
            }
            return 0;
        }
    }
    return 1;
}

void func_80052C88(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    UnkStruct_temp_a3 *temp_a3;

    temp_a0 = ((arg0 << 8) & 0xF800) | ((arg1 * 8) & 0x7C0) | ((arg2 >> 2) & 0x3E) | 1;
    temp_a3 = D_80173CC0 + 8;
    D_80173CC0->unk0 = 0xE7000000;
    D_80173CC0->unk4 = 0;
    D_80173CC0 = temp_a3;
    D_80173CC0 = temp_a3 + 8;
    D_80173CC0->unk8 = 0xF7000000;
    temp_a3->unk4 = (s32) ((temp_a0 << 0x10) | temp_a0);
    D_80173CC0 = temp_a3 + 0x10;
    temp_a3->unkC = 0x300000;
    D_80173CC0 = temp_a3 + 0x18;
    temp_a3->unk10 = 0xE200001C;
    D_80173CC0 = temp_a3 + 0x20;
    temp_a3->unk8 = 0xE3000A01;
    temp_a3->unk14 = 0;
    temp_a3->unk1C = 0;
    temp_a3->unk20 = 0xE7000000;
    temp_a3->unk24 = 0;
    temp_a3->unk28 = 0xE3000A01;
    temp_a3->unk2C = 0;
    D_80173CC0 = temp_a3 + 0x28;
    temp_a3->unk18 = (s32) ((((D_8017CA44 - 1) & 0x3FF) << 0xE) | ((((D_80173C18 - 1) & 0x3FF) * 4) | 0xF6000000));
    D_80173CC0 = temp_a3 + 0x30;
}

void func_80052D84(f32 arg0) {
    f32 temp_fv0;
    f32 var_ft0;
    f32 var_fv0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_ft1;
    s32 var_v0;
    UnkStruct_temp_a0 *temp_a0;

    var_ft0 = arg0 * (f32) D_80173C18 * D_8004BC70;
    temp_fv0 = (f32) ((s32) D_80173C18 / 2);
    if (!(var_ft0 <= temp_fv0)) {
        var_ft0 = temp_fv0;
    }
    var_fv0 = D_8004BC74 - (arg0 * D_8004BC74);
    temp_ft1 = (s32) var_ft0;
    if (!(var_fv0 >= 0.0f)) {
        var_fv0 = 0.0f;
    }
    if (D_8004BC78 <= var_fv0) {
        var_v0 = ((s32) (var_fv0 - D_8004BC78) | 0x80000000) << 8;
    } else {
        var_v0 = (s32) var_fv0 << 8;
    }
    temp_a1 = (var_v0 & 0xF800) | 1;
    temp_a0 = D_80173CC0 + 8;
    D_80173CC0->unk0 = 0xE7000000;
    D_80173CC0->unk4 = 0;
    D_80173CC0 = temp_a0;
    D_80173CC0 = temp_a0 + 8;
    D_80173CC0->unk8 = 0xDE000000;
    temp_a0->unk4 = &gSetupDisplayList;
    D_80173CC0 = temp_a0 + 0x10;
    temp_a0->unkC = 0x300000;
    D_80173CC0 = temp_a0 + 0x18;
    D_80173CC0 = temp_a0 + 0x20;
    temp_a0->unk18 = 0xF7000000;
    temp_a0->unk1C = (s32) ((temp_a1 << 0x10) | temp_a1);
    D_80173CC0 = temp_a0 + 0x28;
    temp_a0->unk8 = 0xE3000A01;
    temp_a0->unk10 = 0xE200001C;
    temp_a0->unk14 = 0;
    temp_a0->unk24 = 0;
    temp_a0->unk30 = 0xE7000000;
    temp_a0->unk34 = 0;
    temp_a0->unk38 = 0xE3000A01;
    temp_a0->unk3C = 0;
    temp_a1_2 = ((D_8017CA44 - 1) & 0x3FF) << 0xE;
    temp_a0->unk20 = (s32) (temp_a1_2 | (((temp_ft1 & 0x3FF) * 4) | 0xF6000000));
    D_80173CC0 = temp_a0 + 0x30;
    D_80173CC0 = temp_a0 + 0x38;
    temp_a0->unk28 = (s32) (temp_a1_2 | ((((D_80173C18 - 1) & 0x3FF) * 4) | 0xF6000000));
    temp_a0->unk2C = (s32) (((D_80173C18 - (temp_ft1 + 1)) & 0x3FF) * 4);
    D_80173CC0 = temp_a0 + 0x40;
}
