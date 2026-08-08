#include "ultra64.h"
s32 sfxHasEntity(void *);                             /* extern */
void gameHandlerSetup(s32, s32);                        /* extern */
extern s32 gHandlerTable;
extern Unk D_801887D0;

void entityHandlerSetupEx(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    if (sfxHasEntity(&gHandlerTable) == 0) {
        D_801887D0.unk4 = arg2;
        D_801887D0.unk8 = arg3;
        D_801887D0.unkC = arg4;
        D_801887D0.unk10 = arg5;
        D_801887D0.unk1C = 0;
        D_801887D0.unk20 = 0;
        D_801887D0.unk14 = arg6;
        gameHandlerSetup(0xA, arg1);
    }
}

s32 entityFindActive(void) {
    Unk *var_a0;
    s32 temp_v0;
    s32 var_v1;

    var_v1 = 0;
    var_a0 = &D_801887D0;
loop_1:
    temp_v0 = var_a0->unk31C;
    if (temp_v0 != 2) {
        if (temp_v0 != 4) {
            var_v1 += 1;
            var_a0 += 4;
            if (var_v1 >= 4) {
                return -1;
            }
            goto loop_1;
        }
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return var_v1;
    }
    return var_v1;
}

s32 func_80070F18(void) {
    Unk *var_a0;
    s32 var_v1;

    var_v1 = 0;
    var_a0 = &D_801887D0;
loop_1:
    if (var_a0->unk31C != 5) {
        var_v1 += 1;
        var_a0 += 4;
        if (var_v1 >= 4) {
            return -1;
        }
        goto loop_1;
    }
    return var_v1;
}
