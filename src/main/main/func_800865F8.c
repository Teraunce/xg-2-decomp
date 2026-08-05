#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_800866E8 (initial). */

void func_800831F8(Unk*, Unk*, void*);                         /* extern */
s32 func_80084F18(Unk*, s32, s32);                       /* extern */
s32 func_80085C5C(s32*, s32, s32);                       /* extern */
extern f32 D_8004CFA8;
extern f32 D_8004CFAC;
extern s32 gAiClock;

s32 func_800865F8(Unk *arg0, s16 arg1, s32 arg2, s32 arg3) {
    s32 temp_a2;
    s32 temp_s1;

    temp_s1 = arg1 * 0x4C;
    func_800831F8(arg0->unk34 + temp_s1 + 0x20, arg2, arg3);
    temp_a2 = arg0->unk34 + temp_s1;
    func_80085C5C(temp_a2 + 0x20, 1, temp_a2);
    func_80084F18(arg0->unk30, 2, arg0->unk34 + temp_s1 + 0x20);
    return arg0->unk34 + temp_s1 + 0x20;
}

f32 func_80086698(s32 arg0) {
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_t7;
    s32 var_a0;

    var_a0 = arg0;
    var_fv1 = 1.0f;
    if (var_a0 >= 0) {
        var_fv0 = D_8004CFA8;
    } else {
        var_fv0 = D_8004CFAC;
        var_a0 = -var_a0;
    }
    if (var_a0 != 0) {
        do {
            temp_t7 = var_a0 >> 1;
            if (var_a0 & 1) {
                var_fv1 *= var_fv0;
            }
            var_fv0 *= var_fv0;
            var_a0 = temp_t7;
        } while (temp_t7 != 0);
    }
    return var_fv1;
}

void func_800866E8(s32 arg0) {

}
