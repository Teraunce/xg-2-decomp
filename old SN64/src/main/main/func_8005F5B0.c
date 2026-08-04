#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8005F6B4 (initial). */

void func_8005CD90(s32, f32, s32, s8, s32);           /* extern */
extern f32 D_8004BF48;
extern f32 D_8004BF4C;
extern f32 D_8004BF50;
extern Unk D_80181588;

void func_8005F5B0(f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    Unk *var_s0;
    f32 temp_fv1;
    f32 var_ft0;
    f32 var_ft1;
    f32 var_ft2;
    f32 var_ft3;
    s32 temp_a0;
    s32 temp_a2;
    s32 var_s1;

    var_ft2 = arg1;
    var_ft0 = arg2;
    var_ft1 = arg3;
    var_ft3 = arg4;
    temp_fv1 = (var_ft2 + var_ft0 + var_ft1 + var_ft3) * D_8004BF48;
    if (D_8004BF4C < temp_fv1) {
        var_ft2 /= temp_fv1;
        var_ft0 /= temp_fv1;
        var_ft1 /= temp_fv1;
        var_ft3 /= temp_fv1;
    }
    var_s1 = 0;
    var_s0 = &D_80181588;
    D_80181588.unk0 = (s32) (var_ft2 * D_8004BF50);
    D_80181588.unk4 = (s32) (var_ft0 * D_8004BF50);
    D_80181588.unk8 = (s32) (var_ft1 * D_8004BF50);
    D_80181588.unkC = (s32) (var_ft3 * D_8004BF50);
    do {
        temp_a0 = var_s0->unk10;
        temp_a2 = var_s0->unk0;
        var_s0 += 4;
        var_s1 += 1;
        func_8005CD90(temp_a0, arg5, temp_a2, arg6, 0);
    } while (var_s1 < 4);
}

void func_8005F6B4(Unk *arg0) {
    arg0->unk7C83;
}
