#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 pad0C[0x59];
    /* 0x65 */ s32 unk65;
} UnkStruct_arg0;

s32 contPakRepairId(Unk*);                          /* extern */
s32 osContPakRead(s32, s32, u16, u8*);                /* extern */

s32 contPakReadNoteDir(UnkStruct_arg0 *arg0) {
    Unk *sp = (Unk*)0;
    s32 sp3C;
    s32 sp1C[9];
    s32 sp18;
    s32 temp_t9;

    if (arg0->unk65 != 0) {
        arg0->unk65 = 0U;
        sp18 = contPakRepairId(arg0);
        if (sp18 != 0) {
            return sp18;
        }
    }
    sp18 = osContPakRead(arg0->unk4, arg0->unk8, 1, &sp1C);
    switch (sp18) {                                 /* irregular */
    case 2:
        sp18 = osContPakRead(arg0->unk4, arg0->unk8, 1, &sp1C);
        if (sp18 != 0) {
            return sp18;
        }
    case 0:
        sp3C = 0;
loop_9:
        if (((Unk *)(sp + sp3C))->unk1C != ((Unk *)(arg0 + sp3C))->unkC) {
            return 2;
        }
        temp_t9 = sp3C + 1;
        sp3C = temp_t9;
        if (temp_t9 >= 0x20) {
            return 0;
        }
        goto loop_9;
    default:
        return sp18;
    }
}
