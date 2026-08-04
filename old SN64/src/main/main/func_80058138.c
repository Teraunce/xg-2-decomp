#include "ultra64.h"
s32 func_80056788(void *, s32, s32);                  /* extern */
f32 func_80079DB8(f32);                             /* extern */
f32 func_8007B5A8(f32);                             /* extern */
extern f32 D_8004BDC0;

void func_80058138(Unk *arg0, Unk *arg1, f32 arg2) {
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa0_3;
    f32 temp_fa0_4;
    f32 temp_fs0;
    f32 temp_ft0;
    f32 temp_ft0_2;
    f32 temp_ft1;
    f32 temp_ft1_2;
    f32 temp_ft2;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;

    func_80056788(arg1, arg1 + 4, arg1 + 8);
    temp_fs0 = func_8007B5A8(arg2);
    temp_fv0 = func_80079DB8(arg2);
    temp_fv1 = arg1->unk0;
    temp_ft0 = arg1->unk4;
    temp_ft1 = arg1->unk8;
    temp_fa0 = D_8004BDC0 - temp_fv0;
    temp_ft2 = temp_fv1 * temp_ft0 * temp_fa0;
    temp_ft0_2 = temp_ft0 * temp_ft1 * temp_fa0;
    temp_ft1_2 = temp_ft1 * temp_fv1 * temp_fa0;
    temp_fa0_2 = temp_fv1 * temp_fv1;
    arg0->unk0 = (f32) (temp_fa0_2 + (temp_fv0 * (D_8004BDC0 - temp_fa0_2)));
    arg0->unk24 = (f32) (temp_ft0_2 - (arg1->unk0 * temp_fs0));
    arg0->unk18 = (f32) (temp_ft0_2 + (arg1->unk0 * temp_fs0));
    temp_fv1_2 = arg1->unk4;
    temp_fa0_3 = temp_fv1_2 * temp_fv1_2;
    arg0->unk14 = (f32) (temp_fa0_3 + (temp_fv0 * (D_8004BDC0 - temp_fa0_3)));
    arg0->unk20 = (f32) (temp_ft1_2 + (arg1->unk4 * temp_fs0));
    arg0->unk8 = (f32) (temp_ft1_2 - (arg1->unk4 * temp_fs0));
    temp_fv1_3 = arg1->unk8;
    temp_fa0_4 = temp_fv1_3 * temp_fv1_3;
    arg0->unk28 = (f32) (temp_fa0_4 + (temp_fv0 * (D_8004BDC0 - temp_fa0_4)));
    arg0->unk10 = (f32) (temp_ft2 - (arg1->unk8 * temp_fs0));
    arg0->unkC = 0;
    arg0->unk1C = 0;
    arg0->unk2C = 0;
    arg0->unk3C = (f32) D_8004BDC0;
    arg0->unk30 = 0;
    arg0->unk34 = 0;
    arg0->unk38 = 0;
    arg0->unk4 = (f32) (temp_ft2 + (arg1->unk8 * temp_fs0));
}
