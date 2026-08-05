#include "ultra64.h"
void func_80079F58(Unk *, f32, f32, f32, f32, f32, f32, f32, f32, f32); /* extern */
void func_8007A758(char*, char*);                          /* extern */

void func_8007A210(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    s32 sp30;

    func_80079F58(&sp30, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    func_8007A758(&sp30, arg0);
}

f32 func_8007A288(f32 arg0) {
    return sqrtf(arg0);
}
