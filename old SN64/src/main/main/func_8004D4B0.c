#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
s32 func_8004D434(s32, s32 *);                        /* extern */
extern s32 D_80090D04;

void func_8004D4B0(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 *var_a3;
    s32 temp_a0;
    s32 var_a2;

    var_a2 = arg2;
    var_a3 = arg3;
    if (arg1 != 0) {
        var_a3 = &D_80090D04;
        var_a2 = D_80090D04;
        if (var_a2 >= arg0) {
            temp_a0 = (arg0 + 0xF) & ~0xF;
            M2C_ERROR(/* Read from unset register $t0 */)->unkD00 = (s32) (arg1 + temp_a0);
            D_80090D04 = var_a2 - temp_a0;
            return;
        }
    }
    func_8004D434(var_a2, var_a3);
}
