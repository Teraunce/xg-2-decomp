#include "ultra64.h"
void func_800608C8(s32, s8, s8, u16, u16, u16);          /* extern */
void func_80060960(s32, s16, s16, s32, s32, s32, s32, s32, u32, u32, u32, u32); /* extern */
void renderLineStrip(void **);                           /* extern */
extern f64 D_8004C060;
extern f64 D_8004C068;
extern f64 D_8004C070;
extern f64 D_8004C078;
extern f64 D_8004C080;
extern f64 D_8004C088;
extern f64 D_8004C090;
extern f64 D_8004C098;
extern f64 D_8004C0A0;
extern f64 D_8004C0A8;
extern f64 D_8004C0B0;
extern f64 D_8004C0B8;
extern f64 D_8004C0C0;
extern f64 D_8004C0C8;
extern f64 D_8004C0D0;
extern f64 D_8004C0D8;
extern f32 D_80178694;
extern f32 D_8017869C;
extern char *D_801823F4;
extern u32 D_801823F8;
extern s32 D_801823FC;
extern s32 D_80182400;
extern u16 D_80182402;
extern u32 D_80182404;
extern s32 D_80182408;
extern u16 D_8018240C;
extern char *D_80182410;
extern u16 D_80182414;
extern s32 D_80182418;
extern u16 D_80182458;
extern s32 D_80182E6C;
extern s16 D_80182E7A;
extern s32 D_80182E7C;
extern s32 D_80182E80;
extern s32 D_80182E98;
extern u16 D_80182E9A;

