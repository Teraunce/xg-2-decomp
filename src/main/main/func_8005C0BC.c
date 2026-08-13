#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of audioRspDoneGetter (initial). */

s32 *heap_alloc_default(s32);                            /* extern */
void audioSetTrack(s32);                               /* extern */
void audioSetRates(s32, s32);                              /* extern */
void audioSetChanA(s32);                               /* extern */
void audioSetChanB(s32);                               /* extern */
void osWritebackInvalDCache(u32, s32);                        /* extern */
void __osInvalICache_full();                                  /* extern */
void overlayLoadEntries(Unk*, s32);                        /* extern */
void audioSynthSetupGetter(void *, void *, s32 *, void *);              /* extern */
void audioHeapInit(void *, s32, s32);                     /* extern */
void audioSetBufLen(s32, s32);                          /* extern */
void audioSetChanWeight(s32, s8, s8);                     /* extern */
void audioSynthInit(Unk*, Unk*);                          /* extern */
void audioMidiInit(Unk*, Unk*);                          /* extern */
s32 geomNodeDispatchGetter(s32);                               /* extern */
s32 spTaskSubmit(Unk*, s32, s32, s32, s32, s32, s32);   /* extern */
extern s32 gAudioBankRomAddr;
extern s32 gAudioBankRomSize;
extern s32 gAudioBankEntryCount;
extern s32 gAudioUcodeRomAddr;
extern s32 gAudioUcodeRomSize;
extern s32 gAudioUcodeEntryCount;
extern s32 gAudioTaskData;
extern f32 gAudioBufScale;
extern s32 gAudioOutputCtx;
extern s32 gAudioBufLen;
extern s32 gMidiCtx;
extern char *gAudioCfgPtr;
extern s32 gAudioFrameLock;
extern s32 gAudioSynthBuf;
extern s32 gAudioMesgQueue;
extern s32 gAudioSyncMesgQueue;
extern s32 gAudioMsgBuf;
extern s32 gAudioSyncMsg;
extern s32 gAudioLoadTask;
extern Unk gAudioYieldBuf;
extern s32 gAudioHeap;
extern s32 gAudioSynthSetup;
extern Unk gAudioSynthCfg;
extern Unk gAudioMidiCfg;
extern Unk gMidiSynthCfg;
extern s32 *gAudioOutBuf;
extern Unk gAudioAiBuf;
extern s32 gMidiNoteTable;
extern s32 gAudioBufSize;
extern s32 gAudioBufSizeMin;
extern s32 *gAudioBankIdx;
extern Unk *gAudioUcodeData;
extern Unk *gAudioBankData;
extern s32 *gAudioDmaDst;
extern s32 gAudioNoteList;
extern Unk gRaceCtx;
extern s32 gAudioOutCtx;
extern s32 audioDmaBufInit;

