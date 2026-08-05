#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8007B30C (initial). */

f32 cosf(f32);                             /* extern */
void guMtxIdent(char*);                            /* extern */
void func_8007AC98(f32 *, f32 *, f32 *);               /* extern */
f32 sinf(f32);                             /* extern */
extern f32 D_8004C878;
extern f32 D_801897F8;

void func_8007B178(Unk *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 temp_fa0;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv1_2;

    D_801897F8 = D_8004C878;
    func_8007AC98(&arg2, &arg3, &arg4);
    temp_fa0 = arg1 * D_801897F8;
    arg1 = temp_fa0;
    sp34 = sinf(temp_fa0);
    temp_fv0 = cosf(arg1);
    temp_fv1 = 1.0f - temp_fv0;
    sp30 = temp_fv0;
    temp_ft4 = arg2 * arg3 * temp_fv1;
    sp2C = temp_ft4;
    temp_ft5 = arg3 * arg4 * temp_fv1;
    sp28 = temp_ft5;
    sp24 = arg4 * arg2 * temp_fv1;
    guMtxIdent(arg0);
    temp_fv0_2 = arg2 * arg2;
    arg0->unk0 = (f32) (((1.0f - temp_fv0_2) * sp30) + temp_fv0_2);
    arg0->unk24 = (f32) (temp_ft5 - (arg2 * sp34));
    arg0->unk18 = (f32) ((arg2 * sp34) + temp_ft5);
    temp_fv1_2 = arg3 * arg3;
    arg0->unk14 = (f32) (((1.0f - temp_fv1_2) * sp30) + temp_fv1_2);
    arg0->unk20 = (f32) ((arg3 * sp34) + sp24);
    arg0->unk8 = (f32) (sp24 - (arg3 * sp34));
    temp_fv0_3 = arg4 * arg4;
    arg0->unk28 = (f32) (((1.0f - temp_fv0_3) * sp30) + temp_fv0_3);
    arg0->unk10 = (f32) (temp_ft4 - (arg4 * sp34));
    arg0->unk4 = (f32) ((arg4 * sp34) + temp_ft4);
}

void func_8007B30C(s32 arg1, s32 arg2, s32 arg3) {

}
