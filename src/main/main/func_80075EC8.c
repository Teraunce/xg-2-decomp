#include "ultra64.h"
s32 intDisable();                                /* extern */
void intRestore(s32);                               /* extern */
void piWriteBytes(s32, u8*, u32);                       /* extern */
s32 sramStartDma(s32, s32, s32);                  /* extern */

s32 func_80075EC8(s32 arg0, s32 arg1, u32 arg2) {
    s32 temp_s4;
    s32 temp_v0;
    s32 var_s2;
    s32 var_s3;
    u32 var_s0;
    u32 var_s1;

    var_s3 = arg1;
    var_s1 = arg2;
    var_s2 = 0;
    temp_s4 = intDisable();
    if (var_s1 != 0) {
loop_2:
        var_s0 = var_s1;
        if (var_s1 > 0x8000U) {
            var_s0 = 0x8000;
        }
        piWriteBytes(0xB1FF0000, var_s3, var_s0);
        temp_v0 = sramStartDma(0x606, var_s0, 0);
        if (temp_v0 != 0) {
            var_s3 += temp_v0;
            var_s1 -= temp_v0;
            var_s2 += temp_v0;
            if (var_s1 != 0) {
                goto loop_2;
            }
        }
    }
    intRestore(temp_s4);
    return var_s2;
}
