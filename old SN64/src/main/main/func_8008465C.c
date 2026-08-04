#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
s32 func_8007D688(u32);             /* extern */
s16 func_8008448C(f64, s32);                             /* extern */
extern s32 D_80095470;
extern s32 D_8009556E;

char *func_8008465C(void) {
    s16 *saved_reg_s0 = (s16*)M2C_ERROR(/* saved s0 */);
    Unk *saved_reg_s3 = M2C_ERROR(/* saved s3 */);
    s32 saved_reg_s5 = (s32)M2C_ERROR(/* saved s5 */);
    s16 *saved_reg_s6 = (s16*)M2C_ERROR(/* saved s6 */);
    s16 temp_v1;
    s32 temp_s7;
    s32 var_v0;
    Unk *temp_a0;
    Unk *temp_s4;
    Unk *temp_s4_2;
    Unk *temp_s4_3;
    Unk *temp_s4_4;
    Unk *temp_s4_5;
    char *temp_s4_6;
    Unk *temp_v0;
    Unk *var_s0;
    char *var_s4;

    temp_a0 = saved_reg_s3->unk0;
    if ((saved_reg_s3->unk48 != 1) || (saved_reg_s5 == 0)) {
        return (s32)M2C_ERROR(/* Read from unset register $t0 */);
    }
    temp_v0 = ((s32(*)())(s32)temp_a0->unk4)(temp_a0, saved_reg_s6, saved_reg_s5, (s32)M2C_ERROR(/* Read from unset register $t0 */));
    temp_s7 = saved_reg_s5 * 2;
    temp_v0->unk0 = (s32) ((*saved_reg_s6 & 0xFFFF) | 0x08000000);
    temp_s4 = temp_v0 + 0x10;
    temp_v0->unk4 = (s32) (((*saved_reg_s0 + 0x440) << 0x10) | (temp_s7 & 0xFFFF));
    temp_v0->unk8 = (s32) (((*saved_reg_s0 + 0x580) & 0xFFFF) | 0x08080000);
    temp_v1 = *saved_reg_s0;
    var_s0 = temp_s4;
    temp_v0->unkC = (s32) (((temp_v1 + 0x800) & 0xFFFF) | ((temp_v1 + 0x6C0) << 0x10));
    if (saved_reg_s3->unk38 != 0) {
        saved_reg_s3->unk38 = 0;
        saved_reg_s3->unk28 = (s16) ((s32) (*(&D_80095470 + (saved_reg_s3->unk18 * 2)) * saved_reg_s3->unk1A) >> 0xF);
        saved_reg_s3->unk26 = func_8008448C((f64)saved_reg_s3->unk28, saved_reg_s3->unk34);
        saved_reg_s3->unk2E = (s16) ((s32) (*(&D_8009556E + -(saved_reg_s3->unk18 * 2)) * saved_reg_s3->unk1A) >> 0xF);
        saved_reg_s3->unk2C = func_8008448C((f64)saved_reg_s3->unk2E, saved_reg_s3->unk34);
        temp_v0->unk10 = (s32) ((saved_reg_s3->unk1C & 0xFFFF) | 0x09060000);
        temp_s4->unk4 = 0;
        temp_s4_2 = temp_s4 + 8;
        temp_s4->unk8 = (s32) ((saved_reg_s3->unk1E & 0xFFFF) | 0x09040000);
        temp_s4_2->unk4 = 0;
        temp_s4_3 = temp_s4_2 + 8;
        temp_s4_2->unk8 = (s32) ((saved_reg_s3->unk28 & 0xFFFF) | 0x09020000);
        temp_s4_4 = temp_s4_3 + 8;
        temp_s4_3->unk4 = (s32) ((saved_reg_s3->unk26 << 0x10) | saved_reg_s3->unk24);
        temp_s4_3->unk8 = (s32) ((saved_reg_s3->unk2E & 0xFFFF) | 0x09000000);
        temp_s4_5 = temp_s4_4 + 8;
        temp_s4_4->unk4 = (s32) ((saved_reg_s3->unk2C << 0x10) | saved_reg_s3->unk2A);
        temp_s4_4->unk8 = (s32) ((saved_reg_s3->unk20 & 0xFFFF) | 0x09080000);
        temp_s4_6 = temp_s4_5 + 8;
        var_s0 = temp_s4_6;
        temp_s4_5->unk4 = (s32) (saved_reg_s3->unk22 & 0xFFFF);
        temp_s4_5->unk8 = 0x03090000;
        var_s4 = temp_s4_6 + 8;
        var_v0 = func_8007D688((s32)saved_reg_s3->unk14);
    } else {
        temp_v0->unk10 = 0x03080000;
        var_s4 = temp_s4 + 8;
        var_v0 = func_8007D688((s32)saved_reg_s3->unk14);
    }
    var_s0->unk4 = var_v0;
    *saved_reg_s6 += temp_s7;
    saved_reg_s3->unk30 = (s32) (saved_reg_s3->unk30 + saved_reg_s5);
    return var_s4;
}

f32 func_800848F4(s32 arg0, s32 arg1, s32 arg2) {
    s32 saved_reg_s0;
    s32 saved_reg_s3;
    s32 saved_reg_s5;
    s32 saved_reg_s6;
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_a2;
    s32 temp_t8;
    s32 temp_t9;
    s32 var_a0;
    s32 var_v0;
    s32 arg3;

    temp_a2 = arg2;
    arg2 = arg1;
    arg3 = temp_a2;
    temp_t9 = arg0 >> 3;
    var_a0 = temp_t9;
    if (temp_t9 == 0) {
        return arg0;
    }
    var_v0 = 0;
    var_fv1 = 1.0f;
    var_fv0 = ((f32) ((s16) arg1 << 0x10) + (f32) (temp_a2 & 0xFFFF)) / 65536.0f;
loop_3:
    temp_t8 = var_a0 >> 1;
    if (var_a0 & 1) {
        var_fv1 *= var_fv0;
    }
    var_a0 = temp_t8;
    if (temp_t8 != 0) {
        var_v0 += 1;
        var_fv0 *= var_fv0;
        if (var_v0 != 0x20) {
            goto loop_3;
        }
    }
    return arg0 * var_fv1;
}
