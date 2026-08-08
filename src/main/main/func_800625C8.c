#include "ultra64.h"
void sfxUpdateChannels();                                  /* extern */
extern u32 gSfxActiveCount;
extern u32 gSfxMaxIndex;
extern u32 gSfxAllocCount;
extern s32 gSfxChannelState;
extern s32 gSfxHeap;

s32 sfxChannelDispatch(char *arg1) {
    Unk *var_v1;
    s32 temp_a0;
    s32 temp_s2;
    s32 temp_v0_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    u32 temp_a0_2;
    u32 var_s1;
    u32 var_s1_2;
    u32 var_s1_3;
    char *temp_a0_3;
    Unk *temp_a0_4;
    Unk *temp_s0;
    Unk *temp_s3;
    Unk *temp_v0;
    Unk *temp_v0_2;
    Unk *temp_v1;
    Unk *var_a1;

    var_a1 = arg1;
    var_s1 = 0;
    if (((Unk*)0 /* implicit $v0 from caller */)->unk0 != 0) {
        temp_s3 = (s32)0 /* implicit $v1 from caller */;
        var_v0 = 0 * 2;
        do {
            temp_v1 = ((var_v0 + var_s1) * 4) + &gSfxHeap;
            temp_a0 = temp_v1->unk4;
            if (temp_a0 & 2) {
                gSfxMaxIndex = var_s1;
                ((s32(*)())(s32)((Unk *)temp_v1->unk0)->unk0)(&gSfxChannelState, var_a1);
                var_s1 = gSfxMaxIndex;
                gSfxMaxIndex = -5U;
                temp_v0 = (var_s1 * 0xC) + &gSfxHeap;
                var_a1 = temp_v0->unk0;
                temp_v0->unk4 = (s32) (temp_v0->unk4 & ~2);
                temp_v0->unk8 = (s32) var_a1->unk10;
            } else if (temp_a0 & 8) {
                gSfxMaxIndex = var_s1;
                ((s32(*)())(s32)((Unk *)temp_v1->unk0)->unk4)(&gSfxChannelState, var_a1);
                gSfxMaxIndex = -5U;
                temp_a0_2 = temp_s3->unk2CB8 - 1;
                temp_s3->unk2CB8 = temp_a0_2;
                if ((u32) gSfxAllocCount >= var_s1) {
                    gSfxAllocCount -= 1;
                }
                var_a1 = (void *) var_s1;
                if (var_s1 < temp_a0_2) {
                    do {
                        temp_a0_3 = ((s32) var_a1 * 2) + var_a1;
                        var_a1 += 1;
                        temp_a0_4 = ((s32) temp_a0_3 * 4) + &gSfxHeap;
                        temp_v0_2 = ((s32) (((s32) var_a1 * 2) + var_a1) * 4) + &gSfxHeap;
                        temp_a0_4->unk0 = (s32) temp_v0_2->unk0;
                        temp_a0_4->unk4 = (s32) temp_v0_2->unk4;
                        temp_a0_4->unk8 = (s32) temp_v0_2->unk8;
                    } while ((u32) var_a1 < (u32) gSfxActiveCount);
                }
                var_s1 -= 1;
            }
            var_s1 += 1;
            var_v0 = var_s1 * 2;
        } while (var_s1 < (u32) temp_s3->unk2CB8);
    }
    var_s1_2 = 0;
    if ((s32)((Unk*)0 /* implicit $v1 */)->unk0 != 0) {
        var_v0_2 = 0 * 2;
        do {
            temp_s0 = ((var_v0_2 + var_s1_2) * 4) + &gSfxHeap;
            if (!(temp_s0->unk4 & 6)) {
                temp_v0_3 = temp_s0->unk8 + 1;
                temp_s0->unk8 = temp_v0_3;
                if (temp_v0_3 >= (s32) ((Unk *)temp_s0->unk0)->unk10) {
                    temp_s2 = temp_s0->unk4 & 1;
                    temp_s0->unk8 = 0;
                    if (temp_s2 != 0) {
                        sfxUpdateChannels();
                    }
                    gSfxMaxIndex = var_s1_2;
                    ((s32(*)())(s32)((Unk *)temp_s0->unk0)->unk8)(&gSfxChannelState, temp_s2);
                    var_s1_2 = gSfxMaxIndex;
                    gSfxMaxIndex = -5U;
                }
            }
            var_s1_2 += 1;
            var_v0_2 = var_s1_2 * 2;
        } while (var_s1_2 < (u32) (s32)((Unk*)0 /* implicit $v1 */)->unk0);
    }
    var_s1_3 = 0;
    if (gSfxActiveCount != 0) {
        var_v1 = &gSfxHeap;
        do {
            if (var_s1_3 == gSfxAllocCount) {
                var_v0_3 = var_v1->unk4 | 1;
            } else {
                var_v0_3 = var_v1->unk4 & ~1;
            }
            var_v1->unk4 = var_v0_3;
            var_s1_3 += 1;
            var_v1 += 0xC;
        } while (var_s1_3 < (u32) gSfxActiveCount);
    }
    return gSfxActiveCount != 0;
}
