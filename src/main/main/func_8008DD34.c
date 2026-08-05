#include "ultra64.h"
s32 func_8007C584(void *, s32);                          /* extern */
s32 func_8007C5CC(void *);                          /* extern */
extern s32 D_800952A8;
extern Unk D_801899E8;

void func_8008DD34(void) {
    Unk *sp2C;
    Unk *sp28;
    s32 sp24;
    s32 temp_hi;

    sp2C = (Unk*)((char*)&D_801899E8 + 0x40);
    sp28 = (Unk*)D_801899E8.unk40;
    if ((D_801899E8.unk40 != 0) && (((Unk*)D_801899E8.unk40)->unk8 < ((Unk*)D_801899E8.unk40)->unk10)) {
        temp_hi = (s32) (sp28->unkC + sp28->unk8) % (s32) sp28->unk10;
        sp24 = temp_hi;
        *(s32*)(s32)(sp28->unk14 + (temp_hi * 4)) = (s32)sp2C->unk4;
        sp28->unk8 = (s32) (sp28->unk8 + 1);
        if (((Unk*)(s32)sp28->unk0)->unk0 != 0) {
            func_8007C584(&D_800952A8, func_8007C5CC(sp28));
        }
    }
}
