#include "ultra64.h"
void gfxSpTaskWait(s32, s32, s32);                    /* extern */
void audioDecodeStart(void);                              /* extern */

void gfxAudioWait(s32 arg0, s32 *arg1) {
    gfxSpTaskWait(arg0, arg1, 0x10);
    audioDecodeStart();
}
