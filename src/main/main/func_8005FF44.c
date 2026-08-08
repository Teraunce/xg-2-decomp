#include "ultra64.h"
s32 sfxMapId(s32);                               /* extern */
void sfxPlayCue(void*, void*);                            /* extern */
void sfxSetCueParams(s32, s32, s32, s32, s32);                   /* extern */
void copyU16Array(u16*, u16*);                          /* extern */
extern s32 gRaceCtrl;
extern s32 gSfxProbeTable;
extern s32 gSfxCopyBufD;
extern s32 gSfxCopyBufC;
extern s32 gSfxCopyBufB;
extern s32 gSfxCopyBufA;
extern s32 gSfxCopyBuf9;
extern s32 gSfxCopyBuf8;
extern s32 gSfxCopyBuf7;
extern s32 gSfxCopyBuf6;
extern s32 gSfxCopyBuf5;
extern s32 gSfxCopyBuf4;
extern s32 gSfxCopyBuf3;
extern s32 gSfxCopyBuf2;
extern s32 gSfxCopyBuf1;
extern s32 gSfxCopyBuf0;

void sfxRaceInit(s32 arg0) {
    gRaceCtrl = arg0;
    copyU16Array(&gSfxCopyBuf9, sfxMapId(0xC6));
    copyU16Array(&gSfxCopyBuf6, sfxMapId(0xC7));
    copyU16Array(&gSfxCopyBufA, sfxMapId(0xC8));
    copyU16Array(&gSfxCopyBuf8, sfxMapId(0xED));
    copyU16Array(&gSfxCopyBufD, sfxMapId(0xCB));
    copyU16Array(&gSfxCopyBuf5, sfxMapId(0xCF));
    copyU16Array(&gSfxCopyBuf1, sfxMapId(0x13E));
    copyU16Array(&gSfxCopyBuf7, sfxMapId(0xB8));
    copyU16Array(&gSfxCopyBuf3, sfxMapId(0x64));
    copyU16Array(&gSfxCopyBuf2, sfxMapId(0xC9));
    copyU16Array(&gSfxCopyBuf4, sfxMapId(0x13B));
    copyU16Array(&gSfxCopyBufC, sfxMapId(0x13C));
    copyU16Array(&gSfxCopyBufB, sfxMapId(0xCA));
    copyU16Array(&gSfxCopyBuf0, sfxMapId(0x13D));
    sfxSetCueParams(3, 4, 0, 0x100, 0);
    sfxPlayCue(&gSfxProbeTable, 0);
}
