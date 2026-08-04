#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
s32 func_80063800(s32);                             /* extern */
s32 func_80063A3C(s32, s32);                          /* extern */
extern s32 D_80092D38;

s32 func_80063B9C(u32 arg0) {
    s32 temp_v0;

    if (arg0 < (u32) (s32)M2C_ERROR(/* Read from unset register $v0 */)) {
        temp_v0 = func_80063800(((Unk*)(s32)((arg0 * 0x10) + D_80092D38))->unk8);
        if (temp_v0 != 0) {
            func_80063A3C(arg0, temp_v0);
            return temp_v0;
        }
    }
    return 0;
}
