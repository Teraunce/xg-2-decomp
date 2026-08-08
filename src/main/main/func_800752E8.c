#include "ultra64.h"
void __osPiRawWriteIo(s32*, s32);                          /* extern */
s32 __osPiRawReadIo(s32*);                             /* extern */

void piWriteByte(s32 arg0, s32 arg1) {
    s32 temp_s0;
    s32 temp_s2;

    temp_s0 = arg0 & ~3;
    temp_s2 = (~arg0 & 3) * 8;
    __osPiRawWriteIo(temp_s0, (__osPiRawReadIo(temp_s0) & ~(0xFF << temp_s2)) | ((arg1 & 0xFF) << temp_s2));
}
