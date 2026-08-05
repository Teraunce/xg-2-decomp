#include "ultra64.h"
s32 *func_8004D550(s32);                            /* extern */
void func_8004D65C(Unk*, Unk*, s32);               /* extern */
void __osInvalICache_full();                                  /* extern */

s32 *overlayDecompress(s32 *arg0) {
    s32 *temp_v0;

    temp_v0 = func_8004D550(*arg0);
    func_8004D65C(temp_v0, arg0, temp_v0);
    *temp_v0 = (s32) (temp_v0 + (*temp_v0 & 0xFFFFFF));
    __osInvalICache_full();
    return temp_v0;
}
