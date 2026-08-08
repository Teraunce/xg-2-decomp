#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of audioGetRspCount (initial). */

void audioRspSubmit(Unk *);                       /* extern */
s32 osRecvMesg(Unk*, s32*, s32);                       /* extern */
extern s32 gRspDmaMesgQueue;
extern s32 gAudioDecodeCount;

void viSwapBuffers(Unk *arg0) {
    s32 sp10;
    s32 temp_a1;

    if (arg0->unk14 != 0) {
        if (gAudioDecodeCount != 0) {
            osRecvMesg(&gRspDmaMesgQueue, &sp10, 1);
            gAudioDecodeCount -= 1;
        }
        temp_a1 = arg0->unk4;
        arg0->unkC = 0;
        arg0->unk8 = (s32) (1 - arg0->unk8);
        arg0->unk10 = (s32) arg0->unk14;
        if (temp_a1 == 0) {
            arg0->unk14 = 0;
            return;
        }
        audioRspSubmit(arg0);
    }
}

s32 audioGetRspCount(void) {
    return gAudioDecodeCount;
}
