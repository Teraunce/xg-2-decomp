#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x60];
    /* 0x60 */ s32 unk60;
} UnkStruct_arg0;

s32 func_8008A7A0(UnkStruct_arg0*, u8, u16*, u8);             /* extern */

s32 func_8008A568(UnkStruct_arg0 *arg0, s32 arg1, u8 arg2, s32 arg3, u8 arg4, u16 *arg5, s32 arg6) {
    u16 sp24;
    u16 sp20;
    s32 sp1C;
    s32 sp18;

    s16 unksp21;
    s16 unksp25;
    sp1C = 0;
    sp24 = *(u16*)(s32)(arg1 + (arg2 * 2));
    if (sp24 != 1) {
        if ((s32) (u8) sp24 > 0) {
            sp18 = 1;
        } else {
            sp18 = arg0->unk60;
        }
    } else if ((s32) arg4 > 0) {
        sp18 = 1;
    } else {
        sp18 = arg0->unk60;
    }
    if (((s32) unksp25 < sp18) && (sp24 != 1)) {
        return 3;
    }
    *arg5 = sp24;
    if (arg6 == 1) {
        *(u16*)(s32)(arg1 + (arg2 * 2)) = 3;
    }
    sp1C = func_8008A7A0(arg0, arg2, arg3, arg4);
    if (sp1C != 0) {
        return sp1C;
    }
    if (sp24 == 1) {
        return 0;
    }
    if ((s32) sp24 >= arg0->unk60) {
loop_17:
        sp20 = sp24;
        sp24 = *(u16*)(s32)(arg1 + (unksp25 * 2));
        *(u16*)(s32)(arg1 + (unksp21 * 2)) = 3;
        sp1C = func_8008A7A0(arg0, unksp21, arg3, arg4);
        if (sp1C != 0) {
            return sp1C;
        }
        if (((u8) sp24 != arg4) || ((s32) sp24 < arg0->unk60)) {
            goto block_21;
        }
        goto loop_17;
    }
block_21:
    if ((s32) sp24 >= arg0->unk60) {
        *(u16*)(s32)(arg1 + (unksp25 * 2)) = 3;
    }
    *arg5 = sp24;
    return 0;
}
