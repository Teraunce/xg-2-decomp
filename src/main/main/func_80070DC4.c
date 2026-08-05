#include "ultra64.h"
s32 func_8006216C(void *);                             /* extern */
void func_80070BCC(s32, s32);                        /* extern */
extern s32 gHandlerTable;
extern Unk D_801887D0;

void func_80070DC4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (func_8006216C(&gHandlerTable) == 0) {
        D_801887D0.unk4 = arg2;
        D_801887D0.unk8 = arg3;
        D_801887D0.unk1C = arg4;
        func_80070BCC(7, arg1);
    }
}
