#include "ultra64.h"
void func_8004F31C(char *arg0, u16 *arg1, s32 arg2, s32 arg3) {
    u16 *temp_s0;
    u16 temp_v1;
    Unk *temp_v0;

    temp_v1 = *arg1;
    if (temp_v1 <= 0xFDFFU) {
        temp_s0 = arg2 + (temp_v1 * 2);
        temp_v0 = arg0 + (*temp_s0 * 0xC);
        temp_v0->unk2 = (u8) (temp_v0->unk2 | 0x10);
        func_8004F31C((char *)(s32)(temp_s0 + 2), NULL, 0, 0);
        func_8004F31C(arg0, temp_s0 + 4, arg2, arg3);
    }
}
