#include "ultra64.h"
s32 func_8007A910(void *, s32);                          /* extern */
void mtxTransformVec(void *, s32, s32, s32, s32, s32, s32); /* extern */

void guMtxXfm(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 sp28;

    func_8007A910(&sp28, arg0);
    mtxTransformVec(&sp28, arg1, arg2, arg3, arg4, arg5, arg6);
}
