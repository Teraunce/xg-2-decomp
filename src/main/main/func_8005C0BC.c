#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of audioRspDoneGetter (initial). */

s32 *heap_alloc_default(s32);                            /* extern */
void audioSetTrack(s32);                               /* extern */
void audioSetRates(s32, s32);                              /* extern */
void audioSetChanA(s32);                               /* extern */
void audioSetChanB(s32);                               /* extern */
void osWritebackInvalDCache(u32, s32);                        /* extern */
void __osInvalICache_full();                                  /* extern */
void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
s32 osRecvMesg(Unk*, s32*, s32);                         /* extern */
void overlayLoadEntries(Unk*, s32);                        /* extern */
void audioSynthSetupGetter(void *, void *, s32 *, void *);              /* extern */
void audioHeapInit(void *, s32, s32);                     /* extern */
void audioSetBufLen(s32, s32);                          /* extern */
void audioSetChanWeight(s32, s8, s8);                     /* extern */
void audioSynthInit(Unk*, Unk*);                          /* extern */
void audioMidiInit(Unk*, Unk*);                          /* extern */
s32 geomNodeDispatchGetter(s32);                               /* extern */
s32 spTaskSubmit(Unk*, s32, s32, s32, s32, s32, s32);   /* extern */
extern s32 D_8004B660;
extern s32 D_8004B664;
extern s32 D_8004B668;
extern s32 D_8004B670;
extern s32 D_8004B674;
extern s32 D_8004B678;
extern s32 D_8004B680;
extern f32 D_8004BDE8;
extern s32 gAudioOutputCtx;
extern s32 gAudioBufLen;
extern s32 D_800927F0;
extern char *gAudioCfgPtr;
extern s32 gAudioFrameLock;
extern s32 D_80092AB0;
extern s32 D_8017EFC8;
extern s32 D_8017EFE8;
extern s32 D_8017F008;
extern s32 D_8017F328;
extern s32 D_8017F338;
extern Unk D_8017F370;
extern s32 D_8017F378;
extern s32 D_8017F388;
extern Unk D_8017F3D8;
extern Unk D_8017F408;
extern Unk D_8017F428;
extern s32 *D_8017F434;
extern Unk D_8017F438;
extern s32 D_801808DC;
extern s32 D_801808E0;
extern s32 D_801808E4;
extern s32 *D_801808EC;
extern Unk *D_801808F0;
extern Unk *D_801808F4;
extern s32 *D_801808F8;
extern s32 D_80180908;
extern Unk D_80182EA8;
extern s32 D_801839A8;
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

    osCreateMesgQueue(&D_8017EFC8, &D_8017F008, 0xC8);
    osCreateMesgQueue(&D_8017EFE8, &D_8017F328, 1);
    audioHeapInit(&D_8017F378, heap_alloc_default(0xB400), 0xB400);
    D_8017F434 = heap_alloc_default(0x4E20);
    D_8017F370.unk0 = heap_alloc_default(0x40);
    D_8017F370.unk4 = heap_alloc_default(0x40);
    D_8017F438.unk0 = heap_alloc_default(0x800);
    D_8017F438.unk4 = heap_alloc_default(0x800);
    temp_s3 = D_8004B674;
    D_8017F438.unk8 = heap_alloc_default(0x800);
    D_801808F0 = heap_alloc_default(temp_s3);
    __osInvalICache_full();
    spTaskSubmit(&D_8017F338, 0, 0, D_8004B670, D_801808F0, temp_s3, &D_8017EFC8);
    osRecvMesg(&D_8017EFC8, 0, 1);
    temp_s3_2 = D_8004B664;
    D_801808F4 = heap_alloc_default(temp_s3_2);
    __osInvalICache_full();
    spTaskSubmit(&D_8017F338, 0, 0, D_8004B660, D_801808F4, temp_s3_2, &D_8017EFC8);
    osRecvMesg(&D_8017EFC8, 0, 1);
    temp_v0 = geomNodeDispatchGetter(0x5622);
    temp_fv1 = (f32) temp_v0 * D_8004BDE8;
    D_8017F3D8.unk18 = temp_v0;
    temp_ft0 = (s32) temp_fv1;
    D_801808E0 = temp_ft0;
    if ((f32) temp_ft0 < temp_fv1) {
        D_801808E0 = temp_ft0 + 1;
    }
    if (D_801808E0 & 0xF) {
        D_801808E0 = (D_801808E0 & ~0xF) + 0x10;
    }
    D_8017F3D8.unk0 = 0x2C;
    D_8017F3D8.unk4 = 0x24;
    D_8017F3D8.unk10 = &audioDmaBufInit;
    D_8017F3D8.unk1C = 6;
    D_8017F3D8.unk20 = &D_80092AB0;
    D_8017F3D8.unk8 = 0x100;
    D_8017F3D8.unk14 = &D_8017F378;
    D_801808E4 = D_801808E0 - 0x10;
    audioSynthSetupGetter(&D_8017F388, &D_8017F3D8, &D_801808E0, &D_8017F3D8);
    D_8017F408.unk0 = 0x10;
    D_8017F408.unk4 = 0x100;
    D_8017F408.unk8 = 0x10;
    D_8017F408.unkC = &D_8017F378;
    D_8017F408.unk10 = 0;
    D_8017F408.unk14 = 0;
    D_8017F408.unk18 = 0;
    audioSynthInit(gAudioOutputCtx, &D_8017F408);
    var_s4 = 0;
    overlayLoadEntries(D_801808F0, D_8004B678);
    temp_a1 = D_801808F0->unk4;
    gAudioBufLen = temp_a1;
    audioSetBufLen(gAudioOutputCtx, temp_a1);
    do {
        temp_a1_2 = var_s4 & 0xFF;
        temp_a2 = (0x10 - var_s4) & 0xFF;
        var_s4 += 1;
        audioSetChanWeight(gAudioOutputCtx, temp_a1_2, temp_a2);
    } while (var_s4 < 0x10);
    D_8017F428.unk0 = 0x1C;
    D_8017F428.unk4 = 0x100;
    D_8017F428.unk8 = &D_8017F378;
    audioMidiInit(D_800927F0, &D_8017F428);
    overlayLoadEntries(D_801808F4, D_8004B668);
    temp_v1 = D_801808F4->unk4;
    gAudioCfgPtr = temp_v1;
    D_801808DC = temp_v1->unkC;
    D_801808EC = heap_alloc_default(0x3800);
    __osInvalICache_full();
    spTaskSubmit(&D_8017F338, 0, 0, D_8004B680, D_801808EC, 4, &D_8017EFC8);
    osRecvMesg(&D_8017EFC8, 0, 1);
    osWritebackInvalDCache(D_801808EC, 4);
    temp_s1 = *D_801808EC * 0x10;
    temp_v0_2 = heap_alloc_default(temp_s1);
    D_801808F8 = temp_v0_2;
    spTaskSubmit(&D_8017F338, 0, 0, D_8004B680 + 8, temp_v0_2, temp_s1, &D_8017EFC8);
    osRecvMesg(&D_8017EFC8, 0, 1);
    osWritebackInvalDCache(D_801808F8, temp_s1);
    var_s4_2 = 0;
    audioSetTrack(D_801839A8);
    audioSetRates(0x78, 0);
    var_v1 = &D_80180908;
    do {
        var_v1->unk0 = 0;
        var_v1->unk4 = 0;
        var_s4_2 += 1;
        var_v1 += 0x14;
    } while (var_s4_2 < 0x1C);
    audioSetChanA(D_80182EA8.unkAFC);
    audioSetChanB(D_80182EA8.unkB04);
}

void audioRspDone(void);  /* forward: GETTER_NOJR fallthrough */
s32 audioRspDoneGetter(void) {
    audioRspDone();  /* GETTER_NOJR: pre-loads gAudioFrameLock into $v0, falls into audioRspDone */
    return gAudioFrameLock;
}
