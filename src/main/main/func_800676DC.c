#include "ultra64.h"
void func_800577A8(Unk*, Unk*, Unk*);                /* extern */
void func_80057A94(s32, s32);                       /* extern */
void func_80063F18(s32);                                 /* extern */
void func_80065224(void **);                           /* extern */
void func_80065274(void **);       /* extern */
void func_80066574(s32, s32, s32);       /* extern */
extern s32 D_8004C328;
extern s32 D_8004C330;
extern s32 D_8004C334;
extern f32 D_8004C338;
extern f32 D_8004C33C;
extern f32 D_8004C340;
extern f32 D_8004C344;
extern f32 D_8004C348;
extern f32 D_8004C34C;
extern f32 D_8004C350;
extern f32 D_8004C354;
extern f32 D_8004C358;
extern s32 gEntityPool;
extern s32 gTrackNodeCount;
extern s32 gPlayerList;
extern s32 D_80170880;
extern Unk *D_80173CC0;
extern s32 D_8017C958;
extern s32 D_8017C968;
extern Unk D_80182EA8;
extern s32 D_80185DB8;
extern s8 D_80185DBC;
extern s8 D_80185DBD;
extern s8 D_80185DBE;

void func_800676DC(s32 arg0) {
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    s32 sp20;
    char *var_a1;
    Unk *var_s1;
    f32 temp_fa0;
    f32 temp_fs0;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_ft0;
    f32 temp_ft0_2;
    f32 temp_ft0_3;
    f32 temp_ft2;
    f32 temp_ft2_2;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 temp_a2;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a3;
    s32 var_condition_bit;
    s32 var_s4;
    s32 var_v0_4;
    s32 var_v0_5;
    s8 var_v0;
    s8 var_v0_2;
    s8 var_v0_3;
    Unk *temp_a0;
    Unk *temp_a2_2;
    Unk *temp_s2;
    Unk *temp_s3;
    Unk *temp_v0;
    Unk *temp_v1;
    Unk *temp_v1_4;
    Unk *var_s0;

    temp_s3 = (arg0 * 0x228) + &gEntityPool;
    if ((D_80182EA8.unk16D8 != 2) && (temp_s3->unkD0 != 0)) {
        sp70 = temp_s3->unkC - temp_s3->unk0;
        var_s4 = 0;
        sp74 = temp_s3->unk10 - temp_s3->unk4;
        sp78 = temp_s3->unk14 - temp_s3->unk8;
        func_80057A94(temp_s3 + ((gPlayerList << 6) + 0x30), &sp20);
        func_80065224(&D_80173CC0);
        func_80063F18(0);
        func_80066574(&D_8004C328, 0, 5);
        temp_a0 = D_80173CC0;
        temp_v1 = D_80173CC0 + 8;
        temp_a0->unk0 = 0xE7000000;
        D_80173CC0 = temp_v1;
        D_80173CC0 = temp_v1 + 8;
        D_80173CC0 = temp_v1 + 0x10;
        temp_a0->unk4 = 0;
        D_80173CC0->unk8 = 0xE200001C;
        temp_v1->unk4 = 0x504A50;
        temp_v1->unk8 = 0xE2001D00;
        temp_v1->unkC = 4;
        if (gTrackNodeCount > 0) {
            temp_s2 = (arg0 << 5) + &D_8017C968;
            var_s0 = temp_s3;
            var_s1 = &D_80170880;
            temp_fs3 = D_8004C338;
            temp_fs0 = D_8004C33C;
            temp_fs2 = D_8004C340;
            do {
                if ((var_s1->unk450 == 0) && (var_s4 != ((Unk *)temp_s3->unkD0)->unk560)) {
                    var_fv1 = D_8004C344;
                    if (((Unk*)(s32)var_s1->unk0)->unkC == 0) {
                        var_fv1 = D_8004C348;
                    }
                    temp_ft2 = (var_s1->unk0 + (var_s1->unk40 * var_fv1)) - temp_s3->unk0;
                    sp60 = temp_ft2;
                    temp_ft2_2 = -temp_ft2;
                    temp_ft0 = (var_s1->unk4 + (var_s1->unk44 * var_fv1)) - temp_s3->unk4;
                    sp64 = temp_ft0;
                    temp_ft0_2 = -temp_ft0;
                    temp_fv1 = (var_s1->unk8 + (var_s1->unk48 * var_fv1)) - temp_s3->unk8;
                    temp_fa0 = -temp_fv1;
                    sp80 = temp_ft2_2;
                    sp84 = temp_ft0_2;
                    sp68 = temp_fv1;
                    sp88 = temp_fa0;
                    if (!(((temp_ft2_2 * sp70) + (temp_ft0_2 * sp74) + (temp_fa0 * sp78)) >= 0.0f) && (func_800577A8(&sp20, &sp60, &sp60), !(sp60 <= temp_fs3)) && !(temp_fs0 <= sp60) && !(sp64 <= temp_fs3) && !(temp_fs0 <= sp64) && !(sp68 <= 0.0f) && !(temp_fs0 <= sp68)) {
                        if (D_8017C958 != 0) {
                            var_v0 = 1;
                            if (!(sp68 < temp_fs2)) {
                                var_v0 = 0;
                            }
                            var_s0->unkD4 = var_v0;
                            var_condition_bit = sp68 < temp_fs2;
                            var_v0_2 = 1;
                            goto block_23;
                        }
                        var_v0_3 = 1;
                        if (!(sp68 < D_8004C34C)) {
                            var_v0_3 = 0;
                        }
                        var_s0->unkD4 = var_v0_3;
                        var_v0_2 = 1;
                        if (D_80182EA8.unk16F4 != 0) {
                            var_condition_bit = sp68 < D_8004C350;
block_23:
                            if (!var_condition_bit) {
                                var_v0_2 = 0;
                            }
                            var_s0->unkDC = var_v0_2;
                        } else {
                            var_s0->unkDC = 0;
                        }
                        if (((Unk*)((char*)&gEntityPool + (arg0 * 0x228)))->unk1E4 != 0) {
                            var_fv0 = temp_s2->unk18 - (sp60 * temp_s2->unk10);
                        } else {
                            var_fv0 = temp_s2->unk18 + (sp60 * temp_s2->unk10);
                        }
                        sp60 = var_fv0;
                        temp_ft0_3 = temp_s2->unk1C - (sp64 * temp_s2->unk14);
                        sp64 = temp_ft0_3;
                        temp_v1_2 = temp_s2->unk0;
                        if (((f32) (temp_v1_2 - 0x18) <= sp60) && (sp60 < (f32) (temp_v1_2 + temp_s2->unk8 + 0x18)) && (temp_v1_3 = temp_s2->unk4, ((f32) (temp_v1_3 - 6) <= temp_ft0_3)) && (temp_ft0_3 < (f32) (temp_v1_3 + temp_s2->unkC + 6))) {
                            if ((var_s0->unk124 != 0) && (temp_a2 = (var_s0->unk124 * (0xFF - var_s1->unk558)) / 255, (temp_a2 > 0))) {
                                temp_v1_4 = D_80173CC0 + 8;
                                D_80173CC0->unk0 = 0xE7000000;
                                D_80173CC0->unk4 = 0;
                                D_80173CC0->unk8 = 0xEE000000;
                                var_fv0_2 = sp68;
                                D_80173CC0 = temp_v1_4;
                                D_80173CC0 = temp_v1_4 + 8;
                                if (!(var_fv0_2 <= temp_fs0)) {
                                    var_fv0_2 = temp_fs0;
                                }
                                var_v0_4 = 0;
                                if (!(var_fv0_2 <= 0.0f)) {
                                    var_fv1_2 = sp68;
                                    if (!(var_fv1_2 <= temp_fs0)) {
                                        var_fv1_2 = temp_fs0;
                                    }
                                    temp_fv0 = var_fv1_2 * D_8004C354;
                                    if (D_8004C358 <= temp_fv0) {
                                        var_v0_4 = ((s32) (temp_fv0 - D_8004C358) | 0x80000000) << 0x10;
                                    } else {
                                        var_v0_4 = (s32) temp_fv0 << 0x10;
                                    }
                                }
                                temp_v1_4->unk4 = var_v0_4;
                                if (D_80182EA8.unk16F4 == 2) {
                                    var_v0_5 = var_s1->unk440;
                                    var_a3 = (s32) sp60;
                                    var_a1 = &D_8004C330;
                                } else {
                                    var_a1 = &D_8004C334;
                                    var_a3 = (s32) sp60;
                                    var_v0_5 = ((var_s4 * 4) + &D_80182EA8)->unk16F8 + 0x15;
                                }
                                func_80066574(var_a1, temp_a2, var_a3);
                                var_s0 += 1;
                            } else {
                                goto block_51;
                            }
                        } else {
                            goto block_50;
                        }
                    } else {
block_50:
                        var_s0->unkD4 = 0;
                        var_s0->unkDC = 0;
                        goto block_51;
                    }
                } else {
block_51:
                    var_s0 += 1;
                }
                var_s4 += 1;
                var_s1 += 0x668;
            } while (var_s4 < gTrackNodeCount);
        }
        temp_a2_2 = D_80173CC0;
        temp_v0 = D_80173CC0 + 8;
        temp_a2_2->unk0 = 0xE7000000;
        D_80173CC0 = temp_v0;
        temp_a2_2->unk4 = 0;
        D_80173CC0 = temp_v0 + 8;
        D_80173CC0->unk8 = 0xE2001D00;
        temp_v0->unk4 = 0;
        func_80065274(&D_80173CC0);
    }
}

void func_80067D90(s8 arg0, s8 arg1, s8 arg2, s32 arg3) {
    D_80185DBC = arg0;
    D_80185DBD = arg1;
    D_80185DBE = arg2;
    D_80185DB8 = arg3;
}
