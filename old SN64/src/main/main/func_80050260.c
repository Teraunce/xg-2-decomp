#include "ultra64.h"
void func_8004FCF8(s32, s32, u16, s32);                 /* extern */
extern s32 D_8017CC80;
extern s32 D_8017CCA0;

void func_80050260(Unk *arg0) {
    s32 var_v1;
    s8 *var_v0;

    var_v1 = 0x1F;
    if (arg0->unk38 != 0) {
        var_v0 = &D_8017CC80 + 0x1F;
        do {
            *var_v0 = 0;
            var_v1 -= 1;
            var_v0 -= 1;
        } while (var_v1 >= 0);
        D_8017CCA0 = 0;
        func_8004FCF8(arg0->unk38, 0, 1, arg0);
    }
}
