#include "ultra64.h"
void audioQueueDispatchGetter(void *, u32, u32);                  /* extern */
void midiQueueProcess();                                  /* extern */
s32 osVirtualToPhysical(u32);                             /* extern */
u32 audioBuildFrame(u32, void *, s32, s16);              /* extern */
extern s32 D_800769A8;
extern s32 D_800777C8;
extern s32 D_80077898;
extern s32 gAudioBufSizes;
extern s32 gAudioModeIdx;
extern s32 gAudioFrameCount;
extern s32 gAudioFrameLock;
extern u16 gAudioBufBase;
extern s32 gAudioStatus;
extern s32 gAudioCallback;
extern s32 D_80093F90;
extern s32 D_80094250;
extern s32 D_8017F370;
extern u32 D_8017F434;
extern s32 D_8017F438;
extern u32 D_80180880;
extern Unk *D_80180884;
extern u16 D_801808E2;
extern Unk D_801808E4;
extern s32 D_801808E8;

void audioFrameBuild(void) {
    s32 sp10;
    s16 *temp_a1;
    s16 temp_v0;
    s32 *temp_s1;
    s32 temp_s0;
    u32 temp_v0_2;

    gAudioFrameLock = 1;
    D_80180880 = D_8017F434;
    temp_s0 = gAudioFrameCount % 3;
    temp_s1 = (temp_s0 * 4) + &D_8017F438;
    D_80180884 = *((gAudioModeIdx * 4) + &D_8017F370);
    D_801808E8 = osVirtualToPhysical(*temp_s1);
    temp_a1 = (temp_s0 * 2) + &gAudioBufSizes;
    temp_v0 = (((D_801808E2 - gAudioBufBase) + 0x28) & ~0xF) + 0x10;
    *temp_a1 = temp_v0;
    if (temp_v0 < D_801808E4.unk0) {
        *temp_a1 = (s16) D_801808E4.unk2;
    }
    if (!((*temp_s1 + (*temp_a1 * 4)) & 0x1FFF)) {
        *temp_a1 = (u16) *temp_a1 + 0x10;
    }
    temp_v0_2 = audioBuildFrame(D_80180880, &sp10, D_801808E8, *temp_a1);
    D_80180880 = temp_v0_2;
    if ((u32) (D_8017F434 + 0x4E20) < temp_v0_2) {
        M2C_BREAK(0);
    }
    D_80180884->unk0 = 2;
    D_80180884->unkC = (s32) (&D_80077898 - &D_800777C8);
    D_80180884->unk8 = &D_800777C8;
    D_80180884->unk10 = &D_800769A8;
    D_80180884->unk14 = 0x1000;
    D_80180884->unk1C = (s32) (((s32) (&D_80094250 - &D_80093F90) >> 3) * 8);
    D_80180884->unk4 = 0;
    D_80180884->unk18 = &D_80093F90;
    D_80180884->unk30 = (u32) D_8017F434;
    D_80180884->unk34 = (s32) (((s32) (temp_v0_2 - D_8017F434) >> 3) * 8);
    audioQueueDispatchGetter(D_80180884, temp_v0_2, D_8017F434);
    midiQueueProcess();
}

void audioSetCallback(s32 arg0) {
    gAudioCallback = arg0;
    if ((gAudioStatus != 0) && (gAudioStatus != 4)) {
        gAudioStatus = 3;
    }
}
