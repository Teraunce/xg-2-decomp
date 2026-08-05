#include "ultra64.h"
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 pad0C[0x44];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ u8 pad54[0x8];
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x65 */ s32 unk65;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} UnkStruct_arg2;

s32 func_80089A68(UnkStruct_arg0*);                          /* extern */
s32 func_80089B64(void *, u16 (*)[], s32, u8);        /* extern */
s32 func_80089E84(Unk*);                          /* extern */
s32 func_80089EF8(s32, s32, u16, u8*);            /* extern */

s32 func_8008AD98(UnkStruct_arg0 *arg0, s32 arg1, UnkStruct_arg2 *arg2) {
    Unk *sp = (Unk*)0;
    s32 sp14C;
    s32 sp148;
    s32 sp28;
    u16 sp24;
    s32 sp20;
    u8 sp1F;
    u8 sp1E;
    s32 temp_t5;
    s32 temp_t9;
    s32 sp2C;
    s32 sp2E;
    u16 sp48[256];

    s16 unksp25;
    s16 unksp2F;
    if ((arg1 >= arg0->unk50) || (arg1 < 0)) {
        return 5;
    }
    if (!(arg0->unk0 & 1)) {
        return 5;
    }
    if (func_80089A68(arg0) == 2) {
        return 2;
    }
    if (arg0->unk65 != 0) {
        arg0->unk65 = 0U;
        sp14C = func_80089E84(arg0);
        if (sp14C != 0) {
            return sp14C;
        }
    }
    sp14C = func_80089EF8(arg0->unk4, arg0->unk8, arg0->unk5C + arg1, &sp28);
    if (sp14C != 0) {
        return sp14C;
    }
    if ((sp2C == 0) || (sp28 == 0)) {
        return 5;
    }
    if ((s32) sp2E < arg0->unk60) {
        return 3;
    }
    sp148 = 0;
    sp1E = unksp2F;
    sp1F = (u8) sp2E;
    if ((s32) (u8) sp2E < (s32) arg0->unk64) {
loop_18:
        sp14C = func_80089B64(arg0, (u16 (*)[]) &sp48[0], 0, sp1F);
        if (sp14C != 0) {
            return sp14C;
        }
        sp24 = (&sp48[0])[sp1E];
        sp148 += 1;
        if ((s32) sp24 >= arg0->unk60) {
loop_21:
            sp148 += 1;
            sp24 = (&sp48[0])[unksp25];
            if ((u8) sp24 != sp1F) {
                sp1F = (u8) sp24;
                sp1E = unksp25;
            } else if ((s32) sp24 >= arg0->unk60) {
                goto loop_21;
            }
        }
        if ((sp24 == 1) || ((s32) sp1F >= (s32) arg0->unk64)) {
            goto block_26;
        }
        goto loop_18;
    }
block_26:
    if (sp24 != 1) {
        return 3;
    }
    arg2->unk0 = (s32) (sp148 << 8);
    arg2->unk8 = sp2C;
    arg2->unk4 = sp28;
    sp20 = 0;
    do {
        ((Unk *)(arg2 + sp20))->unkE /* FIXME: type unknown */ = (u8) ((Unk *)(sp + sp20))->unk38 /* FIXME: type unknown */;
        temp_t5 = sp20 + 1;
        sp20 = temp_t5;
    } while (temp_t5 < 0x10);
    sp20 = 0;
    do {
        ((Unk *)(arg2 + sp20))->unkA /* FIXME: type unknown */ = (u8) ((Unk *)(sp + sp20))->unk34 /* FIXME: type unknown */;
        temp_t9 = sp20 + 1;
        sp20 = temp_t9;
    } while (temp_t9 < 4);
    return 0;
}