void audioSystemInit(void) {
    Unk *var_v1;
    f32 temp_fv1;
    s32 *temp_v0_2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_ft0;
    s32 temp_s1;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_v0;
    s32 var_s4;
    s32 var_s4_2;
    Unk *temp_v1;

    osCreateMesgQueue(&gAudioMesgQueue, &gAudioMsgBuf, 0xC8);
    osCreateMesgQueue(&gAudioSyncMesgQueue, &gAudioSyncMsg, 1);
    audioHeapInit(&gAudioHeap, heap_alloc_default(0xB400), 0xB400);
    gAudioOutBuf = heap_alloc_default(0x4E20);
    gAudioYieldBuf.unk0 = heap_alloc_default(0x40);
    gAudioYieldBuf.unk4 = heap_alloc_default(0x40);
    gAudioAiBuf.unk0 = heap_alloc_default(0x800);
    gAudioAiBuf.unk4 = heap_alloc_default(0x800);
    temp_s3 = gAudioUcodeRomSize;
    gAudioAiBuf.unk8 = heap_alloc_default(0x800);
    gAudioUcodeData = heap_alloc_default(temp_s3);
    __osInvalICache_full();
    spTaskSubmit(&gAudioLoadTask, 0, 0, gAudioUcodeRomAddr, gAudioUcodeData, temp_s3, &gAudioMesgQueue);
    osRecvMesg(&gAudioMesgQueue, 0, 1);
    temp_s3_2 = gAudioBankRomSize;
    gAudioBankData = heap_alloc_default(temp_s3_2);
    __osInvalICache_full();
    spTaskSubmit(&gAudioLoadTask, 0, 0, gAudioBankRomAddr, gAudioBankData, temp_s3_2, &gAudioMesgQueue);
    osRecvMesg(&gAudioMesgQueue, 0, 1);
    temp_v0 = geomNodeDispatchGetter(0x5622);
    temp_fv1 = (f32) temp_v0 * gAudioBufScale;
    gAudioSynthCfg.unk18 = temp_v0;
    temp_ft0 = (s32) temp_fv1;
    gAudioBufSize = temp_ft0;
    if ((f32) temp_ft0 < temp_fv1) {
        gAudioBufSize = temp_ft0 + 1;
    }
    if (gAudioBufSize & 0xF) {
        gAudioBufSize = (gAudioBufSize & ~0xF) + 0x10;
    }
    gAudioSynthCfg.unk0 = 0x2C;
    gAudioSynthCfg.unk4 = 0x24;
    gAudioSynthCfg.unk10 = &audioDmaBufInit;
    gAudioSynthCfg.unk1C = 6;
    gAudioSynthCfg.unk20 = &gAudioSynthBuf;
    gAudioSynthCfg.unk8 = 0x100;
    gAudioSynthCfg.unk14 = &gAudioHeap;
    gAudioBufSizeMin = gAudioBufSize - 0x10;
    audioSynthSetupGetter(&gAudioSynthSetup, &gAudioSynthCfg, &gAudioBufSize, &gAudioSynthCfg);
    gAudioMidiCfg.unk0 = 0x10;
    gAudioMidiCfg.unk4 = 0x100;
    gAudioMidiCfg.unk8 = 0x10;
    gAudioMidiCfg.unkC = &gAudioHeap;
    gAudioMidiCfg.unk10 = 0;
    gAudioMidiCfg.unk14 = 0;
    gAudioMidiCfg.unk18 = 0;
    audioSynthInit(gAudioOutputCtx, &gAudioMidiCfg);
    var_s4 = 0;
    overlayLoadEntries(gAudioUcodeData, gAudioUcodeEntryCount);
    temp_a1 = gAudioUcodeData->unk4;
    gAudioBufLen = temp_a1;
    audioSetBufLen(gAudioOutputCtx, temp_a1);
    do {
        temp_a1_2 = var_s4 & 0xFF;
        temp_a2 = (0x10 - var_s4) & 0xFF;
        var_s4 += 1;
        audioSetChanWeight(gAudioOutputCtx, temp_a1_2, temp_a2);
    } while (var_s4 < 0x10);
    gMidiSynthCfg.unk0 = 0x1C;
    gMidiSynthCfg.unk4 = 0x100;
    gMidiSynthCfg.unk8 = &gAudioHeap;
    audioMidiInit(gMidiCtx, &gMidiSynthCfg);
    overlayLoadEntries(gAudioBankData, gAudioBankEntryCount);
    temp_v1 = gAudioBankData->unk4;
    gAudioCfgPtr = temp_v1;
    gMidiNoteTable = temp_v1->unkC;
    gAudioBankIdx = heap_alloc_default(0x3800);
    __osInvalICache_full();
    spTaskSubmit(&gAudioLoadTask, 0, 0, gAudioTaskData, gAudioBankIdx, 4, &gAudioMesgQueue);
    osRecvMesg(&gAudioMesgQueue, 0, 1);
    osWritebackInvalDCache(gAudioBankIdx, 4);
    temp_s1 = *gAudioBankIdx * 0x10;
    temp_v0_2 = heap_alloc_default(temp_s1);
    gAudioDmaDst = temp_v0_2;
    spTaskSubmit(&gAudioLoadTask, 0, 0, gAudioTaskData + 8, temp_v0_2, temp_s1, &gAudioMesgQueue);
    osRecvMesg(&gAudioMesgQueue, 0, 1);
    osWritebackInvalDCache(gAudioDmaDst, temp_s1);
    var_s4_2 = 0;
    audioSetTrack(gAudioOutCtx);
    audioSetRates(0x78, 0);
    var_v1 = &gAudioNoteList;
    do {
        var_v1->unk0 = 0;
        var_v1->unk4 = 0;
        var_s4_2 += 1;
        var_v1 += 0x14;
    } while (var_s4_2 < 0x1C);
    audioSetChanA(gRaceCtx.unkAFC);
    audioSetChanB(gRaceCtx.unkB04);
}

void audioRspDone(void);  /* forward: GETTER_NOJR fallthrough */
s32 audioRspDoneGetter(void) {
    audioRspDone();  /* GETTER_NOJR: pre-loads gAudioFrameLock into $v0, falls into audioRspDone */
    return gAudioFrameLock;
}
