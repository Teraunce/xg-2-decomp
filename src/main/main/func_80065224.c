#include "ultra64.h"
void rdpStateInit();                                  /* extern */
extern s32 gSfxDL;
extern s32 gFontCacheKey;
extern s32 gGlyphCacheIdx;

void rdpRunSetupDL(void **arg0) {
    Unk *temp_v0;

    temp_v0 = *arg0;
    *arg0 = temp_v0 + 8;
    temp_v0->unk0 = 0xDE000000;
    temp_v0->unk4 = &gSfxDL;
    rdpStateInit();
    gFontCacheKey = 0;
    gGlyphCacheIdx = -1;
}
