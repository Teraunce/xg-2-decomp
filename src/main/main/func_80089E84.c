#include "ultra64.h"
s32 func_80088C98(s32, s32, u16, s32, s32);           /* extern */

s32 func_80089E84(Unk *arg0) {
    Unk *sp = (Unk*)0;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 temp_t1;
    s32 temp_v0;

    sp20 = 0;
    sp24 = 0;
    do {
        ((Unk *)(sp + sp24))->unk28 = (u8) arg0->unk65;
        temp_t1 = sp24 + 1;
        sp24 = temp_t1;
    } while (temp_t1 < 0x20);
    temp_v0 = func_80088C98(arg0->unk4, arg0->unk8, 0x400, &sp28, 0);
    sp20 = temp_v0;
    return temp_v0;
}
