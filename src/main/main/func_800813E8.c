#include "ultra64.h"
void __osTimerUnlink(Unk*);                            /* extern */
void __osTimerInsert(Unk*, void**);                    /* extern */

void func_800813E8(Unk *arg0, Unk *arg1) {
    s16 temp_s3;
    Unk *temp_s1;
    Unk *var_s0;

    var_s0 = arg0->unk50;
    if (var_s0 != NULL) {
loop_2:
        temp_s3 = var_s0->unkC;
        temp_s1 = var_s0->unk0;
        if (((temp_s3 == 0x16) || (temp_s3 == 0x17)) && ((s32)arg1 == var_s0->unk10)) {
            ((s32(*)())(s32)arg0->unk78)(var_s0->unk14);
            __osTimerUnlink(var_s0);
            if (temp_s1 != 0) {
                temp_s1->unk8 = (s32) (temp_s1->unk8 + var_s0->unk8);
            }
            __osTimerInsert(var_s0, arg0 + 0x48);
            if (temp_s3 == 0x16) {
                arg1->unk37 = (u8) (arg1->unk37 & 0xFE);
            } else {
                arg1->unk37 = (u8) (arg1->unk37 & 0xFD);
            }
            if (arg1->unk37 != 0) {
                goto block_11;
            }
        } else {
block_11:
            var_s0 = temp_s1;
            if (temp_s1 != 0) {
                goto loop_2;
            }
        }
    }
}
