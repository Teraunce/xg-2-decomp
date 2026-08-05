#include "ultra64.h"
void safeCopy(u32, u32, u32);                /* extern */
extern s32 D_8017CE08;
extern s32 D_8017D2F8;
extern s32 D_8017DA58;
extern s32 D_8017DA5A;

void func_8005AFC4(void) {
    s16 *temp_a1;
    s16 *temp_s0_3;
    s16 *temp_s2;
    s16 temp_s0;
    s16 temp_v0;
    s16 temp_v0_3;
    s16 temp_v1_3;
    s16 temp_v1_5;
    s16 var_s3;
    s16 var_s3_2;
    s16 var_s3_3;
    s16 var_s4_2;
    s16 var_v0_2;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_s0;
    s32 var_s4;
    s32 var_v0;
    u32 temp_v1_4;

    var_s4 = 0;
    var_s3 = 0;
    var_v0 = 0 << 0x10;
    do {
        temp_a0 = var_v0 >> 0xF;
        temp_a1 = temp_a0 + &D_8017DA58;
        var_v0_2 = var_s3 + 1;
        if (*temp_a1 >= 0x273) {
            temp_v1 = var_s4 << 0x10;
            var_s4 += 1;
            temp_v1_2 = temp_v1 >> 0xF;
            *(temp_v1_2 + &D_8017CE08) = (s16) ((s32) (*(temp_a0 + &D_8017CE08) + 1) >> 1);
            *(temp_v1_2 + &D_8017DA58) = (u16) *temp_a1;
            var_v0_2 = var_s3 + 1;
        }
        var_s3 = var_v0_2;
        var_v0 = var_s3 << 0x10;
    } while (var_v0_2 < 0x273);
    var_s3_2 = 0;
    var_s4_2 = 0x13A;
    do {
        temp_a0_2 = var_s4_2 - 1;
        var_s0 = temp_a0_2;
        temp_v1_3 = *(((s32) (var_s3_2 << 0x10) >> 0xF) + &D_8017CE08) + *(((s32) ((var_s3_2 + 1) << 0x10) >> 0xF) + &D_8017CE08);
        *(((s32) (var_s4_2 << 0x10) >> 0xF) + &D_8017CE08) = temp_v1_3;
        temp_v1_4 = temp_v1_3 & 0xFFFF;
        if (temp_v1_4 < (u16) *(((s32) (temp_a0_2 << 0x10) >> 0xF) + &D_8017CE08)) {
            do {
                temp_v0_2 = var_s0 - 1;
                var_s0 = temp_v0_2;
            } while (temp_v1_4 < (u16) *(((s32) (temp_v0_2 << 0x10) >> 0xF) + &D_8017CE08));
        }
        temp_s0 = var_s0 + 1;
        temp_s0_2 = temp_s0 * 2;
        temp_s2 = temp_s0_2 + &D_8017CE08;
        temp_s1 = ((var_s4_2 - temp_s0) * 2) & 0xFFFF;
        safeCopy(temp_s0_2 + (&D_8017CE08 + 2), temp_s2, temp_s1);
        temp_s0_3 = temp_s0_2 + (&D_8017DA5A - 2);
        *temp_s2 = temp_v1_3;
        safeCopy(temp_s0_2 + &D_8017DA5A, temp_s0_3, temp_s1);
        *temp_s0_3 = var_s3_2;
        temp_v0 = var_s4_2 + 1;
        var_s4_2 = temp_v0;
        var_s3_2 += 2;
    } while (temp_v0 < 0x273);
    var_s3_3 = 0;
    do {
        temp_v1_5 = *(((s32) (var_s3_3 << 0x10) >> 0xF) + &D_8017DA58);
        if (temp_v1_5 < 0x273) {
            *(((temp_v1_5 + 1) * 2) + &D_8017D2F8) = var_s3_3;
        }
        *((temp_v1_5 * 2) + &D_8017D2F8) = var_s3_3;
        temp_v0_3 = var_s3_3 + 1;
        var_s3_3 = temp_v0_3;
    } while (temp_v0_3 < 0x273);
}
