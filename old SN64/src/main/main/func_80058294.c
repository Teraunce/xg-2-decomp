#include "ultra64.h"
s32 func_80056788(f32, f32 *, f32 *);                 /* extern */
void func_80057B74(Unk*, Unk*, Unk*);               /* extern */
extern f32 D_8004BDC4;
extern f32 D_8004BDC8;
extern f32 D_8004BDCC;
extern f32 D_8004BDD0;
extern f32 D_8004BDD4;

void func_80058294(Unk *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 *var_a0;
    f32 temp_ft1;
    f32 temp_ft2;
    f32 temp_ft3;
    f32 var_ft0;
    f32 var_ft0_2;

    temp_ft1 = -arg1;
    sp60 = -arg4;
    sp70 = temp_ft1;
    sp64 = -arg5;
    sp68 = -arg6;
    temp_ft2 = -arg2;
    sp74 = temp_ft2;
    temp_ft3 = -arg3;
    sp78 = temp_ft3;
    if ((temp_ft1 == 0.0f) && (temp_ft2 == 0.0f) && (temp_ft3 == 0.0f)) {
        sp78 = D_8004BDC4;
    }
    if (sp60 == 0.0f) {
        var_a0 = &sp70;
        if (sp64 == 0.0f) {
            if (sp68 == 0.0f) {
                sp64 = D_8004BDC8;
                goto block_8;
            }
        }
    } else {
block_8:
        var_a0 = &sp70;
    }
    func_80057B74(var_a0, &sp60, &sp50);
    var_ft0 = sqrtf((sp50 * sp50) + (sp54 * sp54) + (sp58 * sp58));
    if (var_ft0 == 0.0f) {
        sp68 += D_8004BDCC;
        func_80057B74(&sp60, &sp50, &sp54);
        var_ft0 = sqrtf((sp50 * sp50) + (sp54 * sp54) + (sp58 * sp58));
    }
    sp50 /= var_ft0;
    sp58 /= var_ft0;
    sp54 /= var_ft0;
    func_80057B74(&sp50, &sp60, &sp64);
    var_ft0_2 = sqrtf((sp60 * sp60) + (sp64 * sp64) + (sp68 * sp68));
    if (var_ft0_2 == 0.0f) {
        sp74 += D_8004BDD0;
        func_80057B74(&sp50, &sp60, &sp64);
        var_ft0_2 = sqrtf((sp60 * sp60) + (sp64 * sp64) + (sp68 * sp68));
    }
    sp60 /= var_ft0_2;
    sp68 /= var_ft0_2;
    sp64 /= var_ft0_2;
    func_80056788(sp70, &sp74, &sp78);
    arg0->unk0 = sp50;
    arg0->unk4 = sp54;
    arg0->unkC = 0.0f;
    arg0->unk8 = sp58;
    arg0->unk10 = sp60;
    arg0->unk14 = sp64;
    arg0->unk1C = 0.0f;
    arg0->unk18 = sp68;
    arg0->unk20 = sp70;
    arg0->unk24 = sp74;
    arg0->unk2C = 0.0f;
    arg0->unk30 = 0.0f;
    arg0->unk34 = 0.0f;
    arg0->unk38 = 0.0f;
    arg0->unk3C = (f32) D_8004BDD4;
    arg0->unk28 = sp78;
}
