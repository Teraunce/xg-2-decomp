#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 pad0C[0x44];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ u8 pad54[0x8];
    /* 0x5C */ s32 unk5C;
} UnkStruct_arg0;

s32 func_80089A68(UnkStruct_arg0*);                          /* extern */
s32 func_80089EF8(s32, s32, u16, u8*);            /* extern */

s32 func_8008B088(UnkStruct_arg0 *arg0, u16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 *arg5) {
    Unk *sp = (Unk*)0;
    s32 sp44;
    s32 sp40;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 temp_t4;
    s32 temp_t4_2;
    s32 temp_t9;
    s32 sp24;

    sp1C = 0;
    if (func_80089A68(arg0) == 2) {
        return 2;
    }
    sp44 = 0;
    if (arg0->unk50 > 0) {
loop_3:
        sp1C = func_80089EF8(arg0->unk4, arg0->unk8, arg0->unk5C + sp44, &sp20);
        if (sp1C != 0) {
            return sp1C;
        }
        if ((sp24 == arg1) && (sp20 == arg2)) {
            sp18 = 0;
            if (arg3 != 0) {
                sp40 = 0;
loop_9:
                if (*(s32*)(s32)(arg3 + sp40) != ((Unk *)(sp + sp40))->unk30) {
                    sp18 = 1;
                } else {
                    temp_t4 = sp40 + 1;
                    sp40 = temp_t4;
                    if (temp_t4 < 0x10) {
                        goto loop_9;
                    }
                }
            }
            if ((arg4 != 0) && (sp18 == 0)) {
                sp40 = 0;
loop_15:
                if (*(s32*)(s32)(arg4 + sp40) != ((Unk *)(sp + sp40))->unk2C) {
                    sp18 = 1;
                } else {
                    temp_t4_2 = sp40 + 1;
                    sp40 = temp_t4_2;
                    if (temp_t4_2 < 4) {
                        goto loop_15;
                    }
                }
            }
            if (sp18 == 0) {
                *arg5 = sp44;
                return sp1C;
            }
            goto block_20;
        }
block_20:
        temp_t9 = sp44 + 1;
        sp44 = temp_t9;
        if (temp_t9 >= arg0->unk50) {
            goto block_21;
        }
        goto loop_3;
    }
block_21:
    *arg5 = -1;
    return 5;
}
