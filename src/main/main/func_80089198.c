#include "ultra64.h"
u16 contPakByteSum(u8 *arg0, s32 arg1) {
    s32 spC;
    s32 sp8;
    u8 *sp4;
    s32 temp_t4;

    s16 unkspA;
    sp8 = 0;
    sp4 = arg0;
    spC = 0;
    if (arg1 > 0) {
        do {
            temp_t4 = spC + 1;
            sp8 += *sp4;
            spC = temp_t4;
            sp4 += 1;
            sp8 &= 0xFFFF;
        } while (temp_t4 < arg1);
    }
    return unkspA;
}
