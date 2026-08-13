#include "ultra64.h"
extern s32 osRomBase;

s32 osEPiRawReadIo_cart(s32 arg0, s32 *arg1, s32 arg2) {
    if (arg2 & 3) {
        do {

        } while (PI_STATUS_REG & 3);
    }
    *arg1 = *(s32*)(s32)(osRomBase | arg0 | 0xA0000000);
    return 0;
}
