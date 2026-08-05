#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8008E3B8 (initial). */

s32 __osEnqueueWait(void *);                               /* extern */
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
extern s32 __osRunQueue;
extern Unk *__osRunningThread;
extern s32 D_A4600010;

void func_8008E368(void) {
    s32 temp_s0;

    temp_s0 = osDisableInt();
    __osRunningThread->unk10 = 2;
    __osEnqueueWait(&__osRunQueue);
    osRestoreInt(temp_s0);
}

void func_8008E3B8(void) {

}
