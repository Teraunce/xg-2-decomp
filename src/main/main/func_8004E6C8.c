#include "ultra64.h"
s32 *overlayDecompress(void *);                         /* extern */
extern s32 D_8004B7B0;

s32 func_8004E6C8(s32 arg0) {
    return *overlayDecompress((arg0 * 0x10) + &D_8004B7B0);
}
