#include "ultra64.h"
extern int gFontMesgQueue;

void __piUnlock(void) {
    osSendMesg(&gFontMesgQueue, 0, 0);
}
