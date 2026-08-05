#include "ultra64.h"
s32 intDisable();                                /* extern */
void intRestore(s32);                               /* extern */
void piWriteBytes(s32, u8*, u32);                       /* extern */
s32 func_80075B58(u8*);                             /* extern */
s32 sramStartDma(s32, s32, s32);                    /* extern */

s32 func_80075C7C(s32 arg0, s32 arg1) {
    s32 temp_s2;
    s32 temp_v0;
    s32 var_s0;

    temp_s2 = intDisable();
    temp_v0 = func_80075B58(arg0);
    piWriteBytes(0xB1FF0000, arg0, temp_v0);
    var_s0 = sramStartDma(0x202, arg1, 0);
    if (var_s0 & 0x8000) {
        var_s0 |= 0xFFFF0000;
    }
    intRestore(temp_s2);
    return var_s0;
}
