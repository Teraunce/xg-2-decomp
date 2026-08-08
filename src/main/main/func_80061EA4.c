#include "ultra64.h"
s32 sfxFormatName(s32, u16*, u16*, u16*, u16*, s32);         /* extern */

void sfxFormatName3(s32 arg0, s32 arg1, s32 arg2) {
    sfxFormatName(arg0, arg1, arg2, 0, 0, 0);
}
