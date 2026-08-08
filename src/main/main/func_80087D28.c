#include "ultra64.h"
void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
s32 osSendMesg(Unk*, s32, s32);                         /* extern */
extern s32 gSiAcquired;
extern s32 gSiMutexMsg;
extern s32 gSiMutexQueue;

void __siInit(void) {
    gSiAcquired = 1;
    osCreateMesgQueue(&gSiMutexQueue, &gSiMutexMsg, 1);
    osSendMesg(&gSiMutexQueue, 0, 0);
}
