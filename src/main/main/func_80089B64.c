#include "ultra64.h"
s32 osContPakWrite(s32, s32, u16, s32, s32);      /* extern */
u16 contPakByteSum(u8*, s32);                      /* extern */
s32 contPakRepairId(Unk*);                          /* extern */
s32 osContPakRead(s32, s32, u16, u8*);           /* extern */

s32 contPakReadWriteNote(Unk *arg0, Unk *arg1, u8 arg2, u8 arg3) {
    u8 sp37;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    char *sp24;
    s32 temp_t0;
    s32 temp_t3;
    s32 temp_t4;
    s32 temp_t5;
    s32 var_v0;
    char *temp_t1;
    char *temp_t2;
    char *temp_t5_2;
    char *temp_t6;

    if (arg0->unk65 != 0) {
        arg0->unk65 = 0U;
        sp2C = contPakRepairId(arg0);
        if (sp2C != 0) {
            return sp2C;
        }
    }
    if ((s32) arg3 > 0) {
        sp28 = 1;
    } else {
        sp28 = arg0->unk60;
    }
    if (arg2 == 1) {
        arg1->unk1 = contPakByteSum(arg1 + (sp28 * 2), (sp28 * -2) + 0x100);
    }
    sp30 = 0;
loop_9:
    temp_t2 = arg1 + (sp30 << 5);
    sp24 = temp_t2;
    if (arg2 == 1) {
        sp2C = osContPakWrite(arg0->unk4, arg0->unk8, arg0->unk54 + (arg3 * 8) + sp30, temp_t2, 0);
        var_v0 = osContPakWrite(arg0->unk4, arg0->unk8, arg0->unk58 + (arg3 * 8) + sp30, sp24, 0);
    } else {
        var_v0 = osContPakRead(arg0->unk4, arg0->unk8, arg0->unk54 + (arg3 * 8) + sp30, sp24);
    }
    sp2C = var_v0;
    if (sp2C != 0) {
        return sp2C;
    }
    temp_t5 = sp30 + 1;
    sp30 = temp_t5;
    if (temp_t5 >= 8) {
        if (arg2 == 0) {
            sp37 = contPakByteSum(arg1 + (sp28 * 2), (sp28 * -2) + 0x100);
            if (arg1->unk1 != sp37) {
                sp30 = 0;
                do {
                    temp_t6 = arg1 + (sp30 << 5);
                    sp24 = temp_t6;
                    sp2C = osContPakRead(arg0->unk4, arg0->unk8, arg0->unk58 + (arg3 * 8) + sp30, temp_t6);
                    temp_t4 = sp30 + 1;
                    sp30 = temp_t4;
                } while (temp_t4 < 8);
                if (arg1->unk1 != sp37) {
                    return 3;
                }
                sp30 = 0;
                do {
                    temp_t5_2 = arg1 + (sp30 << 5);
                    sp24 = temp_t5_2;
                    sp2C = osContPakWrite(arg0->unk4, arg0->unk8, arg0->unk54 + (arg3 * 8) + sp30, temp_t5_2, 0);
                    temp_t0 = sp30 + 1;
                    sp30 = temp_t0;
                } while (temp_t0 < 8);
                goto block_26;
            }
            sp30 = 0;
            do {
                temp_t1 = arg1 + (sp30 << 5);
                sp24 = temp_t1;
                sp2C = osContPakWrite(arg0->unk4, arg0->unk8, arg0->unk58 + (arg3 * 8) + sp30, temp_t1, 0);
                temp_t3 = sp30 + 1;
                sp30 = temp_t3;
            } while (temp_t3 < 8);
            goto block_26;
        }
block_26:
        return 0;
    }
    goto loop_9;
}
