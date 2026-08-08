#include "ultra64.h"
extern u8 gSfxVoiceCount;

void func_80087EB8(char *arg0) {
    Unk *spC;
    s8 sp4;
    s32 sp0;
    s32 temp_t9;
    Unk *var_a0;
    s32 sp6; s32 sp8; s32 spA; s32 spB;

    var_a0 = arg0;
    spC = (s32)0 /* implicit $t6 from caller */ - 0x52D8;
    sp0 = 0;
    if ((s32)0 /* implicit $t7 from caller */ > 0) {
        do {
            ((Unk*)&sp4)->unk0 = (s32) (s32) spC->unk0;
            ((Unk*)&sp4)->unk4 = (s32) (s32) spC->unk4;
            var_a0->unk4 = (u8) ((s32) (sp6 & 0xC0) >> 4);
            if (var_a0->unk4 == 0) {
                var_a0->unk0 = sp8;
                var_a0->unk2 = spA;
                var_a0->unk3 = spB;
            }
            temp_t9 = sp0 + 1;
            spC += 8;
            sp0 = temp_t9;
            var_a0 += 6;
        } while (temp_t9 < (s32) gSfxVoiceCount);
    }
}
