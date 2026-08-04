#include "ultra64.h"
void func_8004E594(void *);                           /* extern */
void func_8004E5D8(void *);                            /* extern */
void func_8004EF78(void *, void *, s32);                 /* extern */
void func_8004F2F0(Unk*);                            /* extern */
s32 func_80056788(void *, void *, void *);            /* extern */
void func_800576FC(Unk*, Unk*, Unk*);                 /* extern */
void func_80057B74(Unk*, Unk*, Unk*);            /* extern */
void func_80058294(void *, s32, s32, s32, s32, s32, s32); /* extern */
s32 func_800EEC78(void *, f32, f32, f32, void *);     /* extern */
s32 func_800F1604(void *, void *, void *);               /* extern */
s32 func_801114CC(void *, s32);                       /* extern */
s32 func_801304A8(void *);                          /* extern */
extern s32 D_8004BC60;
extern f32 D_8004BC64;
extern f32 D_8004BC68;
extern f32 D_8004BC6C;
extern s32 D_8017C958;
extern s32 D_80184580;

void func_8005252C(Unk *arg0, Unk *arg1, Unk *arg2, s32 arg3) {
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    s32 sp60;
    s32 sp20;
    s32 temp_fs0;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fs0_2;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft1_2;
    f32 temp_ft2;
    f32 temp_ft3;
    f32 temp_fv1;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    char *temp_s0;
    char *temp_s0_2;
    char *temp_s1;
    Unk *temp_s2;
    char *temp_s2_2;
    char *temp_s4;
    Unk *var_a0;
    Unk *var_a0_2;

    temp_s2 = arg0->unkC;
    if (temp_s2 != NULL) {
        temp_fs0 = D_8004BC60;
        func_80058294(&sp20, arg1->unk0, arg1->unk4, arg1->unk8, 0, temp_fs0, 0);
        sp70 = temp_s2->unk34;
        sp74 = temp_s2->unk38;
        sp78 = temp_s2->unk3C;
        func_800576FC(&sp20, &sp70, &sp80);
        arg0->unk10 = (f32) (arg2->unk0 + sp80);
        arg0->unk14 = (f32) (arg2->unk4 + sp84);
        arg0->unk18 = (f32) (arg2->unk8 + sp88);
        sp70 = temp_s2->unk40;
        sp74 = temp_s2->unk44;
        sp78 = temp_s2->unk48;
        func_800576FC(&sp20, &sp70, &sp80);
        arg0->unk1C = (f32) (arg2->unk0 + sp80);
        arg0->unk20 = (f32) (arg2->unk4 + sp84);
        arg0->unk40 = 0;
        arg0->unk44 = temp_fs0;
        arg0->unk48 = 0;
        arg0->unk24 = (f32) (arg2->unk8 + sp88);
        arg0->unk5FC = (s32) arg0->unk40;
        arg0->unk600 = (s32) arg0->unk44;
        arg0->unk604 = (s32) arg0->unk48;
        arg0->unk608 = (s32) arg0->unk40;
        arg0->unk60C = (s32) arg0->unk44;
        arg0->unk610 = (s32) arg0->unk48;
        temp_ft2 = arg0->unk10 - arg0->unk1C;
        temp_ft1 = arg0->unk14 - arg0->unk20;
        temp_fv1 = arg0->unk18 - arg0->unk24;
        arg0->unk4C = 5;
        arg0->unk50 = 0;
        arg0->unkE8 = 0;
        arg0->unkEC = 0;
        arg0->unkF0 = 0;
        arg0->unkF4 = temp_ft2;
        arg0->unkF8 = temp_ft1;
        arg0->unkFC = temp_fv1;
        temp_ft0 = sqrtf((temp_ft2 * temp_ft2) + (temp_ft1 * temp_ft1) + (temp_fv1 * temp_fv1));
        arg0->unk10C = temp_ft0;
        arg0->unkF4 = (f32) (temp_ft2 / temp_ft0);
        arg0->unkF8 = (f32) (temp_ft1 / temp_ft0);
        arg0->unkB8 = 0;
        arg0->unkBC = 0;
        arg0->unkC0 = 0;
        arg0->unkC4 = 0;
        arg0->unkC8 = 0;
        arg0->unkCC = 0;
        arg0->unkFC = (f32) (arg0->unkFC / temp_ft0);
        arg0->unk28 = (f32) arg0->unk10;
        arg0->unk2C = (f32) arg0->unk14;
        arg0->unk30 = (f32) arg0->unk18;
        arg0->unk34 = (f32) arg0->unk1C;
        arg0->unk38 = (f32) arg0->unk20;
        arg0->unk3C = (f32) arg0->unk24;
        arg0->unkD0 = (s32) arg0->unkB8;
        arg0->unkD4 = (s32) arg0->unkBC;
        arg0->unkD8 = (s32) arg0->unkC0;
        arg0->unkDC = (s32) arg0->unkC4;
        arg0->unkE0 = (s32) arg0->unkC8;
        arg0->unkE4 = (s32) arg0->unkCC;
        arg0->unk518 = (f32) arg0->unk10;
        arg0->unk51C = (f32) arg0->unk14;
        arg0->unk520 = (f32) arg0->unk18;
        arg0->unk524 = (f32) arg0->unk1C;
        arg0->unk528 = (f32) arg0->unk20;
        arg0->unk52C = (f32) arg0->unk24;
        arg0->unk530 = (f32) arg0->unk10;
        arg0->unk534 = (f32) arg0->unk14;
        arg0->unk538 = (f32) arg0->unk18;
        arg0->unk53C = (f32) arg0->unk1C;
        arg0->unk540 = (f32) arg0->unk20;
        arg0->unk544 = (f32) arg0->unk24;
        temp_fa0 = arg0->unk1C;
        temp_ft3 = arg0->unk20;
        temp_ft1_2 = arg0->unk24;
        temp_fa0_2 = temp_fa0 + ((arg0->unk10 - temp_fa0) * D_8004BC64);
        temp_s2_2 = arg0 + 0x190;
        temp_s1 = arg0 + 0x1C;
        arg0->unk448 = 0;
        arg0->unk0 = temp_fa0_2;
        arg0->unk4 = (f32) (temp_ft3 + ((arg0->unk14 - temp_ft3) * D_8004BC64));
        arg0->unk8 = (f32) (temp_ft1_2 + ((arg0->unk18 - temp_ft1_2) * D_8004BC64));
        arg0->unk110 = 0;
        arg0->unk188 = 0;
        func_8004E594(temp_s2_2);
        func_8004E5D8(arg0 + 0x298);
        temp_s0 = arg0 + 0x3B0;
        func_8004EF78(temp_s1, temp_s0, arg3);
        func_800F1604(temp_s0, temp_s1, &sp60);
        arg0->unk450 = 0;
        arg0->unk454 = -1;
        arg0->unk45C = -1;
        arg0->unk5A4 = 0;
        arg0->unk2F4 = 0;
        func_800EEC78(temp_s2_2, arg0->unk1C, arg0->unk20, arg0->unk24, arg0);
        arg0->unk2DC = 0;
        if (arg0->unk588 == 1) {
            var_v0 = 6;
        } else {
            var_v0 = D_80184580;
            if (var_v0 != 1) {
                var_v0 = 3;
            }
        }
        arg0->unk2E0 = var_v0;
        arg0->unk2E4 = var_v0;
        if (D_8017C958 != 0) {
            arg0->unk64C = 1;
        } else {
            arg0->unk64C = 0;
        }
        if (D_8017C958 != 0) {
            arg0->unk64C = 1;
        } else {
            arg0->unk64C = 0;
        }
        var_v1 = 0;
        if (arg0->unk2E4 > 0) {
            var_a0 = arg0;
            do {
                var_a0->unk2E8 = -1;
                var_v1 += 1;
                var_a0 += 2;
            } while (var_v1 < arg0->unk2E4);
        }
        var_v1_2 = 6;
        var_a0_2 = arg0 + 0x18;
        arg0->unk2A4 = -1;
        arg0->unk2A8 = 0;
        arg0->unk2AC = -1;
        do {
            var_a0_2->unk2B0 = -1;
            var_v1_2 -= 1;
            var_a0_2 -= 4;
        } while (var_v1_2 >= 0);
        if (D_80184580 != 4) {
            arg0->unk2CC = 0;
        } else {
            arg0->unk2CC = 0x2A30;
        }
        temp_s4 = arg0 + 0x334;
        temp_fs0_2 = D_8004BC6C;
        arg0->unk2D0 = 0;
        arg0->unk2D4 = 0;
        arg0->unk2D8 = 0;
        arg0->unk324 = 0x3C;
        arg0->unk318 = (f32) D_8004BC68;
        arg0->unk320 = 0;
        arg0->unk350 = 0;
        arg0->unk34C = -1;
        arg0->unk30C = (f32) D_8004BC68;
        arg0->unk308 = 0;
        arg0->unk334 = 0.0f;
        arg0->unk338 = 0.0f;
        arg0->unk33C = temp_fs0_2;
        arg0->unk4E0 = -1;
        arg0->unk314 = (s32) ((Unk *)arg0->unk114)->unk18;
        if (arg0->unk594 == 0) {
            arg0->unk390 = func_801114CC(arg0, -1);
            arg0->unk310 = func_801304A8(arg0);
            arg0->unk594 = 1;
        }
        arg0->unk438 = 1;
        arg0->unk4E4 = 0;
        arg0->unk4E8 = 0;
        arg0->unk4EC = 0;
        arg0->unk4F0 = temp_fs0_2;
        arg0->unk4F4 = 0;
        arg0->unk548 = 0;
        arg0->unk558 = 0;
        arg0->unk55C = 0;
        func_8004F2F0(arg0 + 0x118);
        func_8004F2F0(arg0 + 0x150);
        func_8004F2F0(arg0 + 0x468);
        func_8004F2F0(arg0 + 0x4A0);
        arg0->unk4D8 = 0;
        arg0->unk4DC = 0;
        arg0->unk564 = 0;
        arg0->unk568 = 0;
        arg0->unk56C = 0;
        arg0->unk570 = 0;
        arg0->unk574 = 0;
        arg0->unk578 = 0;
        arg0->unk57C = 0;
        arg0->unk580 = 0;
        arg0->unk584 = 0;
        arg0->unk598 = 0;
        arg0->unk59C = 0;
        arg0->unk5A0 = 0;
        arg0->unk5A8 = 0;
        arg0->unk554 = 0;
        arg0->unk5AC = -1;
        arg0->unk5B0 = -1;
        arg0->unk5B8 = 0;
        arg0->unk5BC = 0;
        arg0->unk5B4 = 0;
        arg0->unk5C0 = 0x3FC;
        arg0->unk5C4 = 0;
        arg0->unk614 = 0;
        arg0->unk334 = (f32) (arg0->unk10 - arg0->unk1C);
        arg0->unk338 = (f32) (arg0->unk14 - arg0->unk20);
        arg0->unk33C = (f32) (arg0->unk18 - arg0->unk24);
        func_80056788(temp_s4, arg0 + 0x338, arg0 + 0x33C);
        temp_s0_2 = arg0 + 0x100;
        arg0->unk340 = (f32) arg0->unk334;
        arg0->unk344 = (f32) arg0->unk338;
        arg0->unk348 = (f32) arg0->unk33C;
        func_80057B74(temp_s4, arg0 + 0x40, temp_s0_2);
        func_80056788(temp_s0_2, arg0 + 0x104, arg0 + 0x108);
        arg0->unk618 = 0;
        arg0->unk61C = 0;
        arg0->unk648 = 0;
        arg0->unk650 = 0;
        arg0->unk658 = 0;
    }
}

f32 func_80052B84(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    return (arg0 * arg3) + (arg1 * arg4) + (arg2 * arg5);
}

/* D_80052BAC: rodata (float constants) — defined in entry.s */
