#include "ultra64.h"
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 pad0C[0x44];
    /* 0x50 */ char *unk50;
    /* 0x54 */ u8 pad54[0x8];
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ u8 pad60[0x5];
    /* 0x65 */ s32 unk65;
} UnkStruct_arg0;

s32 contPakReadNoteDir(UnkStruct_arg0*);                          /* extern */
s32 contPakRepairId(Unk*);                          /* extern */
s32 osContPakRead(s32, s32, u16, u8*);            /* extern */

s32 contPakReadDir(UnkStruct_arg0 *arg0, s32 *arg1, s32 *arg2) {
    s32 sp44;
    s32 sp40;
    s32 sp20;
    s32 sp1C;
    s32 temp_t3;
    s32 sp24;

    sp1C = 0;
    if (!(arg0->unk0 & 1)) {
        return 5;
    }
    if (contPakReadNoteDir(arg0) == 2) {
        return 2;
    }
    if (arg0->unk65 != 0) {
        arg0->unk65 = 0U;
        sp40 = contPakRepairId(arg0);
        if (sp40 != 0) {
            return sp40;
        }
    }
    sp44 = 0;
    if ((s32)arg0->unk50 > 0) {
loop_8:
        sp40 = osContPakRead(arg0->unk4, arg0->unk8, arg0->unk5C + sp44, &sp20);
        if (sp40 != 0) {
            return sp40;
        }
        if ((sp24 != 0) && (sp20 != 0)) {
            sp1C += 1;
        }
        temp_t3 = sp44 + 1;
        sp44 = temp_t3;
        if (temp_t3 >= (s32)arg0->unk50) {
            goto block_14;
        }
        goto loop_8;
    }
block_14:
    *arg2 = sp1C;
    *arg1 = arg0->unk50;
    return 0;
}
