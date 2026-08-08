#include "ultra64.h"
void renderTexLine(s16, s32, s32, s32, s32);           /* extern */

void renderTexLineW(s16 arg3, s16 arg4, s32 arg5, s32 arg6) {
    renderTexLine(arg3, (s32) arg4, arg5, arg6, 0);
}
