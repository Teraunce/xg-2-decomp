#include "ultra64.h"
void guMtxF2L(char*, char*);                          /* extern */
void guPerspectiveF(char*, s16*, f32, f32, f32, f32, f32);        /* extern */

void guPerspective(s32 arg0, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    s32 sp28;

    guPerspectiveF(&sp28, arg2, arg3, arg4, arg5, arg6, arg7);
    guMtxF2L(&sp28, arg0);
}
