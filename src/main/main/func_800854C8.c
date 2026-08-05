#include "ultra64.h"
s32 func_8007D688(u32);                       /* extern */

char *func_800854C8(Unk *arg0, u32 arg1, s32 arg2, s32 arg3, Unk *arg4) {
    u32 sp4C;
    char *sp44;
    char *sp3C;
    char *sp30;
    s32 sp2C;
    u32 sp28;
    s32 sp24;
    s32 temp_a2;
    s32 temp_t3;
    s32 temp_t6;
    u32 temp_a3;
    u32 temp_t1;
    u32 temp_v0;
    u32 var_a1;
    Unk *temp_s0;
    Unk *temp_s0_2;
    Unk *temp_s0_3;
    Unk *temp_s0_4;
    Unk *temp_s0_5;
    char *var_s0;

    var_a1 = arg1;
    temp_v0 = arg0->unk14;
    temp_t6 = arg0->unk1C * 2;
    temp_t1 = temp_v0 + temp_t6;
    if (var_a1 < temp_v0) {
        var_a1 += temp_t6;
    }
    temp_a2 = arg3 * 2;
    temp_a3 = temp_a2 + var_a1;
    temp_s0 = arg4 + 8;
    if (temp_t1 < temp_a3) {
        arg4->unk0 = 0x08000000;
        temp_t3 = ((s32) (temp_t1 - var_a1) >> 1) * 2;
        temp_s0_2 = arg4 + 8;
        arg4->unk4 = (s32) ((arg2 << 0x10) | (temp_t3 & 0xFFFF));
        arg4->unk8 = 0x06000000;
        sp44 = temp_s0_2;
        sp24 = temp_t3;
        sp4C = temp_t1;
        sp28 = temp_a3;
        sp2C = temp_a2;
        temp_s0_3 = temp_s0_2 + 8;
        temp_s0_2->unk4 = func_8007D688(var_a1);
        temp_s0_2->unk8 = 0x08000000;
        temp_s0_4 = temp_s0_3 + 8;
        temp_s0_3->unk4 = (s32) (((temp_t3 + arg2) << 0x10) | ((((s32) (temp_a3 - temp_t1) >> 1) * 2) & 0xFFFF));
        temp_s0_3->unk8 = 0x06000000;
        sp3C = temp_s0_4;
        temp_s0_5 = temp_s0_4 + 8;
        temp_s0_4->unk4 = func_8007D688(arg0->unk14);
        temp_s0_5->unk4 = (s32) (temp_a2 & 0xFFFF);
        temp_s0_4->unk8 = 0x08000000;
        var_s0 = temp_s0_5 + 8;
    } else {
        arg4->unk0 = 0x08000000;
        arg4->unk4 = (s32) ((arg2 << 0x10) | (temp_a2 & 0xFFFF));
        arg4->unk8 = 0x06000000;
        sp30 = temp_s0;
        var_s0 = temp_s0 + 8;
        temp_s0->unk4 = func_8007D688(var_a1);
    }
    return var_s0;
}
