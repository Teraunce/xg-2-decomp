#include "ultra64.h"
s32 osContPakWrite(s32, s32, u16, s32, s32);         /* extern */
s32 contPakRepairId(Unk*);                          /* extern */

s32 contPakWritePage(Unk *arg0, s32 arg1, s32 arg2, u8 arg3) {
    s32 sp24;
    s32 sp20;
    s32 temp_t5;
    s32 temp_v0;

    sp20 = 0;
    arg0->unk65 = arg3;
    sp20 = contPakRepairId(arg0);
    if (sp20 != 0) {
        return sp20;
    }
    sp24 = 0;
loop_3:
    sp20 = osContPakWrite(arg0->unk4, arg0->unk8, (arg1 * 8) + sp24, arg2, 0);
    if (sp20 == 0) {
        temp_t5 = sp24 + 1;
        sp24 = temp_t5;
        if (temp_t5 < 8) {
            goto loop_3;
        }
    }
    arg0->unk65 = 0U;
    temp_v0 = contPakRepairId(arg0);
    sp20 = temp_v0;
    return temp_v0;
}
