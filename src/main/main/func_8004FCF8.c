#include "ultra64.h"
#include "track.h"
void entityListPrune(void);                              /* extern */
s32 vec3Normalize(f32 *, f32 *, f32 *);               /* extern */
void vec3Cross(Unk*, Unk*, Unk*);               /* extern */
s32 func_800FDD50(f32 *, f32 *, f32 *, f32 *, s32, f32 *); /* extern */
extern f32 gTrackNodeRenderA;
extern f32 gTrackNodeRenderB;
extern f32 gTrackNodeRenderC;
extern f32 gTrackNodeRenderD;
extern f32 gTrackFriction;
extern s32 gColorSwapMode;
extern s32 gEntityFlagMask;
extern s32 gSfxInitFlag;
extern s32 gEntityActive;
extern Unk *gCurRenderNode;
extern Unk gRaceCtx;

void trackNodeRender(TrackNode *arg0, s32 arg1, u16 arg2, s32 arg3) {
    f32 spA8;
    f32 sp70;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp20;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft2;
    f32 temp_fv0;
    s32 var_condition_bit;
    s32 var_s6;
    u16 temp_a2;
    u16 temp_v1_2;
    u16 var_a0;
    u16 var_s3;
    TrackNode *temp_s0;
    TrackNode *temp_s2;
    TrackNode *temp_v1;
    TrackNode *var_v1;
    TrackNode *var_v1_2;
    Unk *spA4;

    var_s6 = 0;
    var_s3 = arg2;
    temp_fs3 = gTrackNodeRenderB;
    spA8 = gTrackNodeRenderA;
    temp_fs2 = gTrackNodeRenderC;
    /* Mark the starting node's entity slot as active */
    *(((s32) ((arg0[arg2].flags << 0x10) >> 0x1B)) + &gEntityActive) = 1;

loop_1:
    /* Check branching neighbour — nextNode of the current node */
    temp_a2 = arg0[var_s3].nextNode;
    if ((temp_a2 != var_s3) && (temp_v1 = &arg0[temp_a2], (*(((s32) (temp_v1->flags << 0x10) >> 0x1B) + &gEntityActive) == 0))) {
        /* Only recurse if the branch target begins a new section:
         * the previous node's nextNode == 0x8000 means it is a section end,
         * so the branch target is the first node of a fresh section. */
        if ((temp_v1 - 1)->nextNode == 0x8000) {
            trackNodeRender(arg0, arg1, temp_a2, arg3);
        }
    }
    temp_s2 = &arg0[var_s3];
    /* Select colour from the three race-slot colours based on current race phase */
    temp_s2->colorIdx = (&temp_s2->raceColor0)[gRaceCtx.unk16E0 % 3];
    if (gColorSwapMode != 0) {
        temp_s2->posX    = -temp_s2->posX;
        temp_s2->normalX = (s16) -(s32) temp_s2->normalX;
    }
    if (gSfxInitFlag == 0) {
        if (temp_s2->flags & (gEntityFlagMask * 4)) {
            /* Compute edge vector to next node (cross-element: node[i+1] – node[i]) */
            sp30 = (f32) ((temp_s2 + 1)->posX - temp_s2->posX);
            sp34 = (f32) ((temp_s2 + 1)->posY - temp_s2->posY);
            sp38 = (f32) ((temp_s2 + 1)->posZ - temp_s2->posZ);
            sp10 = (f32) temp_s2->normalX;
            sp14 = (f32) temp_s2->normalY;
            sp18 = (f32) temp_s2->normalZ;
            vec3Cross(&sp30, &sp10, &sp20);
            vec3Cross(&sp30, &sp20, &sp10);
            vec3Normalize(&sp10, &sp14, &sp18);
            sp40 = (f32) temp_s2->posX;
            sp44 = (f32) temp_s2->posY;
            sp48 = (f32) temp_s2->posZ;
            do {
                sp50 = sp40 + (sp10 * temp_fs3);
                sp54 = sp44 + (sp14 * temp_fs3);
                sp58 = sp48 + (sp18 * temp_fs3);
                func_800FDD50(&sp40, &sp50, (f32 *)0x14, NULL, 0, &sp70);
                temp_ft1 = sp50 - sp40;
                temp_ft0 = sp54 - sp44;
                temp_fv0 = sp58 - sp48;
                sp60 = temp_ft1;
                temp_ft2 = (sp10 * temp_ft1) + (sp14 * temp_ft0) + (sp18 * temp_fv0);
                sp64 = temp_ft0;
                var_condition_bit = temp_ft2 <= 0.0f;
                sp68 = temp_fv0;
                if (temp_ft2 <= 0.0f) {
                    sp40 += sp10 * temp_fs2;
                    sp44 += sp14 * temp_fs2;
                    sp48 += sp18 * temp_fs2;
                    var_condition_bit = temp_ft2 <= 0.0f;
                }
            } while (var_condition_bit);
            if (temp_ft2 < spA8) {
                spA8 = temp_ft2;
            }
            temp_s0 = &arg0[var_s3];
            temp_s0->friction   = (s16) (s32) (temp_ft2 + gTrackNodeRenderD);
            sp40 -= sp10 * gTrackFriction;
            sp48 -= sp18 * gTrackFriction;
            sp44 -= sp14 * gTrackFriction;
            func_800FDD50(&sp18, &sp14, &sp50, &sp40, 0x14, &sp70);
            if ((s32)spA4 == gCurRenderNode->unk8) {
                temp_s0->renderNode = 0;
            } else {
                temp_s0->renderNode = (s32) spA4;
            }
            if ((var_s6 == 0) && ((u32) (gRaceCtx.unk16D8 - 1) < 2U) && (spA4 != NULL) && (spA4->unk5C == 0x63)) {
                /* Walk backward to find the first node in the current section.
                 * A node with (ptr-1)->nextNode == 0x8000 is the section start. */
                var_v1 = &arg0[var_s3];
                var_a0 = var_s3;
                while ((var_v1 - 1)->nextNode != 0x8000) {
                    var_v1--;
                    var_a0--;
                }
                /* Clear friction/render state for all nodes in this section */
                var_v1_2 = &arg0[var_a0];
                if (var_v1_2->nextNode != 0x8000) {
                    var_a0 = 0x8000;
                    do {
                        var_v1_2->friction   = 0x206;
                        var_v1_2->renderNode = 0;
                        var_v1_2->flags      = (u16) (var_v1_2->flags & ~0x1C);
                        var_v1_2++;
                    } while (var_v1_2->nextNode != 0x8000);
                }
                var_s6 = 1;
                entityListPrune();
                var_s3 += 1;
            } else {
                goto block_32;
            }
        } else {
            temp_s2->friction   = 0x206;
            temp_s2->renderNode = 0;
            goto block_32;
        }
    } else {
block_32:
        var_s3 += 1;
    }
    temp_v1_2 = arg0[var_s3].nextNode;
    if (temp_v1_2 != 0x8000) {
        if (temp_v1_2 & 0x8000) {
            var_s3 = temp_v1_2 & 0x7FFF;
        }
        if (var_s3 != arg2) {
            goto loop_1;
        }
    }
}
