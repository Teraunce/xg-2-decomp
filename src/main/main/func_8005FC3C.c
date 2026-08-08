#include "ultra64.h"
void sfxMarkEntityActive(void*);                               /* extern */
s32 sfxGetActiveCount();                                /* extern */
s32 sfxGetEntity(s32, s32);                          /* extern */
void sfxFrameBegin();                                  /* extern */
extern s32 gPendingEventFlag;
extern s32 gRaceCtrl;
extern s32 gLoopCount;
extern s32 gSfxRaceReady;
extern s32 gSfxRaceTimer;

void sfxMarkAllActive(void) {
    s32 var_s0;

    sfxFrameBegin();
    if (gSfxRaceReady == 0) {
        gSfxRaceReady = 1;
        gSfxRaceTimer = gLoopCount;
        var_s0 = sfxGetActiveCount() - 1;
        if (var_s0 >= 0) {
            do {
                sfxMarkEntityActive(sfxGetEntity(var_s0, 0));
                var_s0 -= 1;
            } while (var_s0 >= 0);
        }
        gPendingEventFlag = 0;
    }
}

s32 getRaceCtrl(void) {
    return gRaceCtrl;
}
