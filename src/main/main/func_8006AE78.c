#include "ultra64.h"
void mtxCopyTranslate(Unk*, Unk*, f32, f32, f32);           /* extern */
void guMtxScaleF2L(Unk*, Unk*);                          /* extern */
void vec3Cross(Unk*, Unk*, Unk*);               /* extern */
void mtxLookAt(Unk*, f32, f32, f32, f32, f32, f32); /* extern */
void guLookAt(s32, s32, s32, s32, f32, f32, f32, f32, f32, f32); /* extern */
void func_8007A6D8(char *, s32, s32, f32, f32, f32, f32, f32, f32, f32); /* extern */
void guMtxXfm(void *, f32, f32, f32, f32 *, f32 *, f32 *); /* extern */
extern f32 D_8004C404;
extern f32 D_8004C408;
extern f32 D_8004C40C;
extern f32 D_8004C410;
extern f32 D_8004C414;
extern f32 D_8004C418;
extern f32 D_8004C41C;
extern f32 D_8004C420;
extern f32 D_8004C424;
extern f32 D_8004C428;
extern f32 D_8004C42C;
extern f32 D_8004C430;
extern f32 D_8004C434;
extern f32 D_8004C438;
extern f32 D_8004C43C;
extern f32 D_8004C440;
extern s32 gPlayerList;
extern Unk *D_80173CC0;
extern Unk *D_80178690;
extern s32 D_8017C114;
extern s32 D_8017C118;
extern s32 D_8017C1B0;
extern s32 D_8017C7F0;

