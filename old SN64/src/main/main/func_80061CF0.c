#include "ultra64.h"
s32 func_80061CF0(s32 arg0, u16 *arg1, u16 *arg2, u16 *arg3, u16 *arg4, s32 arg5) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_t0;
    s32 var_t1;
    u16 *var_a1;
    u16 *var_t0_2;
    u16 *var_t0_3;
    u16 *var_t0_4;
    u16 temp_v1;
    u16 var_v0;
    u16 var_v1;
    u16 var_v1_2;
    u16 var_v1_3;

    var_a1 = arg1;
    var_v1 = *var_a1;
    var_t1 = 0;
    if (var_v1 != 0) {
        var_t0 = var_v1 & 0xFFFF;
        do {
            temp_v0 = var_t1;
            if (var_t0 == 0x25) {
                var_a1 += 2;
                var_v1 = *var_a1;
                if (var_v1 != 0x32) {
                    if ((s32) var_v1 < 0x33) {
                        if (var_v1 == var_t0) {
                            goto block_27;
                        }
                        var_t0_2 = arg2;
                        if (var_v1 != 0x31) {
                            var_a1 += 2;
                        } else {
                            var_v0 = *var_t0_2;
                            if (var_v0 != 0) {
                                do {
                                    temp_v0_2 = var_v0 & 0xFFFF;
                                    if (arg5 != 0) {
                                        if ((temp_v0_2 == 0xD) || (temp_v0_2 == 0xA)) {
                                            temp_v0_3 = var_t1;
                                            var_t1 += 1;
                                            *(u16 *)(((temp_v0_3 & 0xFFFF) * 2) + arg0) = 0x20;
                                            var_t0_2 += 2;
                                        } else {
                                            goto block_18;
                                        }
                                    } else {
block_18:
                                        var_t1 += 1;
                                        temp_v1 = *var_t0_2;
                                        var_t0_2 += 2;
                                        *(u16 *)(((var_t1 & 0xFFFF) * 2) + arg0) = temp_v1;
                                    }
                                    var_v0 = *var_t0_2;
                                } while (var_v0 != 0);
                                var_a1 += 2;
                            } else {
                                goto block_28;
                            }
                        }
                    } else {
                        var_t0_3 = arg4;
                        if (var_v1 != 0x33) {
                            var_a1 += 2;
                        } else {
                            var_v1_2 = *var_t0_3;
                            if (var_v1_2 != 0) {
                                do {
                                    var_t0_3 += 2;
                                    *(u16 *)(((var_t1 & 0xFFFF) * 2) + arg0) = var_v1_2;
                                    var_v1_2 = *var_t0_3;
                                    var_t1 += 1;
                                } while (var_v1_2 != 0);
                                var_a1 += 2;
                            } else {
                                goto block_28;
                            }
                        }
                    }
                } else {
                    var_t0_4 = arg3;
                    var_v1_3 = *var_t0_4;
                    if (var_v1_3 != 0) {
                        do {
                            var_t0_4 += 2;
                            *(u16 *)(((var_t1 & 0xFFFF) * 2) + arg0) = var_v1_3;
                            var_v1_3 = *var_t0_4;
                            var_t1 += 1;
                        } while (var_v1_3 != 0);
                        var_a1 += 2;
                    } else {
                        goto block_28;
                    }
                }
            } else {
block_27:
                var_t1 += 1;
                *(u16 *)(((temp_v0 & 0xFFFF) * 2) + arg0) = var_v1;
block_28:
                var_a1 += 2;
            }
            var_v1 = *var_a1;
            var_t0 = var_v1 & 0xFFFF;
        } while (var_v1 != 0);
    }
    *(u16 *)(((var_t1 & 0xFFFF) * 2) + arg0) = 0;
    return arg0;
}
