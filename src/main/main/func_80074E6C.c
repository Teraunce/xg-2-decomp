#include "ultra64.h"
void renderTexLineW(s16, s16, s32, s32);                /* extern */

void renderTexLineWW(s16 arg3, s16 arg4, s32 arg5) {
    renderTexLineW(arg3, (s32) arg4, arg5, arg5);
}
