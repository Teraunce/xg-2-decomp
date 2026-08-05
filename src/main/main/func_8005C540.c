#include "ultra64.h"
void func_8005C010();                                  /* extern */
void __osInvalICache_full();                                  /* extern */
s32 osRecvMesg(Unk*, s32*, s32);                         /* extern */
s32 osAiRawStartDma(s32, s32);                          /* extern */
void func_80086A44(void *);                               /* extern */
void osSpTaskStart(s32);                               /* extern */
extern s32 gAudioBufSizes;
extern s32 D_800927D8;
extern s32 gAudioModeIdx;
extern s32 gAudioFrameCount;
extern u32 D_800927FC;
extern s32 D_8017EFC8;
extern s32 D_8017F438;
extern s32 D_80180884;
extern s32 D_801816A8;

s32 func_8005C540(void) {
    s32 temp_a1;
    s32 var_s0;

    if ((s32)0 /* implicit $v0 from caller */ != 0) {
        D_800927FC = (u32) *(u32 *)0xA4500004 >> 2;
        temp_a1 = (gAudioFrameCount - 1) % 3;
        osAiRawStartDma(*((temp_a1 * 4) + &D_8017F438), *((temp_a1 * 2) + &gAudioBufSizes) * 4);
        var_s0 = 0;
        if (D_800927D8 > 0) {
            do {
                osRecvMesg(&D_8017EFC8, 0, 0);
                var_s0 += 1;
            } while (var_s0 < D_800927D8);
        }
        __osInvalICache_full();
        func_80086A44(D_80180884);
        osSpTaskStart(D_80180884);
        func_8005C010();
        D_800927D8 = 0;
        D_801816A8 += 1;
        gAudioFrameCount += 1;
        gAudioModeIdx ^= 1;
    }
    return 0;
}
