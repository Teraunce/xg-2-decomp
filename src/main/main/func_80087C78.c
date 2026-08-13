#include "ultra64.h"
void osWritebackInvalDCache(u32, s32);                            /* extern */
void osWritebackDCache(u32, s32);                            /* extern */
s32 osVirtualToPhysical(u32);                             /* extern */
s32 __osPiIsBusy();                                /* extern */
extern s32 SI_DRAM_ADDR;

s32 osSiRawStartDma(s32 arg0, s32 arg1) {
    if (__osPiIsBusy() != 0) {
        return -1;
    }
    if (arg0 == 1) {
        osWritebackDCache(arg1, 0x40);
    }
    SI_DRAM_ADDR = osVirtualToPhysical(arg1);
    if (arg0 == 0) {
        SI_PIF_ADDR_RD64B = 0x1FC007C0;
    } else {
        SI_PIF_ADDR_WR64B = 0x1FC007C0;
    }
    if (arg0 == 0) {
        osWritebackInvalDCache(arg1, 0x40);
    }
    return 0;
}
