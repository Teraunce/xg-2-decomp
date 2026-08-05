#include "ultra64.h"
u64 func_80061B38(s32, s32, s32, s32);              /* extern */

u64 func_80061C70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_a0_2;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 var_s0;
    u64 temp_ret;
    u64 var_a0;

    var_a0_2 = arg0;
    var_a1 = arg1;
    var_a2 = arg2;
    var_a3 = arg3;
    var_s0 = 0;
    if (var_a0_2 < 0) {
        var_a1 = -var_a1;
        var_a0_2 = -var_a0_2 - (var_a1 != 0);
        var_s0 = 1;
    }
    if (var_a2 < 0) {
        var_a3 = -var_a3;
        var_a2 = -var_a2 - (var_a3 != 0);
        var_s0 = var_s0 == 0;
    }
    temp_ret = func_80061B38(var_a0_2, var_a1, var_a2, var_a3);
    var_a0 = temp_ret;
    if (var_s0 != 0) {
        var_a0 = -(s32) var_a0 - (-(s32) (u32) temp_ret != 0);
    }
    return var_a0;
}
