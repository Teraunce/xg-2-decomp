#include "ultra64.h"
s32 func_80074EA0();                                /* extern */
void func_80074ED8(s32);                               /* extern */
void func_80075360(s32, u8*, u32);                       /* extern */
s32 func_80075B58(u8*);                             /* extern */
s32 func_80075B78(s32, s32, s32);                    /* extern */

s32 func_80075C7C(s32 arg0, s32 arg1) {
    s32 temp_s2;
    s32 temp_v0;
    s32 var_s0;

    temp_s2 = func_80074EA0();
    temp_v0 = func_80075B58(arg0);
    func_80075360(0xB1FF0000, arg0, temp_v0);
    var_s0 = func_80075B78(0x202, arg1, 0);
    if (var_s0 & 0x8000) {
        var_s0 |= 0xFFFF0000;
    }
    func_80074ED8(temp_s2);
    return var_s0;
}
