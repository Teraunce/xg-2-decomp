#include "ultra64.h"
void func_8007FDA8(Unk*, Unk*, s32);                  /* extern */
void func_8007FDFC(Unk*, s32);                       /* extern */

void func_8007FE7C(Unk *arg0, Unk *arg1) {
    s32 temp_s1;
    s32 var_s0;
    Unk *var_v0;

    var_v0 = arg1;
    do {
        temp_s1 = var_v0->unkC;
        var_v0 += 4;
    } while (temp_s1 == 0);
    var_s0 = 0;
    if ((s32) arg0->unk34 > 0) {
        do {
            func_8007FDFC(arg0, var_s0);
            func_8007FDA8(arg0, temp_s1, var_s0);
            var_s0 += 1;
        } while (var_s0 < (s32) arg0->unk34);
    }
    if (arg1->unk8 != 0) {
        func_8007FDFC(arg0, var_s0);
        func_8007FDA8(arg0, arg1->unk8, 9);
    }
}

void func_8007FF30(void) {

}

s32 func_8007FF38(Unk *arg0, s32 arg1) {
    s32 temp_v1;

    temp_v1 = arg0->unk24 - arg1;
    if (temp_v1 >= 0) {
        return temp_v1;
    }
    return 0x3E8;
}

s16 func_8007FF5C(Unk *arg0, Unk *arg1) {
    return (s16) ((u32) (((s32) (arg0->unk36 * arg0->unk33 * arg0->unk30) >> 6) * ((s32) (((Unk*)(s32)(arg1->unk60 + (arg0->unk31 * 0x10)))->unk9 * ((Unk *)arg0->unk20)->unkD * arg1->unk32) >> 0xE)) >> 0xF);
}
