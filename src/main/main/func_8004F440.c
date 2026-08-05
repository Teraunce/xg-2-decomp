#include "ultra64.h"
void func_8004F31C(char*, u16*, s32, s32);              /* extern */
void func_8004F3B8(char*, u16*, s32);                   /* extern */
extern s32 D_8017CCB4;

void func_8004F440(Unk *arg0) {
    s16 sp10;
    s32 temp_a2;
    s32 temp_s1;

    sp10 = 0;
    temp_s1 = arg0->unk50;
    D_8017CCB4 = 0;
    func_8004F31C(temp_s1, &sp10, arg0->unk160, arg0->unk164);
    temp_a2 = arg0->unk168;
    if (temp_a2 != 0) {
        func_8004F3B8(temp_s1, &sp10, temp_a2);
    }
}
