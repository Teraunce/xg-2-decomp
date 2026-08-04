#include "ultra64.h"
s32 func_8007CE48(Unk*, s32, s32);                  /* extern */
s32 func_8008E628(Unk*, s32, s32);                  /* extern */
s32 func_8008E778();                                /* extern */
extern s32 D_80096480;

s32 func_8008E518(Unk *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 var_v0;

    if (D_80096480 == 0) {
        return -1;
    }
    if (arg2 == 0) {
        arg0->unk0 = 0xB;
    } else {
        arg0->unk0 = 0xC;
    }
    arg0->unk2 = (s8) arg1;
    arg0->unk4 = arg6;
    arg0->unk8 = arg4;
    arg0->unkC = arg3;
    arg0->unk10 = arg5;
    arg0->unk14 = 0;
    if (arg1 == 1) {
        var_v0 = func_8008E628(func_8008E778(), arg0, 0);
    } else {
        var_v0 = func_8007CE48(func_8008E778(), arg0, 0);
    }
    return var_v0;
}
