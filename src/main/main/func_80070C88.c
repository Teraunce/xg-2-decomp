#include "ultra64.h"
s32 sfxHasEntity(void *);                             /* extern */
void gameHandlerSetup(s32, s32);                        /* extern */
extern s32 gHandlerTable;

void sfxHandlerEnsure(s32 arg0, s32 arg1) {
    if (sfxHasEntity(&gHandlerTable) == 0) {
        gameHandlerSetup(2, arg1);
    }
}
