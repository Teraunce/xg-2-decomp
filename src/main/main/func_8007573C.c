#include "ultra64.h"
void func_80074F08(s32*, s32);                          /* extern */
s32 func_80074F40(s32*);                             /* extern */
void func_80074F7C(s32);                                 /* extern */

void func_8007573C(void) {
    s32 temp_s4;
    s32 var_s1;
    s32 var_s2;
    u32 temp_s1;
    u32 temp_v1;
    u32 var_s0;

    temp_s4 = func_80074F40(0xB1FFFFF4) & 0xB1FFFFFC;
    temp_s1 = func_80074F40(0xB1FFFFF8) & 0x01FFFFFC;
    func_80074F08(0xB1FFFFFC, 0);
loop_1:
    temp_v1 = temp_s1 >> 2;
    if (func_80074F40(0xB0000010) == 0) {
        func_80074F7C(0x1F4);
        goto loop_1;
    }
    var_s0 = 0;
    if (temp_v1 != 0) {
        var_s2 = temp_s4 & 0xB07FFFFF;
        var_s1 = temp_s4;
        do {
            func_80074F08(var_s2, func_80074F40(var_s1));
            var_s2 += 4;
            var_s0 += 1;
            var_s1 += 4;
        } while (var_s0 < temp_v1);
    }
    func_80074F7C(0x7D0);
    func_80074F08(0xB1FFFFF4, 0);
}
