#include "ultra64.h"
void osSetTimer(void**, s32, s32);                     /* extern */

void audioTimerSetAttack(s32 arg0, s16 arg1) {
    s16 sp1C;
    s16 sp18;

    sp18 = 0xA;
    sp1C = arg1;
    osSetTimer(arg0 + 0x48, &sp18, 0);
}
