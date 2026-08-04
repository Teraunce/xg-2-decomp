#include "ultra64.h"
s32 func_8007C768();                                /* extern */
s32 func_8007C788(s32);                               /* extern */
extern Unk *D_80095644;

void func_80087388(s32 arg0) {
    s32 temp_s0;

    temp_s0 = func_8007C768();
    if (arg0 & 1) {
        D_80095644->unkC = (s32) (D_80095644->unkC | 8);
    }
    if (arg0 & 2) {
        D_80095644->unkC = (s32) (D_80095644->unkC & ~8);
    }
    if (arg0 & 4) {
        D_80095644->unkC = (s32) (D_80095644->unkC | 4);
    }
    if (arg0 & 8) {
        D_80095644->unkC = (s32) (D_80095644->unkC & ~4);
    }
    if (arg0 & 0x10) {
        D_80095644->unkC = (s32) (D_80095644->unkC | 0x10);
    }
    if (arg0 & 0x20) {
        D_80095644->unkC = (s32) (D_80095644->unkC & ~0x10);
    }
    if (arg0 & 0x40) {
        D_80095644->unkC = (s32) (D_80095644->unkC | 0x10000);
        D_80095644->unkC = (s32) (D_80095644->unkC & ~0x300);
    }
    if (arg0 & 0x80) {
        D_80095644->unkC = (s32) (D_80095644->unkC & 0xFFFEFFFF);
        D_80095644->unkC = (s32) (D_80095644->unkC | (((Unk *)D_80095644->unk8)->unk4 & 0x300));
    }
    D_80095644->unk0 = (u16) (D_80095644->unk0 | 8);
    func_8007C788(temp_s0);
}
