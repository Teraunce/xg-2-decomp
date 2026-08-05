#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x1];
    /* 0x01 */ s32 unk1;
} UnkStruct_temp_s1;

s32 func_8008EE98(s32, u8 *, s32);                    /* extern */
extern u8 D_8004D128;

/* Warning: Gap in callee-saved word stack region.
 * Saved: [0x14, 0x1c, 0x24, 0x28], gap at: 0x20. */
void func_80090028(void) {
    Unk *saved_reg_s0 = NULL; /* implicit $s0 set by caller — not saved/restored here */
    s32 saved_reg_s1;
    s32 saved_reg_s2;
    s32 saved_reg_s3;
    s32 saved_reg_s4;
    s16 var_s2;
    s16 var_s2_2;
    s16 var_s3;
    s16 var_s3_2;
    s16 var_s3_3;
    s16 var_v1;
    s32 temp_t7;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 var_v0;
    s32 var_v0_2;
    Unk *var_s1_2;
    s8 temp_t8_3;
    s8 temp_t8_4;
    s8 temp_v1;
    s8 var_s4;
    u8 *var_s1;
    UnkStruct_temp_s1 *temp_s1;
    char *temp_s1_2;

    var_s1 = saved_reg_s1;
    var_s2 = saved_reg_s2;
    var_s3 = saved_reg_s3;
    var_s4 = saved_reg_s4 & 0xFF;
    if (var_s3 <= 0) {
        var_s1 = &D_8004D128;
        var_s3 = 1;
    }
    temp_v1 = var_s4;
    if ((var_s4 == 0x66) || (((temp_v1 == 0x67) || (temp_v1 == 0x47)) && (var_s2 >= -4) && (var_s2 < saved_reg_s0->unk24))) {
        var_s2_2 = var_s2 + 1;
        if (temp_v1 != 0x66) {
            var_v0 = saved_reg_s0->unk24;
            if (!(saved_reg_s0->unk30 & 8) && (var_s3 < var_v0)) {
                saved_reg_s0->unk24 = (s32) var_s3;
                var_v0 = (s32) var_s3;
            }
            temp_t8 = var_v0 - var_s2_2;
            saved_reg_s0->unk24 = temp_t8;
            if (temp_t8 < 0) {
                saved_reg_s0->unk24 = 0;
            }
        }
        if (var_s2_2 <= 0) {
            var_v1 = -var_s2_2;
            *(u8*)(s32)(saved_reg_s0->unk8 + saved_reg_s0->unk14) = 0x30;
            saved_reg_s0->unk14 = (s32) (saved_reg_s0->unk14 + 1);
            if ((saved_reg_s0->unk24 > 0) || (saved_reg_s0->unk30 & 8)) {
                *(u8*)(s32)(saved_reg_s0->unk8 + saved_reg_s0->unk14) = 0x2E;
                saved_reg_s0->unk14 = (s32) (saved_reg_s0->unk14 + 1);
            }
            if (saved_reg_s0->unk24 < var_v1) {
                var_s2_2 = saved_reg_s0->unk24 * -1;
                var_v1 = -var_s2_2;
            }
            temp_t8_2 = saved_reg_s0->unk24 + var_s2_2;
            saved_reg_s0->unk18 = (s32) var_v1;
            saved_reg_s0->unk24 = temp_t8_2;
            if (temp_t8_2 < var_s3) {
                var_s3 = (s16) temp_t8_2;
            }
            saved_reg_s0->unk1C = (s32) var_s3;
            func_8008EE98(saved_reg_s0->unk8 + saved_reg_s0->unk14, var_s1, (s32) var_s3);
            saved_reg_s0->unk20 = (s32) (saved_reg_s0->unk24 - var_s3);
        } else if (var_s3 < var_s2_2) {
            func_8008EE98(saved_reg_s0->unk8 + saved_reg_s0->unk14, var_s1, (s32) var_s3);
            saved_reg_s0->unk14 = (s32) (saved_reg_s0->unk14 + var_s3);
            saved_reg_s0->unk18 = (s32) (var_s2_2 - var_s3);
            if ((saved_reg_s0->unk24 > 0) || (saved_reg_s0->unk30 & 8)) {
                *(u8*)(s32)(saved_reg_s0->unk8 + saved_reg_s0->unk14) = 0x2E;
                saved_reg_s0->unk1C = (s32) (saved_reg_s0->unk1C + 1);
            }
            saved_reg_s0->unk20 = saved_reg_s0->unk24;
        } else {
            func_8008EE98(saved_reg_s0->unk8 + saved_reg_s0->unk14, var_s1, (s32) var_s2_2);
            saved_reg_s0->unk14 = (s32) (saved_reg_s0->unk14 + var_s2_2);
            var_s3_2 = var_s3 - var_s2_2;
            if ((saved_reg_s0->unk24 > 0) || (saved_reg_s0->unk30 & 8)) {
                *(u8*)(s32)(saved_reg_s0->unk8 + saved_reg_s0->unk14) = 0x2E;
                saved_reg_s0->unk14 = (s32) (saved_reg_s0->unk14 + 1);
            }
            if ((s16) saved_reg_s0->unk24 < var_s3_2) {
                var_s3_2 = (s16) saved_reg_s0->unk24;
            }
            func_8008EE98(saved_reg_s0->unk8 + saved_reg_s0->unk14, &var_s1[var_s2_2], (s32) var_s3_2);
            saved_reg_s0->unk14 = (s32) (saved_reg_s0->unk14 + var_s3_2);
            saved_reg_s0->unk18 = (s32) (saved_reg_s0->unk24 - var_s3_2);
        }
    } else {
        if ((temp_v1 == 0x67) || (temp_v1 == 0x47)) {
            var_v0_2 = saved_reg_s0->unk24;
            var_s4 = 0x45;
            if (var_s3 < var_v0_2) {
                saved_reg_s0->unk24 = (s32) var_s3;
                var_v0_2 = (s32) var_s3;
            }
            temp_t7 = var_v0_2 - 1;
            saved_reg_s0->unk24 = temp_t7;
            if (temp_t7 < 0) {
                saved_reg_s0->unk24 = 0;
            }
            if (temp_v1 == 0x67) {
                var_s4 = 0x65;
            }
        }
        *(u8*)(s32)(saved_reg_s0->unk8 + saved_reg_s0->unk14) = *var_s1;
        saved_reg_s0->unk14 = (s32) (saved_reg_s0->unk14 + 1);
        if ((saved_reg_s0->unk24 > 0) || (saved_reg_s0->unk30 & 8)) {
            *(u8*)(s32)(saved_reg_s0->unk8 + saved_reg_s0->unk14) = 0x2E;
            saved_reg_s0->unk14 = (s32) (saved_reg_s0->unk14 + 1);
        }
        if ((s16) saved_reg_s0->unk24 > 0) {
            var_s3_3 = var_s3 - 1;
            if ((s16) saved_reg_s0->unk24 < var_s3_3) {
                var_s3_3 = (s16) saved_reg_s0->unk24;
            }
            func_8008EE98(saved_reg_s0->unk8 + saved_reg_s0->unk14, var_s1 + 1, (s32) var_s3_3);
            saved_reg_s0->unk14 = (s32) (saved_reg_s0->unk14 + var_s3_3);
            saved_reg_s0->unk18 = (s32) (saved_reg_s0->unk24 - var_s3_3);
        }
        temp_s1 = saved_reg_s0->unk8 + saved_reg_s0->unk14;
        temp_s1_2 = temp_s1 + 1;
        (*(f32 *)((char *)(temp_s1_2) - 0x1)) = var_s4;
        if (var_s2 >= 0) {
            temp_s1->unk1 = 0x2B;
            var_s1_2 = temp_s1_2 + 1;
        } else {
            temp_s1->unk1 = 0x2D;
            var_s1_2 = temp_s1_2 + 1;
            var_s2 *= -1;
        }
        if (var_s2 >= 0x64) {
            if (var_s2 >= 0x3E8) {
                temp_t8_3 = (var_s2 / 1000) + 0x30;
                var_s2 = (s16) (var_s2 % 1000);
                var_s1_2->unk0 = temp_t8_3;
                var_s1_2 += 1;
            }
            temp_t8_4 = (var_s2 / 100) + 0x30;
            var_s2 = (s16) (var_s2 % 100);
            var_s1_2->unk0 = temp_t8_4;
            var_s1_2 += 1;
        }
        var_s1_2->unk0 = (var_s2 / 10) + 0x30;
        var_s1_2->unk1 = (s8) ((s16) (var_s2 % 10) + 0x30);
        saved_reg_s0->unk1C = (s32) (((var_s1_2 + 2) - saved_reg_s0->unk8) - saved_reg_s0->unk14);
    }
    if ((saved_reg_s0->unk30 & 0x14) == 0x10) {
        temp_v1_2 = saved_reg_s0->unk28;
        temp_v0 = saved_reg_s0->unkC + saved_reg_s0->unk14 + saved_reg_s0->unk18 + saved_reg_s0->unk1C + saved_reg_s0->unk20;
        if (temp_v0 < temp_v1_2) {
            saved_reg_s0->unk10 = (s32) (temp_v1_2 - temp_v0);
        }
    }
}
