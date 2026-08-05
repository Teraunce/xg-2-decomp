#include "ultra64.h"
s32 func_8008ED50(s64 arg0, s32 arg1, s64 arg2, s32 arg3) {
    s64 sp0;
    s64 temp_hi;

    temp_hi = arg0 % arg2;
    if ((arg2 == -1) && (arg0 == (1 << 0x3F))) {
        M2C_BREAK(6);
    }
    sp0 = temp_hi;
    if (((temp_hi < 0) && (arg2 > 0)) || ((sp0 > 0) && (arg2 < 0))) {
        sp0 += arg2;
    }
    return (s32) sp0;
}

s64 func_8008EDEC(s64 arg0, s32 arg1, s64 arg2, s32 arg3) {
    return (s64) (arg0 >> arg2) >> 0x20;
}
