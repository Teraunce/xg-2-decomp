#include "ultra64.h"
void guMtxF2L(char*, char*);                          /* extern */
void guMtxIdent(char*);                               /* extern */

void guMtxIdentL(s32 arg0) {
    s32 sp18[16];

    guMtxIdent(&sp18);
    guMtxF2L(&sp18, arg0);
}

f32 guMtxL2FFixed(void) {
    return 65536.0f;
}
