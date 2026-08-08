#include "ultra64.h"
void sfxHeapInsert(void *, s32, s32);                         /* extern */
s32 sfxGetAllocEntity();                                /* extern */
extern s32 gHandlerTable;
extern Unk gHandlerCtx;

void gameHandlerSetup(s32 arg1, s32 arg2) {
    gHandlerCtx.unk174 = arg2;
    gHandlerCtx.unk178 = sfxGetAllocEntity();
    gHandlerCtx.unk168 = 1;
    gHandlerCtx.unk16C = 0;
    gHandlerCtx.unk170 = 0;
    gHandlerCtx.unk0 = arg1;
    gHandlerCtx.unk160 = 0;
    sfxHeapInsert(&gHandlerTable, -1, 1);
}
