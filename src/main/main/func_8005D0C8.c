#include "ultra64.h"
s32 sfxQueueCmd(s32, s32, s32, s32, s32);             /* extern */
s32 audioQueueFind(s32, f32*, s32*, s32*);                    /* extern */
extern s32 gSfxAmbientIds;
extern s32 gSfxAmbientParams;
extern s32 gSfxAmbientSlot;
extern s32 gSfxAmbientCount;
extern s32 gSfxAmbientHandle;

void sfxAmbientTick(void) {
    s32 temp_v1;
    s32 temp_v1_2;

    if ((gSfxAmbientSlot != gSfxAmbientCount) && ((gSfxAmbientHandle == 0) || (audioQueueFind(gSfxAmbientHandle, 0, 0, 0) == 0))) {
        temp_v1 = gSfxAmbientSlot * 4;
        gSfxAmbientHandle = sfxQueueCmd(*(temp_v1 + &gSfxAmbientIds), 0x3F800000, 0x10000, *(temp_v1 + &gSfxAmbientParams), 0);
        temp_v1_2 = gSfxAmbientSlot + 1;
        gSfxAmbientSlot = temp_v1_2;
        if (temp_v1_2 >= 8) {
            gSfxAmbientSlot = 0;
        }
    }
}
