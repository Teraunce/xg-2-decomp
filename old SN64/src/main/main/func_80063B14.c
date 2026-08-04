#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
/* Warning: missing "jr $ra" in last block of func_80063B94 (initial). */

u16 func_80063730(s32);                             /* extern */
void func_80063878(u16);                               /* extern */
s32 func_800639B0(s32);                             /* extern */
s32 func_80063A3C(s32, s32);                        /* extern */
extern s32 D_80092D38;
extern s32 D_801823E0;

s32 func_80063B14(u32 arg0) {
    s32 temp_s0;
    s32 var_v0;

    if (arg0 < (u32) (s32)M2C_ERROR(/* Read from unset register $v0 */)) {
        temp_s0 = func_80063730(((Unk*)(s32)((arg0 * 0x10) + D_80092D38))->unk8) & 0xFFFF;
        var_v0 = 0;
        if (temp_s0 != 0) {
            var_v0 = temp_s0;
            if (func_80063A3C(arg0, func_800639B0(temp_s0)) == 0) {
                func_80063878(temp_s0);
                goto block_4;
            }
        }
    } else {
block_4:
        var_v0 = 0;
    }
    return var_v0;
}

s32 func_80063B94(void) {
    return D_801823E0;
}
