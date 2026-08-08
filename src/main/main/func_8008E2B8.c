#include "ultra64.h"
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
extern s32 osIntMask;

void osDisableIntMask(s32 arg0) {
    s32 temp_s0;

    temp_s0 = osDisableInt();
    osIntMask &= ~(arg0 & ~0x401);
    osRestoreInt(temp_s0);
}
