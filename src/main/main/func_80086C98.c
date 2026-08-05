#include "ultra64.h"
s32 osVirtualToPhysical(u32);                             /* extern */
s32 sfxIsBusy();                                /* extern */
extern s32 D_A4040000;
extern s32 D_A4040004;
extern s32 D_A4040008;
extern s32 D_A404000C;

s32 osSpRawStartDma(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (sfxIsBusy() != 0) {
        return -1;
    }
    D_A4040000 = arg1;
    D_A4040004 = osVirtualToPhysical(arg2);
    if (arg0 == 0) {
        D_A404000C = arg3 - 1;
    } else {
        D_A4040008 = arg3 - 1;
    }
    return 0;
}
