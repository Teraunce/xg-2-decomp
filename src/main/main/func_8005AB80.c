#include "ultra64.h"
void audioRspSubmit(Unk*);                               /* extern */
void audioSetupCopySample(Unk*, s32, s32);                       /* extern */
void safeCopy(u32, u32, u32);                  /* extern */
s32 osRecvMesg(Unk*, s32*, s32);                       /* extern */
extern s32 D_8016DF70;
extern s32 D_8017CDF8;
extern s32 D_80190000;

void audioPlayCopySample(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 var_s0;

    var_s0 = arg2;
    audioSetupCopySample(&sp10, arg0, arg1);
    if (sp24 != 0) {
        do {
            if (D_8017CDF8 != 0) {
                osRecvMesg(&D_8016DF70, &sp28, 1);
                D_8017CDF8 -= 1;
            }
            sp1C = 0;
            sp18 = 1 - sp18;
            sp20 = sp24;
            if (sp14 == 0) {
                sp24 = 0;
            } else {
                audioRspSubmit(&sp10);
            }
            safeCopy(var_s0, (sp18 << 0xA) + &D_80190000, sp20);
            var_s0 += sp20;
        } while (sp24 != 0);
    }
}
