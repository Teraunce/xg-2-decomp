#include "ultra64.h"
s32 sfxFreeBlock(s32);                               /* extern */
extern s32 D_801823EC;
extern s32 D_801823F0;
extern s32 D_80182408;
extern s32 D_80182410;
extern s32 D_80182E6C;
extern s32 D_80182E70;
extern s32 D_80182E84;
extern s32 D_80182E88;
extern s32 D_80182E8C;
extern u32 D_80182E98;
extern s32 D_80182EA0;
extern u32 D_80182EA4;

void func_80063DF0(void) {
    D_80182408 = sfxFreeBlock(0x1800);
    D_80182410 = sfxFreeBlock(0x300);
}

void func_80063E24(void) {

}

void func_80063E2C(s32 arg0) {
    D_80182E70 = arg0 & 0xFF;
    D_801823EC = 0;
    D_801823F0 = 0;
}

void func_80063E4C(s32 arg0) {
    s32 temp_v1;
    u32 temp_a0;
    u32 temp_a0_2;
    u32 temp_v0;

    temp_a0 = arg0 & 0xFF;
    D_80182EA4 = temp_a0;
    temp_a0_2 = temp_a0 >> 3;
    D_80182E88 = -2;
    temp_v1 = temp_a0_2 < 4U;
    if (temp_v1 != 0) {
        if ((s32) temp_a0_2 >= 2) {
            if (temp_v1 != 0) {
                D_80182E98 = temp_a0_2;
            } else {
                goto block_5;
            }
        } else {
            D_80182E98 = 1;
        }
    } else {
block_5:
        D_80182E98 = 3;
    }
    temp_v0 = arg0 & 0xFF;
    D_80182E8C = temp_v0 + (temp_v0 >> 1);
    D_801823EC = 0;
    D_801823F0 = 0;
}

void func_80063ED0(s8 arg0) {
    D_80182E88 = (s32) arg0;
}

void func_80063EE4(s32 arg0) {
    D_80182E8C = arg0 & 0xFF;
}

void func_80063EF4(s32 arg0) {
    D_80182E84 = arg0 | 0xFF000000;
    D_80182E6C = 0xFF00FF;
}

void func_80063F18(s32 arg0) {
    D_80182EA0 = arg0;
}

s32 func_80063F24(Unk *arg0) {
    s32 var_a0;
    s32 var_a0_2;
    u8 temp_a1;

    temp_a1 = arg0->unk1;
    if ((s32) temp_a1 < (s32) D_80182EA4) {
        var_a0_2 = (D_80182EA4 - temp_a1) * 2;
        if (arg0->unk0 != D_80182E70) {
            var_a0_2 += 0x100;
        }
        return var_a0_2;
    }
    var_a0 = temp_a1 - D_80182EA4;
    if (arg0->unk0 != D_80182E70) {
        var_a0 += 0x100;
    }
    return var_a0;
}
