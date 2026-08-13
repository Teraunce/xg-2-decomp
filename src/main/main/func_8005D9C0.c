#include "ultra64.h"
#include "entity.h"
#include "render.h"
s32 func_800567DC(f32 *, f32 *, f32 *);               /* extern */
void vec3Cross(Unk*, Unk*, Unk*);               /* extern */
extern f32 gSfxSpatialImplA;
extern f32 gSfxSpatialImplB;
extern f32 gSfxSpatialImplC;
extern f32 gSfxSpatialImplD;
extern f32 gSfxSpatialImplE;
extern f32 gSfxSpatialImplF;
extern f32 gSfxDistMax;
extern f32 gSfxDistClamp4;
extern f32 gSfxDistClamp2;
extern f32 gSfxDistClamp5;
extern f32 gSfxSpatialImplG;
extern f32 gSfxDistClamp3;
extern f32 gSfxSpatialImplH;
extern Entity gEntityPool[];
extern s32 gGameState;
extern s32 gSfxGameParams;
extern s32 gRaceCtrlCount;

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
    Entity *var_s1;
    Entity *var_v1;
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
    RenderNode *temp_v0;
    RenderNode *temp_v0_2;
    RenderNode *temp_v0_3;

    var_s1 = (Entity *)arg10;
    var_ft4 = gSfxSpatialImplA;
    var_s2 = 0;
    var_a2 = 1;
    if (var_s1 != NULL) {
        temp_v0 = var_s1->renderObj;
        var_s2 = var_s1 - gEntityPool;
        if (temp_v0 != NULL) {
            sp10 = temp_v0->posX - arg0;
            sp14 = temp_v0->posY - arg1;
            var_fv0 = temp_v0->posZ - arg3;
        } else {
            sp10 = var_s1->eyeX - arg0;
            sp14 = var_s1->eyeY - arg1;
            var_fv0 = var_s1->eyeZ - arg3;
        }
        sp18 = var_fv0;
        temp_fv1 = fabsf(sp10) + fabsf(sp14) + fabsf(var_fv0);
        if ((var_s1->raceSlotType != 4) && !(gSfxSpatialImplB < temp_fv1)) {
            temp_v0_2 = var_s1->renderObj;
            if (temp_v0_2 == NULL) {
                var_a2 = 0;
            } else if (temp_v0_2->active == 0) {
                var_a2 = 0;
            } else {
                goto block_12;
            }
        } else {
block_12:
            temp_fv0 = var_s1->eyeX - arg0;
            sp10 = temp_fv0;
            temp_fv0_2 = var_s1->eyeY - arg1;
            sp14 = temp_fv0_2;
            temp_fv0_3 = var_s1->eyeZ - arg3;
            sp18 = temp_fv0_3;
            var_ft4 = sqrtf((temp_fv0 * temp_fv0) + (temp_fv0_2 * temp_fv0_2) + (temp_fv0_3 * temp_fv0_3));
        }
    } else {
        var_a0 = 0;
        if ((s32) var_s1 < gRaceCtrlCount) {
            var_v1 = gEntityPool;
            do {
                temp_ft3 = var_v1->atX - arg0;
                temp_ft2 = var_v1->atY - arg1;
                temp_ft1 = var_v1->atZ - arg3;
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
                var_v1++;
            } while (var_a0 < gRaceCtrlCount);
        }
    }
    if (var_a2 != 0) {
        if ((var_s1 == NULL) || (gSfxSpatialImplC <= var_ft4)) {
            *arg7 = 0;
            return 0;
        }
        temp_fs0 = gSfxSpatialImplE;
        *arg7 = (s32) ((f32) *arg7 * (temp_fs0 - (var_ft4 * gSfxSpatialImplD)));
        sp20 = var_s1->unkC0 - arg3;   /* SFX spatial ref X */
        sp24 = var_s1->unkC4 - arg4;   /* SFX spatial ref Y */
        sp28 = var_s1->unkC8 - arg5;   /* SFX spatial ref Z */
        func_800567DC(&sp10, &sp14, &sp18);
        temp_fv1_3 = ((sp10 * sp20) + (sp14 * sp24) + (sp18 * sp28)) * gSfxSpatialImplF;
        var_fv0_2 = temp_fs0 - temp_fv1_3;
        if (!(var_fv0_2 <= gSfxDistMax)) {
            var_fv0_2 = gSfxDistMax;
        }
        if (!(var_fv0_2 <= gSfxDistClamp4)) {
            var_fv1 = temp_fs0 - temp_fv1_3;
            if (!(var_fv1 <= gSfxDistMax)) {
                var_fv1 = gSfxDistMax;
            }
        } else {
            var_fv1 = gSfxDistClamp4;
        }
        temp_ft2_2 = *arg6;
        var_fv0_3 = temp_ft2_2 * var_fv1;
        if (!(var_fv0_3 <= gSfxDistClamp2)) {
            var_fv0_3 = gSfxDistClamp2;
        }
        if (var_fv0_3 <= gSfxDistClamp5) {
            var_fv1_2 = gSfxDistClamp5;
        } else {
            var_fv1_2 = temp_ft2_2 * var_fv1;
            if (!(var_fv1_2 <= gSfxDistClamp2)) {
                var_fv1_2 = gSfxDistClamp2;
            }
        }
        *arg6 = var_fv1_2;
        sp30 = var_s1->atX - var_s1->eyeX;
        sp34 = var_s1->atY - var_s1->eyeY;
        sp38 = var_s1->atZ - var_s1->eyeZ;
        sp40 = var_s1->upX;
        sp44 = var_s1->upY;
        sp48 = var_s1->upZ;
        vec3Cross(&sp30, &sp40, &sp50);
        func_800567DC(&sp50, &sp54, &sp58);
        var_ft1 = (sp10 * sp50) + (sp14 * sp54) + (sp18 * sp58);
        goto block_38;
    }
    var_ft1 = 0.0f;
block_38:
    temp_ft2_3 = (f32) *arg8 - (var_ft1 * gSfxSpatialImplG);
    temp_fv1_4 = (f32) *(var_s2 + (gGameState * 4) + &gSfxGameParams);
    var_ft0 = temp_ft2_3 + temp_fv1_4;
    if (!(var_ft0 <= gSfxDistClamp3)) {
        var_ft0 = gSfxDistClamp3;
    }
    var_v0 = 0;
    if (!(var_ft0 <= 0.0f)) {
        var_fv1_3 = temp_ft2_3 + temp_fv1_4;
        if (!(var_fv1_3 <= gSfxDistClamp3)) {
            var_fv1_3 = gSfxDistClamp3;
        }
        var_v0 = (s32) var_fv1_3;
    }
    *arg8 = var_v0;
    *arg9 = var_s1->raceSlotCount / 3;
    temp_v0_3 = var_s1->renderObj;
    if (temp_v0_3 != NULL) {
        *arg7 = (s32) ((f32) *arg7 * (gSfxSpatialImplH - temp_v0_3->speed));
    }
    return 1;
}
