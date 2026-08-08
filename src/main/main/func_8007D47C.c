#include "ultra64.h"
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
s32 __osGetCount();                                /* extern */
void setCOP0Compare();                              /* extern */
extern s32 gTimerBase;

void __osTimerSetCompare(s32 arg0, u32 arg1) {
    u32 sp24;
    s32 sp20;
    s32 sp1C;
    u32 temp_t3;

    sp1C = osDisableInt();
    gTimerBase = __osGetCount();
    temp_t3 = gTimerBase + arg1;
    sp20 = (temp_t3 < arg1) + arg0;
    sp24 = temp_t3;
    setCOP0Compare();
    osRestoreInt(sp1C);
}
