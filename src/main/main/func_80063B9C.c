#include "ultra64.h"
s32 func_80063800(s32);                             /* extern */
s32 func_80063A3C(s32, s32);                          /* extern */
extern s32 gSfxDefTable;

s32 func_80063B9C(u32 arg0) {
    s32 temp_v0;

    if (arg0 < (u32)(s32)0 /* implicit $v0 from caller */) {
        temp_v0 = func_80063800(((Unk*)(s32)((arg0 * 0x10) + gSfxDefTable))->unk8);
        if (temp_v0 != 0) {
            func_80063A3C(arg0, temp_v0);
            return temp_v0;
        }
    }
    return 0;
}