void func_8006AE78(Unk *arg0, Unk *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp120;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    f32 sp108;
    f32 sp104;
    f32 sp100;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    s32 spB0;
    s32 sp70;
    s32 sp30;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_ft0;
    f32 var_ft0_2;
    s32 **var_a0_2;
    s32 **var_t4;
    Unk *temp_a0;
    s32 *temp_a0_2;
    Unk *temp_a0_3;
    Unk *temp_a0_4;
    Unk *temp_a1;
    Unk *temp_a2;
    Unk *temp_a2_2;
    Unk *temp_a2_3;
    Unk *temp_t0;
    Unk *temp_t1;
    Unk *temp_t1_2;
    Unk *temp_t3;
    Unk *temp_t3_2;
    Unk *temp_t3_3;
    Unk *temp_v0;
    Unk *temp_v0_2;
    Unk *temp_v0_3;
    Unk *temp_v0_4;
    s32 *temp_v1;
    Unk *temp_v1_4;
    Unk *temp_v1_5;
    Unk *temp_v1_6;
    s32 *var_v0_2;
    s32 *var_v0_4;
    s32 *var_v1_3;
    s32 *var_v1_6;
    s32 temp_a0_10;
    s32 temp_a0_5;
    s32 temp_a0_6;
    s32 temp_a0_7;
    s32 temp_a0_8;
    s32 temp_a0_9;
    s32 temp_a2_4;
    s32 temp_a2_5;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_t5;
    s32 var_t5_2;
    s32 var_t6;
    s32 var_t6_2;
    s32 var_v0;
    s32 var_v0_3;
    s32 var_v0_5;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_4;
    s32 var_v1_5;
    s32 var_v1_7;
    s32 var_v1_8;

    temp_fs1 = arg0->unk60;
    temp_fs2 = arg0->unk64;
    temp_fs0 = arg0->unk68;
    mtxLookAt(&sp70, arg0->unk30 - arg0->unk3C, arg0->unk34 - arg0->unk40, arg0->unk38 - arg0->unk44, temp_fs1, temp_fs2, temp_fs0);
    mtxCopyTranslate(&sp70, &sp30, arg0->unk3C - arg1->unk0, arg0->unk40 - arg1->unk4, arg0->unk44 - arg1->unk8);
    guMtxScaleF2L(&sp30, D_8017C7F0 + (D_8017C118 << 7) + (gPlayerList << 6));
    mtxLookAt(&sp70, arg0->unk0 - arg0->unkC, arg0->unk4 - arg0->unk10, arg0->unk8 - arg0->unk14, temp_fs1, temp_fs2, temp_fs0);
    mtxCopyTranslate(&sp70, &sp30, arg0->unkC - arg1->unk0, arg0->unk10 - arg1->unk4, arg0->unk14 - arg1->unk8);
    guMtxScaleF2L(&sp30, D_8017C7F0 + ((D_8017C118 << 7) + 0x80) + (gPlayerList << 6));
    mtxLookAt(&sp70, arg0->unk18 - arg0->unk24, arg0->unk1C - arg0->unk28, arg0->unk20 - arg0->unk2C, temp_fs1, temp_fs2, temp_fs0);
    mtxCopyTranslate(&sp70, &sp30, arg0->unk24 - arg1->unk0, arg0->unk28 - arg1->unk4, arg0->unk2C - arg1->unk8);
    guMtxScaleF2L(&sp30, D_8017C7F0 + ((D_8017C118 << 7) + 0x100) + (gPlayerList << 6));
    temp_v0 = D_80173CC0 + 8;
    D_80173CC0->unk0 = 0xD9FFFFFF;
    D_80173CC0->unk4 = 0x20000;
    D_80173CC0 = temp_v0;
    D_80173CC0 = temp_v0 + 8;
    D_80173CC0->unk8 = 0xDB020000;
    temp_v0->unk4 = 0xA8;
    D_80173CC0 = temp_v0 + 0x10;
    temp_v0->unkC = (s32) (arg3 + 8);
    D_80173CC0 = temp_v0 + 0x18;
    temp_v0->unk14 = (s32) (arg3 + 0x18);
    D_80173CC0 = temp_v0 + 0x20;
    temp_v0->unk1C = (s32) (arg3 + 0x28);
    D_80173CC0 = temp_v0 + 0x28;
    temp_v0->unk24 = (s32) (arg3 + 0x38);
    D_80173CC0 = temp_v0 + 0x30;
    temp_v0->unk2C = (s32) (arg3 + 0x48);
    D_80173CC0 = temp_v0 + 0x38;
    temp_v0->unk34 = (s32) (arg3 + 0x58);
    temp_v0->unk3C = (s32) (arg3 + 0x68);
    temp_v0->unk8 = 0xDC08060A;
    temp_v0->unk10 = 0xDC08090A;
    temp_v0->unk18 = 0xDC080C0A;
    temp_v0->unk20 = 0xDC080F0A;
    temp_v0->unk28 = 0xDC08120A;
    temp_v0->unk30 = 0xDC08150A;
    temp_v0->unk38 = 0xDC08180A;
    temp_v0->unk40 = 0xDC081B0A;
    temp_v0->unk44 = arg3;
    D_80173CC0 = temp_v0 + 0x40;
    D_80173CC0 = temp_v0 + 0x48;
    spF0 = arg0->unk3C - arg1->unk0;
    spF4 = arg0->unk40 - arg1->unk4;
    spF8 = arg0->unk44 - arg1->unk8;
    sp100 = arg1->unk18;
    sp104 = arg1->unk1C;
    sp108 = arg1->unk20;
    vec3Cross(&spF0, &sp100, &sp110);
    func_8007A6D8(&sp120, 0, 0, 0.0f, sp110, sp114, sp118, arg1->unk18, arg1->unk1C, arg1->unk20);
    temp_t0 = D_80173CC0 + 8;
    D_80173CC0->unk0 = 0xDC08000A;
    temp_v1 = (D_8017C114 << 6) + ((gPlayerList << 5) + &D_8017C1B0);
    D_80173CC0->unk4 = temp_v1;
    D_80173CC0->unk8 = 0xDC08030A;
    temp_t0->unk4 = (void *) (temp_v1 + 0x10);
    temp_t0->unk8 = 0xDB060010;
    temp_t0->unkC = (s32 *) D_80178690;
    D_80178690->unk0 = 0xD7000002;
    D_80178690->unk4 = 0x10000800;
    D_80173CC0 = temp_t0;
    D_8017C114 += 1;
    D_80173CC0 = temp_t0 + 8;
    D_80173CC0 = temp_t0 + 0x10;
    D_80178690 += 8;
    guLookAt(&spB0, 0, 0, 0, arg1->unkC - arg1->unk0, arg1->unk10 - arg1->unk4, arg1->unk14 - arg1->unk8, arg1->unk18, arg1->unk1C, arg1->unk20);
    guMtxXfm(&spB0, arg0->unk3C - arg1->unk0, arg0->unk40 - arg1->unk4, arg0->unk44 - arg1->unk8, &sp100, &sp104, &sp108);
    temp_fv0 = -(sp108 + arg1->unkCC) * D_8004C404;
    temp_a0 = D_80178690;
    D_80178690 = temp_a0 + 8;
    if (!(D_8004C408 <= temp_fv0)) {
        var_v1 = (s32) temp_fv0;
        var_t4 = (s32 **)0x80180000;
    } else {
        var_v1 = (s32) (temp_fv0 - D_8004C408) | 0x80000000;
        var_t4 = &D_80178690;
    }
    temp_t3 = *var_t4;
    temp_a0->unk0 = ((var_v1 & 0xFFF) << 0xC) | 0xF2000000;
    temp_a0->unk4 = 0;
    temp_t3->unk0 = 0xDF000000;
    temp_t3->unk4 = 0;
    temp_t3_2 = temp_t3 + 8;
    *var_t4 = temp_t3_2;
    if (((Unk *)arg0->unk6C)->unk28 != 0) {
        var_t5 = 0;
        var_t6 = -1;
        *var_t4 = temp_t3_2 + 8;
        *var_t4 = temp_t3_2 + 0x10;
        *var_t4 = temp_t3_2 + 0x18;
        *var_t4 = temp_t3_2 + 0x20;
        var_ft0 = D_8004C40C;
        *var_t4 = temp_t3_2 + 0x28;
        D_80173CC0->unk0 = 0xDB060018;
        D_80173CC0->unk4 = temp_t3_2;
        temp_t3->unk8 = 0xFD100000;
        *var_t4 = temp_t3_2 + 0x30;
        temp_t3_2->unk8 = 0xE8000000;
        temp_t3_2->unk14 = 0x07000000;
        temp_t3_2->unkC = 0;
        temp_t3_2->unk10 = 0xF5000110;
        temp_t3_2->unk18 = 0xE6000000;
        temp_t3_2->unk1C = 0;
        temp_t3_2->unk20 = 0xF0000000;
        temp_t3_2->unk24 = 0x0703C000;
        temp_t3_2->unk28 = 0xE7000000;
        temp_t3_2->unk2C = 0;
        temp_t3_2->unk4 = (s32) ((Unk *)arg0->unk6C)->unk28;
        temp_fv1 = arg0->unk70;
        D_80173CC0 += 8;
        if (D_8004C410 < temp_fv1) {
            var_t5 = 0x100;
        }
        if (D_8004C414 < temp_fv1) {
            var_t5 = 0x200;
            var_t6 = 0;
            var_ft0 = D_8004C418;
        }
        if (D_8004C41C < temp_fv1) {
            var_t5 = 0x300;
            var_t6 = 1;
            var_ft0 = D_8004C420;
        }
        *var_t4 = temp_t3_2 + 0x38;
        *var_t4 = temp_t3_2 + 0x40;
        *var_t4 = temp_t3_2 + 0x48;
        *var_t4 = temp_t3_2 + 0x50;
        *var_t4 = temp_t3_2 + 0x58;
        temp_t3_2->unk30 = 0xFD100000;
        *var_t4 = temp_t3_2 + 0x60;
        temp_a2 = temp_t3_2 + 0x68;
        *var_t4 = temp_a2;
        temp_t3_2->unk38 = 0xF51000C0;
        temp_v1_2 = var_t6 & 0xF;
        *var_t4 = temp_t3_2 + 0x70;
        temp_t3_2->unk3C = (s32) (temp_v1_2 | 0x07010050);
        temp_t3_2->unk40 = 0xE6000000;
        temp_t3_2->unk44 = 0;
        temp_t3_2->unk48 = 0xF3000000;
        temp_t3_2->unk4C = 0x0707F400;
        temp_t3_2->unk50 = 0xE7000000;
        temp_t3_2->unk54 = 0;
        temp_t3_2->unk58 = 0xF50004C0;
        temp_t3_2->unk5C = (s32) (temp_v1_2 | 0x01010050);
        temp_t3_2->unk60 = 0xF2000000;
        temp_t3_2->unk64 = 0x0107C03C;
        temp_t3_2->unk34 = (s32) (((Unk *)arg0->unk6C)->unk2C + var_t5);
        temp_fv0_2 = arg0->unk74 / var_ft0;
        if (!(D_8004C424 <= temp_fv0_2)) {
            var_a0 = (s32) temp_fv0_2;
        } else {
            var_a0 = (s32) (temp_fv0_2 - D_8004C424) | 0x80000000;
        }
        var_t5_2 = 0;
        var_t6_2 = -1;
        temp_t3_2->unk68 = (s32) (((var_a0 & 0xFFF) << 0xC) | 0xF2000000);
        temp_a2->unk4 = 0x01000000;
        var_ft0_2 = D_8004C428;
        temp_t3_3 = D_80178690 + 8;
        temp_a1 = D_80173CC0;
        D_80178690->unk0 = 0xFC113280;
        D_80178690->unk4 = -8;
        temp_a0_2 = temp_t3_3 + 8;
        D_80178690 = temp_t3_3;
        D_80178690 = temp_a0_2;
        D_80178690->unk8 = 0xDF000000;
        temp_t3_3->unk4 = 0;
        temp_a1->unk4 = temp_a0_2;
        D_80173CC0 += 8;
        temp_a1->unk0 = 0xDB060020;
        temp_t3_3->unk8 = 0xFD100000;
        D_80178690 = temp_t3_3 + 0x10;
        D_80178690 = temp_t3_3 + 0x18;
        D_80178690 = temp_t3_3 + 0x20;
        D_80178690 = temp_t3_3 + 0x28;
        D_80178690 = temp_t3_3 + 0x30;
        temp_t3_3->unk10 = 0xE8000000;
        temp_t3_3->unk1C = 0x07000000;
        temp_t3_3->unk14 = 0;
        temp_t3_3->unk18 = 0xF5000110;
        temp_t3_3->unk20 = 0xE6000000;
        temp_t3_3->unk24 = 0;
        temp_t3_3->unk28 = 0xF0000000;
        temp_t3_3->unk2C = 0x0703C000;
        temp_t3_3->unk30 = 0xE7000000;
        temp_t3_3->unk34 = 0;
        temp_t3_3->unkC = (s32) ((Unk *)arg0->unk6C)->unk28;
        temp_fv1_2 = arg0->unk78;
        D_80178690 = temp_t3_3 + 0x38;
        if (D_8004C42C < temp_fv1_2) {
            var_t5_2 = 0x100;
        }
        if (D_8004C430 < temp_fv1_2) {
            var_t5_2 = 0x200;
            var_t6_2 = 0;
            var_ft0_2 = D_8004C434;
        }
        if (D_8004C438 < temp_fv1_2) {
            var_t5_2 = 0x300;
            var_t6_2 = 1;
            var_ft0_2 = D_8004C43C;
        }
        D_80178690 = temp_t3_3 + 0x40;
        D_80178690 = temp_t3_3 + 0x48;
        D_80178690 = temp_t3_3 + 0x50;
        D_80178690 = temp_t3_3 + 0x58;
        D_80178690 = temp_t3_3 + 0x60;
        temp_t3_3->unk38 = 0xFD100000;
        D_80178690 = temp_t3_3 + 0x68;
        temp_a2_2 = temp_t3_3 + 0x70;
        D_80178690 = temp_a2_2;
        temp_t3_3->unk40 = 0xF51000C0;
        temp_v1_3 = var_t6_2 & 0xF;
        D_80178690 = temp_t3_3 + 0x78;
        temp_t3_3->unk44 = (s32) (temp_v1_3 | 0x07010050);
        temp_t3_3->unk48 = 0xE6000000;
        temp_t3_3->unk4C = 0;
        temp_t3_3->unk50 = 0xF3000000;
        temp_t3_3->unk54 = 0x0707F400;
        temp_t3_3->unk58 = 0xE7000000;
        temp_t3_3->unk5C = 0;
        temp_t3_3->unk60 = 0xF50004C0;
        temp_t3_3->unk64 = (s32) (temp_v1_3 | 0x01010050);
        temp_t3_3->unk68 = 0xF2000000;
        temp_t3_3->unk6C = 0x0107C03C;
        temp_t3_3->unk3C = (s32) (((Unk *)arg0->unk6C)->unk2C + var_t5_2);
        temp_fv0_3 = arg0->unk7C / var_ft0_2;
        if (!(D_8004C440 <= temp_fv0_3)) {
            var_v1_2 = (s32) temp_fv0_3;
        } else {
            var_v1_2 = (s32) (temp_fv0_3 - D_8004C440) | 0x80000000;
        }
        temp_t3_3->unk70 = (s32) (((var_v1_2 & 0xFFF) << 0xC) | 0xF2000000);
        temp_a2_2->unk4 = 0x01000000;
        temp_v1_4 = D_80178690;
        temp_a0_3 = D_80178690 + 8;
        temp_v1_4->unk4 = -8;
        D_80178690 = temp_a0_3;
        D_80178690 = temp_a0_3 + 8;
        temp_v1_4->unk0 = 0xFC113280;
        D_80178690->unk8 = 0xDF000000;
        temp_a0_3->unk4 = 0;
    } else {
        *var_t4 = temp_t3_2 + 8;
        temp_v0_2 = D_80173CC0 + 8;
        D_80173CC0->unk0 = 0xDB060010;
        D_80173CC0->unk4 = temp_t3_2;
        D_80173CC0 = temp_v0_2;
        D_80173CC0 = temp_v0_2 + 8;
        D_80173CC0->unk8 = 0xDB060020;
        temp_v0_2->unk4 = temp_t3_2;
        temp_t3->unk8 = 0xDF000000;
        temp_t3_2->unk4 = 0;
    }
    temp_a2_3 = D_80178690;
    D_80173CC0->unk0 = 0xDB06001C;
    D_80173CC0->unk4 = temp_a2_3;
    D_80173CC0 += 8;
    if (arg2 == 0xFF) {
        var_v1_3 = temp_a2_3 + 8;
        temp_a2_3->unk0 = 0xFC127FFF;
        var_v0 = -0xDC8;
    } else {
        var_v1_3 = temp_a2_3 + 8;
        temp_a2_3->unk0 = 0xFC1217FF;
        var_v0 = -0x1C8;
    }
    D_80178690 = var_v1_3;
    temp_a2_3->unk4 = var_v0;
    temp_a0_4 = D_80178690;
    D_80178690 += 8;
    temp_a0_4->unk0 = 0xDF000000;
    temp_a0_4->unk4 = 0;
    if ((arg2 != 0) && (arg2 != 0xFF)) {
        temp_v1_5 = D_80173CC0;
        temp_t1 = D_80173CC0 + 8;
        temp_v1_5->unk0 = 0xE7000000;
        D_80173CC0 = temp_t1;
        D_80173CC0 = temp_t1 + 8;
        D_80173CC0 = temp_t1 + 0x10;
        temp_v1_5->unk4 = 0;
        temp_t1->unkC = -0xDC8;
        D_80173CC0->unk8 = 0xE200001C;
        temp_t1->unk4 = 0x1F1A3078;
        temp_t1->unk8 = 0xFCFFFFFF;
        switch (arg4) {                             /* irregular */
        case 0:
            temp_t1->unk10 = 0xDA380003;
            temp_t1->unk18 = 0xDE000000;
            temp_a0_5 = D_8017C118 << 7;
            temp_a2_4 = gPlayerList << 6;
            temp_t1->unk14 = (s32) (D_8017C7F0 + temp_a0_5 + temp_a2_4);
            D_80173CC0 = temp_t1 + 0x18;
            D_80173CC0 = temp_t1 + 0x20;
            temp_t1->unk20 = 0xDA380003;
            temp_t1->unk24 = (s32) (D_8017C7F0 + (temp_a0_5 + 0x80) + temp_a2_4);
            temp_t1->unk28 = 0xDE000000;
            temp_t1->unk1C = (s32) ((Unk *)arg0->unk6C)->unk0;
            D_80173CC0 = temp_t1 + 0x28;
            D_80173CC0 = temp_t1 + 0x30;
            temp_t1->unk30 = 0xDA380003;
            temp_t1->unk34 = (s32) (D_8017C7F0 + (temp_a0_5 + 0x100) + temp_a2_4);
            temp_t1->unk38 = 0xDE000000;
            temp_t1->unk2C = (s32) ((Unk *)arg0->unk6C)->unk4;
            D_80173CC0 = temp_t1 + 0x38;
            var_v1_4 = ((Unk *)arg0->unk6C)->unk8;
            var_v0_2 = temp_t1 + 0x40;
block_40:
            D_80173CC0 = var_v0_2;
            temp_t1->unk3C = var_v1_4;
            break;
        case 1:
            temp_t1->unk10 = 0xDA380003;
            temp_t1->unk18 = 0xDE000000;
            temp_a0_6 = D_8017C118 << 7;
            var_a2 = gPlayerList << 6;
            temp_t1->unk14 = (s32) (D_8017C7F0 + temp_a0_6 + var_a2);
            D_80173CC0 = temp_t1 + 0x18;
            D_80173CC0 = temp_t1 + 0x20;
            var_v0_3 = D_8017C7F0 + (temp_a0_6 + 0x80) + var_a2;
            var_a1 = ((Unk *)arg0->unk6C)->unk0;
            var_v1_5 = D_8017C7F0 + (temp_a0_6 + 0x100);
block_39:
            temp_t1->unk20 = 0xDA380003;
            temp_t1->unk24 = var_v0_3;
            temp_t1->unk28 = 0xDE000000;
            temp_t1->unk1C = var_a1;
            D_80173CC0 = temp_t1 + 0x28;
            D_80173CC0 = temp_t1 + 0x30;
            temp_t1->unk30 = 0xDA380003;
            temp_t1->unk34 = (s32) (var_v1_5 + var_a2);
            temp_t1->unk38 = 0xDE000000;
            temp_t1->unk2C = (s32) ((Unk *)arg0->unk6C)->unk10;
            D_80173CC0 = temp_t1 + 0x38;
            var_v1_4 = ((Unk *)arg0->unk6C)->unk14;
            var_v0_2 = temp_t1 + 0x40;
            goto block_40;
        case 2:
            temp_t1->unk10 = 0xDA380003;
            temp_t1->unk18 = 0xDE000000;
            temp_a0_7 = D_8017C118 << 7;
            var_a2 = gPlayerList << 6;
            temp_t1->unk14 = (s32) (D_8017C7F0 + temp_a0_7 + var_a2);
            D_80173CC0 = temp_t1 + 0x18;
            D_80173CC0 = temp_t1 + 0x20;
            var_v0_3 = D_8017C7F0 + (temp_a0_7 + 0x80) + var_a2;
            var_v1_5 = D_8017C7F0 + (temp_a0_7 + 0x100);
            var_a1 = ((Unk *)arg0->unk6C)->unkC;
            goto block_39;
        case 3:
            temp_t1->unk10 = 0xDA380003;
            temp_t1->unk18 = 0xDE000000;
            temp_t1->unk14 = (s32) (D_8017C7F0 + (D_8017C118 << 7) + (gPlayerList << 6));
            D_80173CC0 = temp_t1 + 0x18;
            D_80173CC0 = temp_t1 + 0x20;
            temp_t1->unk1C = (s32) ((Unk *)arg0->unk6C)->unk18;
            break;
        }
        var_a0_2 = (s32 **)0x80170000;
        var_a2_2 = 0x0C184DD8;
    } else {
        var_a0_2 = &D_80173CC0;
        var_a2_2 = 0xC8103078;
    }
    temp_v0_3 = *var_a0_2;
    temp_v0_4 = temp_v0_3 + 8;
    temp_v0_3->unk0 = 0xE7000000;
    *var_a0_2 = temp_v0_4;
    temp_v0_3->unk4 = 0;
    *var_a0_2 = temp_v0_4 + 8;
    temp_v0_3->unk8 = 0xE200001C;
    temp_v0_4->unk4 = var_a2_2;
    if (arg2 != 0xFF) {
        temp_v1_6 = D_80173CC0;
        temp_t1_2 = D_80173CC0 + 8;
        temp_v1_6->unk0 = 0xE7000000;
        D_80173CC0 = temp_t1_2;
        D_80173CC0 = temp_t1_2 + 8;
        temp_v1_6->unk4 = 0;
        D_80173CC0->unk8 = 0xFA000000;
        temp_t1_2->unk4 = (s32) ((0xFF - arg2) & 0xFF);
        D_80173CC0 = temp_t1_2 + 0x10;
        temp_t1_2->unkC = -0x1C8;
        temp_t1_2->unk8 = 0xFC1217FF;
        if (arg4 != 1) {
            if (arg4 < 2) {
                var_v1_6 = (s32 *)0x80180000;
                if (arg4 != 0) {

                } else {
                    temp_t1_2->unk10 = 0xDA380003;
                    temp_t1_2->unk18 = 0xDE000000;
                    temp_a0_8 = D_8017C118 << 7;
                    temp_a2_5 = gPlayerList << 6;
                    temp_t1_2->unk14 = (s32) (D_8017C7F0 + temp_a0_8 + temp_a2_5);
                    D_80173CC0 = temp_t1_2 + 0x18;
                    D_80173CC0 = temp_t1_2 + 0x20;
                    temp_t1_2->unk20 = 0xDA380003;
                    temp_t1_2->unk24 = (s32) (D_8017C7F0 + (temp_a0_8 + 0x80) + temp_a2_5);
                    temp_t1_2->unk28 = 0xDE000000;
                    temp_t1_2->unk1C = (s32) ((Unk *)arg0->unk6C)->unk0;
                    D_80173CC0 = temp_t1_2 + 0x28;
                    D_80173CC0 = temp_t1_2 + 0x30;
                    temp_t1_2->unk30 = 0xDA380003;
                    temp_t1_2->unk34 = (s32) (D_8017C7F0 + (temp_a0_8 + 0x100) + temp_a2_5);
                    temp_t1_2->unk38 = 0xDE000000;
                    temp_t1_2->unk2C = (s32) ((Unk *)arg0->unk6C)->unk4;
                    D_80173CC0 = temp_t1_2 + 0x38;
                    var_v1_7 = ((Unk *)arg0->unk6C)->unk8;
                    var_v0_4 = temp_t1_2 + 0x40;
                    goto block_57;
                }
            } else if (arg4 != 2) {
                var_v1_6 = (s32 *)0x80180000;
                if (arg4 != 3) {

                } else {
                    temp_t1_2->unk10 = 0xDA380003;
                    temp_t1_2->unk18 = 0xDE000000;
                    temp_t1_2->unk14 = (s32) (D_8017C7F0 + (D_8017C118 << 7) + (gPlayerList << 6));
                    D_80173CC0 = temp_t1_2 + 0x18;
                    D_80173CC0 = temp_t1_2 + 0x20;
                    temp_t1_2->unk1C = (s32) ((Unk *)arg0->unk6C)->unk18;
                    goto block_59;
                }
            } else {
                temp_t1_2->unk10 = 0xDA380003;
                temp_t1_2->unk18 = 0xDE000000;
                temp_a0_9 = D_8017C118 << 7;
                var_a2_3 = gPlayerList << 6;
                temp_t1_2->unk14 = (s32) (D_8017C7F0 + temp_a0_9 + var_a2_3);
                D_80173CC0 = temp_t1_2 + 0x18;
                D_80173CC0 = temp_t1_2 + 0x20;
                var_v0_5 = D_8017C7F0 + (temp_a0_9 + 0x80) + var_a2_3;
                var_v1_8 = D_8017C7F0 + (temp_a0_9 + 0x100);
                var_a1_2 = ((Unk *)arg0->unk6C)->unkC;
                goto block_56;
            }
        } else {
            temp_t1_2->unk10 = 0xDA380003;
            temp_t1_2->unk18 = 0xDE000000;
            temp_a0_10 = D_8017C118 << 7;
            var_a2_3 = gPlayerList << 6;
            temp_t1_2->unk14 = (s32) (D_8017C7F0 + temp_a0_10 + var_a2_3);
            D_80173CC0 = temp_t1_2 + 0x18;
            D_80173CC0 = temp_t1_2 + 0x20;
            var_v0_5 = D_8017C7F0 + (temp_a0_10 + 0x80) + var_a2_3;
            var_a1_2 = ((Unk *)arg0->unk6C)->unk0;
            var_v1_8 = D_8017C7F0 + (temp_a0_10 + 0x100);
block_56:
            temp_t1_2->unk20 = 0xDA380003;
            temp_t1_2->unk24 = var_v0_5;
            temp_t1_2->unk28 = 0xDE000000;
            temp_t1_2->unk1C = var_a1_2;
            D_80173CC0 = temp_t1_2 + 0x28;
            D_80173CC0 = temp_t1_2 + 0x30;
            temp_t1_2->unk30 = 0xDA380003;
            temp_t1_2->unk34 = (s32) (var_v1_8 + var_a2_3);
            temp_t1_2->unk38 = 0xDE000000;
            temp_t1_2->unk2C = (s32) ((Unk *)arg0->unk6C)->unk10;
            D_80173CC0 = temp_t1_2 + 0x38;
            var_v1_7 = ((Unk *)arg0->unk6C)->unk14;
            var_v0_4 = temp_t1_2 + 0x40;
block_57:
            D_80173CC0 = var_v0_4;
            temp_t1_2->unk3C = var_v1_7;
            goto block_59;
        }
    } else {
block_59:
        var_v1_6 = &D_8017C118;
    }
    *var_v1_6 += 3;
}
