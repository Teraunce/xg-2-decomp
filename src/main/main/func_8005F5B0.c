#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of gameModeResetGetter (initial). */

void audioQueuePlay(s32, f32, s32, s8, s32);           /* extern */
extern f32 gCamAvgScale;
extern f32 gCamAvgClamp;
extern f32 gSfxListenerScale;
extern Unk gSfxListenerPos;

void audioPlayNormalized(f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    Unk *var_s0;
    f32 temp_fv1;
    f32 var_ft0;
    f32 var_ft1;
    f32 var_ft2;
    f32 var_ft3;
    s32 temp_a0;
    s32 temp_a2;
    s32 var_s1;

    var_ft2 = arg1;
    var_ft0 = arg2;
    var_ft1 = arg3;
    var_ft3 = arg4;
    temp_fv1 = (var_ft2 + var_ft0 + var_ft1 + var_ft3) * gCamAvgScale;
    if (gCamAvgClamp < temp_fv1) {
        var_ft2 /= temp_fv1;
        var_ft0 /= temp_fv1;
        var_ft1 /= temp_fv1;
        var_ft3 /= temp_fv1;
    }
    var_s1 = 0;
    var_s0 = &gSfxListenerPos;
    gSfxListenerPos.unk0 = (s32) (var_ft2 * gSfxListenerScale);
    gSfxListenerPos.unk4 = (s32) (var_ft0 * gSfxListenerScale);
    gSfxListenerPos.unk8 = (s32) (var_ft1 * gSfxListenerScale);
    gSfxListenerPos.unkC = (s32) (var_ft3 * gSfxListenerScale);
    do {
        temp_a0 = var_s0->unk10;
        temp_a2 = var_s0->unk0;
        var_s0 += 4;
        var_s1 += 1;
        audioQueuePlay(temp_a0, arg5, temp_a2, arg6, 0);
    } while (var_s1 < 4);
}

void gameModeReset(void);  /* forward: GETTER_NOJR fallthrough */
void gameModeResetGetter(Unk *arg0) {
    (void) arg0->unk7C83;  /* GETTER_NOJR: lb $zero,0x7C83($a0) prefetch, falls into gameModeReset */
    gameModeReset();
}
