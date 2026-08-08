#include "ultra64.h"
void audioBufRecycle();                                  /* extern */
void __osInvalICache_full();                                  /* extern */
s32 osRecvMesg(Unk*, s32*, s32);                         /* extern */
s32 osAiRawStartDma(s32, s32);                          /* extern */
void sfxLoadUcode(void *);                               /* extern */
void osSpTaskStart(s32);                               /* extern */
extern s32 gAudioBufSizes;
extern s32 gAudioFrameIdx;
extern s32 gAudioModeIdx;
extern s32 gAudioFrameCount;
extern u32 gAiLenCount;
extern s32 gAudioMesgQueue;
extern s32 gAudioAiBuf;
extern s32 gRspTask;
extern s32 gAudioFrameCount;

s32 audioRspDone(void) {
    s32 temp_a1;
    s32 var_s0;

    if ((s32)0 /* implicit $v0 from caller */ != 0) {
        gAiLenCount = (u32) *(u32 *)0xA4500004 >> 2;
        temp_a1 = (gAudioFrameCount - 1) % 3;
        osAiRawStartDma(*((temp_a1 * 4) + &gAudioAiBuf), *((temp_a1 * 2) + &gAudioBufSizes) * 4);
        var_s0 = 0;
        if (gAudioFrameIdx > 0) {
            do {
                osRecvMesg(&gAudioMesgQueue, 0, 0);
                var_s0 += 1;
            } while (var_s0 < gAudioFrameIdx);
        }
        __osInvalICache_full();
        sfxLoadUcode(gRspTask);
        osSpTaskStart(gRspTask);
        audioBufRecycle();
        gAudioFrameIdx = 0;
        gAudioFrameCount += 1;
        gAudioFrameCount += 1;
        gAudioModeIdx ^= 1;
    }
    return 0;
}
