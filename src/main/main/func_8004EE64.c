#include "ultra64.h"
#include "track.h"
void trackNodeSearchNearest(f32 *, s32 *, f32, f32, f32, s32);  /* extern */
extern f32 gTrackSearchDist;
extern s32 gEntityVisited;

s32 trackNodeFindNearest(f32 arg0, f32 arg1, f32 arg2) {
    s32 sp1C;
    f32 sp18;
    s32 temp_v0;
    s32 var_v1;
    s8 *var_v0;
    TrackNode *temp_a0;

    /* implicit $v0 (ptr from caller): $v0->unk8->unk38 — track node array base */
    temp_a0 = (TrackNode *)((Unk *)((Unk*)0 /* implicit $v0 */)->unk8)->unk38;
    var_v1 = 0x1F;
    if (temp_a0 == NULL) {
        return -1;
    }
    var_v0 = &gEntityVisited + 0x1F;
    do {
        *var_v0 = 0;
        var_v1 -= 1;
        var_v0 -= 1;
    } while (var_v1 >= 0);
    sp1C = 1;
    /* Check whether node[1] is a section end — if so, start from index 0 */
    if (!(temp_a0[1].nextNode & 0x8000)) {
loop_5:
        temp_v0 = sp1C + 1;
        if (temp_a0[sp1C].colorIdx != 0) {
            sp1C = temp_v0;
            if (!(temp_a0[temp_v0].nextNode & 0x8000)) {
                goto loop_5;
            }
        }
        if (temp_a0[sp1C].nextNode & 0x8000) {
            goto block_8;
        }
    } else {
block_8:
        sp1C = 0;
    }
    sp18 = gTrackSearchDist;
    trackNodeSearchNearest(&sp18, &sp1C, arg0, arg1, arg2, sp1C);
    return sp1C;
}
