#include "ultra64.h"
s32 osRecvMesg(Unk*, s32*, s32);                       /* extern */
void __siInit();                                  /* extern */
extern s32 D_8018AD10;

void __siAcquire(void) {
    s32 sp1C;

    if ((s32)0 /* implicit $t6 from caller */ == 0) {
        __siInit();
    }
    osRecvMesg(&D_8018AD10, &sp1C, 1);
}
