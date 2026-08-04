#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
/* Warning: missing "jr $ra" in last block of func_80065958 (initial). */

s32 func_80065670(Unk*);                             /* extern */
void func_80065694(Unk*, s32);                               /* extern */
extern f64 D_8004C0E8;

void func_8006584C(s32 arg0) {
    f64 temp_fv1;
    s32 var_s1;
    Unk *temp_s0;
    Unk *temp_s0_2;

    temp_fv1 = (s32)M2C_ERROR(/* Read from unset register $f2 */) + D_8004C0E8;
    var_s1 = (s32) temp_fv1;
    func_80065694(arg0, (s32) temp_fv1 / 100);
    if (var_s1 < 0) {
        var_s1 = -var_s1;
    }
    temp_s0 = arg0 + ((func_80065670(arg0) & 0xFFFF) * 2);
    temp_s0->unk0 = 0x2E;
    temp_s0_2 = temp_s0 + 2;
    temp_s0->unk2 = (s16) (((var_s1 % 100) / 10) + 0x30);
    ((Unk*)((char*)temp_s0_2 + 2))->unk2 = 0;
    temp_s0_2->unk2 = (s16) ((var_s1 % 10) + 0x30);
}

void func_80065958(s32 arg1, s32 arg2, s32 arg3) {

}
