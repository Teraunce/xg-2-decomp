#include "ultra64.h"
s32 sfxHasEntity(void *);                             /* extern */
void gameHandlerSetup(s32, s32);                        /* extern */
extern s32 gHandlerTable;
extern Unk gHandlerCtx;

void entityHandlerSetup(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (sfxHasEntity(&gHandlerTable) == 0) {
        gHandlerCtx.unk4 = arg2;
        gHandlerCtx.unk8 = arg3;
        gHandlerCtx.unk1C = arg4;
        gameHandlerSetup(7, arg1);
    }
}
