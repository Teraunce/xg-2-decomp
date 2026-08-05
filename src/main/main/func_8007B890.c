#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
f32 func_80079DB8(f32);                             /* extern */
f32 func_8007B5A8(f32);                             /* extern */
extern f32 D_80189818;

void func_8007B890(f32 arg1, Unk *arg0, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 sp40;
    f32 sp3C;
    f32 sp34;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fv0;

    temp_fa1 = arg1 * (s32)M2C_ERROR(/* Read from unset register $f0 */);
    arg2 = temp_fa1;
    arg1 = (f32)(s32)arg0;
    D_80189818 = (s32)M2C_ERROR(/* Read from unset register $f0 */);
    arg3 = (s32)M2C_ERROR(/* Read from unset register $f16 */) * (s32)M2C_ERROR(/* Read from unset register $f0 */);
    temp_fs0 = func_8007B5A8(temp_fa1);
    temp_fs1 = func_80079DB8(arg1);
    sp40 = func_8007B5A8(arg2);
    sp34 = func_80079DB8(arg2);
    sp3C = func_8007B5A8(arg3);
    temp_fv0 = func_80079DB8(arg3);
    arg0->unk0 = (f32) (sp34 * temp_fv0 * arg4);
    arg0->unk4 = (f32) (sp34 * sp3C * arg4);
    arg0->unkC = 0.0f;
    arg0->unk8 = (f32) (-sp40 * arg4);
    arg0->unk1C = 0.0f;
    temp_fa0 = temp_fs0 * sp40;
    arg0->unk10 = (f32) (((temp_fa0 * temp_fv0) - (temp_fs1 * sp3C)) * arg4);
    arg0->unk14 = (f32) (((temp_fa0 * sp3C) + (temp_fs1 * temp_fv0)) * arg4);
    arg0->unk18 = (f32) (temp_fs0 * sp34 * arg4);
    arg0->unk2C = 0.0f;
    temp_fa0_2 = temp_fs1 * sp40;
    arg0->unk20 = (f32) (((temp_fa0_2 * temp_fv0) + (temp_fs0 * sp3C)) * arg4);
    arg0->unk24 = (f32) (((temp_fa0_2 * sp3C) - (temp_fs0 * temp_fv0)) * arg4);
    arg0->unk28 = (f32) (temp_fs1 * sp34 * arg4);
    arg0->unk30 = arg5;
    arg0->unk34 = arg6;
    arg0->unk3C = 1.0f;
    arg0->unk38 = arg7;
}
