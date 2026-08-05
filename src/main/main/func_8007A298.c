#include "ultra64.h"
f32 func_8007A288(f32);                             /* extern */
void func_8007A858(char *);                         /* extern */
extern f64 D_8004C858;

void func_8007A298(Unk *arg0, Unk *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10) {
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs1_2;
    f32 temp_fs2;
    f32 temp_fs2_2;
    f32 temp_fs3;
    f32 temp_fs3_2;
    f32 temp_fs4;
    f32 temp_fs4_2;
    f32 temp_fs5;
    f32 temp_fs5_2;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f64 temp_fa0;
    f64 temp_fa0_2;
    f64 temp_fa0_3;
    f64 temp_fa0_4;
    f64 temp_fa0_5;
    f64 temp_fa0_6;
    f64 var_fv0;
    f64 var_fv0_2;
    f64 var_fv0_3;
    f64 var_fv0_4;
    f64 var_fv0_5;
    f64 var_fv0_6;

    func_8007A858(arg0);
    temp_fv0 = arg5 - arg2;
    temp_fs1 = arg6 - arg3;
    temp_fs2 = arg7 - arg4;
    temp_fv1 = (f32) (-1.0 / (f64) func_8007A288((temp_fv0 * temp_fv0) + (temp_fs1 * temp_fs1) + (temp_fs2 * temp_fs2)));
    temp_fs0 = temp_fv0 * temp_fv1;
    temp_fs1_2 = temp_fs1 * temp_fv1;
    temp_fs2_2 = temp_fs2 * temp_fv1;
    temp_fs3 = (arg9 * temp_fs2_2) - (arg10 * temp_fs1_2);
    temp_fs4 = (arg10 * temp_fs0) - (arg8 * temp_fs2_2);
    temp_fs5 = (arg8 * temp_fs1_2) - (arg9 * temp_fs0);
    temp_fa1 = (f32) (1.0 / (f64) func_8007A288((temp_fs3 * temp_fs3) + (temp_fs4 * temp_fs4) + (temp_fs5 * temp_fs5)));
    temp_fs3_2 = temp_fs3 * temp_fa1;
    temp_fs4_2 = temp_fs4 * temp_fa1;
    temp_fs5_2 = temp_fs5 * temp_fa1;
    temp_fv1_2 = (temp_fs1_2 * temp_fs5_2) - (temp_fs2_2 * temp_fs4_2);
    arg8 = temp_fv1_2;
    temp_ft4 = (temp_fs2_2 * temp_fs3_2) - (temp_fs0 * temp_fs5_2);
    arg9 = temp_ft4;
    temp_ft5 = (temp_fs0 * temp_fs4_2) - (temp_fs1_2 * temp_fs3_2);
    arg10 = temp_ft5;
    temp_fa1_2 = (f32) (1.0 / (f64) func_8007A288((temp_fv1_2 * temp_fv1_2) + (temp_ft4 * temp_ft4) + (temp_ft5 * temp_ft5)));
    arg8 *= temp_fa1_2;
    arg9 *= temp_fa1_2;
    temp_fa0 = (f64) temp_fs3_2 * 128.0;
    arg10 *= temp_fa1_2;
    if (temp_fa0 < D_8004C858) {
        var_fv0 = temp_fa0;
    } else {
        var_fv0 = D_8004C858;
    }
    temp_fa0_2 = (f64) temp_fs4_2 * 128.0;
    arg1->unk8 = (s8) (s32) var_fv0;
    if (temp_fa0_2 < D_8004C858) {
        var_fv0_2 = temp_fa0_2;
    } else {
        var_fv0_2 = D_8004C858;
    }
    temp_fa0_3 = (f64) temp_fs5_2 * 128.0;
    arg1->unk9 = (s8) (s32) var_fv0_2;
    if (temp_fa0_3 < D_8004C858) {
        var_fv0_3 = temp_fa0_3;
    } else {
        var_fv0_3 = D_8004C858;
    }
    arg1->unkA = (s8) (s32) var_fv0_3;
    temp_fa0_4 = (f64) arg8 * 128.0;
    if (temp_fa0_4 < D_8004C858) {
        var_fv0_4 = temp_fa0_4;
    } else {
        var_fv0_4 = D_8004C858;
    }
    arg1->unk18 = (s8) (s32) var_fv0_4;
    temp_fa0_5 = (f64) arg9 * 128.0;
    if (temp_fa0_5 < D_8004C858) {
        var_fv0_5 = temp_fa0_5;
    } else {
        var_fv0_5 = D_8004C858;
    }
    arg1->unk19 = (s8) (s32) var_fv0_5;
    temp_fa0_6 = (f64) arg10 * 128.0;
    if (temp_fa0_6 < D_8004C858) {
        var_fv0_6 = temp_fa0_6;
    } else {
        var_fv0_6 = D_8004C858;
    }
    arg1->unk0 = 0;
    arg1->unk1 = 0;
    arg1->unk2 = 0;
    arg1->unk3 = 0;
    arg1->unk4 = 0;
    arg1->unk5 = 0;
    arg1->unk6 = 0;
    arg1->unk7 = 0;
    arg1->unk10 = 0;
    arg1->unk11 = 0x80;
    arg1->unk12 = 0;
    arg1->unk13 = 0;
    arg1->unk14 = 0;
    arg1->unk15 = 0x80;
    arg1->unk16 = 0;
    arg1->unk17 = 0;
    arg1->unk1A = (s8) (s32) var_fv0_6;
    arg0->unk0 = temp_fs3_2;
    arg0->unk10 = temp_fs4_2;
    arg0->unk20 = temp_fs5_2;
    arg0->unk8 = temp_fs0;
    arg0->unk18 = temp_fs1_2;
    arg0->unk28 = temp_fs2_2;
    arg0->unk4 = arg8;
    arg0->unk14 = arg9;
    arg0->unk24 = arg10;
    arg0->unk30 = (f32) -((arg2 * temp_fs3_2) + (arg3 * temp_fs4_2) + (arg4 * temp_fs5_2));
    arg0->unk34 = (f32) -((arg2 * arg8) + (arg3 * arg9) + (arg4 * arg10));
    arg0->unkC = 0.0f;
    arg0->unk1C = 0.0f;
    arg0->unk2C = 0.0f;
    arg0->unk3C = 1.0f;
    arg0->unk38 = (f32) -((arg2 * temp_fs0) + (arg3 * temp_fs1_2) + (arg4 * temp_fs2_2));
}
