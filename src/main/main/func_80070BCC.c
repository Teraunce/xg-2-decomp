#include "ultra64.h"
void sfxHeapInsert(void *, s32, s32);                         /* extern */
s32 func_80062278();                                /* extern */
extern s32 gHandlerTable;
extern Unk D_801887D0;

void gameHandlerSetup(s32 arg1, s32 arg2) {
    D_801887D0.unk174 = arg2;
    D_801887D0.unk178 = func_80062278();
    D_801887D0.unk168 = 1;
    D_801887D0.unk16C = 0;
    D_801887D0.unk170 = 0;
    D_801887D0.unk0 = arg1;
    D_801887D0.unk160 = 0;
    sfxHeapInsert(&gHandlerTable, -1, 1);
}
