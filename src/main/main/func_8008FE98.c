#include "ultra64.h"
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
} UnkStruct_arg0;

s32 func_8008EC64(s32, u32, s32, u32);              /* extern */
u64 __muldi3(s32, u32, s32, u32);              /* extern */

void func_8008FE98(UnkStruct_arg0 *arg0, s32 arg2, u32 arg3, s32 arg4, u32 arg5) {
    u32 sp2C;
    s32 sp28;
    u32 sp24;
    s8 sp20;
    s32 temp_ret;
    s32 temp_t8;
    s32 temp_v0;
    u32 temp_t3;
    u32 temp_t9;
    u32 temp_v1;
    u32 temp_v1_2;
    u64 temp_ret_2;

    temp_ret = func_8008EC64(arg2, arg3, arg4, arg5);
    temp_v0 = temp_ret;
    temp_v1 = (u32) (u64) temp_ret;
    sp20 = temp_v0;
    sp24 = temp_v1;
    temp_ret_2 = __muldi3(arg4, arg5, temp_v0, temp_v1);
    temp_v1_2 = (u32) temp_ret_2;
    temp_t8 = (arg2 - temp_ret_2) - (arg3 < temp_v1_2);
    temp_t9 = arg3 - temp_v1_2;
    sp2C = temp_t9;
    sp28 = temp_t8;
    if (sp20 <= 0) {
        if (sp20 >= 0) {

        } else if ((temp_t8 >= 0) && ((temp_t3 = sp24 + 1, (temp_t8 > 0)) || (temp_t9 != 0))) {
            sp20 += temp_t3 == 0;
            sp24 = temp_t3;
            sp2C = temp_t9 - arg5;
            sp28 = (temp_t8 - arg4) - (temp_t9 < arg5);
        }
    }
    arg0->unk0 = (s32) ((Unk*)&sp20)->unk0;
    arg0->unk4 = (s32) ((Unk*)&sp20)->unk4;
    arg0->unk8 = (s32) ((Unk*)&sp20)->unk8;
    arg0->unkC = (s32) ((Unk*)&sp20)->unkC;
}

s32 func_8008FF98(s32 arg1, s32 arg2) {
    return arg1 / arg2;
}
