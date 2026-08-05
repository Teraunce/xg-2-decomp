#include "ultra64.h"
s32 func_80074EA0();                                /* extern */
void func_80074ED8(s32);                               /* extern */
void func_80075044(s32, s8*, u32);                       /* extern */
s32 sramStartDma(s32, s32, s32);                  /* extern */

s32 func_80075E04(s32 arg0, s32 arg1, u32 arg2) {
    s32 temp_s4;
    s32 temp_v0;
    s32 var_s2;
    s32 var_s3;
    u32 var_a2;
    u32 var_s1;

    var_s3 = arg1;
    var_s1 = arg2;
    var_s2 = 0;
    temp_s4 = func_80074EA0();
    if (var_s1 != 0) {
loop_2:
        var_a2 = var_s1;
        if (var_s1 > 0x8000U) {
            var_a2 = 0x8000;
        }
        temp_v0 = sramStartDma(0x505, var_a2, 0);
        if (temp_v0 != 0) {
            func_80075044(0xB1FF0000, var_s3, temp_v0);
            var_s3 += temp_v0;
            var_s1 -= temp_v0;
            var_s2 += temp_v0;
            if (var_s1 != 0) {
                goto loop_2;
            }
        }
    }
    func_80074ED8(temp_s4);
    return var_s2;
}
