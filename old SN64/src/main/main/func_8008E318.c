#include "ultra64.h"
s32 func_8007C768();                                /* extern */
s32 func_8007C788(s32);                               /* extern */
extern s32 D_80095290;

void func_8008E318(s32 arg0) {
    s32 temp_s0;

    temp_s0 = func_8007C768();
    D_80095290 |= arg0;
    func_8007C788(temp_s0);
}
