#include "ultra64.h"
void guMtxF2L(char*, char*);                          /* extern */
void guRotateDeg(void *, f32, f32);                       /* extern */

void guRotateDegF2L(f32 arg1, s32 arg0) {
    s32 sp18[16];

    guRotateDeg(&sp18, arg0, arg1);
    guMtxF2L(&sp18, arg0);
}
