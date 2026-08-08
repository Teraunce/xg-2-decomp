#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of osEPiRawReadIoGetter (initial). */

s32 __osEnqueueWait(void *);                               /* extern */
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
extern s32 __osRunQueue;
extern Unk *__osRunningThread;
extern s32 PI_STATUS_REG;

void __osPiWait(void) {
    s32 temp_s0;

    temp_s0 = osDisableInt();
    __osRunningThread->unk10 = 2;
    __osEnqueueWait(&__osRunQueue);
    osRestoreInt(temp_s0);
}

s32 osEPiRawReadIo(void);  /* forward: GETTER_NOJR fallthrough */
void osEPiRawReadIoGetter(void) {
    return osEPiRawReadIo();
}
