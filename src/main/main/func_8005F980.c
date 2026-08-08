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
extern f32 D_8004BF74;
extern f32 D_8004BF78;
extern s32 gPlayerList2;
extern s32 gColorSwapMode;
extern s32 gSfxSavedState;
extern s32 D_80092B5C;
extern s32 D_80092B64;
extern s32 gLocale;
extern s16 gLocaleIdx;
extern s32 gRaceCtrl;
extern s32 D_80092B8C;
extern s32 D_80092D20;
extern s32 D_80093338;
extern s32 D_8009333C;
extern s32 D_80093340;
extern s32 D_80093344;
extern s32 D_80093348;
extern s32 gInitStateFlags;
extern s32 D_800E3848;
extern s32 D_80173C38;
extern s32 D_80174C28;
extern s32 D_8017C950;
extern Unk D_8017C968;
extern s32 D_8017CC58;
extern Unk D_80181EF0;
extern s32 D_801821E8;
extern Unk D_80182EA8;

void gameSceneInit(s32 arg0) {
    s32 *var_v1;

    rspResetCounters();
    dlResetPtr();
    sfxTableInit();
    D_80181EF0.unk0 = heap_alloc_default(0x20000);
    D_80181EF0.unk4 = heap_alloc_default(0x20000);
    D_8017C968.unk0 = 0;
    D_8017C968.unk8 = 0x140;
    D_8017C968.unkC = 0xF0;
    D_8017C950 = 1;
    gColorSwapMode = 0;
    D_8017C968.unk4 = 0;
    D_8017CC58 = 1;
    D_8017C968.unk10 = (f32) D_8004BF74;
    D_8017C968.unk14 = (f32) D_8004BF78;
    D_8017C968.unk18 = (f32) D_8004BF74;
    D_8017C968.unk1C = (f32) D_8004BF78;
    if (arg0 == 0) {
        func_800AE150();
        audioBootDecode();
    }
    sfxBufAlloc();
    D_801821E8 = sfxFreeBlock(0x200);
    gLocaleIdx = 0;
    localeCheck(gLocale);
    if (arg0 != 0) {
        sfxSetCueParams(0, 0x55, 0, 4, 0);
        sfxPlayCue(&D_80092D20, 0);
        var_v1 = (s32 *)0x80090000;
    } else {
        sfxSetCueParams(0, 0x100, 2, 4, 0);
        audioSetRates(0, 0);
        audioSetTrack(D_80182EA8.unkB00);
        if (gRaceCtrl != 0) {
            D_80092B64 = 1;
            D_80182EA8.unk16D8 = (s32) D_80093338;
            D_80182EA8.unk16DC = (s32) D_8009333C;
            D_80182EA8.unk16E0 = (s32) D_80093340;
            D_80182EA8.unkB6C = (s32) D_80093344;
            D_80182EA8.unkB0C = (s32) D_80093348;
            if (D_80174C28 != 0) {
                goto block_14;
            }
            func_800C0810(1, D_80093344, D_80093348, D_80174C28);
            var_v1 = (s32 *)0x80090000;
        } else if (D_80174C28 != 0) {
            if ((D_80182EA8.unk16D8 != 1) && (D_80182EA8.unk16D8 != 2) && (D_80182EA8.unk16D8 != 0xB)) {
                if (!(D_80092B8C & 0x2000)) {
                    audioSetCallback(0x15);
                    D_80092B64 = 1;
block_14:
                    sfxQueueCmd(0xE, 0x3F800000, 0x10000, 0x40, 0);
                    func_800C9138(&D_800E3848, 0);
                    var_v1 = (s32 *)0x80090000;
                } else {
                    goto block_16;
                }
            } else {
                goto block_16;
            }
        } else {
block_16:
            if (D_80173C38 != 0) {
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
    D_80092B5C = gPlayerList2;
}
