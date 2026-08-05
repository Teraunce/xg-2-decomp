#include "ultra64.h"
s32 func_80086904(s32 arg0) {
    /* implicit $at: bitmask from caller (SN64 uses $at as GP reg with .set noat) */
    if (arg0 & (s32)0 /* implicit $at bitmask */) {
        return 1;
    }
    return 0;
}
