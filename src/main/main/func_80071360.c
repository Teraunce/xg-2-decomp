#include "ultra64.h"
s32 handlerPostCmd(s32, s32, s32, s32, s32, s32, s32);       /* extern */
extern Unk gHandlerCtx;

void contPakHandlerStatus(s32 arg0) {
    Unk *var_a0;
    s32 temp_v0;
    s32 var_v1;

    var_v1 = 0;
    if (arg0 > 0) {
        var_a0 = &gHandlerCtx;
loop_2:
        temp_v0 = var_a0->unk31C;
        if (temp_v0 != 2) {
            var_v1 += 1;
            if (temp_v0 != 4) {
                var_a0 += 4;
                if (var_v1 >= arg0) {
                    goto block_5;
                }
                goto loop_2;
            }
        }
    } else {
block_5:
        if (gHandlerCtx.unk170 != 0) {
            handlerPostCmd(0x51, arg0, 0, 0, 0, 0, 0);
            gHandlerCtx.unk170 = 0;
            return;
        }
        handlerPostCmd(0x41, arg0, 0, 0, 0, 0, 0);
    }
}
