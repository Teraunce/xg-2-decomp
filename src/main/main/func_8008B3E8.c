#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of contParsePollRespGetter (initial). */

extern s8 D_8018AD68;
extern u8 D_8018AD69;
extern s32 D_8018ADB8;
extern s32 D_8018ADF4;

void siInitPollCmd(s32 arg0) {
    Unk *spC;
    s8 spB;
    s8 spA;
    s8 sp9;
    s8 sp8;
    s8 sp7;
    s8 sp6;
    s8 sp5;
    s8 sp4;
    s32 sp0;
    s32 temp_t7;
    s32 temp_t9;
    s8 temp_a0;

    temp_a0 = arg0 & 0xFF;
    D_8018AD68 = temp_a0;
    sp0 = 0;
    do {
        *(&D_8018ADB8 + (sp0 * 4)) = 0;
        temp_t9 = sp0 + 1;
        sp0 = temp_t9;
    } while (temp_t9 < 0x10);
    D_8018ADF4 = 1;
    spC = &D_8018ADB8;
    sp4 = 0xFF;
    sp5 = 1;
    sp6 = 3;
    sp7 = temp_a0;
    sp8 = 0xFF;
    sp9 = 0xFF;
    spA = 0xFF;
    spB = 0xFF;
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

void contParsePollResp(void);  /* forward: GETTER_NOJR fallthrough */
void contParsePollRespGetter(void) {
    contParsePollResp();
}
