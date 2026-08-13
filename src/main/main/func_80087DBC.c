#include "ultra64.h"
extern int gSiMutexQueue;

void __siUnlock(void) {
    osSendMesg(&gSiMutexQueue, 0, 0);
}
