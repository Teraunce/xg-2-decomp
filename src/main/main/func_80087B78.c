#include "ultra64.h"
s32 func_80087B48();                                /* extern */
extern s32 D_A0000000;

s32 osEPiRawWriteIo(s32 arg0, s32 arg1) {
    if (func_80087B48() != 0) {
        return -1;
    }
    *(s32*)(s32)(arg0 | (s32) &D_A0000000) = arg1;
    return 0;
}
