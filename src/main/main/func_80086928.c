#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad14[0x4];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 pad1C[0x4];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 pad24[0x4];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ u8 pad34[0x4];
    /* 0x38 */ s32 unk38;
} UnkStruct_sp1C;

s32 osVirtualToPhysical(u32);                             /* extern */
s32 memmove(s32, s32, s32);                       /* extern */
extern s32 D_80189AA8;

char *spTaskLoad(s32 arg0) {
    UnkStruct_sp1C *sp1C;
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t3;
    s32 temp_t4;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_t8;

    sp1C = &D_80189AA8;
    memmove(arg0, &D_80189AA8, 0x40);
    temp_t8 = sp1C->unk10;
    if (temp_t8 != 0) {
        sp1C->unk10 = osVirtualToPhysical(temp_t8);
    }
    temp_t1 = sp1C->unk18;
    if (temp_t1 != 0) {
        sp1C->unk18 = osVirtualToPhysical(temp_t1);
    }
    temp_t4 = sp1C->unk20;
    if (temp_t4 != 0) {
        sp1C->unk20 = osVirtualToPhysical(temp_t4);
    }
    temp_t7 = sp1C->unk28;
    if (temp_t7 != 0) {
        sp1C->unk28 = osVirtualToPhysical(temp_t7);
    }
    temp_t0 = sp1C->unk2C;
    if (temp_t0 != 0) {
        sp1C->unk2C = osVirtualToPhysical(temp_t0);
    }
    temp_t3 = sp1C->unk30;
    if (temp_t3 != 0) {
        sp1C->unk30 = osVirtualToPhysical(temp_t3);
    }
    temp_t6 = sp1C->unk38;
    if (temp_t6 != 0) {
        sp1C->unk38 = osVirtualToPhysical(temp_t6);
    }
    return sp1C;
}
