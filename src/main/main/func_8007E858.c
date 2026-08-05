#include "ultra64.h"
s32 func_8007C7A8(s32);                             /* extern */
void func_8007DA18(Unk*);                            /* extern */
void func_8007DA48(Unk*, void**);                    /* extern */
void func_8007E958(Unk*, char*, s32);                  /* extern */

s32 func_8007E858(Unk *arg0, s16 *arg1) {
    s32 sp28;
    s32 sp24;
    s32 var_v1;
    Unk *temp_s0;

    sp24 = func_8007C7A8(1);
    temp_s0 = arg0->unk8;
    var_v1 = 0;
    if (temp_s0 != NULL) {
        func_8007DA18(temp_s0);
        func_8007E958(temp_s0 + 0xC, arg1, 0x10);
        func_8007DA48(temp_s0, arg0);
        var_v1 = temp_s0->unk8;
    } else {
        *arg1 = -1;
    }
    sp28 = var_v1;
    func_8007C7A8(sp24);
    return sp28;
}
