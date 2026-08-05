#include "ultra64.h"
void func_8004D138(s32, s32, s32);                     /* extern */
void func_8004D65C(Unk*, Unk*, s32);                /* extern */
void __osInvalICache_full();                                  /* extern */
extern f32 D_8004BB00;
extern f32 D_8004BB04;
extern f32 D_8004BB08;
extern f32 D_8004BB0C;
extern f32 D_8004BB10;
extern s32 gDLWritePtr;
extern s32 gVideoModeTable;
extern Unk D_800934E0;
extern s32 D_80173C18;
extern f32 D_80178694;
extern f32 D_8017869C;
extern s32 D_8017CA44;
extern s32 D_803DA400;

s32 *func_8004D808(Unk *arg0) {
    s32 *temp_s0;
    s32 temp_a2;

    temp_a2 = arg0->unk4;
    if ((s32) &D_803DA400 >= (gDLWritePtr + temp_a2)) {
        func_8004D138(arg0->unk0, gDLWritePtr, temp_a2);
        temp_s0 = gDLWritePtr + (arg0->unk8 & 0xFFFFFF);
        func_8004D65C(temp_s0, arg0, gDLWritePtr);
        *temp_s0 = gDLWritePtr + (*temp_s0 & 0xFFFFFF);
        gDLWritePtr += arg0->unk4;
        __osInvalICache_full();
        return temp_s0;
    }
    M2C_BREAK(0);
    return NULL;
}

void func_8004D8C0(s32 arg0, s32 arg1) {
    Unk *var_a2;
    f32 temp_ft0;
    f32 temp_fv0;
    s32 var_t0;
    Unk *temp_a0;
    Unk *temp_a1;
    Unk *temp_a3;
    Unk *temp_v1;

    var_t0 = 0;
    var_a2 = &gVideoModeTable;
    temp_ft0 = (f32) arg0 * D_8004BB00;
    D_8017CA44 = arg0;
    temp_fv0 = (f32) arg1 * D_8004BB04;
    D_80173C18 = arg1;
    D_80178694 = temp_ft0;
    D_8017869C = temp_fv0;
    do {
        temp_v1 = var_a2->unk0;
        temp_a1 = var_a2->unk4;
        temp_a0 = var_a2->unk10;
        temp_a3 = var_a2->unk14;
        if (temp_v1 != NULL) {
            temp_v1->unk0 = (s16) (s32) ((f32) var_a2->unk8 * temp_ft0);
            temp_v1->unk4 = 0x1FF;
            temp_v1->unk6 = 0;
            temp_v1->unk2 = (s16) (s32) ((f32) var_a2->unkA * temp_fv0);
            temp_v1->unk8 = (s16) (s32) ((f32) var_a2->unkC * temp_ft0);
            temp_v1->unkC = 0x1FF;
            temp_v1->unkE = 0;
            temp_v1->unkA = (s16) (s32) ((f32) var_a2->unkE * temp_fv0);
        }
        if (temp_a1 != NULL) {
            temp_a1->unk0 = (s16) (s32) ((f32) -var_a2->unk8 * temp_ft0);
            temp_a1->unk4 = 0x1FF;
            temp_a1->unk6 = 0;
            temp_a1->unk2 = (s16) (s32) ((f32) var_a2->unkA * temp_fv0);
            temp_a1->unk8 = (s16) (s32) ((f32) var_a2->unkC * temp_ft0);
            temp_a1->unkC = 0x1FF;
            temp_a1->unkE = 0;
            temp_a1->unkA = (s16) (s32) ((f32) var_a2->unkE * temp_fv0);
        }
        if (temp_a0 != NULL) {
            temp_a0->unk0 = (s32) ((((s32) ((f32) var_a2->unk18 * temp_ft0 * D_8004BB08) & 0xFFF) << 0xC) | (((s32) ((f32) var_a2->unk1A * temp_fv0 * D_8004BB08) & 0xFFF) | 0xED000000));
            temp_a0->unk4 = (s32) ((((s32) ((f32) var_a2->unk1C * temp_ft0 * D_8004BB08) & 0xFFF) << 0xC) | ((s32) ((f32) var_a2->unk1E * temp_fv0 * D_8004BB08) & 0xFFF));
        }
        var_t0 += 1;
        if (temp_a3 != NULL) {
            temp_a3->unk0 = (s32) ((((s32) ((f32) var_a2->unk18 * temp_ft0 * D_8004BB08) & 0xFFF) << 0xC) | (((s32) ((f32) var_a2->unk1A * temp_fv0 * D_8004BB08) & 0xFFF) | 0xED000000));
            temp_a3->unk4 = (s32) ((((s32) ((f32) var_a2->unk1C * temp_ft0 * D_8004BB08) & 0xFFF) << 0xC) | ((s32) ((f32) var_a2->unk1E * temp_fv0 * D_8004BB08) & 0xFFF));
        }
        var_a2 += 0x20;
    } while (var_t0 < 0xC);
    D_800934E0.unk0 = 0xED000000;
    D_800934E0.unk4 = (s32) ((((s32) (D_80178694 * D_8004BB0C) & 0xFFF) << 0xC) | ((s32) (D_8017869C * D_8004BB10) & 0xFFF));
}
