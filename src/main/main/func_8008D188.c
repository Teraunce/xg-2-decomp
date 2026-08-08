#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8008D3B8 (initial). */

s32 osVirtualToPhysical(u32);                             /* extern */
extern s32 gPiHandleTable;
extern s32 gSramBase;
extern s32 PI_DRAM_ADDR;
extern s32 PI_CART_ADDR;
extern s32 PI_RD_LEN;
extern s32 PI_WR_LEN;
extern s32 PI_STATUS_REG;
extern s32 PI_BSD_DOM1_LAT;
extern s32 PI_BSD_DOM1_PWD;
extern s32 PI_BSD_DOM1_PGS;
extern s32 PI_BSD_DOM1_RLS;
extern s32 PI_BSD_DOM1_LAT;
extern s32 PI_BSD_DOM1_PWD;
extern s32 PI_BSD_DOM1_PGS;
extern s32 PI_BSD_DOM1_RLS;

s32 osEPiStartDma(Unk *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp2C;
    s32 sp28;
    Unk *sp24;
    u8 temp_t4;
    u8 temp_t5;
    u8 temp_t5_2;
    u8 temp_t5_3;
    u8 temp_t5_4;
    u8 temp_t8;
    u8 temp_t8_2;
    u8 temp_t8_3;
    u8 temp_t8_4;
    Unk *temp_t6;

    sp2C = PI_STATUS_REG;
    if (PI_STATUS_REG & 3) {
        do {
            sp2C = PI_STATUS_REG;
        } while (sp2C & 3);
    }
    temp_t4 = arg0->unk9;
    temp_t6 = *(&gPiHandleTable + (temp_t4 * 4));
    sp28 = (s32) temp_t4;
    if (temp_t6 != arg0) {
        sp24 = temp_t6;
        if (temp_t4 == 0) {
            temp_t8 = arg0->unk5;
            if (temp_t6->unk5 != temp_t8) {
                PI_BSD_DOM1_LAT = (s32) temp_t8;
            }
            temp_t5 = arg0->unk6;
            if (sp24->unk6 != temp_t5) {
                PI_BSD_DOM1_PGS = (s32) temp_t5;
            }
            temp_t8_2 = arg0->unk7;
            if (sp24->unk7 != temp_t8_2) {
                PI_BSD_DOM1_RLS = (s32) temp_t8_2;
            }
            temp_t5_2 = arg0->unk8;
            if (sp24->unk8 != temp_t5_2) {
                PI_BSD_DOM1_PWD = (s32) temp_t5_2;
            }
        } else {
            temp_t8_3 = arg0->unk5;
            if (sp24->unk5 != temp_t8_3) {
                PI_BSD_DOM1_LAT = (s32) temp_t8_3;
            }
            temp_t5_3 = arg0->unk6;
            if (sp24->unk6 != temp_t5_3) {
                PI_BSD_DOM1_PGS = (s32) temp_t5_3;
            }
            temp_t8_4 = arg0->unk7;
            if (sp24->unk7 != temp_t8_4) {
                PI_BSD_DOM1_RLS = (s32) temp_t8_4;
            }
            temp_t5_4 = arg0->unk8;
            if (sp24->unk8 != temp_t5_4) {
                PI_BSD_DOM1_PWD = (s32) temp_t5_4;
            }
        }
        *(&gPiHandleTable + (sp28 * 4)) = arg0;
    }
    PI_DRAM_ADDR = osVirtualToPhysical(arg3);
    PI_CART_ADDR = (arg0->unkC | arg2) & 0x1FFFFFFF;
    switch (arg1) {                                 /* irregular */
    case 0:
        PI_WR_LEN = arg4 - 1;
block_27:
        return 0;
    case 1:
        PI_RD_LEN = arg4 - 1;
        goto block_27;
    default:
        return -1;
    }
}

void osEPiGetDomainInfo(void);  /* forward: GETTER_NOJR fallthrough */
void func_8008D3B8(void) {
    osEPiGetDomainInfo();
}
