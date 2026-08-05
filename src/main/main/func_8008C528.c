#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
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
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ u8 pad00[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1A */ s32 unk1A;
    /* 0x1B */ s32 unk1B;
} UnkStruct_sp18;

s32 func_800891F4(s32, u16*, u16*);                 /* extern */
s32 func_8008925C(Unk*, Unk*, Unk*);                /* extern */
s32 func_80089674(Unk*, Unk*);                     /* extern */
s32 func_80089E84(Unk*);                          /* extern */
s32 func_80089EF8(s32, s32, u16, u8*);                /* extern */

s32 func_8008C528(UnkStruct_arg0 *arg0) {
    s32 sp64;
    u16 sp62;
    u16 sp60;
    s32 sp40[10];
    s32 sp20[8];
    s32 sp1C;
    UnkStruct_sp18 *sp18;
    s32 temp_t4;

    if (arg0->unk65 != 0) {
        arg0->unk65 = 0U;
        sp1C = func_80089E84(arg0);
        if (sp1C != 0) {
            return sp1C;
        }
    }
    sp1C = func_80089EF8(arg0->unk4, arg0->unk8, 1, &sp40);
    if (sp1C != 0) {
        return sp1C;
    }
    func_800891F4(&sp40, &sp62, &sp60);
    sp18 = &sp40;
    if ((((Unk*)&sp40)->unk1C != sp62) || (((Unk*)&sp40)->unk1E != sp60)) {
        sp1C = func_80089674(arg0, sp18);
        if (sp1C == 0xA) {
            sp1C = func_8008925C(arg0, sp18, &sp20);
            if (sp1C != 0) {
                return sp1C;
            }
            sp18 = &sp20;
            goto block_13;
        }
        if (sp1C != 0) {
            return sp1C;
        }
        goto block_13;
    }
block_13:
    if (!(sp18->unk18 & 1)) {
        sp1C = func_8008925C(arg0, sp18, &sp20);
        if (sp1C != 0) {
            return sp1C;
        }
        sp18 = &sp20;
        if (!(((Unk*)&sp20)->unk18 & 1)) {
            return 0xB;
        }
        goto block_18;
    }
block_18:
    sp64 = 0;
    do {
        ((Unk *)(arg0 + sp64))->unkC = *(u8*)((char*)sp18 + sp64);
        temp_t4 = sp64 + 1;
        sp64 = temp_t4;
    } while (temp_t4 < 0x20);
    arg0->unk4C = (s32) sp18->unk1B;
    arg0->unk64 = (u8) sp18->unk1A;
    arg0->unk60 = (s32) ((arg0->unk64 * 2) + 3);
    arg0->unk50 = 0x10;
    arg0->unk54 = 8;
    arg0->unk58 = (s32) ((arg0->unk64 * 8) + 8);
    arg0->unk5C = (s32) (arg0->unk58 + (arg0->unk64 * 8));
    sp1C = func_80089EF8(arg0->unk4, arg0->unk8, 7, arg0 + 0x2C);
    if (sp1C != 0) {
        return sp1C;
    }
    return 0;
}
