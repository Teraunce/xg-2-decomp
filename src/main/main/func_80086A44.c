#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad08[0x30];
    /* 0x38 */ s32 unk38;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad14[0x4];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8 pad20[0x18];
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
} UnkStruct_sp1C;

void func_8007BC28(u32, s32);                         /* extern */
char *func_80086928(void *);                        /* extern */
s32 func_80086C18();                                /* extern */
void func_80086C48(s32);                                 /* extern */
s32 func_80086C58(s32);                               /* extern */
s32 func_80086C98(s32, s32, s32, s32);               /* extern */
extern s32 D_A0000000;

void func_80086A44(UnkStruct_arg0 *arg0) {
    UnkStruct_sp1C *sp1C;

    sp1C = func_80086928(arg0);
    if (sp1C->unk4 & 1) {
        sp1C->unk18 = (s32) sp1C->unk38;
        sp1C->unk1C = (s32) sp1C->unk3C;
        arg0->unk4 = (s32) (arg0->unk4 & ~1);
        if (sp1C->unk4 & 4) {
            sp1C->unk10 = (s32) *(s32*)(s32)((arg0->unk38 + 0xBFC) | (s32) &D_A0000000);
        }
    }
    func_8007BC28(sp1C, 0x40);
    func_80086C48(0x2B00);
    if (func_80086C58(0x04001000) == -1) {
        do {

        } while (func_80086C58(0x04001000) == -1);
    }
    if (func_80086C98(1, 0x04000FC0, sp1C, 0x40) == -1) {
        do {

        } while (func_80086C98(1, 0x04000FC0, sp1C, 0x40) == -1);
    }
    if (func_80086C18() != 0) {
        do {

        } while (func_80086C18() != 0);
    }
    if (func_80086C98(1, 0x04001000, sp1C->unk8, sp1C->unkC) == -1) {
        do {

        } while (func_80086C98(1, 0x04001000, sp1C->unk8, sp1C->unkC) == -1);
    }
}
