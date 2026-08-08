#include "ultra64.h"
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 pad0C[0x40];
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ u8 unk64;
    /* 0x65 */ s32 unk65;
} UnkStruct_arg1;
typedef struct {
    /* 0x00 */ u8 pad00[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1A */ s32 unk1A;
    /* 0x1B */ s32 unk1B;
} UnkStruct_sp38;

s32 __siLock();                                  /* extern */
void __siUnlock();                                  /* extern */
s32 contPakChecksum(s32, u16*, u16*);                 /* extern */
s32 contPakTransfer(Unk*, Unk*, Unk*);                /* extern */
s32 contPakVerifyNote(Unk*, Unk*);                     /* extern */
s32 contPakRepairId(Unk*);                          /* extern */
s32 osContPakRead(s32, s32, u16, u8*);             /* extern */
s32 contPakRepairNotes(Unk*);                          /* extern */
s32 contPakProbe(s32, s32);                        /* extern */

s32 contPakVerifyRead(s32 arg0, UnkStruct_arg1 *arg1, s32 arg2) {
    s32 sp64;
    s32 sp60;
    u16 sp5E;
    u16 sp5C;
    s32 sp3C[11];
    UnkStruct_sp38 *sp38;
    s32 sp18[9];
    s32 temp_t6;
    s32 temp_v0;

    sp60 = 0;
    __siLock();
    sp60 = contPakProbe(arg0, arg2);
    __siUnlock();
    if (sp60 != 0) {
        return sp60;
    }
    arg1->unk4 = arg0;
    arg1->unk8 = arg2;
    arg1->unk0 = 0;
    arg1->unk65 = 0;
    sp60 = contPakRepairId(arg1);
    if (sp60 != 0) {
        return sp60;
    }
    contPakChecksum(&sp3C, &sp5E, &sp5C);
    sp38 = &sp3C;
    if ((((Unk*)&sp3C)->unk1C != sp5E) || (((Unk*)&sp3C)->unk1E != sp5C)) {
        sp60 = contPakVerifyNote(arg1, sp38);
        if (sp60 != 0) {
            return sp60;
        }
        if (sp60 != 0) {
            return sp60;
        }
        goto block_10;
    }
block_10:
    if (!(sp38->unk18 & 1)) {
        sp60 = contPakTransfer(arg1, sp38, &sp18);
        if (sp60 != 0) {
            return sp60;
        }
        sp38 = &sp18;
        if (!(((Unk*)&sp18)->unk18 & 1)) {
            return 0xB;
        }
        goto block_15;
    }
block_15:
    sp64 = 0;
    do {
        ((Unk *)(arg1 + sp64))->unkC = *(u8*)((char*)sp38 + sp64);
        temp_t6 = sp64 + 1;
        sp64 = temp_t6;
    } while (temp_t6 < 0x20);
    arg1->unk4C = (s32) sp38->unk1B;
    arg1->unk64 = (u8) sp38->unk1A;
    arg1->unk60 = (s32) ((arg1->unk64 * 2) + 3);
    arg1->unk50 = 0x10;
    arg1->unk54 = 8;
    arg1->unk58 = (s32) ((arg1->unk64 * 8) + 8);
    arg1->unk5C = (s32) (arg1->unk58 + (arg1->unk64 * 8));
    sp60 = osContPakRead(arg1->unk4, arg1->unk8, 7, arg1 + 0x2C);
    if (sp60 != 0) {
        return sp60;
    }
    temp_v0 = contPakRepairNotes(arg1);
    sp60 = temp_v0;
    arg1->unk0 = (s32) (arg1->unk0 | 1);
    return temp_v0;
}
