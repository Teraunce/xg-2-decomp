#include "ultra64.h"
void func_8006114C(void **);                   /* extern */
extern s32 D_80092B68;
extern Unk D_80092B6C;
extern u32 D_80092B70;
extern s32 D_80178690;
extern Unk *D_801821E8;

void func_80060B9C(s32 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u32 arg8, u32 arg9, u32 arg10, u32 arg11) {
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_a1;
    s16 temp_a2;
    u32 temp_a1_2;
    u32 temp_v1_5;
    Unk *temp_v1;
    Unk *temp_v1_2;
    Unk *temp_v1_3;
    Unk *temp_v1_4;

    if (D_80092B68 == 0) {
        D_80092B6C.unk0 = 0U;
        D_80092B68 = D_80178690;
    }
    temp_a1 = arg6 << 5;
    temp_v1 = D_80092B68 + (D_80092B6C.unk0 * 0x10);
    temp_v1->unkD = (s8) (arg8 >> 8);
    temp_v1->unkE = (s8) (arg8 >> 0x10);
    temp_v1->unkC = (s8) arg8;
    temp_v1->unkF = (s8) (arg8 >> 0x18);
    temp_a0 = arg1 + arg3;
    temp_v1->unk0 = arg1;
    temp_v1->unk2 = (s16) arg5;
    temp_v1->unk4 = arg2;
    temp_v1->unk6 = 0;
    temp_v1->unk8 = 0;
    temp_v1->unkA = 0;
    temp_v1_2 = D_80092B68 + (D_80092B6C.unk0 * 0x10);
    temp_v1_2->unk1D = (s8) (arg9 >> 8);
    temp_v1_2->unk1E = (s8) (arg9 >> 0x10);
    temp_v1_2->unk1C = (s8) arg9;
    temp_v1_2->unk1F = (s8) (arg9 >> 0x18);
    temp_v1_2->unk14 = arg2;
    temp_a2 = arg2 + arg4;
    temp_v1_2->unk10 = temp_a0;
    temp_v1_2->unk12 = (s16) arg5;
    temp_v1_2->unk16 = 0;
    temp_v1_2->unk18 = temp_a1;
    temp_v1_2->unk1A = 0;
    temp_v1_3 = D_80092B68 + (D_80092B6C.unk0 * 0x10);
    temp_v1_3->unk20 = temp_a0;
    temp_a0_2 = arg7 << 5;
    temp_v1_3->unk22 = (s16) arg5;
    temp_v1_3->unk24 = temp_a2;
    temp_v1_3->unk26 = 0;
    temp_v1_3->unk28 = temp_a1;
    temp_v1_3->unk2A = temp_a0_2;
    temp_v1_3->unk2C = (s8) arg10;
    temp_v1_3->unk2D = (s8) (arg10 >> 8);
    temp_v1_3->unk2E = (s8) (arg10 >> 0x10);
    temp_v1_3->unk2F = (s8) (arg10 >> 0x18);
    temp_v1_4 = D_80092B68 + (D_80092B6C.unk0 * 0x10);
    temp_v1_4->unk3D = (s8) (arg11 >> 8);
    temp_v1_4->unk3E = (s8) (arg11 >> 0x10);
    temp_v1_4->unk34 = temp_a2;
    temp_v1_4->unk30 = arg1;
    temp_v1_4->unk32 = (s16) arg5;
    temp_v1_4->unk36 = 0;
    temp_v1_4->unk38 = 0;
    temp_v1_4->unk3A = temp_a0_2;
    temp_v1_4->unk3C = (s8) arg11;
    temp_v1_4->unk3F = (s8) (arg11 >> 0x18);
    ((Unk*)((char*)D_801821E8 + D_80092B70 * 0x10))->unkC = (s8) (D_80092B6C.unk3 + 3);
    ((Unk*)((char*)D_801821E8 + D_80092B70 * 0x10))->unkD = (s8) (D_80092B6C.unk3 + 2);
    ((Unk*)((char*)D_801821E8 + D_80092B70 * 0x10))->unkE = (s8) (D_80092B6C.unk3 + 1);
    ((Unk*)((char*)D_801821E8 + D_80092B70 * 0x10))->unkF = (u8) D_80092B6C.unk3;
    temp_v1_5 = D_80092B70 + 1;
    D_80092B70 = temp_v1_5;
    temp_a1_2 = D_80092B6C.unk0 + 4;
    D_80092B6C.unk0 = temp_a1_2;
    D_80178690 += 0x40;
    if ((temp_v1_5 >= 0x20U) || (temp_a1_2 >= 0x1DU)) {
        func_8006114C((void **)arg0);
    }
}
