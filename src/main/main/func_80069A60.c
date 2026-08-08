#include "ultra64.h"
void mtxCopyTranslate(Unk*, Unk*, f32, f32, f32);           /* extern */
void mtxXfmPoint3(Unk*, Unk*, Unk*);                 /* extern */
void guMtxScaleF2L(Unk*, Unk*);                          /* extern */
void vec3Cross(Unk*, Unk*, Unk*);               /* extern */
void mtxLookAt(Unk*, f32, f32, f32, f32, f32, f32); /* extern */
void guLookAt(s32, s32, s32, s32, f32, f32, f32, f32, f32, f32); /* extern */
void guLookAtHilite(char *, s32, s32, f32, f32, f32, f32, f32, f32, f32); /* extern */
void guMtxXfm(void *, f32, f32, f32, f32 *, f32 *, f32 *); /* extern */
void guEulerScaleL(s32, f32, f32, s32, f32, f32, f32, f32); /* extern */
s32 func_800AE674(s32, s32, s32, s32);                /* extern */
extern f32 D_8004C3C8;
extern f32 D_8004C3CC;
extern f32 D_8004C3D0;
extern f32 D_8004C3D4;
extern f32 D_8004C3D8;
extern f32 D_8004C3DC;
extern f32 D_8004C3E0;
extern f32 D_8004C3E4;
extern f32 D_8004C3E8;
extern f32 D_8004C3EC;
extern f32 D_8004C3F0;
extern f32 D_8004C3F4;
extern f32 D_8004C3F8;
extern f32 D_8004C3FC;
extern f32 D_8004C400;
extern s32 gPlayerList;
extern s32 D_80170880;
extern s32 D_80173C70;
extern Unk *D_80173CC0;
extern Unk *D_80178690;
extern s32 D_8017C114;
extern s32 D_8017C118;
extern s32 D_8017C1B0;
extern s32 D_8017C7F0;
extern s32 D_80182EA8;

