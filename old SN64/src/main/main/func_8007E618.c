#include "ultra64.h"
s32 func_8007C7A8(s32);                             /* extern */
void func_8007DA18(Unk*);                            /* extern */
void func_8007DA48(Unk*, void**);                    /* extern */

void func_8007E618(Unk *arg0, s16 arg1) {
    s32 sp2C;
    Unk *temp_s1;
    Unk *var_s0;

    sp2C = func_8007C7A8(1);
    var_s0 = arg0->unk8;
    if (var_s0 != NULL) {
        do {
            temp_s1 = var_s0->unk0;
            if (arg1 == var_s0->unkC) {
                if (temp_s1 != NULL) {
                    temp_s1->unk8 = (s32) (temp_s1->unk8 + var_s0->unk8);
                }
                func_8007DA18(var_s0);
                func_8007DA48(var_s0, arg0);
            }
            var_s0 = temp_s1;
        } while (temp_s1 != NULL);
    }
    func_8007C7A8(sp2C);
}
