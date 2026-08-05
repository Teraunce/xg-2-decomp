#include "ultra64.h"
s32 func_8013AB6C(s32, s32, void *, void *, s32);     /* extern */
extern s32 D_80090EA0;
extern s32 D_80091E70;
extern s32 D_800939B8;
extern s32 D_80093A28;
extern s32 D_80093B10;
extern s32 D_80093B98;
extern s32 D_80170874;
extern Unk *D_80173CC0;
extern char *D_80174BF8;
extern s32 D_801786B8;
extern s32 D_8017C118;
extern s32 D_8017C7F0;

void func_80068D2C(s32 arg0, f32 arg1) {
    s32 sp68;
    char *sp64;
    s32 sp60;
    s32 *sp5C;
    s32 *sp58;
    s32 sp50;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    char *var_t3;
    char *var_v0;
    f32 temp_fs0;
    f32 temp_ft0;
    f32 temp_ft0_2;
    f32 temp_ft1;
    f32 temp_ft1_2;
    f32 temp_ft2;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    Unk *var_t0;
    Unk *var_t1;
    s32 temp_s2;
    s32 temp_s6;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_s2;
    s32 var_s5;
    s32 var_t2;
    s32 var_t4;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    Unk *temp_a0;
    Unk *temp_a0_2;
    Unk *temp_a1;
    Unk *temp_a1_2;
    Unk *temp_a3;
    Unk *temp_s1;
    Unk *temp_s4;
    Unk *temp_v0;
    Unk *temp_v0_2;
    Unk *temp_v0_3;
    Unk *temp_v1_3;
    Unk *var_s0;
    Unk *var_s7;

    var_t2 = arg0;
    D_80173CC0->unk0 = 0xDE000000;
    D_80173CC0->unk4 = &D_80093B98;
    temp_a0 = D_80173CC0 + 8;
    D_80173CC0 = temp_a0;
    if (((Unk*)((char*)&D_80090EA0 + (var_t2 * 0x228)))->unk1E4 != 0) {
        D_80173CC0 = temp_a0 + 8;
        var_v0 = &D_80093A28;
    } else {
        D_80173CC0 = temp_a0 + 8;
        var_v0 = &D_800939B8;
    }
    D_80173CC0->unk8 = 0xDE000000;
    temp_a0->unk4 = var_v0;
    D_80173CC0->unk0 = 0xDE000000;
    D_80173CC0->unk4 = &D_80093B10;
    temp_v0 = (var_t2 * 0x228) + &D_80090EA0;
    temp_v1 = temp_v0->unkB4;
    temp_a1 = D_80173CC0 + 8;
    var_t4 = (s32) ((f32) temp_v0->unkB0 * arg1);
    D_80173CC0 = temp_a1;
    if (temp_v1 >= 0x3DF) {
        D_80173CC0 = temp_a1 + 8;
        D_80173CC0->unk8 = 0xDB080000;
        D_80173CC0 = temp_a1 + 0x10;
        temp_a1->unk4 = 0x3200CF00;
        temp_a1->unk8 = 0xE7000000;
        temp_a1->unkC = 0;
        if (D_801786B8 != 0) {
            var_v1 = 0x0C184A50;
        } else {
            var_v1 = 0x0C1849D8;
        }
        D_80173CC0 = temp_a1 + 0x18;
        temp_a1->unk10 = 0xE200001C;
        temp_a1->unk14 = var_v1;
    } else {
        temp_s2 = 0x3E3 - ((s32) (0x3E3 - temp_v1) / 16);
        temp_v1_2 = 0x3E8 - temp_s2;
        D_80173CC0 = temp_a1 + 8;
        D_80173CC0->unk8 = 0xDB080000;
        temp_a1->unk4 = (s32) (((0x1F400 / temp_v1_2) << 0x10) | (((s32) ((0x1F4 - temp_s2) << 8) / temp_v1_2) & 0xFFFF));
        if (D_801786B8 != 0) {
            var_v1_2 = 0xC8104A50;
        } else {
            var_v1_2 = 0xC81049D8;
        }
        D_80173CC0 = temp_a1 + 0x10;
        temp_a1->unk8 = 0xE200001C;
        temp_a1->unkC = var_v1_2;
    }
    temp_v0_2 = (var_t2 * 0x228) + &D_80090EA0;
    var_s7 = D_80174BF8;
    sp40 = temp_v0_2->unkC - temp_v0_2->unk0;
    temp_v1_3 = D_80173CC0;
    temp_a0_2 = D_80173CC0 + 8;
    D_80173CC0 = temp_a0_2;
    sp44 = temp_v0_2->unk10 - temp_v0_2->unk4;
    D_80173CC0 = temp_a0_2 + 8;
    D_80173CC0 = temp_a0_2 + 0x10;
    sp48 = temp_v0_2->unk14 - temp_v0_2->unk8;
    temp_v1_3->unk4 = 0x30;
    temp_v1_3->unk0 = 0xE3001A01;
    temp_a0_2->unk4 = 0xC0;
    D_80173CC0->unk8 = 0xE3001801;
    temp_a0_2->unk8 = 0xE7000000;
    temp_a0_2->unkC = 0;
    if (var_s7 != NULL) {
        var_t3 = &D_80090EA0;
        sp50 = var_t2 * 0x44;
        do {
            temp_s4 = var_s7->unk84;
            var_s2 = 0;
            var_s5 = temp_s4->unk18 + (temp_s4->unk20 * 0x28);
            if (temp_s4->unk24 > 0) {
                temp_s6 = (sp50 + var_t2) * 8;
                temp_s1 = temp_s6 + var_t3;
                temp_fs0 = (f32) var_t4;
                var_t1 = &D_8017C7F0;
                var_t0 = &D_80091E70;
                var_s0 = var_s5 + 0x24;
                do {
                    temp_fv1 = temp_s1->unk0;
                    temp_ft2 = (f32) *(f32*)((char*)var_s0 - 18)- temp_fv1;
                    if ((temp_ft2 < temp_fs0) && (temp_ft1 = temp_s1->unk4, (((f32) *(f32*)((char*)var_s0 - 14)- temp_ft1) < temp_fs0)) && (temp_ft0 = temp_s1->unk8, (((f32) *(f32*)((char*)var_s0 - 10)- temp_ft0) < temp_fs0)) && (temp_fv1_2 = (f32) -var_t4, (temp_fv1_2 < ((f32) *(s32*)((char*)var_s0 - 12) - temp_fv1))) && (temp_fv1_2 < ((f32) *(f32*)((char*)var_s0 - 8)- temp_ft1)) && (temp_fv1_2 < ((f32) *(f32*)((char*)var_s0 - 4)- temp_ft0))) {
                        sp18 = temp_ft2;
                        sp1C = (f32) *(s32*)((char*)var_s0 - 12) - temp_s1->unk0;
                        sp20 = (f32) *(f32*)((char*)var_s0 - 14)- temp_s1->unk4;
                        sp24 = (f32) *(f32*)((char*)var_s0 - 8)- temp_s1->unk4;
                        sp28 = (f32) *(f32*)((char*)var_s0 - 10)- temp_s1->unk8;
                        var_a0 = 0;
                        sp2C = (f32) *(f32*)((char*)var_s0 - 4)- temp_s1->unk8;
                        var_v1_3 = 0 & 1;
loop_23:
                        temp_ft0_2 = (&sp18)[var_v1_3];
                        sp30 = temp_ft0_2;
                        temp_fv0 = *(&sp20 + ((var_a0 * 2) & 4));
                        sp34 = temp_fv0;
                        temp_ft1_2 = *(&sp28 + (var_a0 & 4));
                        sp38 = temp_ft1_2;
                        if (((sp40 * temp_ft0_2) + (sp44 * temp_fv0) + (sp48 * temp_ft1_2)) >= 0.0f) {
                            sp58 = var_t0;
                            sp5C = var_t1;
                            sp60 = var_t2;
                            sp64 = var_t3;
                            sp68 = var_t4;
                            func_8013AB6C(var_t1->unk0 + (D_8017C118 << 7) + (var_t0->unk0 << 6), var_s5, temp_s6 + var_t3, temp_s4, D_80170874);
                            temp_a3 = D_80173CC0;
                            temp_a1_2 = D_80173CC0 + 8;
                            temp_a3->unk0 = 0xDA380003;
                            D_80173CC0 = temp_a1_2;
                            D_80173CC0 = temp_a1_2 + 8;
                            temp_a3->unk4 = (s32) (*(s32*)((char*)var_t1 - 3810)+ (D_8017C118 << 7) + (var_t0->unk1E70 << 6));
                            D_80173CC0->unk8 = 0xDE000000;
                            D_8017C118 += 1;
                            temp_a1_2->unk4 = (s32) var_s0->unk0;
                            var_s0 += 0x28;
                        } else {
                            var_a0 += 1;
                            var_v1_3 = var_a0 & 1;
                            if (var_a0 >= 8) {
                                goto block_26;
                            }
                            goto loop_23;
                        }
                    } else {
block_26:
                        var_s0 += 0x28;
                    }
                    var_s2 += 1;
                    var_s5 += 0x28;
                } while (var_s2 < temp_s4->unk24);
            }
            var_s7 = var_s7->unk0;
        } while (var_s7 != NULL);
    }
    temp_v0_3 = D_80173CC0 + 8;
    D_80173CC0->unk0 = 0xE3001801;
    D_80173CC0->unk4 = 0x40;
    D_80173CC0 = temp_v0_3;
    D_80173CC0 = temp_v0_3 + 8;
    D_80173CC0->unk8 = 0xE7000000;
    temp_v0_3->unk4 = 0;
}
