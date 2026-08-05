#include "ultra64.h"
void __osPiRawWriteIo(s32*, s32);                            /* extern */
s32 __osPiRawReadIo(s32*);                               /* extern */
void __osPiResetCount(s32);                                 /* extern */

s32 func_80075B78(s32 arg0, s32 arg2, s32 arg3) {
    __osPiRawWriteIo(0xB1FFFFE4, 0);
    __osPiRawWriteIo(0xB1FFFFE8, arg2);
    __osPiRawWriteIo(0xB1FFFFEC, arg3);
    __osPiRawWriteIo(0xB1FFFFE0, arg0);
    do {
        __osPiResetCount(0x3E8);
        if (__osPiRawReadIo(0xB1FFFFF0) != 0) {
            M2C_BREAK(1);
        }
    } while (__osPiRawReadIo(0xB1FFFFE0) != 0);
    __osPiRawReadIo(0xB1FFFFDC);
}
