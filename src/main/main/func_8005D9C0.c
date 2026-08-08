#include "ultra64.h"
s32 func_800567DC(f32 *, f32 *, f32 *);               /* extern */
void vec3Cross(Unk*, Unk*, Unk*);               /* extern */
extern f32 D_8004BE4C;
extern f32 D_8004BE50;
extern f32 D_8004BE54;
extern f32 D_8004BE58;
extern f32 D_8004BE5C;
extern f32 D_8004BE60;
extern f32 D_8004BE64;
extern f32 D_8004BE68;
extern f32 D_8004BE6C;
extern f32 D_8004BE70;
extern f32 D_8004BE74;
extern f32 D_8004BE78;
extern f32 D_8004BE7C;
extern s32 gEntityPool;
extern s32 gGameState;
extern s32 D_80092A94;
extern s32 D_8017C950;

s32 sfxComputeSpatialImpl(f32 arg0, f32 arg1, f32 arg3, f32 arg4, f32 arg5, f32 *arg6, s32 *arg7, s32 *arg8, s32 *arg9, char *arg10) {
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    Unk *var_s1;
    Unk *var_v1;
    f32 temp_fs0;
    f32 temp_ft1;
    f32 temp_ft2;
    f32 temp_ft2_2;
    f32 temp_ft2_3;
    f32 temp_ft3;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 var_ft0;
    f32 var_ft1;
    f32 var_ft4;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv0_3;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;
    s32 var_a0;
    s32 var_a2;
    s32 var_s2;
    s32 var_v0;
    Unk *temp_v0;
    Unk *temp_v0_2;
    Unk *temp_v0_3;

    var_s1 = arg10;
    var_ft4 = D_8004BE4C;
    var_s2 = 0;
    var_a2 = 1;
    if (var_s1 != NULL) {
        temp_v0 = var_s1->unkD0;
        var_s2 = ((char*)var_s1 - (char*)&gEntityPool) / 552;
        if (temp_v0 != NULL) {
            sp10 = temp_v0->unk0 - arg0;
            sp14 = ((Unk *)var_s1->unkD0)->unk4 - arg1;
            var_fv0 = ((Unk *)var_s1->unkD0)->unk8 - arg3;
        } else {
            sp10 = var_s1->unkC - arg0;
            sp14 = var_s1->unk10 - arg1;
            var_fv0 = var_s1->unk14 - arg3;
        }
        sp18 = var_fv0;
        temp_fv1 = fabsf(sp10) + fabsf(sp14) + fabsf(var_fv0);
        if ((var_s1->unk1DC != 4) && !(D_8004BE50 < temp_fv1)) {
            temp_v0_2 = var_s1->unkD0;
            if (temp_v0_2 == NULL) {
                var_a2 = 0;
            } else if (temp_v0_2->unk450 == 0) {
                var_a2 = 0;
            } else {
                goto block_12;
            }
        } else {
block_12:
            temp_fv0 = var_s1->unk0 - arg0;
            sp10 = temp_fv0;
            temp_fv0_2 = var_s1->unk4 - arg1;
            sp14 = temp_fv0_2;
            temp_fv0_3 = var_s1->unk8 - arg3;
            sp18 = temp_fv0_3;
            var_ft4 = sqrtf((temp_fv0 * temp_fv0) + (temp_fv0_2 * temp_fv0_2) + (temp_fv0_3 * temp_fv0_3));
        }
    } else {
        var_a0 = 0;
        if ((s32) var_s1 < D_8017C950) {
            var_v1 = &gEntityPool;
            do {
                temp_ft3 = var_v1->unkC - arg0;
                temp_ft2 = var_v1->unk10 - arg1;
                temp_ft1 = var_v1->unk14 - arg3;
                temp_fv1_2 = sqrtf((temp_ft3 * temp_ft3) + (temp_ft2 * temp_ft2) + (temp_ft1 * temp_ft1));
                if (temp_fv1_2 < var_ft4) {
                    var_s1 = var_v1;
                    var_s2 = var_a0;
                    var_ft4 = temp_fv1_2;
                    sp10 = temp_ft3;
                    sp14 = temp_ft2;
                    sp18 = temp_ft1;
                }
                var_a0 += 1;
                var_v1 += 0x228;
            } while (var_a0 < D_8017C950);
        }
    }
    if (var_a2 != 0) {
        if ((var_s1 == NULL) || (D_8004BE54 <= var_ft4)) {
            *arg7 = 0;
            return 0;
        }
        temp_fs0 = D_8004BE5C;
        *arg7 = (s32) ((f32) *arg7 * (temp_fs0 - (var_ft4 * D_8004BE58)));
        sp20 = var_s1->unkC0 - arg3;
        sp24 = var_s1->unkC4 - arg4;
        sp28 = var_s1->unkC8 - arg5;
        func_800567DC(&sp10, &sp14, &sp18);
        temp_fv1_3 = ((sp10 * sp20) + (sp14 * sp24) + (sp18 * sp28)) * D_8004BE60;
        var_fv0_2 = temp_fs0 - temp_fv1_3;
        if (!(var_fv0_2 <= D_8004BE64)) {
            var_fv0_2 = D_8004BE64;
        }
        if (!(var_fv0_2 <= D_8004BE68)) {
            var_fv1 = temp_fs0 - temp_fv1_3;
            if (!(var_fv1 <= D_8004BE64)) {
                var_fv1 = D_8004BE64;
            }
        } else {
            var_fv1 = D_8004BE68;
        }
        temp_ft2_2 = *arg6;
        var_fv0_3 = temp_ft2_2 * var_fv1;
        if (!(var_fv0_3 <= D_8004BE6C)) {
            var_fv0_3 = D_8004BE6C;
        }
        if (var_fv0_3 <= D_8004BE70) {
            var_fv1_2 = D_8004BE70;
        } else {
            var_fv1_2 = temp_ft2_2 * var_fv1;
            if (!(var_fv1_2 <= D_8004BE6C)) {
                var_fv1_2 = D_8004BE6C;
            }
        }
        *arg6 = var_fv1_2;
        sp30 = var_s1->unkC - var_s1->unk0;
        sp34 = var_s1->unk10 - var_s1->unk4;
        sp38 = var_s1->unk14 - var_s1->unk8;
        sp40 = var_s1->unk18;
        sp44 = var_s1->unk1C;
        sp48 = var_s1->unk20;
        vec3Cross(&sp30, &sp40, &sp50);
        func_800567DC(&sp50, &sp54, &sp58);
        var_ft1 = (sp10 * sp50) + (sp14 * sp54) + (sp18 * sp58);
        goto block_38;
    }
    var_ft1 = 0.0f;
block_38:
    temp_ft2_3 = (f32) *arg8 - (var_ft1 * D_8004BE74);
    temp_fv1_4 = (f32) *(var_s2 + (gGameState * 4) + &D_80092A94);
    var_ft0 = temp_ft2_3 + temp_fv1_4;
    if (!(var_ft0 <= D_8004BE78)) {
        var_ft0 = D_8004BE78;
    }
    var_v0 = 0;
    if (!(var_ft0 <= 0.0f)) {
        var_fv1_3 = temp_ft2_3 + temp_fv1_4;
        if (!(var_fv1_3 <= D_8004BE78)) {
            var_fv1_3 = D_8004BE78;
        }
        var_v0 = (s32) var_fv1_3;
    }
    *arg8 = var_v0;
    *arg9 = var_s1->unk218 / 3;
    temp_v0_3 = var_s1->unkD0;
    if (temp_v0_3 != NULL) {
        *arg7 = (s32) ((f32) *arg7 * (D_8004BE7C - temp_v0_3->unk648));
    }
    return 1;
}
