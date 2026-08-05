#include "ultra64.h"
void osWritebackInvalDCache(u32, s32);                          /* extern */
void osWritebackDCache(u32, s32);                          /* extern */
s32 func_8007CD08(Unk*, s32*, s32);                       /* extern */
s32 func_8008E518(Unk*, s32, s32, s32, s32, s32, s32);     /* extern */
extern s32 D_8016DF70;

void func_8004D138(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp38;
    s32 sp20;

    osWritebackDCache(arg1, arg2);
    func_8008E518(&sp20, 0, 0, arg0, arg1, arg2, &D_8016DF70);
    func_8007CD08(&D_8016DF70, &sp38, 1);
    osWritebackInvalDCache(arg1, arg2);
}
