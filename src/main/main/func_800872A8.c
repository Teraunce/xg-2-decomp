#include "ultra64.h"
s32 func_8007C768();                                /* extern */
s32 func_8007C788(s32);                               /* extern */
extern Unk *D_80095644;

void func_800872A8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = func_8007C768();
    D_80095644->unk10 = arg0;
    D_80095644->unk14 = arg1;
    D_80095644->unk2 = (s16) arg2;
    func_8007C788(temp_v0);
}
