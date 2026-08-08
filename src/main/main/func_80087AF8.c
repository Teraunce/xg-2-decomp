#include "ultra64.h"
s32 __osPiIsBusy(void);                                /* static */
extern s32 gPhysMemBase;
extern s32 SI_STATUS;

s32 osEPiRawReadIo(s32 arg0, s32 *arg1) {
    if (__osPiIsBusy() != 0) {
        return -1;
    }
    *arg1 = *(s32*)(s32)(arg0 | (s32) &gPhysMemBase);
    return 0;
}

s32 __osPiIsBusy(void) {

}
