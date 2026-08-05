#include "ultra64.h"
s32 func_8006216C(void *);                             /* extern */
void func_80070BCC(s32, s32);                        /* extern */
extern s32 D_80093EE4;
extern Unk D_801887D0;

void func_80070D50(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_8006216C(&D_80093EE4) == 0) {
        D_801887D0.unk4 = arg2;
        D_801887D0.unk1C = arg3;
        func_80070BCC(6, arg1);
    }
}
