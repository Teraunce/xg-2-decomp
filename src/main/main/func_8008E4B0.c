#include "ultra64.h"
void piMgrInit();                                  /* extern */
extern s32 gFontMesgQueue;

void __piLock(void) {
    s32 sp1C;

    if ((s32)0 /* implicit $t6 from caller */ == 0) {
        piMgrInit();
    }
    osRecvMesg(&gFontMesgQueue, &sp1C, 1);
}
