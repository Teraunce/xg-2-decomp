#include "ultra64.h"
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad02[0x2];
    /* 0x04 */ s32 unk4;
} UnkStruct_D_80095644;

s32 func_8007C768();                                /* extern */
s32 func_8007C788(s32);                               /* extern */
extern UnkStruct_D_80095644 *D_80095644;

void func_800876D8(s32 arg0) {
    s32 sp1C;

    sp1C = func_8007C768();
    D_80095644->unk4 = arg0;
    D_80095644->unk0 = (u16) (D_80095644->unk0 | 0x10);
    func_8007C788(sp1C);
}
