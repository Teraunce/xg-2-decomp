#include "ultra64.h"
void gfxAddLineTex(s32, s8, s8, u16, u16, u16); /* extern */
void gfxAddLineVtx(s32, s16, s16, s32, s32, s32, s32, s32, u32, u32, u32, u32); /* extern */
void renderLineStrip(void**);                            /* extern */
extern f32 D_8004C788;
extern f32 D_8004C78C;
extern f64 D_8004C790;
extern f64 D_8004C798;
extern f32 D_8004C7A0;
extern f32 D_8004C7A4;
extern f64 D_8004C7A8;
extern f64 D_8004C7B0;
extern f32 D_8004C7B8;
extern f32 D_8004C7BC;
extern f64 D_8004C7C0;
extern f64 D_8004C7C8;
extern f32 D_80178694;
extern f32 D_8017869C;
extern char *D_80188E20;
extern s32 D_80188E24;
extern s16 D_80188E2A;
extern s32 D_80188E2C;
extern s32 D_80188E30;
extern s32 D_80188E34;
extern s32 D_80188E38;

void renderTexLine(s32 **arg0, s32 arg1, s32 arg2, s16 arg3, s32 arg4, u32 arg5, u32 arg6, s32 arg7) {
    f32 *sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    u32 sp34;
    u32 sp30;
    f32 *var_t3;
    f32 *var_t3_2;
    f32 *var_t3_3;
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fs0_3;
    f32 temp_fs1;
    f32 temp_fs1_2;
    f32 temp_fs1_3;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv0_5;
    f32 temp_fv0_6;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 temp_fv1_5;
    f32 temp_fv1_6;
    f64 var_fv1;
    f64 var_fv1_2;
    f64 var_fv1_3;
    f64 var_fv1_4;
    f64 var_fv1_5;
    f64 var_fv1_6;
    Unk *temp_a0_3;
    Unk *temp_a0_6;
    Unk *temp_a0_9;
    Unk *temp_v0;
    Unk *temp_v0_10;
    Unk *temp_v0_11;
    Unk *temp_v0_12;
    Unk *temp_v0_13;
    Unk *temp_v0_14;
    Unk *temp_v0_15;
    Unk *temp_v0_16;
    Unk *temp_v0_17;
    Unk *temp_v0_18;
    Unk *temp_v0_19;
    Unk *temp_v0_20;
    Unk *temp_v0_21;
    Unk *temp_v0_22;
    Unk *temp_v0_24;
    Unk *temp_v0_25;
    Unk *temp_v0_26;
    Unk *temp_v0_27;
    Unk *temp_v0_28;
    Unk *temp_v0_29;
    Unk *temp_v0_2;
    Unk *temp_v0_30;
    Unk *temp_v0_31;
    Unk *temp_v0_32;
    Unk *temp_v0_33;
    Unk *temp_v0_34;
    Unk *temp_v0_35;
    Unk *temp_v0_36;
    Unk *temp_v0_37;
    Unk *temp_v0_38;
    Unk *temp_v0_39;
    Unk *temp_v0_3;
    Unk *temp_v0_40;
    Unk *temp_v0_41;
    Unk *temp_v0_42;
    Unk *temp_v0_43;
    Unk *temp_v0_44;
    Unk *temp_v0_45;
    Unk *temp_v0_46;
    Unk *temp_v0_48;
    Unk *temp_v0_49;
    Unk *temp_v0_4;
    Unk *temp_v0_50;
    Unk *temp_v0_51;
    Unk *temp_v0_52;
    Unk *temp_v0_53;
    Unk *temp_v0_54;
    Unk *temp_v0_57;
    Unk *temp_v0_58;
    Unk *temp_v0_59;
    Unk *temp_v0_5;
    Unk *temp_v0_60;
    Unk *temp_v0_62;
    Unk *temp_v0_6;
    Unk *temp_v0_7;
    Unk *temp_v0_8;
    Unk *temp_v0_9;
    s32 *var_v0_9;
    s32 temp_ft1;
    s32 temp_ft1_10;
    s32 temp_ft1_11;
    s32 temp_ft1_12;
    s32 temp_ft1_13;
    s32 temp_ft1_14;
    s32 temp_ft1_15;
    s32 temp_ft1_16;
    s32 temp_ft1_17;
    s32 temp_ft1_18;
    s32 temp_ft1_19;
    s32 temp_ft1_20;
    s32 temp_ft1_21;
    s32 temp_ft1_2;
    s32 temp_ft1_3;
    s32 temp_ft1_4;
    s32 temp_ft1_5;
    s32 temp_ft1_6;
    s32 temp_ft1_7;
    s32 temp_ft1_8;
    s32 temp_ft1_9;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s2_3;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s3_3;
    s32 temp_v0_23;
    s32 temp_v0_47;
    s32 temp_v0_55;
    s32 temp_v0_56;
    s32 temp_v0_61;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_4;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_a2_4;
    s32 var_a2_5;
    s32 var_v0;
    s32 var_v0_10;
    s32 var_v0_11;
    s32 var_v0_12;
    s32 var_v0_13;
    s32 var_v0_14;
    s32 var_v0_15;
    s32 var_v0_16;
    s32 var_v0_17;
    s32 var_v0_19;
    s32 var_v0_20;
    s32 var_v0_21;
    s32 var_v0_22;
    s32 var_v0_23;
    s32 var_v0_24;
    s32 var_v0_25;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v0_8;
    s32 var_v1;
    s32 var_v1_10;
    s32 var_v1_11;
    s32 var_v1_12;
    s32 var_v1_13;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;
    s32 var_v1_6;
    s32 var_v1_7;
    s32 var_v1_8;
    s32 var_v1_9;
    u16 temp_a0_7;
    u16 temp_a0_8;
    u16 temp_a1_2;
    u16 temp_a1_3;
    u16 temp_a1_5;
    u16 temp_a1_6;
    u16 temp_a3;
    u16 temp_a3_2;
    u16 temp_a3_3;
    u16 temp_v1;
    u16 var_a1_3;
    u16 var_v0_18;
    u32 temp_a0;
    u32 temp_a0_2;
    u32 temp_a0_4;
    u32 temp_a0_5;
    u32 temp_s4;
    u32 temp_s4_2;
    u32 temp_s4_3;
    u32 temp_s5;
    u32 temp_s5_2;
    u32 temp_s5_3;
    u32 var_s6;
    u32 var_s6_2;
    u32 var_s6_3;
    char *temp_a1;
    char *temp_a1_4;
    char *temp_a1_7;
    char *temp_a2;
    char *temp_a2_2;
    Unk *temp_s7;
    Unk *var_s1;
    Unk *var_s1_2;
    Unk *var_s1_3;

    sp30 = 0x04000000U / arg5;
    temp_s7 = arg1 + (arg2 * 0x18);
    sp34 = 0x04000000U / arg6;
    temp_v1 = temp_s7->unkA;
    if (temp_v1 == 4) {
        var_s6 = 0;
        if (arg7 == 0) {
            temp_a2 = arg1 + temp_s7->unkC + 8;
            if (temp_a2 != D_80188E20) {
                if (D_80188E20 == NULL) {
                    temp_v0 = *arg0;
                    *arg0 = temp_v0 + 8;
                    temp_v0->unk0 = 0xE7000000;
                    temp_v0->unk4 = 0;
                    temp_v0_2 = *arg0;
                    *arg0 = temp_v0_2 + 8;
                    temp_v0_2->unk0 = 0xE3001001;
                    temp_v0_2->unk4 = 0x8000;
                }
                temp_v0_3 = *arg0;
                *arg0 = temp_v0_3 + 8;
                temp_v0_3->unk0 = 0xFD100000;
                temp_v0_3->unk4 = temp_a2;
                temp_v0_4 = *arg0;
                *arg0 = temp_v0_4 + 8;
                temp_v0_4->unk0 = 0xE8000000;
                temp_v0_4->unk4 = 0;
                temp_v0_5 = *arg0;
                *arg0 = temp_v0_5 + 8;
                temp_v0_5->unk0 = 0xF5000100;
                temp_v0_5->unk4 = 0x07000000;
                temp_v0_6 = *arg0;
                *arg0 = temp_v0_6 + 8;
                temp_v0_6->unk0 = 0xE6000000;
                temp_v0_6->unk4 = 0;
                temp_v0_7 = *arg0;
                *arg0 = temp_v0_7 + 8;
                temp_v0_7->unk0 = 0xF0000000;
                temp_v0_7->unk4 = 0x0703C000;
                temp_v0_8 = *arg0;
                *arg0 = temp_v0_8 + 8;
                temp_v0_8->unk0 = 0xE7000000;
                temp_v0_8->unk4 = 0;
                D_80188E20 = temp_a2;
                var_s6 = 0;
            }
        }
        var_s1 = arg1 + temp_s7->unk10;
        if (temp_s7->unk8 != 0) {
            sp38 = (s32) arg3;
            var_t3 = &D_80178694;
            temp_fs1 = D_8004C788;
            temp_fs0 = D_8004C78C;
            sp3C = (s32) (s16) arg4;
            do {
                var_fv1 = (f64) arg5;
                if ((s32) arg5 < 0) {
                    var_fv1 += D_8004C790;
                }
                var_fv1_2 = (f64) arg6;
                temp_s2 = sp38 + (s32) ((f32) var_s1->unk4 * (f32) var_fv1 * temp_fs1);
                if ((s32) arg6 < 0) {
                    var_fv1_2 += D_8004C798;
                }
                temp_a3 = var_s1->unk0;
                temp_a1 = var_s1 + 8;
                temp_s4 = (u32) ((temp_a3 * arg5) + 0x3FFF) >> 0xE;
                temp_s5 = (u32) ((var_s1->unk2 * arg6) + 0x3FFF) >> 0xE;
                temp_s3 = sp3C + (s32) ((f32) var_s1->unk6 * (f32) var_fv1_2 * temp_fs1);
                if (D_80188E24 != 0) {
                    sp50 = var_t3;
                    gfxAddLineTex(temp_a1, 4, arg7, (s32) temp_a3, (s32) var_s1->unk2, 0);
                    gfxAddLineVtx(arg0, (s32) (temp_s2 << 0xE) >> 0x10, (s32) (temp_s3 << 0xE) >> 0x10, (s32) (temp_s4 << 0xE) >> 0x10, (s32) (temp_s5 << 0xE) >> 0x10, (s32) D_80188E2A, (s32) (s16) var_s1->unk0, (s32) (s16) var_s1->unk2, D_80188E2C, D_80188E30, D_80188E34, D_80188E38);
                } else {
                    if (arg7 != 0) {
                        temp_v0_9 = *arg0;
                        *arg0 = temp_v0_9 + 8;
                        temp_v0_9->unk0 = 0xFD900000;
                        temp_v0_9->unk4 = temp_a1;
                        temp_v0_10 = *arg0;
                        *arg0 = temp_v0_10 + 8;
                        temp_v0_10->unk0 = 0xF5900000;
                        temp_v0_10->unk4 = 0x07080200;
                        temp_v0_11 = *arg0;
                        *arg0 = temp_v0_11 + 8;
                        temp_v0_11->unk0 = 0xE6000000;
                        temp_v0_11->unk4 = 0;
                        temp_v0_12 = *arg0;
                        var_a2 = 0x800;
                        *arg0 = temp_v0_12 + 8;
                        temp_v0_12->unk0 = 0xF3000000;
                        temp_a1_2 = var_s1->unk0;
                        temp_a0 = temp_a1_2 >> 4;
                        if (temp_a0 != 0) {
                            var_a2 = temp_a0 + 0x7FF;
                        }
                        var_v1 = ((s32) ((temp_a1_2 * var_s1->unk2) + 3) >> 2) - 1;
                        if (var_v1 >= 0x800) {
                            var_v1 = 0x7FF;
                        }
                        if (temp_a0 != 0) {
                            var_v0 = (var_a2 / (s32) temp_a0) & 0xFFF;
                        } else {
                            var_v0 = var_a2 & 0xFFF;
                        }
                        temp_v0_12->unk4 = (s32)((((var_v1 & 0xFFF) << 0xC) | 0x07000000 | var_v0));
                        temp_v0_13 = *arg0;
                        *arg0 = temp_v0_13 + 8;
                        temp_v0_13->unk0 = 0xE7000000;
                        temp_v0_13->unk4 = 0;
                        temp_v0_14 = *arg0;
                        *arg0 = temp_v0_14 + 8;
                        temp_v0_14->unk4 = 0x80200;
                        var_v1_2 = 0xF5800000;
                    } else {
                        temp_v0_15 = *arg0;
                        *arg0 = temp_v0_15 + 8;
                        temp_v0_15->unk0 = 0xFD500000;
                        temp_v0_15->unk4 = temp_a1;
                        temp_v0_16 = *arg0;
                        *arg0 = temp_v0_16 + 8;
                        temp_v0_16->unk0 = 0xF5500000;
                        temp_v0_16->unk4 = 0x07080200;
                        temp_v0_17 = *arg0;
                        *arg0 = temp_v0_17 + 8;
                        temp_v0_17->unk0 = 0xE6000000;
                        temp_v0_17->unk4 = 0;
                        temp_v0_18 = *arg0;
                        var_a2_2 = 0x800;
                        *arg0 = temp_v0_18 + 8;
                        temp_v0_18->unk0 = 0xF3000000;
                        temp_a1_3 = var_s1->unk0;
                        temp_a0_2 = temp_a1_3 >> 4;
                        if (temp_a0_2 != 0) {
                            var_a2_2 = temp_a0_2 + 0x7FF;
                        }
                        var_v1_3 = ((s32) ((temp_a1_3 * var_s1->unk2) + 3) >> 2) - 1;
                        if (var_v1_3 >= 0x800) {
                            var_v1_3 = 0x7FF;
                        }
                        if (temp_a0_2 != 0) {
                            var_v0_2 = (var_a2_2 / (s32) temp_a0_2) & 0xFFF;
                        } else {
                            var_v0_2 = var_a2_2 & 0xFFF;
                        }
                        temp_v0_18->unk4 = (s32)((((var_v1_3 & 0xFFF) << 0xC) | 0x07000000 | var_v0_2));
                        temp_v0_19 = *arg0;
                        *arg0 = temp_v0_19 + 8;
                        temp_v0_19->unk0 = 0xE7000000;
                        temp_v0_19->unk4 = 0;
                        temp_v0_20 = *arg0;
                        *arg0 = temp_v0_20 + 8;
                        temp_v0_20->unk4 = 0x80200;
                        var_v1_2 = 0xF5400000;
                    }
                    ((Unk *)*arg0)->unk0 = ((((s32) ((var_s1->unk0 >> 1) + 7) >> 3) & 0x1FF) << 9) | var_v1_2;
                    temp_v0_21 = *arg0;
                    *arg0 = temp_v0_21 + 8;
                    temp_v0_21->unk0 = 0xF2000000;
                    temp_v0_21->unk4 = (s32)((((((var_s1->unk0 - 1) * 4) & 0xFFF) << 0xC) | (((var_s1->unk2 - 1) * 4) & 0xFFF)));
                    temp_a0_3 = *arg0;
                    *arg0 = temp_a0_3 + 8;
                    temp_ft1 = (s32) ((f32) (temp_s2 + temp_s4) * *var_t3);
                    if ((s16) temp_ft1 > 0) {
                        var_v1_4 = (((s16) temp_ft1 & 0xFFF) << 0xC) | 0xE4000000;
                    } else {
                        var_v1_4 = 0xE4000000;
                    }
                    temp_ft1_2 = (s32) ((f32) (temp_s3 + temp_s5) * D_8017869C);
                    if ((s16) temp_ft1_2 > 0) {
                        var_v1_4 |= (s16) temp_ft1_2 & 0xFFF;
                    }
                    temp_a0_3->unk0 = var_v1_4;
                    temp_ft1_3 = (s32) ((f32) temp_s2 * *var_t3);
                    if ((s16) temp_ft1_3 > 0) {
                        var_v0_3 = ((s16) temp_ft1_3 & 0xFFF) << 0xC;
                    } else {
                        var_v0_3 = 0;
                    }
                    var_v1_5 = var_v0_3;
                    temp_ft1_4 = (s32) ((f32) temp_s3 * D_8017869C);
                    if ((s16) temp_ft1_4 > 0) {
                        var_v1_5 |= (s16) temp_ft1_4 & 0xFFF;
                    }
                    temp_a0_3->unk4 = (s32)(var_v1_5);
                    temp_v0_22 = *arg0;
                    *arg0 = temp_v0_22 + 8;
                    temp_fv1 = *var_t3;
                    temp_v0_22->unk0 = 0xE1000000;
                    temp_ft1_5 = (s32) ((f32) temp_s2 * temp_fv1);
                    if ((s16) temp_ft1_5 < 0) {
                        temp_ft1_6 = (s32) ((f32) sp30 / temp_fv1);
                        temp_lo = (s16) temp_ft1_5 * (s16) temp_ft1_6;
                        if ((s16) temp_ft1_6 < 0) {
                            temp_v0_23 = temp_lo >> 7;
                            var_v0_4 = -temp_v0_23;
                            if (temp_v0_23 < 0) {
                                var_v0_5 = 0;
                                goto block_47;
                            }
                        } else {
                            var_v0_5 = temp_lo >> 7;
                            if (var_v0_5 > 0) {
                                var_v0_5 = 0;
                            }
block_47:
                            var_v0_4 = -var_v0_5;
                        }
                        var_a1 = var_v0_4 << 0x10;
                    } else {
                        var_a1 = 0;
                    }
                    temp_fv1_2 = (f32) temp_s3 * D_8017869C;
                    var_v0_6 = var_a1;
                    if (temp_fv1_2 < 0.0f) {
                        temp_ft1_7 = (s32) ((f32) sp34 / D_8017869C);
                        if ((s16) temp_ft1_7 < 0) {
                            var_v0_7 = (s32) ((s16) (s32) temp_fv1_2 * (s16) temp_ft1_7) >> 7;
                            if (var_v0_7 < 0) {
                                var_v0_7 = 0;
                            }
                        } else {
                            var_v0_7 = (s32) ((s16) (s32) temp_fv1_2 * (s16) temp_ft1_7) >> 7;
                            if (var_v0_7 > 0) {
                                var_v0_7 = 0;
                            }
                        }
                        var_v0_6 = var_a1 | (-var_v0_7 & 0xFFFF);
                    }
                    temp_v0_22->unk4 = (s32)(var_v0_6);
                    temp_v0_24 = *arg0;
                    *arg0 = temp_v0_24 + 8;
                    temp_v0_24->unk0 = 0xF1000000;
                    temp_fv0 = (f32) sp30 / *var_t3;
                    if (!(temp_fs0 <= temp_fv0)) {
                        var_a0 = (s32) temp_fv0;
                    } else {
                        var_a0 = (s32) (temp_fv0 - temp_fs0) | 0x80000000;
                    }
                    temp_fv0_2 = (f32) sp34 / D_8017869C;
                    if (!(temp_fs0 <= temp_fv0_2)) {
                        var_v0_8 = (s32) temp_fv0_2 & 0xFFFF;
                    } else {
                        var_v0_8 = ((s32) (temp_fv0_2 - temp_fs0) | 0x80000000) & 0xFFFF;
                    }
                    temp_v0_24->unk4 = (s32)(((var_a0 << 0x10) | var_v0_8));
                }
                var_s6 += 1;
                var_s1 += (((s32) (var_s1->unk0 + 1) >> 1) * var_s1->unk2) + 8;
            } while (var_s6 < (u16) temp_s7->unk8);
            var_v0_9 = (s32 *)0x80190000;
        } else {
            goto block_189;
        }
    } else if (temp_v1 == 8) {
        var_s6_2 = 0;
        if (arg7 == 0) {
            temp_a2_2 = arg1 + temp_s7->unkC + 8;
            if (temp_a2_2 != D_80188E20) {
                if (D_80188E20 == NULL) {
                    temp_v0_25 = *arg0;
                    *arg0 = temp_v0_25 + 8;
                    temp_v0_25->unk0 = 0xE7000000;
                    temp_v0_25->unk4 = 0;
                    temp_v0_26 = *arg0;
                    *arg0 = temp_v0_26 + 8;
                    temp_v0_26->unk0 = 0xE3001001;
                    temp_v0_26->unk4 = 0x8000;
                }
                temp_v0_27 = *arg0;
                *arg0 = temp_v0_27 + 8;
                temp_v0_27->unk0 = 0xFD100000;
                temp_v0_27->unk4 = temp_a2_2;
                temp_v0_28 = *arg0;
                *arg0 = temp_v0_28 + 8;
                temp_v0_28->unk0 = 0xE8000000;
                temp_v0_28->unk4 = 0;
                temp_v0_29 = *arg0;
                *arg0 = temp_v0_29 + 8;
                temp_v0_29->unk0 = 0xF5000100;
                temp_v0_29->unk4 = 0x07000000;
                temp_v0_30 = *arg0;
                *arg0 = temp_v0_30 + 8;
                temp_v0_30->unk0 = 0xE6000000;
                temp_v0_30->unk4 = 0;
                temp_v0_31 = *arg0;
                *arg0 = temp_v0_31 + 8;
                temp_v0_31->unk0 = 0xF0000000;
                temp_v0_31->unk4 = 0x073FC000;
                temp_v0_32 = *arg0;
                *arg0 = temp_v0_32 + 8;
                temp_v0_32->unk0 = 0xE7000000;
                temp_v0_32->unk4 = 0;
                D_80188E20 = temp_a2_2;
                var_s6_2 = 0;
            }
        }
        var_s1_2 = arg1 + temp_s7->unk10;
        if (temp_s7->unk8 != 0) {
            sp40 = (s32) arg3;
            var_t3_2 = &D_80178694;
            temp_fs1_2 = D_8004C7A0;
            temp_fs0_2 = D_8004C7A4;
            sp44 = (s32) (s16) arg4;
            do {
                var_fv1_3 = (f64) arg5;
                if ((s32) arg5 < 0) {
                    var_fv1_3 += D_8004C7A8;
                }
                var_fv1_4 = (f64) arg6;
                temp_s2_2 = sp40 + (s32) ((f32) var_s1_2->unk4 * (f32) var_fv1_3 * temp_fs1_2);
                if ((s32) arg6 < 0) {
                    var_fv1_4 += D_8004C7B0;
                }
                temp_a3_2 = var_s1_2->unk0;
                temp_a1_4 = var_s1_2 + 8;
                temp_s4_2 = (u32) ((temp_a3_2 * arg5) + 0x3FFF) >> 0xE;
                temp_s5_2 = (u32) ((var_s1_2->unk2 * arg6) + 0x3FFF) >> 0xE;
                temp_s3_2 = sp44 + (s32) ((f32) var_s1_2->unk6 * (f32) var_fv1_4 * temp_fs1_2);
                if (D_80188E24 != 0) {
                    sp50 = var_t3_2;
                    gfxAddLineTex(temp_a1_4, 8, arg7, (s32) temp_a3_2, (s32) var_s1_2->unk2, 0);
                    gfxAddLineVtx(arg0, (s32) (temp_s2_2 << 0xE) >> 0x10, (s32) (temp_s3_2 << 0xE) >> 0x10, (s32) (temp_s4_2 << 0xE) >> 0x10, (s32) (temp_s5_2 << 0xE) >> 0x10, (s32) D_80188E2A, (s32) (s16) var_s1_2->unk0, (s32) (s16) var_s1_2->unk2, D_80188E2C, D_80188E30, D_80188E34, D_80188E38);
                } else {
                    if (arg7 != 0) {
                        temp_v0_33 = *arg0;
                        *arg0 = temp_v0_33 + 8;
                        temp_v0_33->unk0 = 0xFD900000;
                        temp_v0_33->unk4 = temp_a1_4;
                        temp_v0_34 = *arg0;
                        *arg0 = temp_v0_34 + 8;
                        temp_v0_34->unk0 = 0xF5900000;
                        temp_v0_34->unk4 = 0x07080200;
                        temp_v0_35 = *arg0;
                        *arg0 = temp_v0_35 + 8;
                        temp_v0_35->unk0 = 0xE6000000;
                        temp_v0_35->unk4 = 0;
                        temp_v0_36 = *arg0;
                        var_a2_3 = 0x800;
                        *arg0 = temp_v0_36 + 8;
                        temp_v0_36->unk0 = 0xF3000000;
                        temp_a1_5 = var_s1_2->unk0;
                        temp_a0_4 = temp_a1_5 >> 3;
                        if (temp_a0_4 != 0) {
                            var_a2_3 = temp_a0_4 + 0x7FF;
                        }
                        var_v1_6 = ((s32) ((temp_a1_5 * var_s1_2->unk2) + 1) >> 1) - 1;
                        if (var_v1_6 >= 0x800) {
                            var_v1_6 = 0x7FF;
                        }
                        if (temp_a0_4 != 0) {
                            var_v0_10 = (var_a2_3 / (s32) temp_a0_4) & 0xFFF;
                        } else {
                            var_v0_10 = var_a2_3 & 0xFFF;
                        }
                        temp_v0_36->unk4 = (s32)((((var_v1_6 & 0xFFF) << 0xC) | 0x07000000 | var_v0_10));
                        temp_v0_37 = *arg0;
                        *arg0 = temp_v0_37 + 8;
                        temp_v0_37->unk0 = 0xE7000000;
                        temp_v0_37->unk4 = 0;
                        temp_v0_38 = *arg0;
                        *arg0 = temp_v0_38 + 8;
                        temp_v0_38->unk4 = 0x80200;
                        var_v1_7 = 0xF5880000;
                    } else {
                        temp_v0_39 = *arg0;
                        *arg0 = temp_v0_39 + 8;
                        temp_v0_39->unk0 = 0xFD500000;
                        temp_v0_39->unk4 = temp_a1_4;
                        temp_v0_40 = *arg0;
                        *arg0 = temp_v0_40 + 8;
                        temp_v0_40->unk0 = 0xF5500000;
                        temp_v0_40->unk4 = 0x07080200;
                        temp_v0_41 = *arg0;
                        *arg0 = temp_v0_41 + 8;
                        temp_v0_41->unk0 = 0xE6000000;
                        temp_v0_41->unk4 = 0;
                        temp_v0_42 = *arg0;
                        var_a2_4 = 0x800;
                        *arg0 = temp_v0_42 + 8;
                        temp_v0_42->unk0 = 0xF3000000;
                        temp_a1_6 = var_s1_2->unk0;
                        temp_a0_5 = temp_a1_6 >> 3;
                        if (temp_a0_5 != 0) {
                            var_a2_4 = temp_a0_5 + 0x7FF;
                        }
                        var_v1_8 = ((s32) ((temp_a1_6 * var_s1_2->unk2) + 1) >> 1) - 1;
                        if (var_v1_8 >= 0x800) {
                            var_v1_8 = 0x7FF;
                        }
                        if (temp_a0_5 != 0) {
                            var_v0_11 = (var_a2_4 / (s32) temp_a0_5) & 0xFFF;
                        } else {
                            var_v0_11 = var_a2_4 & 0xFFF;
                        }
                        temp_v0_42->unk4 = (s32)((((var_v1_8 & 0xFFF) << 0xC) | 0x07000000 | var_v0_11));
                        temp_v0_43 = *arg0;
                        *arg0 = temp_v0_43 + 8;
                        temp_v0_43->unk0 = 0xE7000000;
                        temp_v0_43->unk4 = 0;
                        temp_v0_44 = *arg0;
                        *arg0 = temp_v0_44 + 8;
                        temp_v0_44->unk4 = 0x80200;
                        var_v1_7 = 0xF5480000;
                    }
                    ((Unk *)*arg0)->unk0 = ((((s32) (var_s1_2->unk0 + 7) >> 3) & 0x1FF) << 9) | var_v1_7;
                    temp_v0_45 = *arg0;
                    *arg0 = temp_v0_45 + 8;
                    temp_v0_45->unk0 = 0xF2000000;
                    temp_v0_45->unk4 = (s32)((((((var_s1_2->unk0 - 1) * 4) & 0xFFF) << 0xC) | (((var_s1_2->unk2 - 1) * 4) & 0xFFF)));
                    temp_a0_6 = *arg0;
                    *arg0 = temp_a0_6 + 8;
                    temp_ft1_8 = (s32) ((f32) (temp_s2_2 + temp_s4_2) * *var_t3_2);
                    if ((s16) temp_ft1_8 > 0) {
                        var_v1_9 = (((s16) temp_ft1_8 & 0xFFF) << 0xC) | 0xE4000000;
                    } else {
                        var_v1_9 = 0xE4000000;
                    }
                    temp_ft1_9 = (s32) ((f32) (temp_s3_2 + temp_s5_2) * D_8017869C);
                    if ((s16) temp_ft1_9 > 0) {
                        var_v1_9 |= (s16) temp_ft1_9 & 0xFFF;
                    }
                    temp_a0_6->unk0 = var_v1_9;
                    temp_ft1_10 = (s32) ((f32) temp_s2_2 * *var_t3_2);
                    if ((s16) temp_ft1_10 > 0) {
                        var_v0_12 = ((s16) temp_ft1_10 & 0xFFF) << 0xC;
                    } else {
                        var_v0_12 = 0;
                    }
                    var_v1_10 = var_v0_12;
                    temp_ft1_11 = (s32) ((f32) temp_s3_2 * D_8017869C);
                    if ((s16) temp_ft1_11 > 0) {
                        var_v1_10 |= (s16) temp_ft1_11 & 0xFFF;
                    }
                    temp_a0_6->unk4 = (s32)(var_v1_10);
                    temp_v0_46 = *arg0;
                    *arg0 = temp_v0_46 + 8;
                    temp_fv1_3 = *var_t3_2;
                    temp_v0_46->unk0 = 0xE1000000;
                    temp_ft1_12 = (s32) ((f32) temp_s2_2 * temp_fv1_3);
                    if ((s16) temp_ft1_12 < 0) {
                        temp_ft1_13 = (s32) ((f32) sp30 / temp_fv1_3);
                        temp_lo_2 = (s16) temp_ft1_12 * (s16) temp_ft1_13;
                        if ((s16) temp_ft1_13 < 0) {
                            temp_v0_47 = temp_lo_2 >> 7;
                            var_v0_13 = -temp_v0_47;
                            if (temp_v0_47 < 0) {
                                var_v0_14 = 0;
                                goto block_113;
                            }
                        } else {
                            var_v0_14 = temp_lo_2 >> 7;
                            if (var_v0_14 > 0) {
                                var_v0_14 = 0;
                            }
block_113:
                            var_v0_13 = -var_v0_14;
                        }
                        var_a1_2 = var_v0_13 << 0x10;
                    } else {
                        var_a1_2 = 0;
                    }
                    temp_fv1_4 = (f32) temp_s3_2 * D_8017869C;
                    var_v0_15 = var_a1_2;
                    if (temp_fv1_4 < 0.0f) {
                        temp_ft1_14 = (s32) ((f32) sp34 / D_8017869C);
                        if ((s16) temp_ft1_14 < 0) {
                            var_v0_16 = (s32) ((s16) (s32) temp_fv1_4 * (s16) temp_ft1_14) >> 7;
                            if (var_v0_16 < 0) {
                                var_v0_16 = 0;
                            }
                        } else {
                            var_v0_16 = (s32) ((s16) (s32) temp_fv1_4 * (s16) temp_ft1_14) >> 7;
                            if (var_v0_16 > 0) {
                                var_v0_16 = 0;
                            }
                        }
                        var_v0_15 = var_a1_2 | (-var_v0_16 & 0xFFFF);
                    }
                    temp_v0_46->unk4 = (s32)(var_v0_15);
                    temp_v0_48 = *arg0;
                    *arg0 = temp_v0_48 + 8;
                    temp_v0_48->unk0 = 0xF1000000;
                    temp_fv0_3 = (f32) sp30 / *var_t3_2;
                    if (!(temp_fs0_2 <= temp_fv0_3)) {
                        var_a0_2 = (s32) temp_fv0_3;
                    } else {
                        var_a0_2 = (s32) (temp_fv0_3 - temp_fs0_2) | 0x80000000;
                    }
                    temp_fv0_4 = (f32) sp34 / D_8017869C;
                    if (!(temp_fs0_2 <= temp_fv0_4)) {
                        var_v0_17 = (s32) temp_fv0_4 & 0xFFFF;
                    } else {
                        var_v0_17 = ((s32) (temp_fv0_4 - temp_fs0_2) | 0x80000000) & 0xFFFF;
                    }
                    temp_v0_48->unk4 = (s32)(((var_a0_2 << 0x10) | var_v0_17));
                }
                var_s6_2 += 1;
                var_s1_2 += (var_s1_2->unk0 * var_s1_2->unk2) + 8;
            } while (var_s6_2 < (u16) temp_s7->unk8);
            var_v0_9 = (s32 *)0x80190000;
        } else {
            goto block_189;
        }
    } else {
        var_v0_9 = &D_80188E24;
        if (temp_v1 == 0x10) {
            var_s1_3 = arg1 + temp_s7->unk10;
            if (D_80188E20 != NULL) {
                temp_v0_49 = *arg0;
                *arg0 = temp_v0_49 + 8;
                temp_v0_49->unk0 = 0xE7000000;
                temp_v0_49->unk4 = 0;
                temp_v0_50 = *arg0;
                *arg0 = temp_v0_50 + 8;
                temp_v0_50->unk0 = 0xE3001001;
                temp_v0_50->unk4 = 0;
                D_80188E20 = NULL;
            }
            var_s6_3 = 0;
            if (temp_s7->unk8 != 0) {
                sp48 = (s32) arg3;
                var_t3_3 = &D_80178694;
                temp_fs1_3 = D_8004C7B8;
                temp_fs0_3 = D_8004C7BC;
                sp4C = (s32) (s16) arg4;
                do {
                    var_fv1_5 = (f64) arg5;
                    if ((s32) arg5 < 0) {
                        var_fv1_5 += D_8004C7C0;
                    }
                    var_fv1_6 = (f64) arg6;
                    temp_s2_3 = sp48 + (s32) ((f32) var_s1_3->unk4 * (f32) var_fv1_5 * temp_fs1_3);
                    if ((s32) arg6 < 0) {
                        var_fv1_6 += D_8004C7C8;
                    }
                    temp_a3_3 = var_s1_3->unk0;
                    temp_a1_7 = var_s1_3 + 8;
                    temp_s4_3 = (u32) ((temp_a3_3 * arg5) + 0x3FFF) >> 0xE;
                    temp_s5_3 = (u32) ((var_s1_3->unk2 * arg6) + 0x3FFF) >> 0xE;
                    temp_s3_3 = sp4C + (s32) ((f32) var_s1_3->unk6 * (f32) var_fv1_6 * temp_fs1_3);
                    if (D_80188E24 != 0) {
                        sp50 = var_t3_3;
                        gfxAddLineTex(temp_a1_7, 0x10, arg7, (s32) temp_a3_3, (s32) var_s1_3->unk2, 0);
                        gfxAddLineVtx(arg0, (s32) (temp_s2_3 << 0xE) >> 0x10, (s32) (temp_s3_3 << 0xE) >> 0x10, (s32) (temp_s4_3 << 0xE) >> 0x10, (s32) (temp_s5_3 << 0xE) >> 0x10, (s32) D_80188E2A, (s32) (s16) var_s1_3->unk0, (s32) (s16) var_s1_3->unk2, D_80188E2C, D_80188E30, D_80188E34, D_80188E38);
                    } else {
                        temp_v0_51 = *arg0;
                        *arg0 = temp_v0_51 + 8;
                        temp_v0_51->unk0 = 0xFD100000;
                        temp_v0_51->unk4 = temp_a1_7;
                        temp_v0_52 = *arg0;
                        *arg0 = temp_v0_52 + 8;
                        temp_v0_52->unk0 = 0xF5100000;
                        temp_v0_52->unk4 = 0x07080200;
                        temp_v0_53 = *arg0;
                        *arg0 = temp_v0_53 + 8;
                        temp_v0_53->unk0 = 0xE6000000;
                        temp_v0_53->unk4 = 0;
                        temp_v0_54 = *arg0;
                        *arg0 = temp_v0_54 + 8;
                        temp_v0_54->unk0 = 0xF3000000;
                        temp_a0_7 = var_s1_3->unk0;
                        var_v0_18 = temp_a0_7;
                        if ((s32) temp_a0_7 < 0) {
                            var_v0_18 = temp_a0_7 + 3;
                        }
                        temp_v0_55 = (s32) var_v0_18 >> 2;
                        var_a2_5 = 0x800;
                        if (temp_v0_55 > 0) {
                            var_a2_5 = temp_v0_55 + 0x7FF;
                        }
                        temp_a0_8 = var_s1_3->unk0;
                        var_v1_11 = (temp_a0_8 * var_s1_3->unk2) - 1;
                        if (var_v1_11 >= 0x800) {
                            var_v1_11 = 0x7FF;
                        }
                        var_a1_3 = temp_a0_8;
                        if ((s32) temp_a0_8 < 0) {
                            var_a1_3 = temp_a0_8 + 3;
                        }
                        temp_v0_56 = (s32) var_a1_3 >> 2;
                        if (temp_v0_56 <= 0) {
                            var_v0_19 = var_a2_5 & 0xFFF;
                        } else {
                            var_v0_19 = (var_a2_5 / temp_v0_56) & 0xFFF;
                        }
                        temp_v0_54->unk4 = (s32)((((var_v1_11 & 0xFFF) << 0xC) | 0x07000000 | var_v0_19));
                        temp_v0_57 = *arg0;
                        *arg0 = temp_v0_57 + 8;
                        temp_v0_57->unk0 = 0xE7000000;
                        temp_v0_57->unk4 = 0;
                        temp_v0_58 = *arg0;
                        *arg0 = temp_v0_58 + 8;
                        temp_v0_58->unk4 = 0x80200;
                        temp_v0_58->unk0 = ((((s32) ((var_s1_3->unk0 * 2) + 7) >> 3) & 0x1FF) << 9) | 0xF5100000;
                        temp_v0_59 = *arg0;
                        *arg0 = temp_v0_59 + 8;
                        temp_v0_59->unk0 = 0xF2000000;
                        temp_v0_59->unk4 = (s32)((((((var_s1_3->unk0 - 1) * 4) & 0xFFF) << 0xC) | (((var_s1_3->unk2 - 1) * 4) & 0xFFF)));
                        temp_a0_9 = *arg0;
                        *arg0 = temp_a0_9 + 8;
                        temp_ft1_15 = (s32) ((f32) (temp_s2_3 + temp_s4_3) * *var_t3_3);
                        if ((s16) temp_ft1_15 > 0) {
                            var_v1_12 = (((s16) temp_ft1_15 & 0xFFF) << 0xC) | 0xE4000000;
                        } else {
                            var_v1_12 = 0xE4000000;
                        }
                        temp_ft1_16 = (s32) ((f32) (temp_s3_3 + temp_s5_3) * D_8017869C);
                        if ((s16) temp_ft1_16 > 0) {
                            var_v1_12 |= (s16) temp_ft1_16 & 0xFFF;
                        }
                        temp_a0_9->unk0 = var_v1_12;
                        temp_ft1_17 = (s32) ((f32) temp_s2_3 * *var_t3_3);
                        if ((s16) temp_ft1_17 > 0) {
                            var_v0_20 = ((s16) temp_ft1_17 & 0xFFF) << 0xC;
                        } else {
                            var_v0_20 = 0;
                        }
                        var_v1_13 = var_v0_20;
                        temp_ft1_18 = (s32) ((f32) temp_s3_3 * D_8017869C);
                        if ((s16) temp_ft1_18 > 0) {
                            var_v1_13 |= (s16) temp_ft1_18 & 0xFFF;
                        }
                        temp_a0_9->unk4 = (s32)(var_v1_13);
                        temp_v0_60 = *arg0;
                        *arg0 = temp_v0_60 + 8;
                        temp_fv1_5 = *var_t3_3;
                        temp_v0_60->unk0 = 0xE1000000;
                        temp_ft1_19 = (s32) ((f32) temp_s2_3 * temp_fv1_5);
                        if ((s16) temp_ft1_19 < 0) {
                            temp_ft1_20 = (s32) ((f32) sp30 / temp_fv1_5);
                            temp_lo_3 = (s16) temp_ft1_19 * (s16) temp_ft1_20;
                            if ((s16) temp_ft1_20 < 0) {
                                temp_v0_61 = temp_lo_3 >> 7;
                                var_v0_21 = -temp_v0_61;
                                if (temp_v0_61 < 0) {
                                    var_v0_22 = 0;
                                    goto block_171;
                                }
                            } else {
                                var_v0_22 = temp_lo_3 >> 7;
                                if (var_v0_22 > 0) {
                                    var_v0_22 = 0;
                                }
block_171:
                                var_v0_21 = -var_v0_22;
                            }
                            var_a1_4 = var_v0_21 << 0x10;
                        } else {
                            var_a1_4 = 0;
                        }
                        temp_fv1_6 = (f32) temp_s3_3 * D_8017869C;
                        var_v0_23 = var_a1_4;
                        if (temp_fv1_6 < 0.0f) {
                            temp_ft1_21 = (s32) ((f32) sp34 / D_8017869C);
                            if ((s16) temp_ft1_21 < 0) {
                                var_v0_24 = (s32) ((s16) (s32) temp_fv1_6 * (s16) temp_ft1_21) >> 7;
                                if (var_v0_24 < 0) {
                                    var_v0_24 = 0;
                                }
                            } else {
                                var_v0_24 = (s32) ((s16) (s32) temp_fv1_6 * (s16) temp_ft1_21) >> 7;
                                if (var_v0_24 > 0) {
                                    var_v0_24 = 0;
                                }
                            }
                            var_v0_23 = var_a1_4 | (-var_v0_24 & 0xFFFF);
                        }
                        temp_v0_60->unk4 = (s32)(var_v0_23);
                        temp_v0_62 = *arg0;
                        *arg0 = temp_v0_62 + 8;
                        temp_v0_62->unk0 = 0xF1000000;
                        temp_fv0_5 = (f32) sp30 / *var_t3_3;
                        if (!(temp_fs0_3 <= temp_fv0_5)) {
                            var_a0_3 = (s32) temp_fv0_5;
                        } else {
                            var_a0_3 = (s32) (temp_fv0_5 - temp_fs0_3) | 0x80000000;
                        }
                        temp_fv0_6 = (f32) sp34 / D_8017869C;
                        if (!(temp_fs0_3 <= temp_fv0_6)) {
                            var_v0_25 = (s32) temp_fv0_6 & 0xFFFF;
                        } else {
                            var_v0_25 = ((s32) (temp_fv0_6 - temp_fs0_3) | 0x80000000) & 0xFFFF;
                        }
                        temp_v0_62->unk4 = (s32)(((var_a0_3 << 0x10) | var_v0_25));
                    }
                    var_s6_3 += 1;
                    var_s1_3 += (var_s1_3->unk0 * var_s1_3->unk2 * 2) + 8;
                } while (var_s6_3 < (u16) temp_s7->unk8);
            }
block_189:
            var_v0_9 = &D_80188E24;
        }
    }
    if (*var_v0_9 != 0) {
        renderLineStrip(arg0);
    }
}
