#include "ultra64.h"
void **overlayDecompress(void *);                       /* extern */
extern s32 gOverlayTable2;

void overlayLoadAlt(s32 arg0, Unk *arg1, Unk *arg2) {
    Unk *temp_v0;

    temp_v0 = *overlayDecompress((arg0 * 0x10) + &gOverlayTable2);
    arg2->unk6C = temp_v0;
    arg1->unk64C = 1;
    arg1->unkC = (s32) temp_v0->unk30;
}
