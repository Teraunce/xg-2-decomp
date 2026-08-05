#include "ultra64.h"
void func_8004D138(s32, s32, s32);                       /* extern */
s32 heap_alloc_default(s32);                               /* extern */

s32 func_8004D504(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = heap_alloc_default(arg1);
    func_8004D138(arg0, temp_v0, arg1);
    return temp_v0;
}
