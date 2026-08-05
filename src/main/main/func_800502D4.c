#include "ultra64.h"
s16 viRenderSync();                                /* extern */

s32 func_800502D4(void) {
    return viRenderSync() & 0xFF;
}
