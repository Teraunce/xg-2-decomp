#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ s32 unk10;
} UnkStruct_sp1C;

void piDmaNotify();                                  /* extern */
extern s32 osIntMask;
extern s32 SRAM_ADDR_REG;

void piCartDmaComplete(void) {
    UnkStruct_sp1C *sp1C;
    s32 sp18;

    sp1C = (s32)0 /* implicit $t6 from caller */ + 0x14;
    sp18 = PI_STATUS_REG;
    if (sp18 & 3) {
        do {
            sp18 = PI_STATUS_REG;
        } while (sp18 & 3);
    }
    SRAM_ADDR_REG = sp1C->unk10 | 0x10000000;
    sp18 = PI_STATUS_REG;
    if (sp18 & 3) {
        do {
            sp18 = PI_STATUS_REG;
        } while (sp18 & 3);
    }
    SRAM_ADDR_REG = sp1C->unk10;
    piDmaNotify();
    PI_STATUS_REG = 2;
    osIntMask |= 0x100401;
}
