#include "ultra64.h"
u32 __osPiRawReadIo(s32);

s32 piReadByteUnaligned(s32 arg0) {
    s32 shift = (~arg0 & 3) << 3;
    return (__osPiRawReadIo(arg0 & -4) >> shift) & 0xFF;
}
