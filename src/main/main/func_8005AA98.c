#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8005AB28 (initial). */

void func_8005A978(Unk *);                       /* extern */
s32 osRecvMesg(Unk*, s32*, s32);                       /* extern */
extern s32 D_8016DF70;
extern s32 D_8017CDF8;

void viSwapBuffers(Unk *arg0) {
    s32 sp10;
    s32 temp_a1;

    if (arg0->unk14 != 0) {
        if (D_8017CDF8 != 0) {
            osRecvMesg(&D_8016DF70, &sp10, 1);
            D_8017CDF8 -= 1;
        }
        temp_a1 = arg0->unk4;
        arg0->unkC = 0;
        arg0->unk8 = (s32) (1 - arg0->unk8);
        arg0->unk10 = (s32) arg0->unk14;
        if (temp_a1 == 0) {
            arg0->unk14 = 0;
            return;
        }
        func_8005A978(arg0);
    }
}

s32 func_8005AB28(void) {
    return D_8017CDF8;
}
