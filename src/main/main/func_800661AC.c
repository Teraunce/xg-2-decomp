#include "ultra64.h"
s32 func_80065B44(s32, s16, s16);                     /* extern */
void func_80065BDC(s32, u8**, s32);                       /* extern */
extern s16 D_80182E68;
extern u16 D_80182E74;
extern s16 D_80182E76;
extern Unk D_80182E8C;
extern s16 D_80182E92;
extern u16 D_80182E94;

void func_800661AC(s32 arg0, s32 arg1) {
    s16 var_s0;
    s16 var_s0_2;
    s16 var_v0;
    s32 *var_v1;
    u16 var_s1;
    Unk *temp_v0;
    Unk *var_a0;

    if ((s32)0 /* implicit $v0 from caller */ & 1) {
loop_2:
        if (D_80182E92 < func_80065B44(arg1, 0, D_80182E68)) {
            var_s0 = (u16) D_80182E68 - 1;
            if (var_s0 >= 0) {
                var_v1 = (var_s0 * 0x10) + arg1;
loop_5:
                if (*var_v1 != 0) {
                    var_s0 -= 1;
                    var_v1 -= 0x10;
                    if (var_s0 >= 0) {
                        goto loop_5;
                    }
                }
                if (var_s0 >= 0) {
                    if (func_80065B44(arg1, 0, var_s0) < ((s16) (u16) D_80182E92 / 2)) {
                        var_s0_2 = (u16) D_80182E68 - 1;
                        if (var_s0_2 > 0) {
loop_10:
                            if (D_80182E92 < func_80065B44(arg1, 0, var_s0_2)) {
                                var_s0_2 -= 1;
                                if (var_s0_2 <= 0) {

                                } else {
                                    goto loop_10;
                                }
                            }
                        }
                        goto block_17;
                    }
                    var_s1 = (u16) D_80182E68;
                    D_80182E68 = var_s0;
                    var_s0_2 = var_s0 + 1;
                } else {
                    goto block_14;
                }
            } else {
block_14:
                var_s0_2 = (u16) D_80182E68 - 1;
                if (var_s0_2 > 0) {
loop_15:
                    if (D_80182E92 < func_80065B44(arg1, 0, var_s0_2)) {
                        var_s0_2 -= 1;
                        if (var_s0_2 > 0) {
                            goto loop_15;
                        }
                    }
                }
block_17:
                var_s1 = (u16) D_80182E68;
                D_80182E68 = var_s0_2;
            }
            func_80065BDC(arg0, arg1, 1);
            D_80182E74 = D_80182E94;
            if ((D_80182E76 + D_80182E8C.unk0) >= 0x100) {
                var_v0 = 0xFF;
            } else {
                var_v0 = (u16) D_80182E76 + D_80182E8C.unk2;
            }
            D_80182E76 = var_v0;
            if (var_s0_2 < (s32) var_s1) {
                var_a0 = (var_s0_2 * 0x10) + arg1;
                do {
                    var_s0_2 += 1;
                    temp_v0 = (((u16) D_80182E68 & 0xFFFF) * 0x10) + arg1;
                    temp_v0->unk0 = (s32) var_a0->unk0;
                    temp_v0->unk4 = (s32) var_a0->unk4;
                    temp_v0->unk8 = (s32) var_a0->unk8;
                    temp_v0->unkC = (s32) var_a0->unkC;
                    var_a0 += 0x10;
                    D_80182E68 = (u16) D_80182E68 + 1;
                } while (var_s0_2 < (s32) var_s1);
            }
            goto loop_2;
        }
    }
}
