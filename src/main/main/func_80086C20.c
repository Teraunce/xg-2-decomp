#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of osSpSetPcIfHalted (initial). */

s32 osSpSetPc(s32, s32);                              /* extern */
extern s32 SP_STATUS_REG;

s32 osSpGetStatusBits(s32 arg0) {
    if (arg0 & 0x1C) {
        return 1;
    }
    return 0;
}

void osSpSetStatus(s32 arg0) {
    SP_STATUS_REG = arg0;
}

s32 osSpSetPcIfHalted(s32 arg0) {
    return osSpSetPc(arg0, SP_STATUS_REG);
}
