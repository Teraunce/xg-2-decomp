#include "ultra64.h"
void guMtxF2L(char*, char*);                          /* extern */
void guOrthoF(void *, s32, s32, s32, f32, f32, f32, f32);   /* extern */

void guOrtho(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    s32 sp28;

    guOrthoF(&sp28, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    guMtxF2L(&sp28, arg0);
}
