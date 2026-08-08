#include "ultra64.h"
s16 viRenderSync();                                /* extern */

s32 viGetSyncByte(void) {
    return viRenderSync() & 0xFF;
}
