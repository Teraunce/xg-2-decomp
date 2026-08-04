#include "ultra64.h"
char *func_800841B8(Unk *arg0, s32 arg1, s32 arg2, s32 arg3, Unk *arg4) {
    s32 temp_v0;
    s32 var_s0;
    void **var_s1;
    Unk *temp_a0;
    char *var_s2;

    temp_v0 = arg2 * 2;
    arg4->unk0 = 0x020006C0;
    arg4->unk4 = temp_v0;
    arg4->unk8 = 0x02000800;
    arg4->unkC = temp_v0;
    var_s0 = 0;
    var_s2 = arg4 + 0x10;
    if (arg0->unk14 > 0) {
        var_s1 = arg0->unk1C;
        do {
            temp_a0 = *var_s1;
            var_s0 += 1;
            var_s1 += 4;
            var_s2 = ((s32(*)())(s32)temp_a0->unk4)(temp_a0, arg1, arg2, arg3, var_s2);
        } while (var_s0 < arg0->unk14);
    }
    return var_s2;
}

f64 func_80084298(f64 arg0, s32 arg2) {
    f64 var_fa0;

    var_fa0 = arg0;
    if (arg2 != 0) {
        var_fa0 *= (f64) (1 << arg2);
    }
    return var_fa0;
}

f64 func_800842C0(f64 arg0, s32 *arg2) {
    f64 var_fv0;
    f64 var_fv1;

    *arg2 = 0;
    if (arg0 == 0.0) {
        return arg0;
    }
    if (arg0 > 0.0) {
        var_fv0 = arg0;
    } else {
        var_fv0 = -arg0;
    }
    if (var_fv0 >= 1.0) {
        do {
            var_fv0 *= 0.5;
            *arg2 += 1;
        } while (var_fv0 >= 1.0);
    }
    if (var_fv0 < 0.5) {
        do {
            var_fv0 *= 2.0;
            *arg2 -= 1;
        } while (var_fv0 < 0.5);
    }
    if (arg0 > 0.0) {
        var_fv1 = var_fv0;
    } else {
        var_fv1 = -var_fv0;
    }
    return var_fv1;
}
