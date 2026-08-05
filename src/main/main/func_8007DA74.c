#include "ultra64.h"
void func_80086078();                                  /* extern */
extern s32 gPendingFlushFlag;

void func_8007DA74(void) {
    if ((s32)0 /* implicit $t6 from caller */ != 0) {
        func_80086078();
        gPendingFlushFlag = 0;
    }
}

void func_8007DAA4(void) {

}
