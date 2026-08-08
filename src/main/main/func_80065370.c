#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of sfxGetState (initial). */

s32 sfxGetState();                                /* static */
extern s32 gRdpSyncDone;
extern s32 gTextFontId;
extern s32 gTextVisible;

void sfxRenderBegin(void **arg0, s32 arg1) {
    Unk *temp_v0;
    Unk *temp_v0_2;
    Unk *temp_v0_3;

    sfxGetState();
    temp_v0 = *arg0;
    *arg0 = temp_v0 + 8;
    temp_v0->unk0 = 0xE7000000;
    temp_v0->unk4 = 0;
    temp_v0_2 = *arg0;
    *arg0 = temp_v0_2 + 8;
    temp_v0_2->unk0 = 0xE3000C00;
    temp_v0_2->unk4 = 0x80000;
    temp_v0_3 = *arg0;
    *arg0 = temp_v0_3 + 8;
    temp_v0_3->unk0 = 0xFC121824;
    temp_v0_3->unk4 = 0xFF33FFFF;
    gTextFontId = 1;
    gRdpSyncDone = arg1;
}

s32 sfxGetState(void) {
    return gTextVisible;
}
