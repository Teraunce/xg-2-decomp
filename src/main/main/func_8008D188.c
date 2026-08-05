#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8008D3B8 (initial). */

s32 osVirtualToPhysical(u32);                             /* extern */
extern s32 D_800964A0;
extern s32 D_8018C214;
extern s32 D_A4600000;
extern s32 D_A4600004;
extern s32 D_A4600008;
extern s32 D_A460000C;
extern s32 D_A4600010;
extern s32 D_A4600014;
extern s32 D_A4600018;
extern s32 D_A460001C;
extern s32 D_A4600020;
extern s32 D_A4600024;
extern s32 D_A4600028;
extern s32 D_A460002C;
extern s32 D_A4600030;

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

    sp2C = D_A4600010;
    if (D_A4600010 & 3) {
        do {
            sp2C = D_A4600010;
        } while (sp2C & 3);
    }
    temp_t4 = arg0->unk9;
    temp_t6 = *(&D_800964A0 + (temp_t4 * 4));
    sp28 = (s32) temp_t4;
    if (temp_t6 != arg0) {
        sp24 = temp_t6;
        if (temp_t4 == 0) {
            temp_t8 = arg0->unk5;
            if (temp_t6->unk5 != temp_t8) {
                D_A4600014 = (s32) temp_t8;
            }
            temp_t5 = arg0->unk6;
            if (sp24->unk6 != temp_t5) {
                D_A460001C = (s32) temp_t5;
            }
            temp_t8_2 = arg0->unk7;
            if (sp24->unk7 != temp_t8_2) {
                D_A4600020 = (s32) temp_t8_2;
            }
            temp_t5_2 = arg0->unk8;
            if (sp24->unk8 != temp_t5_2) {
                D_A4600018 = (s32) temp_t5_2;
            }
        } else {
            temp_t8_3 = arg0->unk5;
            if (sp24->unk5 != temp_t8_3) {
                D_A4600024 = (s32) temp_t8_3;
            }
            temp_t5_3 = arg0->unk6;
            if (sp24->unk6 != temp_t5_3) {
                D_A460002C = (s32) temp_t5_3;
            }
            temp_t8_4 = arg0->unk7;
            if (sp24->unk7 != temp_t8_4) {
                D_A4600030 = (s32) temp_t8_4;
            }
            temp_t5_4 = arg0->unk8;
            if (sp24->unk8 != temp_t5_4) {
                D_A4600028 = (s32) temp_t5_4;
            }
        }
        *(&D_800964A0 + (sp28 * 4)) = arg0;
    }
    D_A4600000 = osVirtualToPhysical(arg3);
    D_A4600004 = (arg0->unkC | arg2) & 0x1FFFFFFF;
    switch (arg1) {                                 /* irregular */
    case 0:
        D_A460000C = arg4 - 1;
block_27:
        return 0;
    case 1:
        D_A4600008 = arg4 - 1;
        goto block_27;
    default:
        return -1;
    }
}

void func_8008D3B8(void) {

}
