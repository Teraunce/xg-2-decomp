#include "ultra64.h"
void dlResetPtr();                                  /* extern */
void rspResetCounters();                                  /* extern */
s32 heap_alloc_default(s32);                               /* extern */
void audioSetCallback(s32);                                 /* extern */
void audioSetTrack(s32);                               /* extern */
void audioSetRates(s32, s32);                              /* extern */
s32 sfxQueueCmd(s32, s32, s32, s32, s32);                   /* extern */
void audioBootDecode();                                  /* extern */
void sfxRaceInit(s32);                                 /* extern */
s32 localeCheck(s32);                               /* extern */
void sfxPlayCue(void*, void*);                            /* extern */
void sfxSetCueParams(s32, s32, s32, s32, s32);                   /* extern */
void sfxTableInit();                                  /* extern */
s32 sfxFreeBlock(s32);                               /* extern */
void sfxBufAlloc();                                  /* extern */
s32 func_800AE150();                                  /* extern */
s32 func_800C0810(s32, s32, s32, s32);                  /* extern */
s32 func_800C9138(void *, s32);                            /* extern */
s32 func_800CD200();                                  /* extern */
extern f32 gVidScaleX;
extern f32 gVidScaleY;
extern s32 gPlayerList2;
extern s32 gColorSwapMode;
extern s32 gSfxSavedState;
extern s32 gPlayerCount2;
extern s32 gSfxOutputActive;
extern s32 gLocale;
extern s16 gLocaleIdx;
extern s32 gRaceCtrl;
extern s32 gRaceFlags;
extern s32 gSfxCueData;
extern s32 gRaceSceneE;
extern s32 gRaceSceneD;
extern s32 gRaceSceneC;
extern s32 gRaceSceneA;
extern s32 gRaceSceneB;
extern s32 gInitStateFlags;
extern s32 gRaceConfig;
extern s32 gTrackReady;
extern s32 gSceneReady;
extern s32 gRaceCtrlCount;
extern Unk gVideoMode;
extern s32 gSceneActiveFlag;
extern Unk gSfxChanFuncs;
extern s32 gLineTexBase;
extern Unk gRaceCtx;

void gameSceneInit(s32 arg0) {
    s32 *var_v1;

    rspResetCounters();
    dlResetPtr();
    sfxTableInit();
    gSfxChanFuncs.unk0 = heap_alloc_default(0x20000);
    gSfxChanFuncs.unk4 = heap_alloc_default(0x20000);
    gVideoMode.unk0 = 0;
    gVideoMode.unk8 = 0x140;
    gVideoMode.unkC = 0xF0;
    gRaceCtrlCount = 1;
    gColorSwapMode = 0;
    gVideoMode.unk4 = 0;
    gSceneActiveFlag = 1;
    gVideoMode.unk10 = (f32) gVidScaleX;
    gVideoMode.unk14 = (f32) gVidScaleY;
    gVideoMode.unk18 = (f32) gVidScaleX;
    gVideoMode.unk1C = (f32) gVidScaleY;
    if (arg0 == 0) {
        func_800AE150();
        audioBootDecode();
    }
    sfxBufAlloc();
    gLineTexBase = sfxFreeBlock(0x200);
    gLocaleIdx = 0;
    localeCheck(gLocale);
    if (arg0 != 0) {
        sfxSetCueParams(0, 0x55, 0, 4, 0);
        sfxPlayCue(&gSfxCueData, 0);
        var_v1 = (s32 *)0x80090000;
    } else {
        sfxSetCueParams(0, 0x100, 2, 4, 0);
        audioSetRates(0, 0);
        audioSetTrack(gRaceCtx.unkB00);
        if (gRaceCtrl != 0) {
            gSfxOutputActive = 1;
            gRaceCtx.unk16D8 = (s32) gRaceSceneE;
            gRaceCtx.unk16DC = (s32) gRaceSceneD;
            gRaceCtx.unk16E0 = (s32) gRaceSceneC;
            gRaceCtx.unkB6C = (s32) gRaceSceneA;
            gRaceCtx.unkB0C = (s32) gRaceSceneB;
            if (gSceneReady != 0) {
                goto block_14;
            }
            func_800C0810(1, gRaceSceneA, gRaceSceneB, gSceneReady);
            var_v1 = (s32 *)0x80090000;
        } else if (gSceneReady != 0) {
            if ((gRaceCtx.unk16D8 != 1) && (gRaceCtx.unk16D8 != 2) && (gRaceCtx.unk16D8 != 0xB)) {
                if (!(gRaceFlags & 0x2000)) {
                    audioSetCallback(0x15);
                    gSfxOutputActive = 1;
block_14:
                    sfxQueueCmd(0xE, 0x3F800000, 0x10000, 0x40, 0);
                    func_800C9138(&gRaceConfig, 0);
                    var_v1 = (s32 *)0x80090000;
                } else {
                    goto block_16;
                }
            } else {
                goto block_16;
            }
        } else {
block_16:
            if (gTrackReady != 0) {
                sfxRaceInit(0);
                var_v1 = (s32 *)0x80090000;
            } else {
                sfxQueueCmd(0xE, 0x3F800000, 0x10000, 0x40, 0);
                func_800CD200();
                var_v1 = &gSfxSavedState;
            }
        }
    }
    *var_v1 = 1;
    gInitStateFlags = 0;
    gPlayerCount2 = gPlayerList2;
}
