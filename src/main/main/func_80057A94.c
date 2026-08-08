#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_80057AB8 (initial). */

s32 guMtxL2FFixed(s32, s32);                            /* extern */

void guMtxL2FFixedW(s32 arg0, s32 arg1) {
    guMtxL2FFixed(arg1, arg0);
}

f32 func_80057AB8(f32 *arg0, f32 *arg1) {
    return *arg1 - *arg0;
}