void cameraViewRender(Unk *arg0, Unk *arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7) {
    f32 *sp1A0;
    s32 sp160;
    f32 sp158;
    f32 sp154;
    f32 sp150;
    f32 sp148;
    f32 sp144;
    f32 sp140;
    f32 sp138;
    f32 sp134;
    f32 sp130;
    s32 spF0;
    s32 spB0;
    s32 sp70;
    s32 sp30;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_ft1;
    f32 var_ft2;
    f32 var_fv1;
    s32 *var_s0;
    s32 *var_s2;
    s32 temp_a0;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 temp_a0_6;
    s32 temp_a0_7;
    s32 temp_a0_8;
    s32 temp_a0_9;
    s32 temp_a1_3;
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_hi;
    s32 var_s6;
    s32 var_t0;
    s32 var_t5;
    s32 var_t6;
    s32 var_v0_2;
    s32 var_v0_4;
    s32 var_v0_6;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_5;
    s32 var_v1_6;
    s32 var_v1_7;
    s32 var_v1_8;
    void **var_a0;
    void **var_v1;
    Unk *temp_a0_2;
    Unk *temp_a0_3;
    Unk *temp_a1;
    Unk *temp_a1_2;
    Unk *temp_a2;
    Unk *temp_a3;
    Unk *temp_a3_2;
    Unk *temp_t0;
    Unk *temp_t1;
    Unk *temp_t1_2;
    Unk *temp_t2;
    Unk *temp_t3;
    Unk *temp_v0;
    Unk *temp_v0_2;
    Unk *temp_v0_3;
    Unk *temp_v0_4;
    char *temp_v1;
    Unk *temp_v1_5;
    Unk *temp_v1_6;
    Unk *temp_v1_7;
    char *var_v0;
    char *var_v0_3;
    char *var_v0_5;
    char *var_v1_4;

    var_s6 = arg6;
    temp_fs1 = arg0->unk40;
    temp_fs2 = arg0->unk44;
    temp_fs0 = arg0->unk48;
    mtxLookAt(&sp70, arg0->unk10 - arg0->unk34, arg0->unk14 - arg0->unk38, arg0->unk18 - arg0->unk3C, temp_fs1, temp_fs2, temp_fs0);
    mtxCopyTranslate(&sp70, &sp30, arg0->unk34 - arg1->unk0, arg0->unk38 - arg1->unk4, arg0->unk3C - arg1->unk8);
    guMtxScaleF2L(&sp30, D_8017C7F0 + (D_8017C118 << 7) + (gPlayerList << 6));
    sp1A0 = &sp130;
    sp134 = 0.0f;
    sp130 = ((Unk *)arg0->unkC)->unk78;
    sp138 = ((Unk *)arg0->unkC)->unk80;
    mtxXfmPoint3(&sp70, &sp130, &sp140);
    mtxLookAt(&spB0, (sp140 + arg0->unk34) - arg0->unk1C, (sp144 + arg0->unk38) - arg0->unk20, (sp148 + arg0->unk3C) - arg0->unk24, temp_fs1, temp_fs2, temp_fs0);
    mtxLookAt(&sp70, arg0->unk10 - arg0->unk1C, arg0->unk14 - arg0->unk20, arg0->unk18 - arg0->unk24, temp_fs1, temp_fs2, temp_fs0);
    mtxCopyTranslate(&sp70, &sp30, arg0->unk10 - arg1->unk0, arg0->unk14 - arg1->unk4, arg0->unk18 - arg1->unk8);
    guMtxScaleF2L(&sp30, D_8017C7F0 + ((D_8017C118 << 7) + 0x80) + (gPlayerList << 6));
    mtxCopyTranslate(&spB0, &sp30, arg0->unk1C - arg1->unk0, arg0->unk20 - arg1->unk4, arg0->unk24 - arg1->unk8);
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
    sp130 = arg0->unk1C - arg1->unk0;
    sp134 = arg0->unk20 - arg1->unk4;
    sp138 = arg0->unk24 - arg1->unk8;
    sp140 = arg1->unk18;
    sp144 = arg1->unk1C;
    sp148 = arg1->unk20;
    vec3Cross(sp1A0, &sp140, &sp150);
    guLookAtHilite(&sp160, 0, 0, 0.0f, sp150, sp154, sp158, arg1->unk18, arg1->unk1C, arg1->unk20);
    temp_a1 = D_80173CC0;
    temp_a3 = D_80173CC0 + 8;
    temp_a1->unk0 = 0xDC08000A;
    D_80173CC0 = temp_a3;
    temp_v1 = (D_8017C114 << 6) + ((gPlayerList << 5) + &D_8017C1B0);
    temp_a1->unk4 = temp_v1;
    D_80173CC0->unk8 = 0xDC08030A;
    temp_a3->unk4 = (void *) (temp_v1 + 0x10);
    temp_a1_2 = arg0->unkC;
    D_80173CC0 = temp_a3 + 8;
    D_8017C114 += 1;
    if (temp_a1_2->unk0 == 0) {
        var_ft1 = (temp_a1_2->unk38 - temp_a1_2->unk44) * D_8004C3C8;
        var_ft2 = (temp_a1_2->unk3C - temp_a1_2->unk48) * D_8004C3C8;
        temp_v1_2 = ((Unk*)((char*)&D_80170880 + arg7 * 0x668))->unk64C;
        if (temp_v1_2 != 0) {
            var_s0 = (s32 *)0x80180000;
            if (temp_v1_2 != 1) {
                var_s2 = (s32 *)0x80180000;
            } else {
                var_ft1 -= D_8004C3D0;
                var_ft2 += D_8004C3D4;
                goto block_6;
            }
        } else {
            var_ft1 -= D_8004C3CC;
block_6:
            var_s0 = &D_8017C118;
            var_s2 = &D_8017C7F0;
        }
        guEulerScaleL(*var_s2 + ((*var_s0 << 7) + 0x80) + (gPlayerList << 6), D_8004C3D8, D_8004C3D8, 0, D_8004C3DC, (temp_a1_2->unk34 - temp_a1_2->unk40) * D_8004C3C8, var_ft1, var_ft2);
        temp_v1_3 = *var_s2;
        temp_t2 = D_80173CC0 + 8;
        temp_a1_3 = *var_s0 << 7;
        D_80173CC0->unk0 = 0xDA380003;
        temp_a0 = gPlayerList << 6;
        D_80173CC0->unk4 = (void *) (temp_v1_3 + temp_a1_3 + temp_a0);
        D_80173CC0 = temp_t2;
        D_80173CC0 = temp_t2 + 8;
        D_80173CC0 = temp_t2 + 0x10;
        D_80173CC0->unk8 = 0xDA380001;
        temp_t2->unk4 = (s32) (temp_v1_3 + (temp_a1_3 + 0x80) + temp_a0);
        temp_t2->unk8 = 0xE7000000;
        temp_t2->unkC = 0;
        if (arg2 != 0) {
            if (arg2 < 0xFF) {
                temp_t2->unk18 = 0xFC121BFF;
                temp_t2->unk1C = -0x1C8;
                temp_t2->unk10 = 0xE200001C;
                temp_t2->unk14 = 0xC81049D8;
                temp_t2->unk20 = 0xFB000000;
                temp_t2->unk24 = (s32) (~arg2 & 0xFF);
                temp_t2->unk28 = 0xE3001001;
                temp_t2->unk2C = 0x8000;
                D_80173CC0 = temp_t2 + 0x18;
                D_80173CC0 = temp_t2 + 0x20;
                var_t0 = ((Unk*)(((Unk*)((char*)&D_80182EA8 + arg7 * 4))->unk16F8))->unk8;
                var_hi = MULT_HI(var_t0, 0x4EC4EC4F);
                D_80173CC0 = temp_t2 + 0x28;
                var_v0 = temp_t2 + 0x30;
                goto block_11;
            }
            goto block_72;
        }
        temp_t2->unk18 = 0xFC127FFF;
        temp_t2->unk1C = -0xDC8;
        temp_t2->unk14 = 0xC8103078;
        temp_t2->unk10 = 0xE200001C;
        temp_t2->unk20 = 0xE3001001;
        temp_t2->unk24 = 0x8000;
        var_t0 = ((Unk*)(((Unk*)((char*)&D_80182EA8 + arg7 * 4))->unk16F8))->unk8;
        D_80173CC0 = temp_t2 + 0x18;
        var_hi = MULT_HI(var_t0, 0x4EC4EC4F);
        D_80173CC0 = temp_t2 + 0x20;
        var_v0 = temp_t2 + 0x28;
block_11:
        D_80173CC0 = var_v0;
        func_800AE674(var_t0 - (((var_hi >> 2) - (var_t0 >> 0x1F)) * 0xD), arg0->unk4C, arg0->unk50, arg7);
        var_v1 = (void **)0x80170000;
    } else {
        D_80173CC0 = temp_a3 + 0x10;
        temp_a3->unk8 = 0xDB060010;
        temp_a3->unkC = (void *) D_80178690;
        D_80178690->unk0 = 0xE7000000;
        D_80178690->unk4 = 0;
        D_80178690 += 8;
        if (arg0->unk54 >= 0xD) {
            temp_a3->unk10 = 0xDB060020;
            D_80173CC0 = temp_a3 + 0x18;
            temp_a3->unk14 = (s32) *(s32*)((char*)(((char*)(s32)D_80173C70 + arg0->unk54 * 4)) - 34)
        }
        D_80178690->unk0 = 0xD7000002;
        D_80178690->unk4 = 0x10000800;
        D_80178690 += 8;
        guLookAt(&spF0, 0, 0, 0, arg1->unkC - arg1->unk0, arg1->unk10 - arg1->unk4, arg1->unk14 - arg1->unk8, arg1->unk18, arg1->unk1C, arg1->unk20);
        guMtxXfm(&spF0, arg0->unk0 - arg1->unk0, arg0->unk4 - arg1->unk4, arg0->unk8 - arg1->unk8, &sp140, &sp144, &sp148);
        temp_fv0 = -(sp148 + arg1->unkCC) * D_8004C3E0;
        temp_a3_2 = D_80178690;
        D_80178690 = temp_a3_2 + 8;
        if (!(D_8004C3E4 <= temp_fv0)) {
            var_v1_2 = (s32) temp_fv0;
        } else {
            var_v1_2 = (s32) (temp_fv0 - D_8004C3E4) | 0x80000000;
        }
        temp_a3_2->unk0 = (s32) (((var_v1_2 & 0xFFF) << 0xC) | 0xF2000000);
        temp_a3_2->unk4 = 0;
        temp_t3 = D_80178690 + 8;
        D_80178690->unk0 = 0xDF000000;
        D_80178690->unk4 = 0;
        D_80173CC0->unk0 = 0xDB060018;
        D_80173CC0->unk4 = temp_t3;
        D_80178690->unk8 = 0xE7000000;
        temp_t3->unk4 = 0;
        D_80178690 = temp_t3;
        D_80173CC0 += 8;
        D_80178690 = temp_t3 + 8;
        if (((Unk *)arg0->unkC)->unk2C != 0) {
            var_t5 = 0;
            var_t6 = -1;
            D_80178690 = temp_t3 + 0x10;
            D_80178690 = temp_t3 + 0x18;
            D_80178690 = temp_t3 + 0x20;
            D_80178690 = temp_t3 + 0x28;
            D_80178690 = temp_t3 + 0x30;
            var_fv1 = D_8004C3E8;
            temp_t3->unk8 = 0xFD100000;
            D_80178690 = temp_t3 + 0x38;
            temp_t3->unk10 = 0xE8000000;
            temp_t3->unk1C = 0x07000000;
            temp_t3->unk14 = 0;
            temp_t3->unk18 = 0xF5000110;
            temp_t3->unk20 = 0xE6000000;
            temp_t3->unk24 = 0;
            temp_t3->unk28 = 0xF0000000;
            temp_t3->unk2C = 0x0703C000;
            temp_t3->unk30 = 0xE7000000;
            temp_t3->unk34 = 0;
            temp_t3->unkC = (s32) ((Unk *)arg0->unkC)->unk2C;
            if (D_8004C3EC < arg5) {
                var_t5 = 0x100;
            }
            if (D_8004C3F0 < arg5) {
                var_t5 = 0x200;
                var_t6 = 0;
                var_fv1 = D_8004C3F4;
            }
            if (D_8004C3F8 < arg5) {
                var_t5 = 0x300;
                var_t6 = 1;
                var_fv1 = D_8004C3FC;
            }
            D_80178690 = temp_t3 + 0x40;
            D_80178690 = temp_t3 + 0x48;
            D_80178690 = temp_t3 + 0x50;
            D_80178690 = temp_t3 + 0x58;
            D_80178690 = temp_t3 + 0x60;
            temp_t3->unk38 = 0xFD100000;
            temp_a2 = temp_t3 + 0x70;
            D_80178690 = temp_t3 + 0x68;
            D_80178690 = temp_a2;
            D_80178690 = temp_t3 + 0x78;
            temp_fv0_2 = arg4 / var_fv1;
            temp_t3->unk40 = 0xF51000C0;
            temp_v1_4 = var_t6 & 0xF;
            temp_t3->unk54 = 0x0707F400;
            temp_t3->unk44 = (s32) (temp_v1_4 | 0x07010050);
            temp_t3->unk48 = 0xE6000000;
            temp_t3->unk4C = 0;
            temp_t3->unk50 = 0xF3000000;
            temp_t3->unk58 = 0xE7000000;
            temp_t3->unk5C = 0;
            temp_t3->unk60 = 0xF50004C0;
            temp_t3->unk64 = (s32) (temp_v1_4 | 0x01010050);
            temp_t3->unk68 = 0xF2000000;
            temp_t3->unk6C = 0x0107C03C;
            temp_t3->unk3C = (s32) (((Unk *)arg0->unkC)->unk30 + var_t5);
            if (!(D_8004C400 <= temp_fv0_2)) {
                var_v1_3 = (s32) temp_fv0_2;
            } else {
                var_v1_3 = (s32) (temp_fv0_2 - D_8004C400) | 0x80000000;
            }
            temp_t3->unk70 = (s32) (((var_v1_3 & 0xFFF) << 0xC) | 0xF2000000);
            temp_a2->unk4 = 0x01000000;
            temp_v1_5 = D_80178690;
            D_80178690 += 8;
            temp_v1_5->unk0 = 0xFC113280;
            temp_v1_5->unk4 = -8;
        }
        temp_a0_2 = D_80178690;
        temp_t0 = D_80178690 + 8;
        temp_a0_2->unk0 = 0xDF000000;
        D_80178690 = temp_t0;
        D_80178690 = temp_t0 + 8;
        temp_a0_2->unk4 = 0;
        D_80173CC0->unk0 = 0xDB06001C;
        D_80173CC0->unk4 = temp_t0;
        D_80178690->unk8 = 0xE7000000;
        temp_t0->unk4 = 0;
        D_80173CC0 += 8;
        if (arg2 == 0xFF) {
            var_v1_4 = temp_t0 + 0x10;
            temp_t0->unk8 = 0xFC127FFF;
            var_v0_2 = -0xDC8;
        } else {
            var_v1_4 = temp_t0 + 0x10;
            temp_t0->unk8 = 0xFC1217FF;
            var_v0_2 = -0x1C8;
        }
        D_80178690 = var_v1_4;
        temp_t0->unkC = var_v0_2;
        temp_a0_3 = D_80178690;
        D_80178690 += 8;
        temp_a0_3->unk0 = 0xDF000000;
        temp_a0_3->unk4 = 0;
        if (var_s6 != 1) {
            if (var_s6 >= 2) {
                if (var_s6 != 2) {
                    if (var_s6 == 3) {
                        var_s6 = 2;
                        goto block_36;
                    }
                } else {
block_36:
                    if (((Unk *)arg0->unkC)->unkC == 0) {
                        var_s6 = 1;
                    }
                    goto block_38;
                }
            }
        } else {
block_38:
            if (((Unk *)arg0->unkC)->unk10 == 0) {
                var_s6 = 0;
            }
        }
        if ((arg2 != 0) && (arg2 != 0xFF)) {
            temp_v1_6 = D_80173CC0;
            temp_t1 = D_80173CC0 + 8;
            temp_v1_6->unk0 = 0xE7000000;
            D_80173CC0 = temp_t1;
            D_80173CC0 = temp_t1 + 8;
            D_80173CC0 = temp_t1 + 0x10;
            temp_v1_6->unk4 = 0;
            temp_t1->unkC = -0xDC8;
            D_80173CC0->unk8 = 0xE200001C;
            temp_t1->unk4 = 0x1F1A3078;
            temp_t1->unk8 = 0xFCFFFFFF;
            switch (var_s6) {                       /* irregular */
            case 0:
                temp_t1->unk10 = 0xDA380003;
                temp_t1->unk18 = 0xDE000000;
                temp_a0_4 = D_8017C118 << 7;
                temp_a2_2 = gPlayerList << 6;
                temp_t1->unk14 = (s32) (D_8017C7F0 + temp_a0_4 + temp_a2_2);
                D_80173CC0 = temp_t1 + 0x18;
                D_80173CC0 = temp_t1 + 0x20;
                temp_t1->unk20 = 0xDA380003;
                temp_t1->unk24 = (s32) (D_8017C7F0 + (temp_a0_4 + 0x80) + temp_a2_2);
                temp_t1->unk28 = 0xDE000000;
                temp_t1->unk1C = (s32) ((Unk *)arg0->unkC)->unk0;
                D_80173CC0 = temp_t1 + 0x28;
                D_80173CC0 = temp_t1 + 0x30;
                temp_t1->unk30 = 0xDA380003;
                temp_t1->unk34 = (s32) (D_8017C7F0 + (temp_a0_4 + 0x100) + temp_a2_2);
                temp_t1->unk38 = 0xDE000000;
                temp_t1->unk2C = (s32) ((Unk *)arg0->unkC)->unk4;
                D_80173CC0 = temp_t1 + 0x38;
                var_v1_5 = ((Unk *)arg0->unkC)->unk8;
                var_v0_3 = temp_t1 + 0x40;
block_53:
                D_80173CC0 = var_v0_3;
                temp_t1->unk3C = var_v1_5;
                break;
            case 1:
                temp_t1->unk10 = 0xDA380003;
                temp_t1->unk18 = 0xDE000000;
                temp_a0_5 = D_8017C118 << 7;
                var_a2 = gPlayerList << 6;
                temp_t1->unk14 = (s32) (D_8017C7F0 + temp_a0_5 + var_a2);
                D_80173CC0 = temp_t1 + 0x18;
                D_80173CC0 = temp_t1 + 0x20;
                var_v0_4 = D_8017C7F0 + (temp_a0_5 + 0x80) + var_a2;
                var_a1 = ((Unk *)arg0->unkC)->unk0;
                var_v1_6 = D_8017C7F0 + (temp_a0_5 + 0x100);
block_52:
                temp_t1->unk20 = 0xDA380003;
                temp_t1->unk24 = var_v0_4;
                temp_t1->unk28 = 0xDE000000;
                temp_t1->unk1C = var_a1;
                D_80173CC0 = temp_t1 + 0x28;
                D_80173CC0 = temp_t1 + 0x30;
                temp_t1->unk30 = 0xDA380003;
                temp_t1->unk34 = (s32) (var_v1_6 + var_a2);
                temp_t1->unk38 = 0xDE000000;
                temp_t1->unk2C = (s32) ((Unk *)arg0->unkC)->unk10;
                D_80173CC0 = temp_t1 + 0x38;
                var_v1_5 = ((Unk *)arg0->unkC)->unk14;
                var_v0_3 = temp_t1 + 0x40;
                goto block_53;
            case 2:
                temp_t1->unk10 = 0xDA380003;
                temp_t1->unk18 = 0xDE000000;
                temp_a0_6 = D_8017C118 << 7;
                var_a2 = gPlayerList << 6;
                temp_t1->unk14 = (s32) (D_8017C7F0 + temp_a0_6 + var_a2);
                D_80173CC0 = temp_t1 + 0x18;
                D_80173CC0 = temp_t1 + 0x20;
                var_v0_4 = D_8017C7F0 + (temp_a0_6 + 0x80) + var_a2;
                var_v1_6 = D_8017C7F0 + (temp_a0_6 + 0x100);
                var_a1 = ((Unk *)arg0->unkC)->unkC;
                goto block_52;
            case 3:
                temp_t1->unk10 = 0xDA380003;
                temp_t1->unk18 = 0xDE000000;
                temp_t1->unk14 = (s32) (D_8017C7F0 + (D_8017C118 << 7) + (gPlayerList << 6));
                D_80173CC0 = temp_t1 + 0x18;
                D_80173CC0 = temp_t1 + 0x20;
                temp_t1->unk1C = (s32) ((Unk *)arg0->unkC)->unk18;
                break;
            }
            var_a0 = (void **)0x80170000;
            var_a2_2 = 0x0C184DD8;
        } else {
            var_a0 = &D_80173CC0;
            var_a2_2 = 0xC8103078;
        }
        temp_v0_2 = *var_a0;
        temp_v0_3 = temp_v0_2 + 8;
        temp_v0_2->unk0 = 0xE7000000;
        *var_a0 = temp_v0_3;
        temp_v0_2->unk4 = 0;
        *var_a0 = temp_v0_3 + 8;
        temp_v0_2->unk8 = 0xE200001C;
        temp_v0_3->unk4 = var_a2_2;
        if (arg2 != 0xFF) {
            temp_v1_7 = D_80173CC0;
            temp_t1_2 = D_80173CC0 + 8;
            temp_v1_7->unk0 = 0xE7000000;
            D_80173CC0 = temp_t1_2;
            D_80173CC0 = temp_t1_2 + 8;
            temp_v1_7->unk4 = 0;
            D_80173CC0->unk8 = 0xFA000000;
            temp_t1_2->unk4 = (s32) ((0xFF - arg2) & 0xFF);
            D_80173CC0 = temp_t1_2 + 0x10;
            temp_t1_2->unkC = -0x1C8;
            temp_t1_2->unk8 = 0xFC1217FF;
            if (var_s6 != 1) {
                if (var_s6 < 2) {
                    var_v1 = (void **)0x80170000;
                    if (var_s6 != 0) {

                    } else {
                        temp_t1_2->unk10 = 0xDA380003;
                        temp_t1_2->unk18 = 0xDE000000;
                        temp_a0_7 = D_8017C118 << 7;
                        temp_a2_3 = gPlayerList << 6;
                        temp_t1_2->unk14 = (s32) (D_8017C7F0 + temp_a0_7 + temp_a2_3);
                        D_80173CC0 = temp_t1_2 + 0x18;
                        D_80173CC0 = temp_t1_2 + 0x20;
                        temp_t1_2->unk20 = 0xDA380003;
                        temp_t1_2->unk24 = (s32) (D_8017C7F0 + (temp_a0_7 + 0x80) + temp_a2_3);
                        temp_t1_2->unk28 = 0xDE000000;
                        temp_t1_2->unk1C = (s32) ((Unk *)arg0->unkC)->unk0;
                        D_80173CC0 = temp_t1_2 + 0x28;
                        D_80173CC0 = temp_t1_2 + 0x30;
                        temp_t1_2->unk30 = 0xDA380003;
                        temp_t1_2->unk34 = (s32) (D_8017C7F0 + (temp_a0_7 + 0x100) + temp_a2_3);
                        temp_t1_2->unk38 = 0xDE000000;
                        temp_t1_2->unk2C = (s32) ((Unk *)arg0->unkC)->unk4;
                        D_80173CC0 = temp_t1_2 + 0x38;
                        var_v1_7 = ((Unk *)arg0->unkC)->unk8;
                        var_v0_5 = temp_t1_2 + 0x40;
                        goto block_70;
                    }
                } else if (var_s6 != 2) {
                    var_v1 = (void **)0x80170000;
                    if (var_s6 != 3) {

                    } else {
                        temp_t1_2->unk10 = 0xDA380003;
                        temp_t1_2->unk18 = 0xDE000000;
                        temp_t1_2->unk14 = (s32) (D_8017C7F0 + (D_8017C118 << 7) + (gPlayerList << 6));
                        D_80173CC0 = temp_t1_2 + 0x18;
                        D_80173CC0 = temp_t1_2 + 0x20;
                        temp_t1_2->unk1C = (s32) ((Unk *)arg0->unkC)->unk18;
                        goto block_72;
                    }
                } else {
                    temp_t1_2->unk10 = 0xDA380003;
                    temp_t1_2->unk18 = 0xDE000000;
                    temp_a0_8 = D_8017C118 << 7;
                    var_a2_3 = gPlayerList << 6;
                    temp_t1_2->unk14 = (s32) (D_8017C7F0 + temp_a0_8 + var_a2_3);
                    D_80173CC0 = temp_t1_2 + 0x18;
                    D_80173CC0 = temp_t1_2 + 0x20;
                    var_v0_6 = D_8017C7F0 + (temp_a0_8 + 0x80) + var_a2_3;
                    var_v1_8 = D_8017C7F0 + (temp_a0_8 + 0x100);
                    var_a1_2 = ((Unk *)arg0->unkC)->unkC;
                    goto block_69;
                }
            } else {
                temp_t1_2->unk10 = 0xDA380003;
                temp_t1_2->unk18 = 0xDE000000;
                temp_a0_9 = D_8017C118 << 7;
                var_a2_3 = gPlayerList << 6;
                temp_t1_2->unk14 = (s32) (D_8017C7F0 + temp_a0_9 + var_a2_3);
                D_80173CC0 = temp_t1_2 + 0x18;
                D_80173CC0 = temp_t1_2 + 0x20;
                var_v0_6 = D_8017C7F0 + (temp_a0_9 + 0x80) + var_a2_3;
                var_a1_2 = ((Unk *)arg0->unkC)->unk0;
                var_v1_8 = D_8017C7F0 + (temp_a0_9 + 0x100);
block_69:
                temp_t1_2->unk20 = 0xDA380003;
                temp_t1_2->unk24 = var_v0_6;
                temp_t1_2->unk28 = 0xDE000000;
                temp_t1_2->unk1C = var_a1_2;
                D_80173CC0 = temp_t1_2 + 0x28;
                D_80173CC0 = temp_t1_2 + 0x30;
                temp_t1_2->unk30 = 0xDA380003;
                temp_t1_2->unk34 = (s32) (var_v1_8 + var_a2_3);
                temp_t1_2->unk38 = 0xDE000000;
                temp_t1_2->unk2C = (s32) ((Unk *)arg0->unkC)->unk10;
                D_80173CC0 = temp_t1_2 + 0x38;
                var_v1_7 = ((Unk *)arg0->unkC)->unk14;
                var_v0_5 = temp_t1_2 + 0x40;
block_70:
                D_80173CC0 = var_v0_5;
                temp_t1_2->unk3C = var_v1_7;
                goto block_72;
            }
        } else {
block_72:
            var_v1 = &D_80173CC0;
        }
    }
    temp_v0_4 = *var_v1;
    *var_v1 = temp_v0_4 + 8;
    temp_v0_4->unk0 = 0xE7000000;
    temp_v0_4->unk4 = 0;
    D_8017C118 += 3;
}
