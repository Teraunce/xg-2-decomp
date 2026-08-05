#include "ultra64.h"
s32 handlerGetResult(s32);                                 /* extern */

void func_80070B0C(void) {
loop_1:
    handlerGetResult(-1);
    goto loop_1;
}
