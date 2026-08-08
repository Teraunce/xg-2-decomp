#include "ultra64.h"
s32 osContPakWrite(s32, s32, u16, s32, s32);      /* extern */
s32 contPakChecksum(s32, u16*, u16*);              /* extern */
s32 contPakRepairId(Unk*);                          /* extern */
s32 osContPakRead(s32, s32, u16, u8*);           /* extern */

s32 contPakVerifyNote(Unk *arg0, Unk *arg1) {
    Unk *sp = (Unk*)0;
    s8 sp30;
    s32 sp2C;
    u16 sp2A;
    u16 sp28;
    s32 sp24;
    s32 sp20;
    s32 temp_t6;
    s32 temp_t8;

    sp2C = 0;
    if (arg0->unk65 != 0) {
        arg0->unk65 = 0U;
        sp2C = contPakRepairId(arg0);
        if (sp2C != 0) {
            return sp2C;
        }
    }
    ((Unk*)&sp30)->unk0 = 1;
    ((Unk*)&sp30)->unk2 = 3;
    ((Unk*)&sp30)->unk4 = 4;
    ((Unk*)&sp30)->unk6 = 6;
    sp24 = 1;
loop_4:
    sp2C = osContPakRead(arg0->unk4, arg0->unk8, (sp + (sp24 * 2))->unk30, arg1);
    if (sp2C != 0) {
        return sp2C;
    }
    contPakChecksum(arg1, &sp2A, &sp28);
    if (((arg1->unk1C == sp2A) && (arg1->unk1E == sp28)) || (temp_t8 = sp24 + 1, sp24 = temp_t8, ((temp_t8 < 4) == 0))) {
        if (sp24 == 4) {
            return 0xA;
        }
        sp20 = 0;
loop_12:
        if (sp20 != sp24) {
            sp2C = osContPakWrite(arg0->unk4, arg0->unk8, (sp + (sp20 * 2))->unk30, arg1, 1);
            if (sp2C != 0) {
                return sp2C;
            }
        }
        temp_t6 = sp20 + 1;
        sp20 = temp_t6;
        if (temp_t6 >= 4) {
            return 0;
        }
        goto loop_12;
    }
    goto loop_4;
}
