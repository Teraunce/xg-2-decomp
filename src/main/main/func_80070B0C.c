#include "ultra64.h"
s32 handlerGetResult(s32);                                 /* extern */

void contPakHandlerWait(void) {
loop_1:
    handlerGetResult(-1);
    goto loop_1;
}
