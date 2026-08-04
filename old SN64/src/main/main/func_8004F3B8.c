#include "ultra64.h"
void func_8004F3B8(char *arg0, u16 *arg1, s32 arg2) {
    u16 *temp_s0;
    Unk *temp_v0;

    if (!(*arg1 & 0x8000)) {
        temp_s0 = arg2 + (*arg1 * 2);
        temp_v0 = arg0 + (*temp_s0 * 0xC);
        temp_v0->unk2 = (u8) (temp_v0->unk2 | 0x10);
        func_8004F3B8((char *)(s32)(temp_s0 + 2), NULL, 0);
        func_8004F3B8(arg0, temp_s0 + 4, arg2);
    }
}
