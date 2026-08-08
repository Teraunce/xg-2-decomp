#include "ultra64.h"
s32 __osPiIsBusy();                                /* extern */
extern s32 gPhysMemBase;

s32 osEPiRawWriteIo(s32 arg0, s32 arg1) {
    if (__osPiIsBusy() != 0) {
        return -1;
    }
    *(s32*)(s32)(arg0 | (s32) &gPhysMemBase) = arg1;
    return 0;
}
