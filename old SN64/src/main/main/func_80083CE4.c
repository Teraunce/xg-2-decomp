#include "ultra64.h"
char *func_80083BB8(s32, s32, s32, s16 *);          /* extern */

char *func_80083CE4(Unk *arg0, s16 *arg1, s32 arg2, s32 arg3, Unk *arg4) {
    s32 sp90;
    s32 sp8C;                                       /* compiler-managed */
    s32 sp88;
    s32 sp80;
    s32 sp7C;
    s32 sp5C;
    s32 sp50;
    s16 temp_a3;
    s16 var_a2_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_t3;
    s32 temp_t4;
    s32 temp_t7;
    s32 temp_t8;
    s32 temp_t9;
    s32 temp_v0_2;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_fp;
    s32 var_t1;
    s32 var_t1_2;
    s32 var_t5;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    u32 temp_a0;
    u32 temp_t0;
    u32 temp_v0;
    u32 temp_v0_3;
    u32 temp_v1;
    u32 var_a1_3;
    Unk *temp_v0_4;
    Unk *temp_v0_5;
    char *temp_v0_6;
    Unk *var_t2;
    char *var_t2_2;

    var_t5 = 0;
    if (arg2 == 0) {
        return arg4;
    }
    arg4->unk0 = (s32) ((arg0->unk2C & 0xFFFFFF) | 0x0B000000);
    var_t2 = arg4 + 8;
    var_a2 = 0;
    arg4->unk4 = (s32) ((((Unk *)arg0->unk28)->unk10 + 8) & 0x1FFFFFFF);
    temp_v1 = arg0->unk38;
    temp_a0 = arg0->unk20;
    var_a1 = arg2;
    var_t1 = temp_a0 < (u32) (temp_v1 + arg2);
    if (var_t1 != 0) {
        var_t1 = arg0->unk24 != 0;
    }
    if (var_t1 != 0) {
        var_a1 = temp_a0 - temp_v1;
    }
    temp_v1_2 = arg0->unk3C;
    if (temp_v1_2 != 0) {
        var_a2 = 0x10 - temp_v1_2;
    }
    var_a0 = var_a1 - var_a2;
    if (var_a0 < 0) {
        var_a0 = 0;
    }
    if (var_t1 != 0) {
        temp_t8 = (s32) (var_a0 + 0xF) >> 4;
        temp_t1 = temp_t8 * 9;
        sp5C = temp_t1;
        sp8C = var_a1;
        var_fp = temp_t8;
        temp_v1_3 = arg0->unk3C;
        var_a1_2 = var_a1;
        var_t1_2 = temp_t1;
        var_t2_2 = func_80083BB8(var_a0, var_a1, var_a2, arg1);
        if (temp_v1_3 != 0) {
            *arg1 += temp_v1_3 * 2;
        } else {
            *arg1 += 0x20;
        }
        temp_v0 = arg0->unk1C;
        arg0->unk3C = (s32) (temp_v0 & 0xF);
        arg0->unk44 = (s32) (((Unk *)arg0->unk28)->unk0 + ((temp_v0 >> 4) * 9) + 9);
        arg0->unk38 = temp_v0;
        var_a2_2 = *arg1;
        if (var_a1_2 < arg2) {
            var_v1 = var_a1_2 * 2;
            do {
                temp_v0_2 = arg0->unk24;
                temp_t0 = arg2 - var_a1_2;
                temp_a3 = (((var_fp + 1) << 5) + var_a2_2) & ~0x1F;
                temp_a2 = var_a2_2 + var_v1;
                if ((temp_v0_2 != -1) && (temp_v0_2 != 0)) {
                    arg0->unk24 = (s32) (temp_v0_2 - 1);
                }
                temp_v0_3 = arg0->unk20 - arg0->unk1C;
                if (temp_t0 < temp_v0_3) {
                    var_a1_3 = temp_t0;
                } else {
                    var_a1_3 = temp_v0_3;
                }
                var_a0_2 = (var_a1_3 + arg0->unk3C) - 0x10;
                if (var_a0_2 < 0) {
                    var_a0_2 = 0;
                }
                temp_t9 = (s32) (var_a0_2 + 0xF) >> 4;
                temp_t1_2 = temp_t9 * 9;
                sp5C = temp_t1_2;
                var_fp = temp_t9;
                arg2 = (s32) temp_t0;
                sp88 = (s32) temp_a3;
                sp80 = temp_a2;
                sp8C = var_a1_3;
                temp_v0_4 = func_80083BB8(var_a0_2, (s32) var_a1_3, temp_a2, (s16 *) temp_a3);
                var_a1_2 = (s32) var_a1_3;
                var_a2_2 = (s16) temp_a2;
                var_t1_2 = temp_t1_2;
                var_v1 = var_a1_2 * 2;
                temp_v0_4->unk0 = (s32) ((((arg0->unk3C * 2) + temp_a3) & 0xFFFFFF) | 0x0A000000);
                temp_v0_4->unk4 = (s32) ((var_a2_2 << 0x10) | (var_v1 & 0xFFFF));
                var_t2_2 = temp_v0_4 + 8;
            } while (var_a1_2 < arg2);
        }
        arg0->unk3C = (s32) ((arg0->unk3C + arg2) & 0xF);
        arg0->unk38 = (u32) (arg0->unk38 + arg2);
        arg0->unk44 = (s32) (arg0->unk44 + var_t1_2);
        return var_t2_2;
    }
    temp_v0_5 = arg0->unk28;
    temp_t7 = (s32) (var_a0 + 0xF) >> 4;
    temp_t1_3 = temp_t7 * 9;
    temp_t3 = arg0->unk44 + temp_t1_3;
    var_v1_2 = (temp_t3 - temp_v0_5->unk0) - temp_v0_5->unk4;
    temp_a1 = temp_t7 * 0x10;
    if (var_v1_2 < 0) {
        var_v1_2 = 0;
    }
    var_a0_3 = (var_v1_2 / 9) * 0x10;
    temp_t4 = temp_a1 + var_a2;
    if (temp_t4 < var_a0_3) {
        var_a0_3 = temp_t4;
    }
    if ((var_a0_3 - (var_a0_3 & 0xF)) < arg2) {
        sp7C = 1;
        sp50 = temp_t4;
        sp5C = temp_t1_3;
        sp90 = var_a0_3;
        temp_v0_6 = func_80083BB8(var_a0_3, temp_a1, temp_t1_3 - var_v1_2, arg1);
        temp_v1_4 = arg0->unk3C;
        var_t5 = 1;
        var_t2 = temp_v0_6;
        if (temp_v1_4 != 0) {
            *arg1 += temp_v1_4 * 2;
        } else {
            *arg1 += 0x20;
        }
        arg0->unk3C = (s32) ((arg0->unk3C + arg2) & 0xF);
        arg0->unk38 = (u32) (arg0->unk38 + arg2);
        arg0->unk44 = (s32) (arg0->unk44 + temp_t1_3);
    } else {
        arg0->unk3C = 0;
        arg0->unk44 = temp_t3;
    }
    if (var_a0_3 != 0) {
        arg0->unk3C = 0;
        if (var_t5 != 0) {
            var_v1_3 = (temp_t4 - var_a0_3) * 2;
        } else {
            var_v1_3 = 0;
        }
        var_t2->unk4 = (s32) (var_a0_3 * 2);
        var_t2->unk0 = (s32) (((*arg1 + var_v1_3) & 0xFFFFFF) | 0x02000000);
        var_t2 += 8;
    }
    return var_t2;
}

s32 func_80084188(Unk *arg0, s32 arg1, s32 arg2) {
    if (arg1 == 2) {
        *(s32*)(s32)(arg0->unk1C + (arg0->unk14 * 4)) = arg2;
        arg0->unk14 = (s32) (arg0->unk14 + 1);
    }
    return 0;
}