u16 func_8006421C(void **arg0, Unk *arg1, u32 arg2, s16 arg3, s32 arg4, u32 arg5) {
    s16 subroutine_argD = 0;
    s16 subroutine_argF = 0;
    f64 var_ft0;
    f64 var_ft0_2;
    f64 var_ft1;
    f64 var_ft1_2;
    f64 var_fv1;
    f64 var_fv1_10;
    f64 var_fv1_11;
    f64 var_fv1_12;
    f64 var_fv1_2;
    f64 var_fv1_3;
    f64 var_fv1_4;
    f64 var_fv1_5;
    f64 var_fv1_6;
    f64 var_fv1_7;
    f64 var_fv1_8;
    f64 var_fv1_9;
    s32 temp_a0;
    s32 temp_ft2;
    s32 temp_ft2_10;
    s32 temp_ft2_11;
    s32 temp_ft2_12;
    s32 temp_ft2_2;
    s32 temp_ft2_3;
    s32 temp_ft2_4;
    s32 temp_ft2_5;
    s32 temp_ft2_6;
    s32 temp_ft2_7;
    s32 temp_ft2_8;
    s32 temp_ft2_9;
    s32 temp_s4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_4;
    s32 var_a2;
    s32 var_s3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;
    u32 temp_fp;
    u32 temp_lo;
    u32 temp_s0;
    u32 temp_s0_2;
    Unk *temp_a1;
    Unk *temp_a1_2;
    Unk *temp_v0;
    Unk *temp_v0_10;
    Unk *temp_v0_11;
    Unk *temp_v0_12;
    Unk *temp_v0_13;
    Unk *temp_v0_14;
    Unk *temp_v0_2;
    Unk *temp_v0_3;
    Unk *temp_v0_4;
    Unk *temp_v0_7;
    Unk *temp_v0_8;
    Unk *temp_v0_9;
    Unk *temp_v1_2;
    Unk *temp_v1_3;

    temp_s0 = arg5 >> 0x1C;
    temp_fp = (u32) (arg1->unk2 * arg2) >> 0x10;
    temp_lo = 0x04000000U / arg2;
    if (((u32) ((arg3 + 0x140) & 0xFFFF) < 0x3C1U) && ((s16) arg4 >= -0xF0) && ((s16) arg4 < 0x1E1)) {
        if (D_80182E80 != 0) {
            temp_s4 = arg5 | 0xFF000000;
            var_s3 = temp_s4;
            if (D_80182E6C != 0xFF00FF) {
                var_s3 = D_80182E6C | 0xFF000000;
            }
            if (((void*)D_801823F4 != (void*)arg1) || (D_80182404 != temp_s0)) {
                temp_s0_2 = temp_s0 & 0xFF;
                func_800608C8(arg1->unk4, 4, 0, (arg1->unk0 + 0xF) & 0x1F0, (s32) arg1->unk1, temp_s0_2);
                D_801823F4 = arg1;
                D_80182404 = temp_s0_2;
            }
            if (D_80182E7C != 0) {
                func_80060960(arg0, (s16) (arg3 + D_80182E9A), (s16) (D_80182E9A + (arg4 - temp_fp)), (s16) subroutine_argD, (s32) (s16) subroutine_argF, (s32) D_80182E7A, (s32) arg1->unk0, (s32) arg1->unk1, 0x80000000, 0x80000000, 0x80000000, 0x80000000);
                renderLineStrip(arg0);
            }
            func_80060960(arg0, arg3, (s16) (arg4 - temp_fp), (s16) subroutine_argD, (s32) (s16) subroutine_argF, (s32) D_80182E7A, (s32) arg1->unk0, (s32) arg1->unk1, temp_s4, temp_s4, var_s3, var_s3);
            if (D_80182E7C != 0) {
                renderLineStrip(arg0);
            }
        } else {
            if (((void*)D_801823F4 != (void*)arg1) || (D_80182404 != temp_s0)) {
                temp_v0 = *arg0;
                *arg0 = temp_v0 + 8;
                temp_v0->unk0 = 0xFD500000;
                temp_v0->unk4 = (s32) arg1->unk4;
                temp_v0_2 = *arg0;
                *arg0 = temp_v0_2 + 8;
                temp_v0_2->unk0 = 0xF5500000;
                temp_v0_2->unk4 = 0x07080200;
                temp_v0_3 = *arg0;
                *arg0 = temp_v0_3 + 8;
                temp_v0_3->unk0 = 0xE6000000;
                temp_v0_3->unk4 = 0;
                temp_v0_4 = *arg0;
                *arg0 = temp_v0_4 + 8;
                temp_v0_4->unk0 = 0xF3000000;
                temp_v0_5 = (arg1->unk0 + 0xF) & 0xFFF0;
                var_a0 = temp_v0_5;
                if (temp_v0_5 < 0) {
                    var_a0 = temp_v0_5 + 0xF;
                }
                temp_v1 = var_a0 >> 4;
                var_a1 = 0x800;
                if (temp_v1 > 0) {
                    var_a1 = temp_v1 + 0x7FF;
                }
                temp_a0 = (arg1->unk0 + 0xF) & 0xFFF0;
                var_v1 = ((u32) (temp_a0 * arg1->unk1) >> 2) - 1;
                if (var_v1 >= 0x800) {
                    var_v1 = 0x7FF;
                }
                var_a2 = temp_a0;
                if (temp_a0 < 0) {
                    var_a2 = temp_a0 + 0xF;
                }
                temp_v0_6 = var_a2 >> 4;
                if (temp_v0_6 <= 0) {
                    var_v0 = var_a1 & 0xFFF;
                } else {
                    var_v0 = (var_a1 / temp_v0_6) & 0xFFF;
                }
                temp_v0_4->unk4 = (s32) (((var_v1 & 0xFFF) << 0xC) | 0x07000000 | var_v0);
                temp_v0_7 = *arg0;
                *arg0 = temp_v0_7 + 8;
                temp_v0_7->unk0 = 0xE7000000;
                temp_v0_7->unk4 = 0;
                temp_v0_8 = *arg0;
                *arg0 = temp_v0_8 + 8;
                temp_v0_8->unk4 = (s32) ((temp_s0 << 0x14) | 0x80200);
                temp_v0_8->unk0 = (s32) ((((u32) (arg1->unk0 + 0xF) >> 4) << 9) | 0xF5400000);
                temp_v0_9 = *arg0;
                *arg0 = temp_v0_9 + 8;
                temp_v0_9->unk0 = 0xF2000000;
                D_801823F4 = arg1;
                D_80182404 = temp_s0;
                temp_v0_9->unk4 = (s32) (((((((arg1->unk0 + 0xF) & 0xFFF0) - 1) * 4) & 0xFFF) << 0xC) | (((arg1->unk1 - 1) * 4) & 0xFFF));
            }
            if (D_80182E7C != 0) {
                temp_v0_10 = *arg0;
                *arg0 = temp_v0_10 + 8;
                temp_v0_10->unk0 = 0xFA000000;
                temp_v0_10->unk4 = 0x80;
                temp_a1 = *arg0;
                *arg0 = temp_a1 + 8;
                temp_ft2 = (s32) ((f32) (((arg3 + (s16) subroutine_argD) - 1) * 4) * D_80178694);
                if ((s16) temp_ft2 > 0) {
                    var_a0_2 = (((s16) temp_ft2 & 0xFFF) << 0xC) | 0xE4000000;
                } else {
                    var_a0_2 = 0xE4000000;
                }
                temp_ft2_2 = (s32) ((f32) (((((s16) arg4 - (s16) temp_fp) + (s16) subroutine_argF) - 1) * 4) * D_8017869C);
                if ((s16) temp_ft2_2 > 0) {
                    var_a0_2 |= (s16) temp_ft2_2 & 0xFFF;
                }
                temp_ft2_3 = (s32) ((f32) ((arg3 + D_80182E98) * 4) * D_80178694);
                temp_a1->unk0 = var_a0_2;
                if ((s16) temp_ft2_3 > 0) {
                    var_a1_2 = ((s16) temp_ft2_3 & 0xFFF) << 0xC;
                } else {
                    var_a1_2 = 0;
                }
                temp_ft2_4 = (s32) ((f32) ((((s16) arg4 - (s16) temp_fp) + D_80182E98) * 4) * D_8017869C);
                var_v1_2 = var_a1_2;
                if ((s16) temp_ft2_4 > 0) {
                    var_v1_2 |= (s16) temp_ft2_4 & 0xFFF;
                }
                temp_a1->unk4 = var_v1_2;
                temp_v0_11 = *arg0;
                *arg0 = temp_v0_11 + 8;
                temp_v0_11->unk0 = 0xE1000000;
                temp_ft2_5 = (s32) ((f32) ((arg3 + D_80182E98) * 4) * D_80178694);
                if ((s16) temp_ft2_5 < 0) {
                    var_fv1 = (f64) temp_lo;
                    if ((s32) temp_lo < 0) {
                        var_fv1 += D_8004C060;
                    }
                    if ((s32) ((f32) var_fv1 / D_80178694) & 0x8000) {
                        var_fv1_2 = (f64) temp_lo;
                        if ((s32) temp_lo < 0) {
                            var_fv1_2 += D_8004C068;
                        }
                        var_v1_3 = (s32) ((s16) temp_ft2_5 * (s16) (s32) ((f32) var_fv1_2 / D_80178694)) >> 7;
                        if (var_v1_3 < 0) {
                            var_v1_3 = 0;
                        }
                    } else {
                        var_fv1_3 = (f64) temp_lo;
                        if ((s32) temp_lo < 0) {
                            var_fv1_3 += D_8004C070;
                        }
                        var_v1_3 = (s32) ((s16) temp_ft2_5 * (s16) (s32) ((f32) var_fv1_3 / D_80178694)) >> 7;
                        if (var_v1_3 > 0) {
                            var_v1_3 = 0;
                        }
                    }
                    var_a1_3 = (8 - var_v1_3) << 0x10;
                } else {
                    var_a1_3 = 0x80000;
                }
                temp_ft2_6 = (s32) ((f32) ((((s16) arg4 - (s16) temp_fp) + D_80182E98) * 4) * D_8017869C);
                var_v0_2 = var_a1_3;
                if (temp_ft2_6 < 0) {
                    var_fv1_4 = (f64) temp_lo;
                    if ((s32) temp_lo < 0) {
                        var_fv1_4 += D_8004C078;
                    }
                    if ((s32) ((f32) var_fv1_4 / D_8017869C) & 0x8000) {
                        var_fv1_5 = (f64) temp_lo;
                        if ((s32) temp_lo < 0) {
                            var_fv1_5 += D_8004C080;
                        }
                        var_v0_3 = (s32) ((s16) temp_ft2_6 * (s16) (s32) ((f32) var_fv1_5 / D_8017869C)) >> 7;
                        if (var_v0_3 < 0) {
                            var_v0_3 = 0;
                        }
                    } else {
                        var_fv1_6 = (f64) temp_lo;
                        if ((s32) temp_lo < 0) {
                            var_fv1_6 += D_8004C088;
                        }
                        var_v0_3 = (s32) ((s16) temp_ft2_6 * (s16) (s32) ((f32) var_fv1_6 / D_8017869C)) >> 7;
                        if (var_v0_3 > 0) {
                            var_v0_3 = 0;
                        }
                    }
                    var_v0_2 = var_a1_3 | (-var_v0_3 & 0xFFFF);
                }
                temp_v0_11->unk4 = var_v0_2;
                temp_v1_2 = *arg0;
                var_ft0 = (f64) temp_lo;
                *arg0 = temp_v1_2 + 8;
                temp_v1_2->unk0 = 0xF1000000;
                if ((s32) temp_lo < 0) {
                    var_ft0 += D_8004C090;
                }
                var_ft1 = (f64) temp_lo;
                if ((s32) temp_lo < 0) {
                    var_ft1 += D_8004C098;
                }
                temp_v1_2->unk4 = (s32) (((s32) ((f32) var_ft0 / D_80178694) << 0x10) | ((s32) ((f32) var_ft1 / D_8017869C) & 0xFFFF));
                temp_v0_12 = *arg0;
                *arg0 = temp_v0_12 + 8;
                temp_v0_12->unk0 = 0xFA000000;
                temp_v0_12->unk4 = (s32) ((arg5 << 0x18) | (((arg5 >> 8) & 0xFF) << 0x10) | ((arg5 >> 8) & 0xFF00) | 0xFF);
            } else if (D_801823F8 != arg5) {
                temp_v0_13 = *arg0;
                *arg0 = temp_v0_13 + 8;
                temp_v0_13->unk0 = 0xFA000000;
                temp_v0_13->unk4 = (s32) ((arg5 << 0x18) | (((arg5 >> 8) & 0xFF) << 0x10) | ((arg5 >> 8) & 0xFF00) | 0xFF);
                D_801823F8 = arg5;
            }
            temp_a1_2 = *arg0;
            *arg0 = temp_a1_2 + 8;
            temp_ft2_7 = (s32) ((f32) (((arg3 + (s16) subroutine_argD) - 1) * 4) * D_80178694);
            if ((s16) temp_ft2_7 > 0) {
                var_a0_3 = (((s16) temp_ft2_7 & 0xFFF) << 0xC) | 0xE4000000;
            } else {
                var_a0_3 = 0xE4000000;
            }
            temp_ft2_8 = (s32) ((f32) (((((s16) arg4 - (s16) temp_fp) + (s16) subroutine_argF) - 1) * 4) * D_8017869C);
            if ((s16) temp_ft2_8 > 0) {
                var_a0_3 |= (s16) temp_ft2_8 & 0xFFF;
            }
            temp_a1_2->unk0 = var_a0_3;
            temp_ft2_9 = (s32) ((f32) ((s32) (arg3 << 0x10) >> 0xE) * D_80178694);
            if ((s16) temp_ft2_9 > 0) {
                var_a0_4 = ((s16) temp_ft2_9 & 0xFFF) << 0xC;
            } else {
                var_a0_4 = 0;
            }
            temp_ft2_10 = (s32) ((f32) (((s16) arg4 - (s16) temp_fp) * 4) * D_8017869C);
            var_v1_4 = var_a0_4;
            if ((s16) temp_ft2_10 > 0) {
                var_v1_4 |= (s16) temp_ft2_10 & 0xFFF;
            }
            temp_a1_2->unk4 = var_v1_4;
            temp_v0_14 = *arg0;
            *arg0 = temp_v0_14 + 8;
            temp_v0_14->unk0 = 0xE1000000;
            temp_ft2_11 = (s32) ((f32) ((s32) (arg3 << 0x10) >> 0xE) * D_80178694);
            if ((s16) temp_ft2_11 < 0) {
                var_fv1_7 = (f64) temp_lo;
                if ((s32) temp_lo < 0) {
                    var_fv1_7 += D_8004C0A0;
                }
                if ((s32) ((f32) var_fv1_7 / D_80178694) & 0x8000) {
                    var_fv1_8 = (f64) temp_lo;
                    if ((s32) temp_lo < 0) {
                        var_fv1_8 += D_8004C0A8;
                    }
                    var_v1_5 = (s32) ((s16) temp_ft2_11 * (s16) (s32) ((f32) var_fv1_8 / D_80178694)) >> 7;
                    if (var_v1_5 < 0) {
                        var_v1_5 = 0;
                    }
                } else {
                    var_fv1_9 = (f64) temp_lo;
                    if ((s32) temp_lo < 0) {
                        var_fv1_9 += D_8004C0B0;
                    }
                    var_v1_5 = (s32) ((s16) temp_ft2_11 * (s16) (s32) ((f32) var_fv1_9 / D_80178694)) >> 7;
                    if (var_v1_5 > 0) {
                        var_v1_5 = 0;
                    }
                }
                var_a1_4 = (8 - var_v1_5) << 0x10;
            } else {
                var_a1_4 = 0x80000;
            }
            temp_ft2_12 = (s32) ((f32) (((s16) arg4 - (s16) temp_fp) * 4) * D_8017869C);
            var_v0_4 = var_a1_4;
            if (temp_ft2_12 < 0) {
                var_fv1_10 = (f64) temp_lo;
                if ((s32) temp_lo < 0) {
                    var_fv1_10 += D_8004C0B8;
                }
                if ((s32) ((f32) var_fv1_10 / D_8017869C) & 0x8000) {
                    var_fv1_11 = (f64) temp_lo;
                    if ((s32) temp_lo < 0) {
                        var_fv1_11 += D_8004C0C0;
                    }
                    var_v0_5 = (s32) ((s16) temp_ft2_12 * (s16) (s32) ((f32) var_fv1_11 / D_8017869C)) >> 7;
                    if (var_v0_5 < 0) {
                        var_v0_5 = 0;
                    }
                } else {
                    var_fv1_12 = (f64) temp_lo;
                    if ((s32) temp_lo < 0) {
                        var_fv1_12 += D_8004C0C8;
                    }
                    var_v0_5 = (s32) ((s16) temp_ft2_12 * (s16) (s32) ((f32) var_fv1_12 / D_8017869C)) >> 7;
                    if (var_v0_5 > 0) {
                        var_v0_5 = 0;
                    }
                }
                var_v0_4 = var_a1_4 | (-var_v0_5 & 0xFFFF);
            }
            temp_v0_14->unk4 = var_v0_4;
            temp_v1_3 = *arg0;
            var_ft0_2 = (f64) temp_lo;
            *arg0 = temp_v1_3 + 8;
            temp_v1_3->unk0 = 0xF1000000;
            if ((s32) temp_lo < 0) {
                var_ft0_2 += D_8004C0D0;
            }
            var_ft1_2 = (f64) temp_lo;
            if ((s32) temp_lo < 0) {
                var_ft1_2 += D_8004C0D8;
            }
            temp_v1_3->unk4 = (s32) (((s32) ((f32) var_ft0_2 / D_80178694) << 0x10) | ((s32) ((f32) var_ft1_2 / D_8017869C) & 0xFFFF));
        }
    }
    return subroutine_argD;
}

