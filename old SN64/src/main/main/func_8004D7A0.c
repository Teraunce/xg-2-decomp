#include "ultra64.h"
s32 *func_8004D550(s32);                            /* extern */
void func_8004D65C(Unk*, Unk*, s32);               /* extern */
void func_8007BCA8();                                  /* extern */

s32 *func_8004D7A0(s32 *arg0) {
    s32 *temp_v0;

    temp_v0 = func_8004D550(*arg0);
    func_8004D65C(temp_v0, arg0, temp_v0);
    *temp_v0 = (s32) (temp_v0 + (*temp_v0 & 0xFFFFFF));
    func_8007BCA8();
    return temp_v0;
}
