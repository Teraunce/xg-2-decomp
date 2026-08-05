#include "ultra64.h"
void osWritebackInvalDCache(u32, s32);                       /* extern */
s32 spTaskSubmit(Unk*, s32, s32, s32, s32, s32, s32);  /* extern */
extern s32 D_8016DF70;
extern s32 D_8017CDF8;
extern s32 D_8017EFB0;
extern s32 D_80190000;

void func_8005A978(Unk *arg0) {
    s32 temp_s1;
    u32 temp_a0;
    u32 var_s1;

    var_s1 = arg0->unk4;
    if (var_s1 >= 0x401U) {
        var_s1 = 0x400;
    }
    arg0->unk14 = var_s1;
    if (var_s1 != 0) {
        temp_s1 = (var_s1 + 7) & ~7;
        osWritebackInvalDCache(((1 - arg0->unk8) << 0xA) + &D_80190000, temp_s1);
        spTaskSubmit(&D_8017EFB0, 0, 0, arg0->unk0, ((1 - arg0->unk8) << 0xA) + &D_80190000, temp_s1, &D_8016DF70);
        temp_a0 = arg0->unk14;
        D_8017CDF8 += 1;
        arg0->unk0 = (s32) (arg0->unk0 + temp_a0);
        arg0->unk4 = (u32) (arg0->unk4 - temp_a0);
    }
}
