#include "ultra64.h"
void func_8005DF20(f32, f32, s32, s32, f32, s32);      /* extern */
extern f32 D_8004BE80;

void func_8005DED4(f32 arg4, f32 arg5, s32 arg6, s32 arg7) {
    func_8005DF20(arg4, arg5, arg6, arg7, D_8004BE80, 0x10000);
}
