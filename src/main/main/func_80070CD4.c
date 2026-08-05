#include "ultra64.h"
s32 sfxHasEntity(void *);                             /* extern */
s32 func_800705D0(s32);                               /* extern */
void gameHandlerSetup(s32, s32);                        /* extern */
extern s32 gHandlerTable;
extern Unk D_801887D0;

void func_80070CD4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (sfxHasEntity(&gHandlerTable) == 0) {
        D_801887D0.unk4 = arg2;
        D_801887D0.unk8 = func_800705D0(arg3);
        gameHandlerSetup(5, arg1);
    }
}
