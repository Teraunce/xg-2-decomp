#include "ultra64.h"
s32 osRecvMesg(Unk*, s32*, s32);                       /* extern */
void piMgrInit();                                  /* extern */
extern s32 D_8018D310;

void __piLock(void) {
    s32 sp1C;

    if ((s32)0 /* implicit $t6 from caller */ == 0) {
        piMgrInit();
    }
    osRecvMesg(&D_8018D310, &sp1C, 1);
}
