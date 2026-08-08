#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of sfxRaceSetupGetter (initial). */

s32 sfxQueueCmd(s16, f32, s32, s8, s32);               /* extern */
extern f32 D_8004BE94;
extern s32 gTrackNodeCount;
extern s32 D_80092B48;
extern s32 gGameFlags;
extern s32 D_80173C28;
extern s32 D_8017C958;
extern s32 D_80181588;
extern s32 D_80181648;
extern s32 D_8018164C;
extern s32 D_80181658;
extern s32 D_80181668;
extern s32 D_80181678;
extern s32 D_80181688;
extern s32 D_80182EA8;
extern s32 D_80184580;

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
        D_80181648 = 1;
    } else if (D_80184580 == 0xE) {
        D_80181648 = 4;
    } else {
        D_80181648 = D_80173C28;
    }
    var_s1 = 0;
    if (D_80181648 > 0) {
        temp_fs0 = D_8004BE94;
        var_s2 = &D_80182EA8;
        var_s0 = &D_80181588;
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
                    if (D_8017C958 == 0) {
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
                    var_v0 = *((((Unk *)var_s2->unk16F8)->unk8 % 13) + &D_80092B48) + 3;
                }
                var_s0->unk2C = var_v0;
            }
            var_s2 += 4;
            var_s1 += 1;
            var_s0 += 0x30;
        } while (var_s1 < D_80181648);
    }
    var_s1_2 = 7;
    if (arg0 == 0) {
        var_v0_2 = &D_80181688 + 0x1C;
        do {
            *var_v0_2 = 0;
            var_s1_2 -= 1;
            var_v0_2 -= 4;
        } while (var_s1_2 >= 0);
        if ((D_80184580 != 0xE) && (D_80184580 != 2)) {
            var_a0 = 4 - D_80181648;
            if (var_a0 < 0) {
                var_a0 = 0;
            }
            var_v1 = gTrackNodeCount - D_80181648;
            if (var_a0 < var_v1) {
                var_v1 = var_a0;
            }
            D_8018164C = var_v1;
        } else {
            D_8018164C = 0;
        }
        var_s1_3 = 0;
        if (D_8018164C > 0) {
            var_a1 = &D_80181658;
            var_a0_2 = &D_80181678;
            var_v1_2 = &D_80181668;
            do {
                *var_v1_2 = D_80181648 + var_s1_3;
                *var_a0_2 = 0;
                *var_a1 = 0;
                var_a1 += 4;
                var_a0_2 += 4;
                var_s1_3 += 1;
                var_v1_2 += 4;
            } while (var_s1_3 < D_8018164C);
        }
    }
}

void geomCollisionDispatch(void);  /* forward: GETTER_NOJR fallthrough */
s32 sfxRaceSetupGetter(void) {
    geomCollisionDispatch();  /* GETTER_NOJR: pre-loads state, falls into geomCollisionDispatch */
    return D_80181648;
}
