#include "ultra64.h"
s32 sfxHasEntity(void *);                             /* extern */
s32 alignUp256(s32);                               /* extern */
void gameHandlerSetup(s32, s32);                        /* extern */
extern s32 gHandlerTable;
extern Unk gHandlerCtx;

void handlerSetupLooped(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (sfxHasEntity(&gHandlerTable) == 0) {
        gHandlerCtx.unk4 = arg2;
        gHandlerCtx.unk8 = alignUp256(arg3);
        gameHandlerSetup(5, arg1);
    }
}
