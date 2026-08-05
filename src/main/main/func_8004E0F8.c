#include "ultra64.h"
void func_8004DC24(Unk*, s32, s32, s32, s32, s32, s32);       /* extern */
void func_8007BD08(OSThread*, OSId, u32, s32, u32, OSPri);          /* extern */
void func_8007D008(Unk*, s32);                              /* extern */
void func_8007D0E8(Unk*);                               /* extern */
void func_80086DD8(s32);                                 /* extern */
void func_80087318(char*);                               /* extern */
void func_80087388(s32);                                 /* extern */
void func_80087A88(u8);                                 /* extern */
void func_8008CF18(s32, char*, char*, s32);                    /* extern */
extern s32 D_8016D9D0;
extern s32 D_80170310;
extern s32 D_80170378;
extern s32 D_80170398;
extern s32 D_801706B8;
extern s32 func_8004E21C;

void func_8004E0F8(void) {
    func_80086DD8(0xFE);
    func_8004DC24(&D_80170310, 0x140, 0xF0, 0, 0, 0, 0);
    func_80087318(&D_80170310);
    func_80087388(0x42);
    func_80087A88(1);
    func_8008CF18(0x96, &D_80170378, &D_80170398, 0xC8);
    func_8007BD08(&D_801706B8, 3, &func_8004E21C, 0, &D_8016D9D0, 0xA);
    func_8007D0E8(&D_801706B8);
    func_8007D008(0, 0);
loop_1:
    goto loop_1;
}
