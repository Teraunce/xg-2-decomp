#include "ultra64.h"
void func_8007E734(void**, s32, s32);                     /* extern */

void func_8007E9D8(s32 arg0, s32 arg1) {
    s32 sp1C;
    s16 sp18;

    sp1C = arg1;
    sp18 = 0xE;
    func_8007E734(arg0 + 0x48, &sp18, 0);
}
