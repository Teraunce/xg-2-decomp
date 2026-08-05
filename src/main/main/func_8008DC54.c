#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ s32 unk10;
} UnkStruct_sp1C;

void piDmaNotify();                                  /* extern */
extern s32 osIntMask;
extern s32 D_A4600010;
extern s32 D_A5000510;

void func_8008DC54(void) {
    UnkStruct_sp1C *sp1C;
    s32 sp18;

    sp1C = (s32)0 /* implicit $t6 from caller */ + 0x14;
    sp18 = D_A4600010;
    if (sp18 & 3) {
        do {
            sp18 = D_A4600010;
        } while (sp18 & 3);
    }
    D_A5000510 = sp1C->unk10 | 0x10000000;
    sp18 = D_A4600010;
    if (sp18 & 3) {
        do {
            sp18 = D_A4600010;
        } while (sp18 & 3);
    }
    D_A5000510 = sp1C->unk10;
    piDmaNotify();
    D_A4600010 = 2;
    osIntMask |= 0x100401;
}
