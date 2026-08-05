#include "ultra64.h"
s32 func_8007C768();                                /* extern */
s32 func_8007C788(s32);                               /* extern */
extern Unk *D_80095644;

void func_80087678(f32 arg0) {
    s32 temp_s0;

    temp_s0 = func_8007C768();
    D_80095644->unk24 = arg0;
    D_80095644->unk0 = (u16) (D_80095644->unk0 | 4);
    func_8007C788(temp_s0);
}
