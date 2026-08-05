#include "ultra64.h"
s32 func_80070F50(s32, s32, s32, s32, s32, s32, s32);     /* extern */
s32 func_80071108(s32, s32);                            /* extern */
void func_800716E4(s32, s32);                       /* extern */
s32 func_8008B248(s32, u8*);                       /* extern */
extern s32 gSfxChannelMute;
extern s32 D_80174724;
extern s32 D_801887A0;
extern Unk D_801887D0;
extern s32 D_80188938;

void func_80071A28(s32 *arg0) {
    u8 sp20;
    char *var_a0;
    Unk *var_s1;
    Unk *var_v1;
    Unk *var_v1_2;
    Unk *var_v1_3;
    Unk *var_v1_4;
    s32 *var_s2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s0_6;
    s32 var_v0;
    s8 *var_v0_2;
    Unk *var_v0_3;

    D_801887D0.unk164 = 0;
    if (D_80174724 != 0) {
        func_80070F50(0x4B, 0, 0x4B, 0, 0, 0, 0);
    }
    var_s0 = 0;
    var_v1 = &D_801887D0;
    do {
        var_v1->unk31C = 0;
        var_v1->unk32C = 0;
        var_v1->unk33C = 0;
        var_v1->unk34C = 0;
        var_v1->unk35C = 0;
        var_v1->unk36C = 0;
        var_v1->unk37C = 0;
        var_s0 += 1;
        var_v1 += 4;
    } while (var_s0 < 4);
loop_4:
    var_a0 = &D_801887A0;
loop_5:
    if (func_8008B248(var_a0, &sp20) == 0) {
        var_s0_2 = 0;
        var_s1 = &D_801887D0;
        var_s2 = arg0;
        do {
            if ((((s32) sp20 >> var_s0_2) & 1) && (*var_s2 != 0)) {
                if ((var_s1->unk31C != 2) && (func_800716E4(var_s0_2, 0), (var_s1->unk31C == 2)) && (*(var_s0_2 + &gSfxChannelMute) != 0)) {
                    func_80071108(var_s0_2, -1);
                    var_s1 += 4;
                } else {
                    goto block_15;
                }
            } else {
                if (var_s1->unk31C != 2) {
                    var_s1->unk31C = 1;
                }
block_15:
                var_s1 += 4;
            }
            var_s0_2 += 1;
            var_s2 += 0x24;
        } while (var_s0_2 < 4);
        var_s0_3 = 0;
        var_v1_2 = &D_801887D0;
loop_18:
        if (*(var_s0_3 + &gSfxChannelMute) == 0) {
            var_s0_3 += 1;
            goto block_28;
        }
        temp_v0 = var_v1_2->unk31C;
        switch (temp_v0) {                          /* irregular */
        default:
            var_s0_3 += 1;
block_28:
            var_v1_2 += 4;
            if (var_s0_3 >= 4) {
                var_s0_4 = 0;
                var_v1_3 = &D_801887D0;
loop_30:
                temp_v0_2 = var_v1_3->unk31C;
                if ((temp_v0_2 != 2) && (temp_v0_2 != 4)) {
                    var_v0 = var_s0_4 < 4;
                    if (temp_v0_2 != 3) {
                        var_s0_4 += 1;
                        var_v1_3 += 4;
                        if (var_s0_4 >= 4) {
                            goto block_34;
                        }
                        goto loop_30;
                    }
                } else {
block_34:
                    var_v0 = var_s0_4 < 4;
                }
                if ((var_v0 == 0) && (func_80070F50(0x4D, 0, 0x52, 0x36, 0, 0, 0) == 0)) {
                    var_s0_5 = 3;
                    var_v0_2 = &gSfxChannelMute + 3;
                    do {
                        *var_v0_2 = 0;
                        var_s0_5 -= 1;
                        var_v0_2 -= 1;
                    } while (var_s0_5 >= 0);
                    var_a0 = (void *)0x80190000;
                    goto loop_5;
                }
                goto block_43;
            }
            goto loop_18;
        case 5:
            /* fallthrough */
        case 1:
        case 4:
            if (func_80070F50(0x4A, var_s0_3, 0x52, 0x36, 0, 0, 0) != 0) {
                var_v1_4 = &D_801887D0;
            } else {
                goto loop_4;
            }
            break;
        }
    } else {
        var_s0_6 = 3;
        var_v0_3 = &D_801887D0 + 0xC;
        do {
            var_v0_3->unk31C = 1;
            var_s0_6 -= 1;
            var_v0_3 -= 4;
        } while (var_s0_6 >= 0);
        D_80188938 = 0;
block_43:
        var_v1_4 = &D_801887D0;
    }
    var_v1_4->unk160 = (s32) (var_v1_4->unk160 - 1);
}
