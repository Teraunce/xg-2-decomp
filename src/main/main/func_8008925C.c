#include "ultra64.h"
s32 __osGetCount();                                /* extern */
s32 osContPakWrite(s32, s32, u16, s32, s32);        /* extern */
s32 contPakChecksum(s32, u16*, u16*);              /* extern */
s32 contPakRepairId(Unk*);                          /* extern */
s32 osContPakRead(s32, s32, u16, u8*);               /* extern */

s32 func_8008925C(Unk *arg0, Unk *arg1, Unk *arg2) {
    Unk *sp = (Unk*)0;
    s32 sp74;
    u8 sp54;
    u8 sp34;
    u8 sp33;
    s32 sp2C;
    s32 sp28;
    s8 sp20;
    s32 temp_t3;
    s32 temp_t4;
    s32 temp_t5;
    s32 temp_t5_2;
    u8 *temp_t0;

    sp74 = 0;
    sp33 = 0;
    if (arg0->unk65 != 0) {
        arg0->unk65 = 0U;
        sp74 = contPakRepairId(arg0);
        if (sp74 != 0) {
            return sp74;
        }
    }
    arg2->unk0 = -1;
    arg2->unk4 = __osGetCount();
    arg2->unk8 = (s32) arg1->unk8;
    arg2->unkC = (s32) arg1->unkC;
    arg2->unk10 = (s32) arg1->unk10;
    arg2->unk14 = (s32) arg1->unk14;
    sp28 = 0;
loop_4:
    arg0->unk65 = (u8) sp28;
    sp74 = contPakRepairId(arg0);
    if (sp74 != 0) {
        return sp74;
    }
    sp74 = osContPakRead(arg0->unk4, arg0->unk8, 0, &sp54);
    if (sp74 != 0) {
        return sp74;
    }
    sp54 = sp28 | 0x80;
    sp2C = 1;
    do {
        temp_t0 = &(&sp54)[sp2C];
        *temp_t0 = ~*temp_t0;
        temp_t5 = sp2C + 1;
        sp2C = temp_t5;
    } while (temp_t5 < 0x20);
    sp74 = osContPakWrite(arg0->unk4, arg0->unk8, 0U, &sp54, 0);
    if (sp74 != 0) {
        return sp74;
    }
    sp74 = osContPakRead(arg0->unk4, arg0->unk8, 0, &sp34);
    if (sp74 != 0) {
        return sp74;
    }
    sp2C = 0;
loop_15:
    if (((Unk *)(sp + sp2C))->unk54 == ((Unk *)(sp + sp2C))->unk34) {
        temp_t4 = sp2C + 1;
        sp2C = temp_t4;
        if (temp_t4 < 0x20) {
            goto loop_15;
        }
    }
    if (sp2C == 0x20) {
        if (sp28 > 0) {
            arg0->unk65 = 0U;
            sp74 = contPakRepairId(arg0);
            if (sp74 != 0) {
                return sp74;
            }
            sp74 = osContPakRead(arg0->unk4, arg0->unk8, 0, &sp54);
            if (sp74 != 0) {
                return sp74;
            }
            if (sp54 == 0x80) {
                goto block_24;
            }
            goto block_25;
        }
block_24:
        sp28 += 1;
        if (sp28 >= 0x3E) {
            goto block_25;
        }
        goto loop_4;
    }
block_25:
    arg0->unk65 = 0U;
    sp74 = contPakRepairId(arg0);
    if (sp74 != 0) {
        return sp74;
    }
    if (sp28 > 0) {
        sp33 = 1;
    } else {
        sp33 = 0;
    }
    arg2->unk18 = (s16) ((arg1->unk18 & 0xFFFE) | sp33);
    arg2->unk1A = (s8) sp28;
    arg2->unk1B = (u8) arg1->unk1B;
    contPakChecksum(arg2, arg2 + 0x1C, arg2 + 0x1E);
    ((Unk*)&sp20)->unk0 = 1;
    ((Unk*)&sp20)->unk2 = 3;
    ((Unk*)&sp20)->unk4 = 4;
    ((Unk*)&sp20)->unk6 = 6;
    sp2C = 0;
loop_31:
    sp74 = osContPakWrite(arg0->unk4, arg0->unk8, (sp + (sp2C * 2))->unk20, arg2, 1);
    if (sp74 != 0) {
        return sp74;
    }
    temp_t3 = sp2C + 1;
    sp2C = temp_t3;
    if (temp_t3 >= 4) {
        sp74 = osContPakRead(arg0->unk4, arg0->unk8, 1, &sp54);
        if (sp74 != 0) {
            return sp74;
        }
        sp2C = 0;
loop_37:
        if (((Unk *)(sp + sp2C))->unk54 != (arg2 + sp2C)->unk54) {
            return 0xA;
        }
        temp_t5_2 = sp2C + 1;
        sp2C = temp_t5_2;
        if (temp_t5_2 >= 0x20) {
            return 0;
        }
        goto loop_37;
    }
    goto loop_31;
}
