#include "ultra64.h"
void __osPiRawWriteIo(s32*, s32);                          /* extern */
void piWriteByteUnaligned(s32, s32);                          /* extern */

void piSetBytes(s32 arg0, s32 arg1, u32 arg2) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 var_a0;
    s32 var_s1;
    s32 var_v0;
    u32 var_s0;

    var_s1 = arg0;
    var_s0 = arg2;
    if (var_s0 != 0) {
        var_v0 = var_s1 & 3;
loop_2:
        temp_a0 = var_s1;
        if (var_v0 != 0) {
            var_s1 += 1;
            piWriteByteUnaligned(temp_a0, arg1 & 0xFF);
            var_s0 -= 1;
            var_v0 = var_s1 & 3;
            if (var_s0 != 0) {
                goto loop_2;
            }
        }
    }
    temp_a0_2 = arg1 & 0xFF;
    if (var_s0 >= 4U) {
        do {
            __osPiRawWriteIo(var_s1, (temp_a0_2 << 0x18) | (temp_a0_2 << 0x10) | (temp_a0_2 << 8) | temp_a0_2);
            var_s0 -= 4;
            var_s1 += 4;
        } while (var_s0 >= 4U);
    }
    var_a0 = var_s1;
    if (var_s0 != 0) {
        do {
            var_s1 += 1;
            piWriteByteUnaligned(var_a0, arg1 & 0xFF);
            var_s0 -= 1;
            var_a0 = var_s1;
        } while (var_s0 != 0);
    }
}
