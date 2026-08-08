#include "ultra64.h"
char *audioAdpcmDecodeCmd(Unk *arg0, s16 *arg1, s32 arg2, s32 arg3, Unk *arg4) {
    char *sp4C;
    s32 sp48;
    s32 sp2C;
    s16 var_t0;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a3;
    s32 temp_s1;
    s32 temp_t0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_6;
    s32 temp_v0_8;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_a3;
    s32 var_s1;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s3;
    s32 var_v1;
    u32 temp_v0_5;
    u32 temp_v1;
    Unk *temp_t1;
    Unk *temp_t1_2;
    Unk *temp_t1_3;
    Unk *temp_v0_7;
    Unk *var_t1;

    var_a3 = arg3;
    var_s3 = arg2;
    var_t1 = arg4;
    if (arg2 == 0) {
        return arg4;
    }
    temp_v0 = arg0->unk38;
    temp_v1 = arg0->unk20;
    if ((temp_v1 < (u32) (temp_v0 + var_s3)) && (var_s2 = temp_v1 - temp_v0, (arg0->unk24 != 0))) {
        var_s1 = var_s2 * 2;
        if (var_s2 > 0) {
            temp_v0_2 = ((s32(*)())(s32)arg0->unk30)(arg0->unk44, var_s1, arg0->unk34);
            var_a2 = temp_v0_2 & 7;
            var_a3 = var_s1 + var_a2;
            temp_t1 = arg4 + 8;
            arg4->unk4 = (s32) (((var_a3 - (var_a3 & 7)) + 8) & 0xFFFF);
            arg4->unk0 = (s32) ((*arg1 & 0xFFFF) | 0x08000000);
            temp_t1->unk4 = (s32) (temp_v0_2 - var_a2);
            arg4->unk8 = 0x04000000;
            var_t1 = temp_t1 + 8;
        } else {
            var_a2 = 0;
        }
        *arg1 += var_a2;
        temp_v0_3 = arg0->unk1C;
        arg0->unk38 = temp_v0_3;
        arg0->unk44 = (s32) (((Unk *)arg0->unk28)->unk0 + (temp_v0_3 * 2));
        var_t0 = *arg1;
        if (var_s2 < var_s3) {
            do {
                temp_v0_4 = arg0->unk24;
                temp_t0 = var_t0 + var_s1;
                var_s3 -= var_s2;
                if ((temp_v0_4 != -1) && (temp_v0_4 != 0)) {
                    arg0->unk24 = (s32) (temp_v0_4 - 1);
                }
                temp_v0_5 = arg0->unk20 - arg0->unk1C;
                var_s2 = (s32) temp_v0_5;
                if ((u32) var_s3 < temp_v0_5) {
                    var_s2 = var_s3;
                }
                sp4C = var_t1;
                sp2C = temp_t0;
                var_s1 = var_s2 * 2;
                temp_v0_6 = ((s32(*)())(s32)arg0->unk30)(arg0->unk44, var_s1, arg0->unk34, var_a3);
                var_t0 = (s16) temp_t0;
                temp_a1 = temp_v0_6 & 7;
                temp_v1_2 = var_t0 & 7;
                var_a3 = var_s1 + temp_a1;
                if (temp_v1_2 != 0) {
                    var_a2_2 = 8 - temp_v1_2;
                } else {
                    var_a2_2 = 0;
                }
                temp_t1_2 = var_t1 + 8;
                var_t1->unk4 = (s32) (((var_a3 - (var_a3 & 7)) + 8) & 0xFFFF);
                var_t1->unk0 = (s32) (((var_t0 + var_a2_2) & 0xFFFF) | 0x08000000);
                var_t1->unk8 = 0x04000000;
                temp_t1_2->unk4 = (s32) (temp_v0_6 - temp_a1);
                var_t1 = temp_t1_2 + 8;
                if ((temp_a1 != 0) || (var_a2_2 != 0)) {
                    temp_t1_2->unk8 = (s32) (((var_t0 + temp_a1 + var_a2_2) & 0xFFFFFF) | 0x0A000000);
                    var_t1->unk4 = (s32) ((var_t0 << 0x10) | (var_s1 & 0xFFFF));
                    var_t1 += 8;
                }
            } while (var_s2 < var_s3);
        }
        arg0->unk38 = (s32) (arg0->unk38 + var_s3);
        arg0->unk44 = (s32) (arg0->unk44 + (var_s3 * 2));
    } else {
        temp_v0_7 = arg0->unk28;
        temp_a0 = arg0->unk44;
        temp_s1 = var_s3 * 2;
        temp_v1_3 = temp_a0 + temp_s1;
        var_s2_2 = (temp_v1_3 - temp_v0_7->unk0) - temp_v0_7->unk4;
        if (var_s2_2 < 0) {
            var_s2_2 = 0;
        }
        if (temp_s1 < var_s2_2) {
            var_s2_2 = temp_s1;
        }
        if (var_s2_2 < temp_s1) {
            var_a2_3 = 0;
            if (var_s3 > 0) {
                temp_a1_2 = temp_s1 - var_s2_2;
                sp48 = temp_a1_2;
                temp_v0_8 = ((s32(*)())(s32)arg0->unk30)(temp_a0, temp_a1_2, arg0->unk34);
                var_a2_3 = temp_v0_8 & 7;
                temp_a3 = sp48 + var_a2_3;
                temp_t1_3 = arg4 + 8;
                arg4->unk4 = (s32) (((temp_a3 - (temp_a3 & 7)) + 8) & 0xFFFF);
                arg4->unk0 = (s32) ((*arg1 & 0xFFFF) | 0x08000000);
                temp_t1_3->unk4 = (s32) (temp_v0_8 - var_a2_3);
                arg4->unk8 = 0x04000000;
                var_t1 = temp_t1_3 + 8;
            }
            *arg1 += var_a2_3;
            arg0->unk38 = (s32) (arg0->unk38 + var_s3);
            arg0->unk44 = (s32) (arg0->unk44 + temp_s1);
        } else {
            arg0->unk44 = temp_v1_3;
        }
        var_v1 = temp_s1 - var_s2_2;
        if (var_s2_2 != 0) {
            if (var_v1 < 0) {
                var_v1 = 0;
            }
            var_t1->unk0 = (s32) (((*arg1 + var_v1) & 0xFFFFFF) | 0x02000000);
            var_t1->unk4 = var_s2_2;
            var_t1 += 8;
        }
    }
    return var_t1;
}
