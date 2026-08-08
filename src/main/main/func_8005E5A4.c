#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of sfxRaceSetupGetter (initial). */

s32 sfxQueueCmd(s16, f32, s32, s8, s32);               /* extern */
extern f32 gSfxRaceParamA;
extern s32 gTrackNodeCount;
extern s32 gRaceOrderTbl;
extern s32 gGameFlags;
extern s32 gRaceMax;
extern s32 gRaceActive;
extern s32 gSfxListenerPos;
extern s32 gRacePhase;
extern s32 gSfxEntityHandle;
extern s32 gRaceEntityBufD;
extern s32 gRaceEntityBufC;
extern s32 gRaceEntityBufB;
extern s32 gRaceEntityBufA;
extern s32 gRaceCtx;
extern s32 gGameMode;

void sfxRaceSetup(s32 arg0) {
    Unk *var_s0;
    Unk *var_s2;
    f32 temp_fs0;
    s32 *var_a0_2;
    s32 *var_a1;
    s32 *var_v0_2;
    s32 *var_v1_2;
    s32 var_a0;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_v0;
    s32 var_v1;

    if (arg0 != 0) {
        gRacePhase = 1;
    } else if (gGameMode == 0xE) {
        gRacePhase = 4;
    } else {
        gRacePhase = gRaceMax;
    }
    var_s1 = 0;
    if (gRacePhase > 0) {
        temp_fs0 = gSfxRaceParamA;
        var_s2 = &gRaceCtx;
        var_s0 = &gSfxListenerPos;
        do {
            var_s0->unk0 = 0;
            var_s0->unk4 = 0;
            var_s0->unk8 = 0;
            var_s0->unkC = 0;
            var_s0->unk10 = 0;
            var_s0->unk14 = 0;
            var_s0->unk18 = 0;
            var_s0->unk1C = 0;
            var_s0->unk20 = -1;
            var_s0->unk24 = -1;
            var_s0->unk28 = -1;
            var_s0->unk2C = -1;
            if (arg0 != 0) {
                var_s0->unk10 = sfxQueueCmd(0, temp_fs0, 0, 0x40, 0);
                var_s0->unk14 = sfxQueueCmd(1, temp_fs0, 0, 0x40, 0);
                var_s0->unk18 = sfxQueueCmd(2, temp_fs0, 0, 0x40, 0);
                var_s0->unk1C = sfxQueueCmd(5, temp_fs0, 0, 0x40, 0);
            } else if (((Unk *)var_s2->unk16F8)->unk8 < 0xD) {
                if (gGameFlags & 0x400) {
                    if (gRaceActive == 0) {
                        var_v0 = 0x4B;
                        var_s0->unk24 = 1;
                    } else {
                        goto block_14;
                    }
                } else {
block_14:
                    var_s0->unk20 = 0;
                    var_s0->unk24 = 1;
                    var_s0->unk28 = 2;
                    var_v0 = *((((Unk *)var_s2->unk16F8)->unk8 % 13) + &gRaceOrderTbl) + 3;
                }
                var_s0->unk2C = var_v0;
            }
            var_s2 += 4;
            var_s1 += 1;
            var_s0 += 0x30;
        } while (var_s1 < gRacePhase);
    }
    var_s1_2 = 7;
    if (arg0 == 0) {
        var_v0_2 = &gRaceEntityBufA + 0x1C;
        do {
            *var_v0_2 = 0;
            var_s1_2 -= 1;
            var_v0_2 -= 4;
        } while (var_s1_2 >= 0);
        if ((gGameMode != 0xE) && (gGameMode != 2)) {
            var_a0 = 4 - gRacePhase;
            if (var_a0 < 0) {
                var_a0 = 0;
            }
            var_v1 = gTrackNodeCount - gRacePhase;
            if (var_a0 < var_v1) {
                var_v1 = var_a0;
            }
            gSfxEntityHandle = var_v1;
        } else {
            gSfxEntityHandle = 0;
        }
        var_s1_3 = 0;
        if (gSfxEntityHandle > 0) {
            var_a1 = &gRaceEntityBufD;
            var_a0_2 = &gRaceEntityBufB;
            var_v1_2 = &gRaceEntityBufC;
            do {
                *var_v1_2 = gRacePhase + var_s1_3;
                *var_a0_2 = 0;
                *var_a1 = 0;
                var_a1 += 4;
                var_a0_2 += 4;
                var_s1_3 += 1;
                var_v1_2 += 4;
            } while (var_s1_3 < gSfxEntityHandle);
        }
    }
}

void geomCollisionDispatch(void);  /* forward: GETTER_NOJR fallthrough */
s32 sfxRaceSetupGetter(void) {
    geomCollisionDispatch();  /* GETTER_NOJR: pre-loads state, falls into geomCollisionDispatch */
    return gRacePhase;
}
