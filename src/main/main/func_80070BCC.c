#include "ultra64.h"
void func_80061FB4(void *, s32, s32);                         /* extern */
s32 func_80062278();                                /* extern */
extern s32 D_80093EE4;
extern Unk D_801887D0;

void func_80070BCC(s32 arg1, s32 arg2) {
    D_801887D0.unk174 = arg2;
    D_801887D0.unk178 = func_80062278();
    D_801887D0.unk168 = 1;
    D_801887D0.unk16C = 0;
    D_801887D0.unk170 = 0;
    D_801887D0.unk0 = arg1;
    D_801887D0.unk160 = 0;
    func_80061FB4(&D_80093EE4, -1, 1);
}
