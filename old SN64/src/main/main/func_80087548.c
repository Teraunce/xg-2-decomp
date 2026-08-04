#include "ultra64.h"
s32 func_8007C768();                                /* extern */
s32 func_8007C788(s32);                               /* extern */
extern Unk *D_80095644;

void func_80087548(f32 arg0) {
    s32 temp_v0;

    temp_v0 = func_8007C768();
    D_80095644->unk18 = arg0;
    D_80095644->unk0 = (u16) (D_80095644->unk0 | 2);
    D_80095644->unk20 = (s32) ((u32) (D_80095644->unk18 * (f32) (((Unk *)D_80095644->unk8)->unk20 & 0xFFF)) & 0xFFF);
    func_8007C788(temp_v0);
}
