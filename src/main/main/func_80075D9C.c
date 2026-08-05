#include "ultra64.h"
s32 intDisable();                                /* extern */
void intRestore(s32);                               /* extern */
s32 sramStartDma(s32, s32, s32);                    /* extern */

s32 func_80075D9C(s32 arg0) {
    s32 temp_s1;
    s32 var_s0;

    temp_s1 = intDisable();
    var_s0 = sramStartDma(0x404, 0, 0);
    if (var_s0 & 0x8000) {
        var_s0 |= 0xFFFF0000;
    }
    intRestore(temp_s1);
    return var_s0;
}
