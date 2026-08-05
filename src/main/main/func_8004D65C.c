#include "ultra64.h"
s32 osVirtualToPhysical(u32);                             /* extern */

void func_8004D65C(Unk *arg0, Unk *arg1, s32 arg2) {
    s32 *temp_a1;
    Unk *var_a2;
    s32 *var_s1;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_s0;
    s32 temp_v1;
    s32 temp_v1_2;
    Unk *temp_s0_2;

    temp_v1 = arg0->unk4;
    if (temp_v1 != 0) {
        var_a2 = arg2 + (temp_v1 & 0xFFFFFF);
    } else {
        var_a2 = NULL;
    }
    temp_a0 = arg0->unk8;
    if (temp_a0 != 0) {
        var_s1 = arg2 + (temp_a0 & 0xFFFFFF);
    } else {
        var_s1 = NULL;
    }
    if ((var_a2 != NULL) && (var_a2->unk0 != 0)) {
        do {
            temp_v1_2 = var_a2->unk4;
            temp_a1 = arg2 + (var_a2->unk0 & 0xFFFFFF);
            temp_a0_2 = *temp_a1;
            var_a2 += 8;
            *temp_a1 = (temp_a0_2 & ~temp_v1_2) | (((temp_a0_2 & temp_v1_2 & 0xFFFFFF) + arg2) & temp_v1_2);
        } while (var_a2->unk0 != 0);
    }
    if ((var_s1 != NULL) && (*var_s1 != 0)) {
        do {
            temp_s0 = *var_s1;
            var_s1 += 4;
            temp_s0_2 = arg2 + (temp_s0 & 0xFFFFFF);
            temp_s0_2->unk0 = (s32) (((arg1->unkC * 4) & 0xFFFF) | 0xDB060000);
            temp_s0_2->unk4 = osVirtualToPhysical(arg2);
        } while (*var_s1 != 0);
    }
}
