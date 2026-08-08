#include "ultra64.h"
void gfxAddLineTex(s32, s8, s8, u16, u16, u16);          /* extern */
void gfxAddLineVtx(s32, s16, s16, s32, s32, s32, s32, s32, u32, u32, u32, u32); /* extern */
void renderLineStrip(void **);                           /* extern */
extern f64 gTexLineParam60;
extern f64 gTexLineParam68;
extern f64 gTexLineParam70;
extern f64 gTexLineParam78;
extern f64 gTexLineParam80;
extern f64 gTexLineParam88;
extern f64 gTexLineParam90;
extern f64 gTexLineParam98;
extern f64 gTexLineParamA0;
extern f64 gTexLineParamA8;
extern f64 gTexLineParamB0;
extern f64 gTexLineParamB8;
extern f64 gTexLineParamC0;
extern f64 gTexLineParamC8;
extern f64 gTexLineParamD0;
extern f64 gTexLineParamD8;
extern f32 gTexScaleX;
extern f32 gTexScaleY;
extern char *gFontCacheKey;
extern u32 gTexColorKey;
extern s32 gTexAddrKey;
extern s32 gTexCacheSlot;
extern u16 gGlyphColorIdx;
extern u32 gGlyphCacheIdx;
extern s32 gTextVertBuf;
extern u16 gTextTexU;
extern char *gTextGlyphCoords;
extern u16 gTextGlyphIdx;
extern s32 gTextColorBuf;
extern u16 gTextTexV;
extern s32 gTrackColorKey;
extern s16 gLineVtxBright2;
extern s32 gTextWrap;
extern s32 gTextFontId;
extern s32 gTextIndent;
extern u16 gLineVtxOffset;

