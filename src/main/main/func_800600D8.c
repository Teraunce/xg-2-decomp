#include "ultra64.h"
void rdpSetFillColor(s32, s32, s32);                           /* extern */
void sfxUpdateHeap(s32);                               /* extern */
void sfxFlushInactive();                                  /* extern */
void rdpSetFogColor(s32, s32, s32, s32);                      /* extern */
s32 func_800B1558(s32);                             /* extern */
extern s32 gSfxSavedState;
extern s32 gSceneDL;
extern u32 gAudioFrameTick;
extern Unk *gDLPtr;
extern s32 gLoopCount;
extern s32 gSfxRaceReady;
extern s32 gSfxRaceTimer;
extern u16 gPerspMtx;

void rdpFrameBegin(s32 arg0, s32 arg1) {
    s32 var_a0;
    s32 var_a1;
    s32 var_v0;
    Unk *temp_v1;

    temp_v1 = gDLPtr + 8;
    gDLPtr->unk0 = 0xDE000000;
    gDLPtr->unk4 = &gSceneDL;
    gDLPtr = temp_v1;
    gDLPtr = temp_v1 + 8;
    gDLPtr->unk8 = 0xDB0E0000;
    temp_v1->unk4 = (s32) gPerspMtx;
    if (gSfxRaceReady == 1) {
        goto block_25;
    }
    switch (gSfxRaceReady) {                           /* irregular */
    case 0:
        if (((u32) (arg0 - 5) >= 2U) && (arg0 != 3)) {
            if (arg0 == 4) {
                if (gSfxSavedState != 0) {
                    goto block_12;
                }
                goto block_13;
            }
        } else {
block_12:
            rdpSetFillColor(0, 0, 0);
block_13:
            if (arg0 == 4) {
                sfxUpdateHeap((u32) gAudioFrameTick >= 5U);
            }
        }
        if (arg1 != 0) {
            var_v0 = arg1;
            if (arg1 < 0) {
                var_v0 = arg1 + 0xFF;
            }
            var_a0 = var_v0 >> 8;
            if (var_a0 >= 0x100) {
                var_a0 = 0xFF;
            }
            var_a1 = arg1 / 256;
            if (var_a1 >= 0x100) {
                var_a1 = 0xFF;
            }
            if (var_a1 <= 0) {
                var_a0 = 0;
            }
            rdpSetFogColor(var_a0, 0, 0, 0);
        }
        break;
    case 3:
block_25:
        rdpSetFillColor(0, 0, 0);
        break;
    case 2:
        rdpSetFillColor(0, 0, 0);
        if (func_800B1558(gLoopCount - gSfxRaceTimer) == 0) {
            gSfxRaceReady = 3;
        }
        break;
    }
    sfxFlushInactive();
    gAudioFrameTick += 1;
}
