#include "ultra64.h"
void __siInit();                                  /* extern */
extern s32 gSiMutexQueue;

void __siAcquire(void) {
    s32 sp1C;

    if ((s32)0 /* implicit $t6 from caller */ == 0) {
        __siInit();
    }
    osRecvMesg(&gSiMutexQueue, &sp1C, 1);
}
