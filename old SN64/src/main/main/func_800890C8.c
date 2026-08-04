#include "ultra64.h"
u8 func_800890C8(u8 *arg0) {
    u8 spF;
    u8 spE;
    s32 sp8;
    s32 sp4;
    s32 temp_t5;
    s32 temp_t7;
    s32 var_a1;
    u8 *var_a0;
    u8 temp_t1;

    var_a0 = arg0;
    spF = 0;
    sp8 = 0;
    do {
        sp4 = 7;
loop_2:
        if (spF & 0x80) {
            spE = 0x85;
        } else {
            spE = 0;
        }
        temp_t1 = spF * 2;
        spF = temp_t1;
        if (sp8 == 0x20) {
            spF = temp_t1 & 0xFF;
        } else {
            if (*var_a0 & (1 << sp4)) {
                var_a1 = 1;
            } else {
                var_a1 = 0;
            }
            spF |= var_a1;
        }
        temp_t5 = sp4 - 1;
        sp4 = temp_t5;
        spF ^= spE;
        if (temp_t5 >= 0) {
            goto loop_2;
        }
        var_a0 += 1;
        temp_t7 = sp8 + 1;
        sp8 = temp_t7;
    } while (temp_t7 < 0x21);
    return spF;
}
