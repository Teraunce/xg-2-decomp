#include "ultra64.h"
extern s32 D_8018AD28;
extern s32 D_8018AD64;
extern u8 D_8018AD69;

void func_80087F54(void) {
    Unk *spC;
    s8 spB;
    s8 spA;
    s16 sp8;
    s8 sp7;
    s8 sp6;
    s8 sp5;
    s8 sp4;
    s32 sp0;
    s32 temp_t0;
    s32 temp_t7;

    spC = &D_8018AD28;
    sp0 = 0;
    do {
        *(&D_8018AD28 + (sp0 * 4)) = 0;
        temp_t0 = sp0 + 1;
        sp0 = temp_t0;
    } while (temp_t0 < 0x10);
    D_8018AD64 = 1;
    sp4 = 0xFF;
    sp5 = 1;
    sp6 = 4;
    sp7 = 1;
    sp8 = 0xFFFF;
    spA = -1;
    spB = -1;
    sp0 = 0;
    if ((s32) D_8018AD69 > 0) {
        do {
            spC->unk0 = (s32) ((Unk*)&sp4)->unk0;
            spC->unk4 = (s32) ((Unk*)&sp4)->unk4;
            temp_t7 = sp0 + 1;
            sp0 = temp_t7;
            spC += 8;
        } while (temp_t7 < (s32) D_8018AD69);
    }
    spC->unk0 = 0xFE;
}
