#include "ultra64.h"
s32 func_80074FC4(s32);                             /* extern */
void func_80075270(s32, s32);                          /* extern */

void func_80075518(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;

    var_s1 = arg0;
    var_s2 = arg1;
    var_s0 = arg2 - 1;
    if (arg2 != 0) {
        var_a0 = var_s2;
        do {
            var_s2 += 1;
            temp_a0 = var_s1;
            var_s1 += 1;
            func_80075270(temp_a0, func_80074FC4(var_a0) & 0xFF);
            var_s0 -= 1;
            var_a0 = var_s2;
        } while (var_s0 != -1);
    }
}
