#include "ultra64.h"
void func_8007E734(void**, s32, s32);                     /* extern */

void func_8007EAA8(s32 arg0, s16 arg1) {
    s16 sp1C;
    s16 sp18;

    sp18 = 0xA;
    sp1C = arg1;
    func_8007E734(arg0 + 0x48, &sp18, 0);
}
