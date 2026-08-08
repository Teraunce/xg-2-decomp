#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x60];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ u8 pad00[0x100];
    /* 0x100 */ s32 unk100;
} UnkStruct_arg2;

s32 contPakReadWriteNote(Unk*, Unk*, u8, u8);           /* extern */

s32 contPakCountNoteLinks(UnkStruct_arg0 *arg0, u8 arg1, UnkStruct_arg2 *arg2) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    u8 sp23;
    s32 sp1C;
    s32 sp18;
    s32 temp_t4;
    u8 temp_t0;

    sp24 = 0;
    sp18 = 0;
    sp28 = ((s32) arg1 / 4) + (((s32) arg1 % 8) << 5);
    sp23 = 0;
    if ((s32) arg0->unk64 > 0) {
loop_1:
        if ((s32) sp23 > 0) {
            sp1C = 1;
        } else {
            sp1C = arg0->unk60;
        }
        if ((sp23 == arg1) || (((Unk *)((char*)arg2 + sp28))->unk101 & (1 << ((s32) sp23 % 8)))) {
            if (sp23 != arg2->unk100) {
                sp18 = contPakReadWriteNote(arg0, arg2, 0, sp23);
                if ((sp18 != 0) && (sp18 != 3)) {
                    return sp18;
                }
                arg2->unk100 = sp23;
                goto block_11;
            }
block_11:
            sp2C = sp1C;
            if ((sp24 < 2) && (sp1C < 0x80)) {
loop_13:
                if (*(u16*)((char*)arg2 + (sp2C * 2)) == (u16) arg1) {
                    sp24 += 1;
                }
                temp_t4 = sp2C + 1;
                sp2C = temp_t4;
                if ((sp24 < 2) && (temp_t4 < 0x80)) {
                    goto loop_13;
                }
            }
            if (sp24 >= 2) {
                return 2;
            }
            goto block_19;
        }
block_19:
        temp_t0 = sp23 + 1;
        sp23 = temp_t0;
        if ((temp_t0 & 0xFF) >= (s32) arg0->unk64) {
            goto block_20;
        }
        goto loop_1;
    }
block_20:
    return sp24;
}
