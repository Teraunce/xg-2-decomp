#include "ultra64.h"
s32 func_8007C768();                                /* extern */
s32 func_8007C788(s32);                               /* extern */
extern u16 *D_80095644;

void func_80087A88(u8 arg0) {
    s32 temp_s0;

    temp_s0 = func_8007C768();
    if (arg0 != 0) {
        *D_80095644 |= 0x20;
    } else {
        *D_80095644 &= ~0x20;
    }
    func_8007C788(temp_s0);
}
