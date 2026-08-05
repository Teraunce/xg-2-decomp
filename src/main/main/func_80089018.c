#include "ultra64.h"
s32 crc5Calc(s32 arg0) {
    u8 spF;
    u8 spE;
    s32 sp8;
    s32 temp_t1;
    s32 var_a0;
    s32 var_a1;
    u8 temp_t4;

    var_a0 = arg0 & 0xFFFF;
    spF = 0;
    sp8 = 0;
    do {
        if (spF & 0x10) {
            spE = 0x15;
        } else {
            spE = 0;
        }
        spF *= 2;
        if (var_a0 & 0x400) {
            var_a1 = 1;
        } else {
            var_a1 = 0;
        }
        temp_t4 = spF | (var_a1 & 0xFF);
        temp_t1 = sp8 + 1;
        spF = temp_t4;
        sp8 = temp_t1;
        var_a0 = (var_a0 * 2) & 0xFFFF;
        spF = (temp_t4 & 0xFF) ^ spE;
    } while (temp_t1 < 0x10);
    return spF & 0x1F & 0xFF;
}
