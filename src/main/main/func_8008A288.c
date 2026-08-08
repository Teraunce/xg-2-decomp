#include "ultra64.h"
s32 osContPakWrite(s32, s32, u16, s32, s32);       /* extern */
s32 contPakReadNoteDir(void *);                          /* extern */
s32 contPakReadWriteNote(Unk*, Unk*, u8, u8);              /* extern */
s32 contPakRepairId(Unk*);                          /* extern */
s32 osContPakRead(s32, s32, u16, u8*);            /* extern */
s32 contPakReadChain(void *, s32, u8, s32, u8, u16*, s32); /* extern */
s32 contPakReadNote(void *, u16, s32, s32, s32, s32*); /* extern */

s32 contPakLoadSave(Unk *arg0, u16 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Unk *sp = NULL; /* $sp base — used as Unk byte-ptr into local stack (nonmatching) */
    s32 sp3B = 0; /* sp+0x3B — stack slot read before write (nonmatching) */
    s32 sp15C;
    s32 sp158;
    s32 sp154;
    s32 sp54;
    s16 sp3E;
    s8 sp3C;
    u8 sp3A;
    s16 sp38;
    s32 sp34;
    s16 sp32;
    u16 sp30;
    u8 sp2F;
    u8 sp2E;
    s32 temp_t3;
    s32 temp_t9;
    s32 temp_v0;

    s16 unksp31;
    sp32 = 0;
    if ((arg1 == 0) || (arg2 == 0)) {
        return 5;
    }
    if (!(arg0->unk0 & 1)) {
        return 5;
    }
    if (contPakReadNoteDir(arg0) == 2) {
        return 2;
    }
    if (arg0->unk65 != 0) {
        arg0->unk65 = 0U;
        sp154 = contPakRepairId(arg0);
        if (sp154 != 0) {
            return sp154;
        }
    }
    sp154 = contPakReadNote(arg0, arg1, arg2, arg3, arg4, &sp15C);
    if (sp154 != 0) {
        return sp154;
    }
    if (sp15C == -1) {
        return 5;
    }
    sp154 = osContPakRead(arg0->unk4, arg0->unk8, arg0->unk5C + sp15C, &sp34);
    if (sp154 != 0) {
        return sp154;
    }
    sp2F = sp3B;
    sp2E = sp3A;
    if ((s32) sp3A < (s32) arg0->unk64) {
loop_17:
        sp154 = contPakReadWriteNote(arg0, &sp54, 0, sp2E);
        if (sp154 != 0) {
            return sp154;
        }
        sp154 = contPakReadChain(arg0, &sp54, sp2F, &sp32, (s32) sp2E, &sp30, 1);
        if (sp154 != 0) {
            return sp154;
        }
        sp154 = contPakReadWriteNote(arg0, &sp54, 1, sp2E);
        if (sp154 != 0) {
            return sp154;
        }
        if ((sp30 == 1) || (sp2E = (u8) sp30, sp2F = unksp31, (((s32) sp2E < (s32) arg0->unk64) == 0))) {
            goto block_25;
        }
        goto loop_17;
    }
block_25:
    if ((s32) sp2E >= (s32) arg0->unk64) {
        return 3;
    }
    sp34 = 0;
    sp38 = 0;
    sp3A = 0;
    sp3E = 0;
    sp158 = 0;
    do {
        ((Unk *)(sp + sp158))->unk44 = 0;
        temp_t3 = sp158 + 1;
        sp158 = temp_t3;
    } while (temp_t3 < 0x10);
    sp158 = 0;
    do {
        ((Unk *)(sp + sp158))->unk40 = 0;
        temp_t9 = sp158 + 1;
        sp158 = temp_t9;
    } while (temp_t9 < 4);
    sp3C = 0;
    temp_v0 = osContPakWrite(arg0->unk4, arg0->unk8, arg0->unk5C + sp15C, &sp34, 0);
    sp154 = temp_v0;
    return temp_v0;
}
