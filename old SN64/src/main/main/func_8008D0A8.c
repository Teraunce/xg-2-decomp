#include "ultra64.h"
s32 func_8007D688(u32);                             /* extern */
extern s32 D_80000308;
extern s32 D_A4600000;
extern s32 D_A4600004;
extern s32 D_A4600008;
extern s32 D_A460000C;
extern s32 D_A4600010;

s32 func_8008D0A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_A4600010 & 3) {
        do {

        } while (D_A4600010 & 3);
    }
    D_A4600000 = func_8007D688(arg2);
    D_A4600004 = (D_80000308 | arg1) & 0x1FFFFFFF;
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
