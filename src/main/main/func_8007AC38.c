#include "ultra64.h"
void guMtxF2L(char*, char*);                          /* extern */
s32 guMtxL2FFixed(void *, s32);                          /* extern */
void guMtxCatF(char*, f32*, char*);                     /* extern */

void guMtxCat(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp98[16];
    s32 sp58[16];
    s32 sp18[16];

    guMtxL2FFixed(&sp98, arg0);
    guMtxL2FFixed(&sp58, arg1);
    guMtxCatF(&sp98, &sp58, &sp18);
    guMtxF2L(&sp18, arg2);
}
