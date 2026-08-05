#include "ultra64.h"
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
extern u16 *gVIConfig;

void func_80087A88(u8 arg0) {
    s32 temp_s0;

    temp_s0 = osDisableInt();
    if (arg0 != 0) {
        *gVIConfig |= 0x20;
    } else {
        *gVIConfig &= ~0x20;
    }
    osRestoreInt(temp_s0);
}
