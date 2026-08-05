#include "ultra64.h"
s32 osVirtualToPhysical(u32);                             /* extern */
extern s32 osRomBase;
extern s32 D_A4600000;
extern s32 D_A4600004;
extern s32 D_A4600008;
extern s32 D_A460000C;
extern s32 D_A4600010;

s32 osEPiStartDma_simple(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_A4600010 & 3) {
        do {

        } while (D_A4600010 & 3);
    }
    D_A4600000 = osVirtualToPhysical(arg2);
    D_A4600004 = (osRomBase | arg1) & 0x1FFFFFFF;
    switch (arg0) {                                 /* irregular */
    case 0:
        D_A460000C = arg3 - 1;
block_8:
        return 0;
    case 1:
        D_A4600008 = arg3 - 1;
        goto block_8;
    default:
        return -1;
    }
}
