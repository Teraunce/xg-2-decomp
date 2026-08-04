#include "ultra64.h"
s32 func_80076154();                                /* extern */
void func_80076160();                              /* extern */

s32 func_80074EA0(void) {
    s32 temp_v0;

    temp_v0 = func_80076154();
    func_80076160();
    return temp_v0 & 1;
}
