#include "ultra64.h"
/* Warning: Gap in callee-saved word stack region.
 * Saved: [0x14, 0x28, 0x2c], gap at: 0x18. */
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
} UnkStruct_temp_s0;
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
} UnkStruct_temp_s0_2;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} UnkStruct_var_s0;

char *audioRspBuildDL(void) {
    Unk *saved_reg_s0 = NULL; /* implicit $s0 set by caller */
    s32 saved_reg_s1 = 0; /* implicit $s1 set by caller */
    Unk *saved_reg_s2 = NULL; /* implicit $s2 set by caller */
    s32 saved_reg_s3 = 0; /* implicit $s3 set by caller */
    s32 saved_reg_s4 = 0; /* implicit $s4 set by caller */
    s32 saved_reg_s5 = 0; /* implicit $s5 set by caller */
    s32 saved_reg_s6 = 0; /* implicit $s6 set by caller */
    s32 temp_s1;
    s32 temp_v0;
    s32 var_a2;
    UnkStruct_temp_s0 *temp_s0;
    UnkStruct_temp_s0_2 *temp_s0_2;
    UnkStruct_var_s0 *var_s0;

    var_s0 = saved_reg_s0;
    if (saved_reg_s1 > 0) {
        temp_v0 = ((s32(*)())(s32)saved_reg_s2->unk30)(saved_reg_s2->unk44, saved_reg_s1, saved_reg_s2->unk34);
        var_a2 = temp_v0 & 7;
        temp_s1 = saved_reg_s1 + var_a2;
        saved_reg_s0->unk0 = (s32) (((s16) saved_reg_s3 & 0xFFFF) | 0x08000000);
        temp_s0_2 = saved_reg_s0 + 8;
        saved_reg_s0->unk4 = (s32) (((temp_s1 - (temp_s1 & 7)) + 8) & 0xFFFF);
        saved_reg_s0->unk8 = 0x04000000;
        temp_s0_2->unk4 = (s32) (temp_v0 - var_a2);
        var_s0 = temp_s0_2 + 8;
    } else {
        var_a2 = 0;
    }
    if (saved_reg_s4 & 2) {
        var_s0->unk0 = 0x0F000000;
        var_s0->unk4 = (s32) (saved_reg_s2->unk18 & 0x1FFFFFFF);
        var_s0 += 8;
    }
    var_s0->unk0 = (s32) ((((s16) saved_reg_s3 + var_a2) & 0xFFFF) | 0x08000000);
    temp_s0 = var_s0 + 8;
    var_s0->unk4 = (s32) (((s16) saved_reg_s5 << 0x10) | ((saved_reg_s6 * 2) & 0xFFFF));
    var_s0->unk8 = (s32) (((saved_reg_s4 & 0xFF) << 0x10) | 0x01000000);
    temp_s0->unk4 = (s32) (saved_reg_s2->unk14 & 0x1FFFFFFF);
    saved_reg_s2->unk40 = 0;
    return temp_s0 + 8;
}
