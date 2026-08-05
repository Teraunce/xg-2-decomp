#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x60];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ u8 pad00[0x100];
    /* 0x100 */ s32 unk100;
} UnkStruct_arg1;
typedef struct {
    /* 0x00 */ u8 pad00[0x101];
    /* 0x101 */ u8 unk101;
} UnkStruct_temp_t8;

s32 func_80089B64(void *, u16 (*)[], s32, u8);        /* extern */

s32 func_8008C18C(UnkStruct_arg0 *arg0, UnkStruct_arg1 *arg1) {
    s32 sp12C;
    s32 sp128;
    s32 sp124;
    u8 sp123;
    u16 sp120;
    s32 sp1C;
    s32 temp_t0;
    s32 temp_t7;
    s32 temp_t9;
    u8 temp_t3;
    u16 sp20[256];
    UnkStruct_temp_t8 *temp_t8;

    s16 unksp121;
    sp12C = 0;
    do {
        ((Unk *)(arg1 + sp12C))->unk101 /* FIXME: type unknown */ = 0;
        temp_t0 = sp12C + 1;
        sp12C = temp_t0;
    } while (temp_t0 < 0x100);
    arg1->unk100 = 0xFF;
    sp123 = 0;
    if ((s32) arg0->unk64 > 0) {
loop_3:
        if ((s32) sp123 > 0) {
            sp124 = 1;
        } else {
            sp124 = arg0->unk60;
        }
        sp1C = func_80089B64(arg0, (u16 (*)[]) &sp20[0], 0, sp123);
        if ((sp1C != 0) && (sp1C != 3)) {
            return sp1C;
        }
        sp12C = sp124;
        if (sp124 < 0x80) {
            do {
                sp120 = (&sp20[0])[sp12C];
                if (((s32) sp120 >= arg0->unk60) && ((u8) sp120 != sp123)) {
                    temp_t7 = ((s32) unksp121 / 4) + (((s32) (u8) sp120 % 8) << 5);
                    sp128 = temp_t7;
                    temp_t8 = arg1 + temp_t7;
                    temp_t8->unk101 = (u8) (temp_t8->unk101 | (1 << ((s32) sp123 % 8)));
                }
                temp_t9 = sp12C + 1;
                sp12C = temp_t9;
            } while (temp_t9 < 0x80);
        }
        temp_t3 = sp123 + 1;
        sp123 = temp_t3;
        if ((temp_t3 & 0xFF) >= (s32) arg0->unk64) {
            goto block_15;
        }
        goto loop_3;
    }
block_15:
    return 0;
}
