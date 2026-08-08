#include "ultra64.h"
void audioQueueDispatchGetter(void *, u32, u32);                  /* extern */
void midiQueueProcess();                                  /* extern */
s32 osVirtualToPhysical(u32);                             /* extern */
u32 audioBuildFrame(u32, void *, s32, s16);              /* extern */
extern s32 gAudioRspData;
extern s32 gAudioUcode;
extern s32 gAudioUcodeEnd;
extern s32 gAudioBufSizes;
extern s32 gAudioModeIdx;
extern s32 gAudioFrameCount;
extern s32 gAudioFrameLock;
extern u16 gAudioBufBase;
extern s32 gAudioStatus;
extern s32 gAudioCallback;
extern s32 gAudioUcodeStart;
extern s32 gAudioUcodeImemEnd;
extern s32 gAudioYieldBuf;
extern u32 gAudioOutBuf;
extern s32 gAudioAiBuf;
extern u32 gAudioBufPtr;
extern Unk *gRspTask;
extern u16 gAudioBufBase2;
extern Unk gAudioBufSizeMin;
extern s32 gAudioBufPhys;

void audioFrameBuild(void) {
    s32 sp10;
    s16 *temp_a1;
    s16 temp_v0;
    s32 *temp_s1;
    s32 temp_s0;
    u32 temp_v0_2;

    gAudioFrameLock = 1;
    gAudioBufPtr = gAudioOutBuf;
    temp_s0 = gAudioFrameCount % 3;
    temp_s1 = (temp_s0 * 4) + &gAudioAiBuf;
    gRspTask = *((gAudioModeIdx * 4) + &gAudioYieldBuf);
    gAudioBufPhys = osVirtualToPhysical(*temp_s1);
    temp_a1 = (temp_s0 * 2) + &gAudioBufSizes;
    temp_v0 = (((gAudioBufBase2 - gAudioBufBase) + 0x28) & ~0xF) + 0x10;
    *temp_a1 = temp_v0;
    if (temp_v0 < gAudioBufSizeMin.unk0) {
        *temp_a1 = (s16) gAudioBufSizeMin.unk2;
    }
    if (!((*temp_s1 + (*temp_a1 * 4)) & 0x1FFF)) {
        *temp_a1 = (u16) *temp_a1 + 0x10;
    }
    temp_v0_2 = audioBuildFrame(gAudioBufPtr, &sp10, gAudioBufPhys, *temp_a1);
    gAudioBufPtr = temp_v0_2;
    if ((u32) (gAudioOutBuf + 0x4E20) < temp_v0_2) {
        M2C_BREAK(0);
    }
    gRspTask->unk0 = 2;
    gRspTask->unkC = (s32) (&gAudioUcodeEnd - &gAudioUcode);
    gRspTask->unk8 = &gAudioUcode;
    gRspTask->unk10 = &gAudioRspData;
    gRspTask->unk14 = 0x1000;
    gRspTask->unk1C = (s32) (((s32) (&gAudioUcodeImemEnd - &gAudioUcodeStart) >> 3) * 8);
    gRspTask->unk4 = 0;
    gRspTask->unk18 = &gAudioUcodeStart;
    gRspTask->unk30 = (u32) gAudioOutBuf;
    gRspTask->unk34 = (s32) (((s32) (temp_v0_2 - gAudioOutBuf) >> 3) * 8);
    audioQueueDispatchGetter(gRspTask, temp_v0_2, gAudioOutBuf);
    midiQueueProcess();
}

void audioSetCallback(s32 arg0) {
    gAudioCallback = arg0;
    if ((gAudioStatus != 0) && (gAudioStatus != 4)) {
        gAudioStatus = 3;
    }
}
