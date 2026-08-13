#include "ultra64.h"
#include "track.h"
/* Warning: missing "jr $ra" in last block of trackNodeFindNearestGetter (initial). */

extern s32 gEntityFlagMask;
extern s32 gEntityVisited;
extern Unk *gCurRenderNode;

void trackNodeSearchNearest(f32 *arg0, s32 *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 temp_ft0;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    s32 var_s0;
    u16 temp_v1;
    u16 temp_v1_2;
    TrackNode *temp_s1;
    TrackNode *temp_a0;
    TrackNode *temp_a0_2;

    temp_s1 = (TrackNode *)((Unk *)gCurRenderNode->unk8)->unk38;
    var_s0 = arg5;
    *(((s32) ((temp_s1[arg5].flags & 0xF800) >> 0xB)) + &gEntityVisited) = 1;

loop_1:
    temp_a0 = &temp_s1[var_s0];
    temp_v1 = temp_a0->nextNode;
    if (temp_v1 != var_s0) {
        if (*(((s32) ((temp_s1[temp_v1].flags & 0xF800) >> 0xB)) + &gEntityVisited) == 0) {
            trackNodeSearchNearest(arg0, arg1, arg2, arg3, arg4, (s32) temp_a0->nextNode);
        }
    }
    temp_a0_2 = &temp_s1[var_s0];
    if (temp_a0_2->flags & (gEntityFlagMask * 4)) {
        temp_fv1   = arg2 - (f32) temp_a0_2->posX;
        temp_ft0   = arg3 - (f32) temp_a0_2->posY;
        temp_fv0   = arg4 - (f32) temp_a0_2->posZ;
        temp_fv1_2 = (temp_fv1 * temp_fv1) + (temp_ft0 * temp_ft0) + (temp_fv0 * temp_fv0);
        if (temp_fv1_2 < *arg0) {
            *arg0 = temp_fv1_2;
            *arg1 = var_s0;
        }
    }
    var_s0 += 1;
    temp_v1_2 = temp_s1[var_s0].nextNode;
    if (temp_v1_2 != 0x8000) {
        if (temp_v1_2 & 0x8000) {
            var_s0 = temp_v1_2 & 0x7FFF;
        }
        if (var_s0 != arg5) {
            goto loop_1;
        }
    }
}

char *trackNodeFindNearestGetter(void) {
    trackNodeFindNearest(0.0f, 0.0f, 0.0f);
    return gCurRenderNode;
}
