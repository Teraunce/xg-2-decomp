#include "ultra64.h"
s32 sfxQueueCmd(s16, f32, s32, s8, s32);           /* extern */
void audioQueuePlay(s32, f32, s32, s8, s32);           /* extern */
void audioQueueStop(s32);                               /* extern */
s32 audioQueueFind(s32, f32*, s32*, s32*);                    /* extern */
s32 sfxComputeSpatial(f32, f32, s32, s32, f32, f32, f32 *, s32 *, s32 *, s32 *, s32); /* extern */
extern f32 gSfxFreqParamA;
extern f32 gSfxFreqParamB;
extern f32 gSfxFreqThresh;
extern f32 gSfxFreqScale;
extern s32 gEntityPool;
extern s32 gSfxSpatialCount;
extern s32 gRaceCtrlCount;

void sfxPositionalUpdateDoppler(Unk *arg0, Unk *arg1, s32 arg2, f32 arg3, s32 arg4, s32 *arg5) {
    s32 sp34;
    s32 sp30;
    f32 temp_fv1;
    f32 var_a1;
    s32 temp_a0;
    s32 temp_a0_2;

    sp30 = 0x40;
    sp34 = 0;
    if (sfxComputeSpatial(arg0->unk0, arg0->unk4, arg0->unk8, arg1->unk0, arg1->unk4, arg1->unk8, &arg3, &arg4, &sp30, &sp34, 0) != 0) {
        temp_fv1 = (arg3 * gSfxFreqParamA) + (arg3 * gSfxFreqParamB);
        arg3 = temp_fv1;
        temp_a0 = *arg5;
        if (temp_a0 != 0) {
            if (audioQueueFind(temp_a0, 0, 0, 0) != 0) {
                audioQueuePlay(*arg5, arg3, arg4, sp30, sp34);
                return;
            }
            if (gSfxSpatialCount < 0x1A) {
                var_a1 = arg3;
                goto block_7;
            }
            goto block_10;
        }
        var_a1 = temp_fv1;
block_7:
        *arg5 = sfxQueueCmd(arg2, var_a1, arg4, sp30, sp34);
        return;
    }
    temp_a0_2 = *arg5;
    if (temp_a0_2 != 0) {
        audioQueueStop(temp_a0_2);
block_10:
        *arg5 = 0;
    }
}

s32 entityFindNearest(f32 arg0, f32 arg1, f32 arg2, s32 *arg3, s32 *arg4) {
    Unk *var_a1;
    Unk *var_v1;
    f32 temp_ft0;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_ft1;
    s32 var_a0;
    Unk *temp_v0;

    var_a0 = 0;
    var_ft1 = gSfxFreqThresh;
    var_a1 = NULL;
    if (gRaceCtrlCount > 0) {
        var_v1 = &gEntityPool;
        do {
            temp_fv0 = var_v1->unkC - arg0;
            temp_ft0 = var_v1->unk10 - arg1;
            temp_fv1 = var_v1->unk14 - arg2;
            temp_fv0_2 = sqrtf((temp_fv0 * temp_fv0) + (temp_ft0 * temp_ft0) + (temp_fv1 * temp_fv1));
            var_a0 += 1;
            if (temp_fv0_2 < var_ft1) {
                var_a1 = var_v1;
                var_ft1 = temp_fv0_2;
            }
            var_v1 += 0x228;
        } while (var_a0 < gRaceCtrlCount);
    }
    if (var_a1 == NULL) {
        return 0;
    }
    *arg4 = var_a1->unk218 / 3;
    temp_v0 = var_a1->unkD0;
    if (temp_v0 != NULL) {
        *arg3 = (s32) ((f32) *arg3 * (gSfxFreqScale - temp_v0->unk648));
    }
    return 1;
}
