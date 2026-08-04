#include "ultra64.h"
void **func_8004D7A0(void *);                       /* extern */
extern s32 D_8004B8B0;

void func_8004E670(s32 arg0, Unk *arg1, Unk *arg2) {
    Unk *temp_v0;

    temp_v0 = *func_8004D7A0((arg0 * 0x10) + &D_8004B8B0);
    arg2->unk6C = temp_v0;
    arg1->unk64C = 1;
    arg1->unkC = (s32) temp_v0->unk30;
}
