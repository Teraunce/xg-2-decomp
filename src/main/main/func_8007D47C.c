#include "ultra64.h"
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
s32 __osGetCount();                                /* extern */
void func_8007D678();                              /* extern */
extern s32 D_80189A98;

void func_8007D47C(s32 arg0, u32 arg1) {
    u32 sp24;
    s32 sp20;
    s32 sp1C;
    u32 temp_t3;

    sp1C = osDisableInt();
    D_80189A98 = __osGetCount();
    temp_t3 = D_80189A98 + arg1;
    sp20 = (temp_t3 < arg1) + arg0;
    sp24 = temp_t3;
    func_8007D678();
    osRestoreInt(sp1C);
}
