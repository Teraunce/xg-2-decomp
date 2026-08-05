#include "ultra64.h"
s32 func_8007C768();                                /* extern */
s32 func_8007C788(s32);                               /* extern */
extern Unk *D_80095644;

void func_80087318(char *arg0) {
    s32 temp_v0;

    temp_v0 = func_8007C768();
    D_80095644->unk8 = arg0;
    D_80095644->unk0 = 1;
    D_80095644->unkC = (s32) ((Unk *)D_80095644->unk8)->unk4;
    func_8007C788(temp_v0);
}
