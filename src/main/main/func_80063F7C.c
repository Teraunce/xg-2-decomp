#include "ultra64.h"
s32 sfxComputeFreqOffset(Unk*);                          /* extern */
extern s32 D_80092F40;
extern Unk *D_801823E8;
extern Unk *D_801823EC;
extern Unk *D_801823F0;
extern s32 D_80182EA4;

s32 fontGetCharWidth(u16 arg0, s32 *arg1, s32 *arg2) {
    Unk *var_s0;
    s32 var_v0;
    s32 var_v1;
    u32 temp_a1;
    u32 temp_s4;
    u32 temp_v0;
    u32 var_a1;
    u32 var_a1_2;
    u32 var_a2;
    u32 var_s0_2;
    u32 var_s2;
    u32 var_s3;
    Unk *temp_a0;
    Unk *temp_s1;

    temp_a1 = arg0 & 0xFFFF;
    if (temp_a1 != 0x20) {
        if ((D_801823EC != NULL) && (D_801823F0 != NULL) && (temp_a1 >= (u16) D_801823EC->unk0) && ((s32) temp_a1 < (D_801823EC->unk0 + D_801823EC->unk2))) {
            *arg1 = (s32) (D_80182EA4 << 0x10) / (s32) D_801823F0->unk1;
            if (arg2 != NULL) {
                *arg2 = 0;
            }
            var_v1 = D_801823F0->unk4;
            var_v0 = temp_a1 - D_801823EC->unk0;
            goto block_19;
        }
        var_a1 = 0;
        if (D_801823E8->unk0 != 0) {
            temp_s4 = arg0 & 0xFFFF;
            var_a2 = 0;
loop_10:
            temp_s1 = D_801823E8->unk4 + var_a2;
            if (temp_s4 >= (u16) temp_s1->unk0) {
                var_s3 = 0;
                if ((s32) temp_s4 < (temp_s1->unk0 + temp_s1->unk2)) {
                    var_s0_2 = 1;
                    var_s2 = sfxComputeFreqOffset(temp_s1->unk8);
                    if ((u16) temp_s1->unk4 > 1U) {
                        do {
                            temp_v0 = sfxComputeFreqOffset(temp_s1->unk8 + (var_s0_2 * 8));
                            if (temp_v0 < var_s2) {
                                var_s2 = temp_v0;
                                var_s3 = var_s0_2;
                            }
                            var_s0_2 += 1;
                        } while (var_s0_2 < (u16) temp_s1->unk4);
                    }
                    D_801823EC = temp_s1;
                    temp_a0 = temp_s1->unk8 + (var_s3 * 8);
                    D_801823F0 = temp_a0;
                    *arg1 = (s32) (D_80182EA4 << 0x10) / (s32) temp_a0->unk1;
                    if (arg2 != NULL) {
                        *arg2 = 0;
                    }
                    var_v1 = temp_a0->unk4;
                    var_v0 = temp_s4 - temp_s1->unk0;
block_19:
                    return var_v1 + (var_v0 * 8);
                }
                goto block_21;
            }
block_21:
            var_a1 += 1;
            var_a2 += 0xC;
            if (var_a1 >= (u16) D_801823E8->unk0) {
                goto block_22;
            }
            goto loop_10;
        }
block_22:
        var_a1_2 = 0;
        var_s0 = &D_80092F40;
loop_23:
        var_a1_2 += 1;
        if ((arg0 & 0xFFFF) == var_s0->unk0) {
            if (arg2 != NULL) {
                *arg2 = fontGetCharWidth(var_s0->unk4, arg1, NULL);
            }
            return fontGetCharWidth(var_s0->unk2, arg1, NULL);
        }
        var_s0 += 6;
        if (var_a1_2 >= 0x3BU) {
            goto block_28;
        }
        goto loop_23;
    }
block_28:
    *arg1 = 0;
    return 0;
}