s32 func_80065008(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4) {
    s32 *var_v1;
    u16 temp_a3;
    u32 var_t1;
    u32 var_t1_2;
    Unk *temp_a1;
    Unk *temp_a2;
    Unk *temp_v0;
    Unk *var_v1_2;

    if (((u32) ((arg2 + 0x140) & 0xFFFF) >= 0x3C1U) || (arg3 < -0xF0) || (arg3 >= 0x1E1)) {
        return 1;
    }
    if ((u16) D_8018240C >= 0x400U) {
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return 0;
    }
    if ((D_80182400 < 0) || (arg4 != D_801823FC)) {
        var_t1 = 0;
        if (D_80182458 != 0) {
            var_v1 = &D_80182418;
loop_10:
            if (*var_v1 != arg4) {
                var_t1 += 1;
                var_v1 += 4;
                if (var_t1 >= (u16) D_80182458) {

                } else {
                    goto loop_10;
                }
            }
            if (var_t1 >= (u16) D_80182458) {
                goto block_14;
            }
            goto block_16;
        }
block_14:
        if (var_t1 < 0x10U) {
            (&D_80182418)[var_t1] = arg4;
            D_80182458 += 1;
block_16:
            D_80182400 = (s32) var_t1;
            D_801823FC = arg4;
            goto block_17;
        }
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return 0;
    }
block_17:
    var_t1_2 = 0;
    if (D_80182414 != 0) {
        var_v1_2 = D_80182410;
loop_19:
        if ((var_v1_2->unk8 != arg0) || (var_v1_2->unk4 != arg1)) {
            var_t1_2 += 1;
            var_v1_2 += 0xC;
            if (var_t1_2 >= (u16) D_80182414) {

            } else {
                goto loop_19;
            }
        }
        if (var_t1_2 >= (u16) D_80182414) {
            goto block_24;
        }
        /* Duplicate return node #26. Try simplifying control flow for better match */
        temp_a3 = D_8018240C;
        temp_a2 = (var_t1_2 * 0xC) + D_80182410;
        temp_a1 = (temp_a3 * 6) + D_80182408;
        D_8018240C = temp_a3 + 1;
        temp_a1->unk2 = arg2;
        temp_a1->unk4 = arg3;
        temp_a1->unk0 = (u16) ((temp_a1->unk0 & 0xF) | (temp_a2->unk2 * 0x10));
        temp_a1->unk0 = (u16) ((temp_a1->unk0 & 0xFFF0) | (D_80182402 & 0xF));
        temp_a2->unk0 = (s32) temp_a3;
        return 1;
    }
block_24:
    if (var_t1_2 < 0x40U) {
        temp_v0 = (var_t1_2 * 0xC) + D_80182410;
        temp_v0->unk0 = 0;
        temp_v0->unk4 = arg1;
        temp_v0->unk8 = arg0;
        D_80182414 += 1;
        temp_a3 = D_8018240C;
        temp_a2 = (var_t1_2 * 0xC) + D_80182410;
        temp_a1 = (temp_a3 * 6) + D_80182408;
        D_8018240C = temp_a3 + 1;
        temp_a1->unk2 = arg2;
        temp_a1->unk4 = arg3;
        temp_a1->unk0 = (u16) ((temp_a1->unk0 & 0xF) | (temp_a2->unk2 * 0x10));
        temp_a1->unk0 = (u16) ((temp_a1->unk0 & 0xFFF0) | (D_80182402 & 0xF));
        temp_a2->unk0 = (s32) temp_a3;
        return 1;
    }
    return 0;
}
