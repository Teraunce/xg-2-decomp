#include "ultra64.h"
s32 func_80074F40(s32*);                               /* extern */
void func_80075044(s32, s8*, u32);                     /* extern */
void func_8007515C(s32, s32, u32);                     /* extern */
void func_80075360(s32, u8*, u32);                     /* extern */
void func_8007544C(s32, s32, u32);                       /* extern */
void func_80075518(s32, s32, s32);                     /* extern */
extern u32 D_80093F48;
extern s32 D_80093F4C;
extern s32 D_8F188E48;

void func_8007558C(s32 arg0) {
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a0;
    s32 var_v1;
    u32 var_a0_2;
    u32 var_a1;
    u32 var_s0;
    u32 var_s1;
    u32 var_s2;
    u32 var_s3;

    var_s2 = 0xB1FE0000;
    var_s1 = func_80074F40(0xB1FFFFF4);
    var_s3 = func_80074F40(0xB1FFFFF8);
    if (var_s1 > 0xEFFFFFFFU) {
        var_s1 = (u32) (var_s1 + &D_8F188E48);
    }
    if (var_s3 != 0) {
        do {
            var_a0 = 0;
            if ((u32) D_80093F48 < var_s1) {
                var_v1 = 0;
                do {
                    var_v1 += 8;
                    var_a0 += 1;
                } while ((u32) *(&D_80093F48 + var_v1) < var_s1);
            }
            temp_a0 = var_a0 * 8;
            var_s0 = *(&D_80093F48 + temp_a0) - (var_s1 - 1);
            if (var_s3 < var_s0) {
                var_s0 = var_s3;
            }
            temp_v1 = *(&D_80093F4C + temp_a0);
            if (temp_v1 & arg0) {
                if (temp_v1 & 4) {
                    var_a0_2 = var_s1;
                    if (arg0 == 1) {
                        var_a0_2 = var_s2;
                        var_a1 = var_s1;
                    } else {
                        var_a1 = var_s2;
                    }
                    func_80075518(var_a0_2, var_a1, var_s0);
                    var_s2 += var_s0;
                } else if (arg0 == 1) {
                    func_80075360(var_s2, var_s1, var_s0);
                    var_s2 += var_s0;
                } else if (temp_v1 & 8) {
                    func_8007515C(var_s2, var_s1, var_s0);
                    var_s2 += var_s0;
                } else {
                    func_80075044(var_s2, var_s1, var_s0);
                    goto block_23;
                }
            } else if (arg0 == 1) {
                func_8007544C(var_s2, 0, var_s0);
                var_s2 += var_s0;
            } else {
block_23:
                var_s2 += var_s0;
            }
            var_s3 -= var_s0;
            var_s1 += var_s0;
        } while (var_s3 != 0);
    }
}
