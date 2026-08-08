#include "ultra64.h"
void audioRspSubmit(Unk *);                                  /* extern */
extern s32 gAudioDecodeCount;

void audioSetupCopySample(Unk *arg0, s32 arg1, s32 arg2) {
    arg0->unk0 = arg1;
    arg0->unk4 = arg2;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk10 = 0;
    gAudioDecodeCount = 0;
    audioRspSubmit(arg0);
}
