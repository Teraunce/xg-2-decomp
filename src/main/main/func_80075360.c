#include "ultra64.h"
void __osPiRawWriteIo(s32 *, s32);                       /* extern */
void piWriteByteUnaligned(s32, s32);                           /* extern */

void piWriteBytes(s32 arg0, u8 *arg1, u32 arg2) {
    s32 temp_a0;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_s1;
    s32 var_v0;
    u32 var_s0;
    u8 *var_s2;
    u8 temp_a1;
    u8 temp_a1_2;
    u8 temp_a1_3;
    u8 temp_a2;
    u8 temp_v0;
    u8 temp_v1;
    Unk *var_s3;

    var_s1 = arg0;
    var_s2 = arg1;
    var_s0 = arg2;
    if (var_s0 != 0) {
        var_v0 = var_s1 & 3;
loop_2:
        temp_a0 = var_s1;
        if (var_v0 != 0) {
            var_s1 += 1;
            temp_a1 = *var_s2;
            var_s2 += 1;
            var_s0 -= 1;
            piWriteByteUnaligned(temp_a0, temp_a1);
            var_v0 = var_s1 & 3;
            if (var_s0 != 0) {
                goto loop_2;
            }
        }
    }
    var_a0 = var_s1;
    if (var_s0 >= 4U) {
        var_s3 = var_s2 + 3;
        do {
            var_s1 += 4;
            temp_v0 = *(u16*)((char*)var_s3 - 2)
            temp_v1 = *(u8*)((char*)var_s3 - 1)
            temp_a2 = var_s3->unk0;
            var_s3 += 4;
            temp_a1_2 = *var_s2;
            var_s2 += 4;
            var_s0 -= 4;
            __osPiRawWriteIo(var_a0, (temp_a1_2 << 0x18) | (temp_v0 << 0x10) | (temp_v1 << 8) | temp_a2);
            var_a0 = var_s1;
        } while (var_s0 >= 4U);
    }
    var_a0_2 = var_s1;
    if (var_s0 != 0) {
        do {
            var_s1 += 1;
            temp_a1_3 = *var_s2;
            var_s2 += 1;
            var_s0 -= 1;
            piWriteByteUnaligned(var_a0_2, temp_a1_3);
            var_a0_2 = var_s1;
        } while (var_s0 != 0);
    }
}