u16 renderCurveStrip(void **arg0, Unk *arg1, u32 arg2, s16 arg3, s32 arg4, u32 arg5) {
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
        if (gTextFontId != 0) {
            temp_s4 = arg5 | 0xFF000000;
            var_s3 = temp_s4;
            if (gTrackColorKey != 0xFF00FF) {
                var_s3 = gTrackColorKey | 0xFF000000;
            }
            if (((void*)gFontCacheKey != (void*)arg1) || (gGlyphCacheIdx != temp_s0)) {
                temp_s0_2 = temp_s0 & 0xFF;
                gfxAddLineTex(arg1->unk4, 4, 0, (arg1->unk0 + 0xF) & 0x1F0, (s32) arg1->unk1, temp_s0_2);
                gFontCacheKey = arg1;
                gGlyphCacheIdx = temp_s0_2;
            }
            if (gTextWrap != 0) {
                gfxAddLineVtx(arg0, (s16) (arg3 + gLineVtxOffset), (s16) (gLineVtxOffset + (arg4 - temp_fp)), (s16) subroutine_argD, (s32) (s16) subroutine_argF, (s32) gLineVtxBright2, (s32) arg1->unk0, (s32) arg1->unk1, 0x80000000, 0x80000000, 0x80000000, 0x80000000);
                renderLineStrip(arg0);
            }
            gfxAddLineVtx(arg0, arg3, (s16) (arg4 - temp_fp), (s16) subroutine_argD, (s32) (s16) subroutine_argF, (s32) gLineVtxBright2, (s32) arg1->unk0, (s32) arg1->unk1, temp_s4, temp_s4, var_s3, var_s3);
            if (gTextWrap != 0) {
                renderLineStrip(arg0);
            }
        } else {
            if (((void*)gFontCacheKey != (void*)arg1) || (gGlyphCacheIdx != temp_s0)) {
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
                gFontCacheKey = arg1;
                gGlyphCacheIdx = temp_s0;
                temp_v0_9->unk4 = (s32) (((((((arg1->unk0 + 0xF) & 0xFFF0) - 1) * 4) & 0xFFF) << 0xC) | (((arg1->unk1 - 1) * 4) & 0xFFF));
            }
            if (gTextWrap != 0) {
                temp_v0_10 = *arg0;
                *arg0 = temp_v0_10 + 8;
                temp_v0_10->unk0 = 0xFA000000;
                temp_v0_10->unk4 = 0x80;
                temp_a1 = *arg0;
                *arg0 = temp_a1 + 8;
                temp_ft2 = (s32) ((f32) (((arg3 + (s16) subroutine_argD) - 1) * 4) * gTexScaleX);
                if ((s16) temp_ft2 > 0) {
                    var_a0_2 = (((s16) temp_ft2 & 0xFFF) << 0xC) | 0xE4000000;
                } else {
                    var_a0_2 = 0xE4000000;
                }
                temp_ft2_2 = (s32) ((f32) (((((s16) arg4 - (s16) temp_fp) + (s16) subroutine_argF) - 1) * 4) * gTexScaleY);
                if ((s16) temp_ft2_2 > 0) {
                    var_a0_2 |= (s16) temp_ft2_2 & 0xFFF;
                }
                temp_ft2_3 = (s32) ((f32) ((arg3 + gTextIndent) * 4) * gTexScaleX);
                temp_a1->unk0 = var_a0_2;
                if ((s16) temp_ft2_3 > 0) {
                    var_a1_2 = ((s16) temp_ft2_3 & 0xFFF) << 0xC;
                } else {
                    var_a1_2 = 0;
                }
                temp_ft2_4 = (s32) ((f32) ((((s16) arg4 - (s16) temp_fp) + gTextIndent) * 4) * gTexScaleY);
                var_v1_2 = var_a1_2;
                if ((s16) temp_ft2_4 > 0) {
                    var_v1_2 |= (s16) temp_ft2_4 & 0xFFF;
                }
                temp_a1->unk4 = var_v1_2;
                temp_v0_11 = *arg0;
                *arg0 = temp_v0_11 + 8;
                temp_v0_11->unk0 = 0xE1000000;
                temp_ft2_5 = (s32) ((f32) ((arg3 + gTextIndent) * 4) * gTexScaleX);
                if ((s16) temp_ft2_5 < 0) {
                    var_fv1 = (f64) temp_lo;
                    if ((s32) temp_lo < 0) {
                        var_fv1 += gTexLineParam60;
                    }
                    if ((s32) ((f32) var_fv1 / gTexScaleX) & 0x8000) {
                        var_fv1_2 = (f64) temp_lo;
                        if ((s32) temp_lo < 0) {
                            var_fv1_2 += gTexLineParam68;
                        }
                        var_v1_3 = (s32) ((s16) temp_ft2_5 * (s16) (s32) ((f32) var_fv1_2 / gTexScaleX)) >> 7;
                        if (var_v1_3 < 0) {
                            var_v1_3 = 0;
                        }
                    } else {
                        var_fv1_3 = (f64) temp_lo;
                        if ((s32) temp_lo < 0) {
                            var_fv1_3 += gTexLineParam70;
                        }
                        var_v1_3 = (s32) ((s16) temp_ft2_5 * (s16) (s32) ((f32) var_fv1_3 / gTexScaleX)) >> 7;
                        if (var_v1_3 > 0) {
                            var_v1_3 = 0;
                        }
                    }
                    var_a1_3 = (8 - var_v1_3) << 0x10;
                } else {
                    var_a1_3 = 0x80000;
                }
                temp_ft2_6 = (s32) ((f32) ((((s16) arg4 - (s16) temp_fp) + gTextIndent) * 4) * gTexScaleY);
                var_v0_2 = var_a1_3;
                if (temp_ft2_6 < 0) {
                    var_fv1_4 = (f64) temp_lo;
                    if ((s32) temp_lo < 0) {
                        var_fv1_4 += gTexLineParam78;
                    }
                    if ((s32) ((f32) var_fv1_4 / gTexScaleY) & 0x8000) {
                        var_fv1_5 = (f64) temp_lo;
                        if ((s32) temp_lo < 0) {
                            var_fv1_5 += gTexLineParam80;
                        }
                        var_v0_3 = (s32) ((s16) temp_ft2_6 * (s16) (s32) ((f32) var_fv1_5 / gTexScaleY)) >> 7;
                        if (var_v0_3 < 0) {
                            var_v0_3 = 0;
                        }
                    } else {
                        var_fv1_6 = (f64) temp_lo;
                        if ((s32) temp_lo < 0) {
                            var_fv1_6 += gTexLineParam88;
                        }
                        var_v0_3 = (s32) ((s16) temp_ft2_6 * (s16) (s32) ((f32) var_fv1_6 / gTexScaleY)) >> 7;
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
                    var_ft0 += gTexLineParam90;
                }
                var_ft1 = (f64) temp_lo;
                if ((s32) temp_lo < 0) {
                    var_ft1 += gTexLineParam98;
                }
                temp_v1_2->unk4 = (s32) (((s32) ((f32) var_ft0 / gTexScaleX) << 0x10) | ((s32) ((f32) var_ft1 / gTexScaleY) & 0xFFFF));
                temp_v0_12 = *arg0;
                *arg0 = temp_v0_12 + 8;
                temp_v0_12->unk0 = 0xFA000000;
                temp_v0_12->unk4 = (s32) ((arg5 << 0x18) | (((arg5 >> 8) & 0xFF) << 0x10) | ((arg5 >> 8) & 0xFF00) | 0xFF);
            } else if (gTexColorKey != arg5) {
                temp_v0_13 = *arg0;
                *arg0 = temp_v0_13 + 8;
                temp_v0_13->unk0 = 0xFA000000;
                temp_v0_13->unk4 = (s32) ((arg5 << 0x18) | (((arg5 >> 8) & 0xFF) << 0x10) | ((arg5 >> 8) & 0xFF00) | 0xFF);
                gTexColorKey = arg5;
            }
            temp_a1_2 = *arg0;
            *arg0 = temp_a1_2 + 8;
            temp_ft2_7 = (s32) ((f32) (((arg3 + (s16) subroutine_argD) - 1) * 4) * gTexScaleX);
            if ((s16) temp_ft2_7 > 0) {
                var_a0_3 = (((s16) temp_ft2_7 & 0xFFF) << 0xC) | 0xE4000000;
            } else {
                var_a0_3 = 0xE4000000;
            }
            temp_ft2_8 = (s32) ((f32) (((((s16) arg4 - (s16) temp_fp) + (s16) subroutine_argF) - 1) * 4) * gTexScaleY);
            if ((s16) temp_ft2_8 > 0) {
                var_a0_3 |= (s16) temp_ft2_8 & 0xFFF;
            }
            temp_a1_2->unk0 = var_a0_3;
            temp_ft2_9 = (s32) ((f32) ((s32) (arg3 << 0x10) >> 0xE) * gTexScaleX);
            if ((s16) temp_ft2_9 > 0) {
                var_a0_4 = ((s16) temp_ft2_9 & 0xFFF) << 0xC;
            } else {
                var_a0_4 = 0;
            }
            temp_ft2_10 = (s32) ((f32) (((s16) arg4 - (s16) temp_fp) * 4) * gTexScaleY);
            var_v1_4 = var_a0_4;
            if ((s16) temp_ft2_10 > 0) {
                var_v1_4 |= (s16) temp_ft2_10 & 0xFFF;
            }
            temp_a1_2->unk4 = var_v1_4;
            temp_v0_14 = *arg0;
            *arg0 = temp_v0_14 + 8;
            temp_v0_14->unk0 = 0xE1000000;
            temp_ft2_11 = (s32) ((f32) ((s32) (arg3 << 0x10) >> 0xE) * gTexScaleX);
            if ((s16) temp_ft2_11 < 0) {
                var_fv1_7 = (f64) temp_lo;
                if ((s32) temp_lo < 0) {
                    var_fv1_7 += gTexLineParamA0;
                }
                if ((s32) ((f32) var_fv1_7 / gTexScaleX) & 0x8000) {
                    var_fv1_8 = (f64) temp_lo;
                    if ((s32) temp_lo < 0) {
                        var_fv1_8 += gTexLineParamA8;
                    }
                    var_v1_5 = (s32) ((s16) temp_ft2_11 * (s16) (s32) ((f32) var_fv1_8 / gTexScaleX)) >> 7;
                    if (var_v1_5 < 0) {
                        var_v1_5 = 0;
                    }
                } else {
                    var_fv1_9 = (f64) temp_lo;
                    if ((s32) temp_lo < 0) {
                        var_fv1_9 += gTexLineParamB0;
                    }
                    var_v1_5 = (s32) ((s16) temp_ft2_11 * (s16) (s32) ((f32) var_fv1_9 / gTexScaleX)) >> 7;
                    if (var_v1_5 > 0) {
                        var_v1_5 = 0;
                    }
                }
                var_a1_4 = (8 - var_v1_5) << 0x10;
            } else {
                var_a1_4 = 0x80000;
            }
            temp_ft2_12 = (s32) ((f32) (((s16) arg4 - (s16) temp_fp) * 4) * gTexScaleY);
            var_v0_4 = var_a1_4;
            if (temp_ft2_12 < 0) {
                var_fv1_10 = (f64) temp_lo;
                if ((s32) temp_lo < 0) {
                    var_fv1_10 += gTexLineParamB8;
                }
                if ((s32) ((f32) var_fv1_10 / gTexScaleY) & 0x8000) {
                    var_fv1_11 = (f64) temp_lo;
                    if ((s32) temp_lo < 0) {
                        var_fv1_11 += gTexLineParamC0;
                    }
                    var_v0_5 = (s32) ((s16) temp_ft2_12 * (s16) (s32) ((f32) var_fv1_11 / gTexScaleY)) >> 7;
                    if (var_v0_5 < 0) {
                        var_v0_5 = 0;
                    }
                } else {
                    var_fv1_12 = (f64) temp_lo;
                    if ((s32) temp_lo < 0) {
                        var_fv1_12 += gTexLineParamC8;
                    }
                    var_v0_5 = (s32) ((s16) temp_ft2_12 * (s16) (s32) ((f32) var_fv1_12 / gTexScaleY)) >> 7;
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
                var_ft0_2 += gTexLineParamD0;
            }
            var_ft1_2 = (f64) temp_lo;
            if ((s32) temp_lo < 0) {
                var_ft1_2 += gTexLineParamD8;
            }
            temp_v1_3->unk4 = (s32) (((s32) ((f32) var_ft0_2 / gTexScaleX) << 0x10) | ((s32) ((f32) var_ft1_2 / gTexScaleY) & 0xFFFF));
        }
    }
    return subroutine_argD;
}

s32 gfxAddPoint(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4) {
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
    if ((u16) gTextTexU >= 0x400U) {
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return 0;
    }
    if ((gTexCacheSlot < 0) || (arg4 != gTexAddrKey)) {
        var_t1 = 0;
        if (gTextTexV != 0) {
            var_v1 = &gTextColorBuf;
loop_10:
            if (*var_v1 != arg4) {
                var_t1 += 1;
                var_v1 += 4;
                if (var_t1 >= (u16) gTextTexV) {

                } else {
                    goto loop_10;
                }
            }
            if (var_t1 >= (u16) gTextTexV) {
                goto block_14;
            }
            goto block_16;
        }
block_14:
        if (var_t1 < 0x10U) {
            (&gTextColorBuf)[var_t1] = arg4;
            gTextTexV += 1;
block_16:
            gTexCacheSlot = (s32) var_t1;
            gTexAddrKey = arg4;
            goto block_17;
        }
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return 0;
    }
block_17:
    var_t1_2 = 0;
    if (gTextGlyphIdx != 0) {
        var_v1_2 = gTextGlyphCoords;
loop_19:
        if ((var_v1_2->unk8 != arg0) || (var_v1_2->unk4 != arg1)) {
            var_t1_2 += 1;
            var_v1_2 += 0xC;
            if (var_t1_2 >= (u16) gTextGlyphIdx) {

            } else {
                goto loop_19;
            }
        }
        if (var_t1_2 >= (u16) gTextGlyphIdx) {
            goto block_24;
        }
        /* Duplicate return node #26. Try simplifying control flow for better match */
        temp_a3 = gTextTexU;
        temp_a2 = (var_t1_2 * 0xC) + gTextGlyphCoords;
        temp_a1 = (temp_a3 * 6) + gTextVertBuf;
        gTextTexU = temp_a3 + 1;
        temp_a1->unk2 = arg2;
        temp_a1->unk4 = arg3;
        temp_a1->unk0 = (u16) ((temp_a1->unk0 & 0xF) | (temp_a2->unk2 * 0x10));
        temp_a1->unk0 = (u16) ((temp_a1->unk0 & 0xFFF0) | (gGlyphColorIdx & 0xF));
        temp_a2->unk0 = (s32) temp_a3;
        return 1;
    }
block_24:
    if (var_t1_2 < 0x40U) {
        temp_v0 = (var_t1_2 * 0xC) + gTextGlyphCoords;
        temp_v0->unk0 = 0;
        temp_v0->unk4 = arg1;
        temp_v0->unk8 = arg0;
        gTextGlyphIdx += 1;
        temp_a3 = gTextTexU;
        temp_a2 = (var_t1_2 * 0xC) + gTextGlyphCoords;
        temp_a1 = (temp_a3 * 6) + gTextVertBuf;
        gTextTexU = temp_a3 + 1;
        temp_a1->unk2 = arg2;
        temp_a1->unk4 = arg3;
        temp_a1->unk0 = (u16) ((temp_a1->unk0 & 0xF) | (temp_a2->unk2 * 0x10));
        temp_a1->unk0 = (u16) ((temp_a1->unk0 & 0xFFF0) | (gGlyphColorIdx & 0xF));
        temp_a2->unk0 = (s32) temp_a3;
        return 1;
    }
    return 0;
}
