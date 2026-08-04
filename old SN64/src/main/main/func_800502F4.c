#include "ultra64.h"
s32 func_800502D4();                                /* extern */
s32 func_800503F0();                                /* static */
extern s32 D_80091FD0;
extern s32 D_8017C950;

s32 func_800502F4(void) {
    s32 temp_s0;

    temp_s0 = (func_800502D4() & 0xFF) << 8;
    return (func_800502D4() & 0xFF) | temp_s0;
}

s32 func_80050328(s32 arg0) {
    if (arg0 != 0x10) {
        if (arg0 < 0x11) {
            if (arg0 != 4) {
                if (arg0 < 5) {
                    if (arg0 != 2) {
                        return func_800503F0();
                    }
                    return 1;
                }
                if (arg0 != 8) {
                    return func_800503F0();
                }
                return 3;
            }
            return 2;
        }
        if (arg0 != 0x40) {
            if (arg0 < 0x41) {
                if (arg0 != 0x20) {
                    return func_800503F0();
                }
                return 5;
            }
            if (arg0 != 0x80) {
                if (arg0 != 0x100) {
                    return func_800503F0();
                }
                return 8;
            }
            return 7;
        }
        return 6;
    }
    return 4;
}

s32 func_800503F0(void) {
    return 0;
}

s32 func_800503F8(void) {
    return D_8017C950;
}
