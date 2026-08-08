#include "ultra64.h"
extern s32 gSiCmdBuf;
extern s32 gSiWriteReady;
extern u8 gSfxVoiceCount;

void siInitControllerReadCmd(s32 arg0) {
    Unk *spC;
    s8 spB;
    s8 spA;
    s8 sp9;
    s8 sp8;
    s8 sp7;
    s8 sp6;
    s8 sp5;
    s8 sp4;
    s32 sp0;
    s32 temp_t7;
    s32 temp_t9;

    sp0 = 0;
    do {
        *(&gSiCmdBuf + (sp0 * 4)) = 0;
        temp_t9 = sp0 + 1;
        sp0 = temp_t9;
    } while (temp_t9 < 0x10);
    gSiWriteReady = 1;
    spC = &gSiCmdBuf;
    sp4 = 0xFF;
    sp5 = 1;
    sp6 = 3;
    sp7 = arg0 & 0xFF;
    sp8 = 0xFF;
    sp9 = 0xFF;
    spA = 0xFF;
    spB = 0xFF;
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
