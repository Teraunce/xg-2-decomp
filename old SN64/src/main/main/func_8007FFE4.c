#include "ultra64.h"
void func_8007DA18(Unk*);                            /* extern */
void func_8007DA48(Unk*, void**);                    /* extern */
void func_8007E734(void**, s32, s32);                /* extern */
void func_80086418(void *, void *, s16, s32);               /* extern */
void func_800865E8(s32, void *, s16);                    /* extern */

void func_8007FFE4(Unk *arg0, Unk *arg1, s32 arg2) {
    char *sp54;
    s16 sp50;
    Unk *temp_s1;
    Unk *temp_s6;
    Unk *var_s0;

    temp_s6 = arg1->unk10;
    if (temp_s6->unk34 == 0) {
        var_s0 = arg0->unk50;
        if (var_s0 != NULL) {
            do {
                temp_s1 = var_s0->unk0;
                if ((var_s0->unkC == 6) && ((s32)arg1 == var_s0->unk10)) {
                    if (temp_s1 != NULL) {
                        temp_s1->unk8 = (s32) (temp_s1->unk8 + var_s0->unk8);
                    }
                    func_8007DA18(var_s0);
                    func_8007DA48(var_s0, arg0 + 0x48);
                }
                var_s0 = temp_s1;
            } while (temp_s1 != NULL);
        }
    }
    temp_s6->unk33 = 0;
    temp_s6->unk34 = 3U;
    temp_s6->unk30 = 0;
    temp_s6->unk24 = (s32) (arg0->unk1C + arg2);
    func_800865E8(arg0->unk14, arg1, 0);
    func_80086418(arg0->unk14, arg1, 0, arg2);
    sp50 = 5;
    sp54 = arg1;
    func_8007E734(arg0 + 0x48, &sp50, arg2);
}
