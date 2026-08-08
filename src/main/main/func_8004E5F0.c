#include "ultra64.h"
s32 *overlayDecompress(void *);                            /* extern */
extern s32 gOverlayTable;
extern s32 gSceneOverlayData;
extern s32 gSceneOverlay;

void overlayLoadEntry(s32 arg0, Unk *arg1) {
    s32 temp_v0;

    if ((arg0 >= 0xD) && (gSceneOverlay == 0)) {
        gSceneOverlay = *overlayDecompress(&gSceneOverlayData);
    }
    temp_v0 = *overlayDecompress((arg0 * 0x10) + &gOverlayTable);
    arg1->unk64C = 0;
    arg1->unkC = temp_v0;
}
