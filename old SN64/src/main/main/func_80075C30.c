#include "ultra64.h"
s32 func_80074EA0();                                /* extern */
void func_80074ED8(s32);                               /* extern */
s32 func_80075B78(s32, s32, s32);                      /* extern */

s32 func_80075C30(void) {
    s32 temp_s0;
    s32 temp_s0_2;

    temp_s0_2 = func_80074EA0();
    temp_s0 = func_80075B78(0x101, 0, 0);
    func_80074ED8(temp_s0_2);
    return temp_s0;
}
