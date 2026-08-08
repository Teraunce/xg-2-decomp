#include "ultra64.h"
void osSetTimer(void**, s32, s32);                     /* extern */

void audioTimerSetDecay(s32 arg0, s32 arg1) {
    s32 sp1C;
    s16 sp18;

    sp1C = arg1;
    sp18 = 0xD;
    osSetTimer(arg0 + 0x48, &sp18, 0);
}
