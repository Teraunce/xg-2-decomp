#include "ultra64.h"
s32 func_8007C7A8(s32);                             /* extern */
void func_8007DA18(Unk*);                               /* extern */
void func_8007DA48(Unk*, void**);                       /* extern */

void func_8007E6C4(Unk *arg0) {
    s32 sp2C;
    char *temp_s1;
    char *var_s0;

    sp2C = func_8007C7A8(1);
    var_s0 = arg0->unk8;
    if (var_s0 != NULL) {
        do {
            temp_s1 = *var_s0;
            func_8007DA18(var_s0);
            func_8007DA48(var_s0, arg0);
            var_s0 = temp_s1;
        } while (temp_s1 != NULL);
    }
    func_8007C7A8(sp2C);
}
