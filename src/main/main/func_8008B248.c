#include "ultra64.h"
s32 osRecvMesg(Unk*, s32*, s32);                       /* extern */
s32 osSiRawStartDma(s32, s32);                          /* extern */
s32 __siLock();                                  /* extern */
void __siUnlock();                                  /* extern */
void siInitPollCmd(s32);                                 /* extern */
s32 func_8008B4E4(void *, s32 (*)[]);                    /* extern */
extern u8 D_8018AD69;
extern s32 D_8018ADB8;

s32 siQueryControllers(s32 arg0, u8 *arg1) {
    Unk *sp = (Unk*)0;
    s32 sp3C;
    s32 sp38[2];
    s32 sp37;
    s32 sp20;
    u8 sp1F;
    s32 sp18;
    Unk *temp_t4;
    s32 temp_t5;
    s32 temp_t5_2;
    Unk sp24[8];

    sp3C = 0;
    sp1F = 0;
    sp18 = 3;
    __siLock();
    do {
        siInitPollCmd(0);
        sp3C = osSiRawStartDma(1, &D_8018ADB8);
        osRecvMesg(arg0, &sp38, 1);
        sp3C = osSiRawStartDma(0, &D_8018ADB8);
        osRecvMesg(arg0, &sp38, 1);
        func_8008B4E4(&sp37, (s32 (*)[]) (void*) &sp24[0]);
        sp20 = 0;
        if ((s32) D_8018AD69 > 0) {
loop_2:
            if (!((sp + (sp20 * 4))->unk26 & 4)) {
                sp18 -= 1;
            } else {
                temp_t5 = sp20 + 1;
                sp20 = temp_t5;
                if (temp_t5 < (s32) D_8018AD69) {
                    goto loop_2;
                }
            }
        }
        if (D_8018AD69 == sp20) {
            sp18 = 0;
        }
    } while (sp18 > 0);
    sp20 = 0;
    if ((s32) D_8018AD69 > 0) {
        do {
            temp_t4 = &(&sp24[0])[sp20];
            if ((temp_t4->unk3 == 0) && (temp_t4->unk2 & 1)) {
                sp1F |= 1 << sp20;
            }
            temp_t5_2 = sp20 + 1;
            sp20 = temp_t5_2;
        } while (temp_t5_2 < (s32) D_8018AD69);
    }
    __siUnlock();
    *arg1 = sp1F;
    return sp3C;
}
