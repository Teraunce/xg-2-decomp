#include "ultra64.h"
extern s32 gSiCmdBuf;
extern s32 gSiWriteReady;
extern u8 gSfxVoiceCount;

void siInitControllerCmds(void) {
    Unk *spC;
    s8 spB;
    s8 spA;
    s16 sp8;
    s8 sp7;
    s8 sp6;
    s8 sp5;
    s8 sp4;
    s32 sp0;
    s32 temp_t0;
    s32 temp_t7;

    spC = &gSiCmdBuf;
    sp0 = 0;
    do {
        *(&gSiCmdBuf + (sp0 * 4)) = 0;
        temp_t0 = sp0 + 1;
        sp0 = temp_t0;
    } while (temp_t0 < 0x10);
    gSiWriteReady = 1;
    sp4 = 0xFF;
    sp5 = 1;
    sp6 = 4;
    sp7 = 1;
    sp8 = 0xFFFF;
    spA = -1;
    spB = -1;
    sp0 = 0;
    if ((s32) gSfxVoiceCount > 0) {
        do {
            spC->unk0 = (s32) ((Unk*)&sp4)->unk0;
            spC->unk4 = (s32) ((Unk*)&sp4)->unk4;
            temp_t7 = sp0 + 1;
            sp0 = temp_t7;
            spC += 8;
        } while (temp_t7 < (s32) gSfxVoiceCount);
    }
    spC->unk0 = 0xFE;
}
