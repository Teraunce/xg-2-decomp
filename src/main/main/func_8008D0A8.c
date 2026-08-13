#include "ultra64.h"
s32 osVirtualToPhysical(u32);                             /* extern */
extern s32 osRomBase;
extern s32 PI_DRAM_ADDR;
extern s32 PI_CART_ADDR;
extern s32 PI_RD_LEN;
extern s32 PI_WR_LEN;

s32 osEPiStartDma_simple(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (PI_STATUS_REG & 3) {
        do {

        } while (PI_STATUS_REG & 3);
    }
    PI_DRAM_ADDR = osVirtualToPhysical(arg2);
    PI_CART_ADDR = (osRomBase | arg1) & 0x1FFFFFFF;
    switch (arg0) {                                 /* irregular */
    case 0:
        PI_WR_LEN = arg3 - 1;
block_8:
        return 0;
    case 1:
        PI_RD_LEN = arg3 - 1;
        goto block_8;
    default:
        return -1;
    }
}
