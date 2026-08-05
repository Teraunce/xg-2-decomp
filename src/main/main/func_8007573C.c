#include "ultra64.h"
void __osPiRawWriteIo(s32*, s32);                          /* extern */
s32 __osPiRawReadIo(s32*);                             /* extern */
void __osPiResetCount(s32);                                 /* extern */

void func_8007573C(void) {
    s32 temp_s4;
    s32 var_s1;
    s32 var_s2;
    u32 temp_s1;
    u32 temp_v1;
    u32 var_s0;

    temp_s4 = __osPiRawReadIo(0xB1FFFFF4) & 0xB1FFFFFC;
    temp_s1 = __osPiRawReadIo(0xB1FFFFF8) & 0x01FFFFFC;
    __osPiRawWriteIo(0xB1FFFFFC, 0);
loop_1:
    temp_v1 = temp_s1 >> 2;
    if (__osPiRawReadIo(0xB0000010) == 0) {
        __osPiResetCount(0x1F4);
        goto loop_1;
    }
    var_s0 = 0;
    if (temp_v1 != 0) {
        var_s2 = temp_s4 & 0xB07FFFFF;
        var_s1 = temp_s4;
        do {
            __osPiRawWriteIo(var_s2, __osPiRawReadIo(var_s1));
            var_s2 += 4;
            var_s0 += 1;
            var_s1 += 4;
        } while (var_s0 < temp_v1);
    }
    __osPiResetCount(0x7D0);
    __osPiRawWriteIo(0xB1FFFFF4, 0);
}
