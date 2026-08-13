#include "ultra64.h"
#include "track.h"
void trackNodeRender(TrackNode *, s32, u16, s32);         /* extern */
extern s32 gEntityActive;
extern s32 gLoopFlag;

void trackEdgeProcess(Unk *arg0) {
    s32 var_v1;
    s8 *var_v0;

    var_v1 = 0x1F;
    if (arg0->unk38 != 0) {
        var_v0 = &gEntityActive + 0x1F;
        do {
            *var_v0 = 0;
            var_v1 -= 1;
            var_v0 -= 1;
        } while (var_v1 >= 0);
        gLoopFlag = 0;
        trackNodeRender((TrackNode *)arg0->unk38, 0, 1, arg0);
    }
}
