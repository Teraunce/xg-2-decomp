#include "ultra64.h"
extern s32 D_80000308;
extern s32 D_A4600010;

s32 func_8008CEC0(s32 arg0, s32 *arg1, s32 arg2) {
    if (arg2 & 3) {
        do {

        } while (D_A4600010 & 3);
    }
    *arg1 = *(s32*)(s32)(D_80000308 | arg0 | 0xA0000000);
    return 0;
}
