#include "ultra64.h"
void guMtxF2L(char*, char*);                          /* extern */
s32 func_8007A910(void *, s32);                          /* extern */
void guMtxCatF(char*, f32*, char*);                     /* extern */

void guMtxCat(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp98[16];
    s32 sp58[16];
    s32 sp18[16];

    func_8007A910(&sp98, arg0);
    func_8007A910(&sp58, arg1);
    guMtxCatF(&sp98, &sp58, &sp18);
    guMtxF2L(&sp18, arg2);
}
