#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 pad0C[0x59];
    /* 0x65 */ s32 unk65;
} UnkStruct_arg0;

u16 func_80089198(u8*, s32);                          /* extern */
s32 contPakRepairId(Unk*);                          /* extern */
s32 osContPakRead(s32, s32, u16, u8*);              /* extern */

s32 func_8008A7A0(UnkStruct_arg0 *arg0, u8 arg1, u16 *arg2, u8 arg3) {
    s32 sp3C;
    s32 sp38;
    s32 sp18[10];
    s32 temp_t9;

    sp38 = 0;
    arg0->unk65 = arg3;
    sp38 = contPakRepairId(arg0);
    if (sp38 != 0) {
        return sp38;
    }
    sp3C = 0;
loop_3:
    sp38 = osContPakRead(arg0->unk4, arg0->unk8, (arg1 * 8) + sp3C, &sp18);
    if (sp38 != 0) {
        arg0->unk65 = 0U;
        contPakRepairId(arg0);
    } else {
        *arg2 += func_80089198(&sp18, 0x20);
        temp_t9 = sp3C + 1;
        sp3C = temp_t9;
        if (temp_t9 >= 8) {
            arg0->unk65 = 0U;
            sp38 = contPakRepairId(arg0);
        } else {
            goto loop_3;
        }
    }
    return sp38;
}
