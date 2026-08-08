#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of osEPiRawWriteIoGetter (initial). */

extern s32 gPhysMemBase;
extern s32 PI_STATUS_REG;

s32 osEPiRawReadIo(Unk *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    if (arg3 & 3) {
        do {

        } while (PI_STATUS_REG & 3);
    }
    *arg2 = *(s32*)(s32)(arg0->unkC | arg1 | (s32) &gPhysMemBase);
    return 0;
}

s32 osEPiRawWriteIo(void);  /* forward: GETTER_NOJR fallthrough */
void osEPiRawWriteIoGetter(void) {
    return osEPiRawWriteIo();
}
