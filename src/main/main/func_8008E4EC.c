#include "ultra64.h"
void osSendMesg(void *, int, int);
extern int gFontMesgQueue;

void __piUnlock(void) {
    osSendMesg(&gFontMesgQueue, 0, 0);
}
