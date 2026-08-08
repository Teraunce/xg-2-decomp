#include "ultra64.h"
void osSendMesg(void *, int, int);
extern int gSiMutexQueue;

void __siUnlock(void) {
    osSendMesg(&gSiMutexQueue, 0, 0);
}
