#include "ultra64.h"
void gfxSpTaskWait(s32, s32, s32);                    /* extern */
s32 heap_alloc_default(s32);                             /* extern */
void audioDecodeStart(void);                              /* extern */
extern s32 D_80192880;

s32 gfxAudioDecodeWait(s32 arg0) {
    s32 temp_s1;
    s32 temp_v0;

    gfxSpTaskWait(arg0, &D_80192880, 0x10);
    temp_s1 = D_80192880;
    temp_v0 = heap_alloc_default(temp_s1);
    audioDecodeStart();
    return temp_v0;
}
