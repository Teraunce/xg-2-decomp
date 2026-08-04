#include "ultra64.h"
s32 func_8007FD48(s32, s32, s32, s32, s32);               /* extern */
void func_80084EF8(Unk*, s32, s32, s32);              /* extern */
extern s32 func_80083638;
extern s32 func_80083CE4;

void func_8008300C(Unk *arg0, s32 (*arg1)(void *), s32 arg2) {
    func_80084EF8(arg0, &func_80083CE4, &func_80083638, 0);
    arg0->unk14 = func_8007FD48(0, 0, arg2, 1, 0x20);
    arg0->unk18 = func_8007FD48(0, 0, arg2, 1, 0x20);
    arg0->unk30 = arg1(arg0 + 0x34);
    arg0->unk3C = 0;
    arg0->unk40 = 1;
    arg0->unk44 = 0;
}
