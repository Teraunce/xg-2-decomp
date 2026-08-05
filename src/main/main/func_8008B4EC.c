#include "ultra64.h"
extern u8 D_8018AD69;
extern s32 D_8018ADB8;

void func_8008B4EC(u8 *arg0, char *arg1) {
    Unk *sp14;
    s8 spC;
    s32 sp8;
    u8 sp7;
    s32 temp_t7;
    Unk *var_a1;
    s32 spE; s32 sp10; s32 sp11; s32 sp12;

    var_a1 = arg1;
    sp7 = 0;
    sp14 = &D_8018ADB8;
    sp8 = 0;
    if ((s32)0 /* implicit $t7 from caller */ > 0) {
        do {
            ((Unk*)&spC)->unk0 = (s32) (s32) sp14->unk0;
            ((Unk*)&spC)->unk4 = (s32) (s32) sp14->unk4;
            var_a1->unk3 = (u8) ((s32) (spE & 0xC0) >> 4);
            if (var_a1->unk3 == 0) {
                var_a1->unk0 = (s16) ((sp11 << 8) | sp10);
                var_a1->unk2 = sp12;
                sp7 |= 1 << sp8;
            }
            temp_t7 = sp8 + 1;
            sp14 += 8;
            sp8 = temp_t7;
            var_a1 += 4;
        } while (temp_t7 < (s32) D_8018AD69);
    }
    *arg0 = sp7;
}
