#include "ultra64.h"
s32 viGetSyncByte();                                /* extern */
s32 sfxNullReturn();                                /* static */
extern s32 gEntityFlagMask;
extern s32 gRaceCtrlCount;

s32 viGetSyncWord(void) {
    s32 temp_s0;

    temp_s0 = (viGetSyncByte() & 0xFF) << 8;
    return (viGetSyncByte() & 0xFF) | temp_s0;
}

s32 func_80050328(s32 arg0) {
    if (arg0 != 0x10) {
        if (arg0 < 0x11) {
            if (arg0 != 4) {
                if (arg0 < 5) {
                    if (arg0 != 2) {
                        return sfxNullReturn();
                    }
                    return 1;
                }
                if (arg0 != 8) {
                    return sfxNullReturn();
                }
                return 3;
            }
            return 2;
        }
        if (arg0 != 0x40) {
            if (arg0 < 0x41) {
                if (arg0 != 0x20) {
                    return sfxNullReturn();
                }
                return 5;
            }
            if (arg0 != 0x80) {
                if (arg0 != 0x100) {
                    return sfxNullReturn();
                }
                return 8;
            }
            return 7;
        }
        return 6;
    }
    return 4;
}

s32 sfxNullReturn(void) {
    return 0;
}

s32 sfxGetRunning(void) {
    return gRaceCtrlCount;
}
