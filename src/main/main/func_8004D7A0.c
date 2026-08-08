#include "ultra64.h"
s32 *rspTaskAlloc(s32);                            /* extern */
void overlayRelocate(Unk*, Unk*, s32);               /* extern */
void __osInvalICache_full();                                  /* extern */

s32 *overlayDecompress(s32 *arg0) {
    s32 *temp_v0;

    temp_v0 = rspTaskAlloc(*arg0);
    overlayRelocate(temp_v0, arg0, temp_v0);
    *temp_v0 = (s32) (temp_v0 + (*temp_v0 & 0xFFFFFF));
    __osInvalICache_full();
    return temp_v0;
}
