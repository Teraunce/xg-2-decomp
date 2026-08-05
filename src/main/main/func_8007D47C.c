#include "ultra64.h"
s32 func_8007C768();                                /* extern */
s32 func_8007C788(s32);                               /* extern */
s32 func_8007C9D8();                                /* extern */
void func_8007D678();                              /* extern */
extern s32 D_80189A98;

void func_8007D47C(s32 arg0, u32 arg1) {
    u32 sp24;
    s32 sp20;
    s32 sp1C;
    u32 temp_t3;

    sp1C = func_8007C768();
    D_80189A98 = func_8007C9D8();
    temp_t3 = D_80189A98 + arg1;
    sp20 = (temp_t3 < arg1) + arg0;
    sp24 = temp_t3;
    func_8007D678();
    func_8007C788(sp1C);
}
