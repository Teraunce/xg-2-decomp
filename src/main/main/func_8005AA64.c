#include "ultra64.h"
void audioRspSubmit(Unk *);                                  /* extern */
extern s32 D_8017CDF8;

void audioSetupCopySample(Unk *arg0, s32 arg1, s32 arg2) {
    arg0->unk0 = arg1;
    arg0->unk4 = arg2;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk10 = 0;
    D_8017CDF8 = 0;
    audioRspSubmit(arg0);
}
