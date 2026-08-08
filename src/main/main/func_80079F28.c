#include "ultra64.h"
s16 sinInt(s32);                               /* extern */

void func_80079F28(s32 arg0) {
    sinInt((arg0 + 0x4000) & 0xFFFF);
}
