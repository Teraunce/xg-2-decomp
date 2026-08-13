#include "ultra64.h"
u16 *gfxGetWritePtr();                               /* extern */
s32 heap_alloc_default(s32, s32);                        /* extern */
void overlayNodeMark(Unk*);                            /* extern */
void mtxIdentInit(Unk*, s32, s32, s32);                   /* extern */
s32 triComputeNormal(Unk*, Unk*, Unk*, Unk*);                /* extern */
s32 func_8013BDF4(s32);                               /* extern */
extern f32 gNodeInitF;
extern s32 gColorSwapMode;
extern s32 gEntityFlagMask;
extern char *gTrackNodePtr;

void renderNodeSetup(Unk *arg0, s32 arg1) {
    s32 saved_reg_s7;
    s32 sp30;
    f32 sp28;
    f32 sp24;
    f32 temp_fa0;
    f32 temp_fs1;
    f32 temp_ft2;
    f32 temp_ft3;
    f32 temp_fv1;
    f32 var_ft0;
    f32 var_ft1;
    f32 var_fv0;
    s32 *temp_v1_20;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a3;
    s32 temp_a3_2;
    s32 temp_s0;
    s32 temp_s5;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_7;
    s32 temp_v1;
    s32 temp_v1_10;
    s32 temp_v1_11;
    s32 temp_v1_12;
    s32 temp_v1_13;
    s32 temp_v1_14;
    s32 temp_v1_15;
    s32 temp_v1_16;
    s32 temp_v1_18;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 temp_v1_8;
    s32 temp_v1_9;
    s32 var_a0_5;
    s32 var_a1;
    s32 var_a1_3;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_condition_bit;
    s32 var_lo;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s1_6;
    s32 var_s1_7;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6_2;
    s32 var_s7;
    s32 var_t0;
    s32 var_v1_3;
    u16 *temp_fp;
    u16 *temp_v0;
    u16 *var_a0_4;
    Unk *var_v1;
    u16 *var_v1_2;
    u16 temp_a0;
    u16 temp_v0_2;
    u16 temp_v0_5;
    u16 var_a1_2;
    u16 var_s6;
    u32 temp_v1_17;
    u8 *var_a0;
    u8 temp_v1_19;
    Unk *temp_v0_6;
    Unk *var_a0_2;
    Unk *var_a0_3;
    Unk *var_s2;

    var_s7 = saved_reg_s7;
    temp_v1 = arg0->unk20;
    if (temp_v1 != 0) {
        arg0->unk20 = (s32) ((temp_v1 & 0xFFFFFF) + arg1);
    }
    temp_v1_2 = arg0->unk28;
    if (temp_v1_2 != 0) {
        arg0->unk28 = (s32) ((temp_v1_2 & 0xFFFFFF) + arg1);
    }
    temp_v1_3 = arg0->unk30;
    if (temp_v1_3 != 0) {
        arg0->unk30 = (s32) ((temp_v1_3 & 0xFFFFFF) + arg1);
    }
    temp_v1_4 = arg0->unk5C;
    if (temp_v1_4 != 0) {
        arg0->unk5C = (s32) ((temp_v1_4 & 0xFFFFFF) + arg1);
    }
    temp_v1_5 = arg0->unk4C;
    if (temp_v1_5 != 0) {
        arg0->unk4C = (s32) ((temp_v1_5 & 0xFFFFFF) + arg1);
    }
    temp_v1_6 = arg0->unk1C;
    if (temp_v1_6 != 0) {
        arg0->unk1C = (s32) ((temp_v1_6 & 0xFFFFFF) + arg1);
    }
    temp_v1_7 = arg0->unk38;
    if (temp_v1_7 != 0) {
        arg0->unk38 = (s32) ((temp_v1_7 & 0xFFFFFF) + arg1);
    }
    temp_v1_8 = arg0->unk40;
    if (temp_v1_8 != 0) {
        arg0->unk40 = (s32) ((temp_v1_8 & 0xFFFFFF) + arg1);
    }
    temp_v1_9 = arg0->unk50;
    if (temp_v1_9 != 0) {
        arg0->unk50 = (s32) ((temp_v1_9 & 0xFFFFFF) + arg1);
    }
    temp_v1_10 = arg0->unk54;
    if (temp_v1_10 != 0) {
        arg0->unk54 = (s32) ((temp_v1_10 & 0xFFFFFF) + arg1);
    }
    temp_v1_11 = arg0->unk160;
    if (temp_v1_11 != 0) {
        arg0->unk160 = (s32) ((temp_v1_11 & 0xFFFFFF) + arg1);
    }
    temp_v1_12 = arg0->unk164;
    if (temp_v1_12 != 0) {
        arg0->unk164 = (s32) ((temp_v1_12 & 0xFFFFFF) + arg1);
    }
    temp_v1_13 = arg0->unk168;
    if (temp_v1_13 != 0) {
        arg0->unk168 = (s32) ((temp_v1_13 & 0xFFFFFF) + arg1);
    }
    temp_v1_14 = arg0->unk16C;
    if (temp_v1_14 != 0) {
        arg0->unk16C = (s32) ((temp_v1_14 & 0xFFFFFF) + arg1);
    }
    temp_v1_15 = arg0->unk170;
    if (temp_v1_15 != 0) {
        arg0->unk170 = (s32) ((temp_v1_15 & 0xFFFFFF) + arg1);
    }
    temp_v1_16 = arg0->unk174;
    if (temp_v1_16 != 0) {
        arg0->unk174 = (s32) ((temp_v1_16 & 0xFFFFFF) + arg1);
    }
    var_s0 = 0;
    var_s6 = 0;
    var_s5 = 0;
    var_s1 = 0;
    if (arg0->unk58 > 0) {
        var_a0 = arg0->unk50 + 2;
        do {
            var_s1 += 1;
            *var_a0 &= 0xEF;
            var_a0 += 0xC;
        } while (var_s1 < arg0->unk58);
    }
    overlayNodeMark(arg0);
    var_s1_2 = 0;
    temp_v0 = gfxGetWritePtr();
    *((0 * 2) + temp_v0) = 0;
    if (arg0->unk58 <= 0) {

    } else {
        var_a0_2 = arg0->unk50 + 6;
        do {
            var_a0_2->unk0 = (u16) (var_a0_2->unk0 + var_s6);
            var_s6 = var_a0_2->unk0;
            temp_v0_2 = *(u16*)((char*)var_a0_2 - 2)+ var_s5;
            *(u16*)((char*)var_a0_2 - 2)= temp_v0_2;
            var_s5 = temp_v0_2 & 0xFFFF;
            if (var_s0 < (s32) var_s6) {
                var_s0 = (s32) var_s6;
                temp_v0[var_s6] = 0;
            }
            var_s1_2 += 1;
            var_a0_2 += 0xC;
        } while (var_s1_2 < arg0->unk58);
        var_s1_3 = 0;
        if (arg0->unk58 > 0) {
            var_a0_3 = arg0->unk50 + 6;
            do {
                if (*(s32*)((char*)var_a0_3 - 4)& (gEntityFlagMask | 0x10)) {
                    temp_v0[var_a0_3->unk0] = 1;
                }
                var_s1_3 += 1;
                var_a0_3 += 0xC;
            } while (var_s1_3 < arg0->unk58);
        }
    }
    var_a1 = 0;
    temp_v0_3 = var_s0 + 1;
    var_s1_4 = 0;
    if (temp_v0_3 > 0) {
        var_v1 = temp_v0;
        do {
            if (var_v1->unk0 != 0) {
                var_a1 += 1;
            }
            var_s1_4 += 1;
            var_v1 += 2;
        } while (var_s1_4 < temp_v0_3);
    }
    arg0->unk4C = heap_alloc_default(var_a1 * 0xC, var_a1);
    var_a1_2 = 0;
    temp_fp = gfxGetWritePtr();
    temp_v0_4 = var_s0 + 1;
    var_s1_5 = 0;
    if (temp_v0_4 > 0) {
        var_v1_2 = temp_fp;
        var_a0_4 = temp_v0;
        do {
            if (*var_a0_4 == 0) {
                *var_v1_2 = 0xFFFF;
            } else {
                *var_v1_2 = var_a1_2;
                var_a1_2 += 1;
            }
            var_v1_2 += 2;
            var_s1_5 += 1;
            var_a0_4 += 2;
        } while (var_s1_5 < temp_v0_4);
    }
    var_s6_2 = 0;
    var_s4 = arg0->unk50;
    sp30 = arg0->unk44;
    temp_s5 = arg0->unk4C;
    var_s1_6 = 0;
    if (arg0->unk58 > 0) {
        var_s2 = var_s4 + 3;
        temp_fs1 = gNodeInitF;
        do {
            if (temp_fp[var_s2->unk3] == 0xFFFF) {
                var_s2->unk3 = 0U;
                var_s2 += 0xC;
                var_s4 += 0xC;
            } else {
                temp_a0 = *(u16 *)(s32)var_s4;
                temp_v1_17 = temp_a0 & 0xFFFF;
                var_a2 = (temp_v1_17 >> 5) & 0x1F;
                var_t0 = (temp_v1_17 >> 0xA) & 0x1F;
                temp_a1 = temp_a0 & 0x1F;
                if (gColorSwapMode != 0) {
                    temp_v1_18 = var_t0 << 5;
                    temp_a0_2 = var_t0;
                    var_t0 = var_a2;
                    *(u16 *)(s32)var_s4 = (u16) (temp_v1_18 | (var_t0 << 0xA) | temp_a1);
                    temp_v1_19 = var_s2->unk0;
                    var_a2 = temp_a0_2;
                    if (temp_v1_19 & 0x80) {
                        var_s2->unk0 = (u8) (temp_v1_19 ^ 0x20);
                    }
                }
                temp_v0_5 = temp_fp[var_s2->unk3];
                temp_s0 = temp_v0_5 & 0xFFFF;
                var_s2->unk3 = temp_v0_5;
                if (temp_s0 == var_s6_2) {
                    temp_a3 = *(s32 *)((char *)(s32)sp30 + var_s2->unk1 * 0x10);
                    temp_a3_2 = temp_a3 | 0x80000000;
                    if (temp_a3 & 0x80000000) {
                        var_a0_5 = temp_a3_2 + (temp_a1 * 6);
                        var_a1_3 = temp_a3_2 + (var_a2 * 6);
                        var_a2_2 = var_t0 * 6;
                    } else {
                        var_a0_5 = temp_a3_2 + (temp_a1 * 0x10);
                        var_a1_3 = temp_a3_2 + (var_a2 * 0x10);
                        var_a2_2 = var_t0 * 0x10;
                    }
                    triComputeNormal(var_a0_5, var_a1_3, temp_a3_2 + var_a2_2, temp_s5 + (temp_s0 * 0xC));
                    var_s6_2 += 1;
                }
                temp_v0_6 = (temp_s0 * 0xC) + temp_s5;
                sp24 = 0.0f;
                sp28 = 0.0f;
                var_ft1 = temp_v0_6->unk0;
                temp_fv1 = sp24;
                sp24 = temp_fs1;
                temp_fa0 = var_ft1;
                sp28 = temp_fv1;
                var_ft0 = temp_v0_6->unk4;
                sp24 = temp_fv1;
                sp28 = temp_fs1;
                var_fv0 = temp_v0_6->unk8;
                temp_ft3 = var_ft0;
                temp_ft2 = var_fv0;
                if (temp_fa0 < temp_fv1) {
                    var_ft1 = -temp_fa0;
                }
                if (temp_ft3 < temp_fv1) {
                    var_ft0 = -temp_ft3;
                }
                if (temp_ft2 < temp_fv1) {
                    var_fv0 = -temp_ft2;
                }
                var_v1_3 = 0;
                if ((var_ft0 < var_ft1) && (var_fv0 < var_ft1)) {
                    var_v1_3 = 2;
                }
                if (var_ft0 < var_fv0) {
                    if (var_ft1 <= var_fv0) {
                        var_v1_3 = 1;
                    }
                }
                if (var_v1_3 != 1) {
                    if (var_v1_3 < 2) {
                        if (var_v1_3 != 0) {
                            var_s4 += 0xC;
                        } else {
                            var_s7 = 1;
                            if (temp_ft3 < 0.0f) {
                                var_s7 = 0;
                            }
                            goto block_97;
                        }
                    } else if (var_v1_3 != 2) {
                        var_s4 += 0xC;
                    } else {
                        var_s7 = 0;
                        var_condition_bit = temp_fa0 < 0.0f;
                        goto block_95;
                    }
                } else {
                    var_condition_bit = temp_ft2 < 0.0f;
                    var_s7 = 0;
block_95:
                    if (var_condition_bit) {
                        var_s7 = 1;
                    }
block_97:
                    var_s4 += 0xC;
                }
                var_s2->unk0 = (u8) ((var_s2->unk0 & 0x1F) | ((var_v1_3 << 6) | (var_s7 << 5)));
                var_s2 += 0xC;
            }
            var_s1_6 += 1;
        } while (var_s1_6 < arg0->unk58);
    }
    if (gColorSwapMode != 0) {
        temp_a1_2 = arg0->unk1C;
        arg0->unk10 = (s32) -(arg0->unk10 + (arg0->unk8 * arg0->unk4));
        if (temp_a1_2 != 0) {
            var_s1_7 = 0;
            if (arg0->unkC > 0) {
                do {
                    temp_a0_3 = arg0->unk8;
                    var_s0_2 = 0;
                    if ((temp_a0_3 / 2) > 0) {
                        var_lo = var_s1_7 * temp_a0_3;
                        do {
                            temp_v1_20 = (s32 *)((char *)(s32)temp_a1_2 + (var_lo + var_s0_2) * 4);
                            temp_a0_5 = *temp_v1_20;
                            *temp_v1_20 = *(s32*)((char*)(((char *)(s32)temp_a1_2 + ((var_lo + arg0->unk8) - var_s0_2) * 4)) - 4);
                            temp_v0_7 = arg0->unk8;
                            *(s32*)((char*)(((char *)(s32)temp_a1_2 + (((var_s1_7 * temp_v0_7) + temp_v0_7) - var_s0_2) * 4)) - 4)= temp_a0_5;
                            temp_a0_4 = arg0->unk8;
                            var_s0_2 += 1;
                            var_lo = var_s1_7 * temp_a0_4;
                        } while (var_s0_2 < (temp_a0_4 / 2));
                    }
                    var_s1_7 += 1;
                } while (var_s1_7 < arg0->unkC);
            }
        }
    }
    mtxIdentInit(arg0 + 0x60, 0, 0, 0);
    mtxIdentInit(arg0 + 0xA0, 0, 0, 0);
    mtxIdentInit(arg0 + 0xE0, 0, 0, 0);
    mtxIdentInit(arg0 + 0x120, 0, 0, 0);
    if (gColorSwapMode != 0) {
        func_8013BDF4(arg0->unk5C);
    }
}

void entityListPrune(void) {
    char *var_a0;
    Unk *var_v1;

    var_v1 = gTrackNodePtr;
    var_a0 = NULL;
    if (var_v1 != NULL) {
loop_2:
        if (((Unk *)((Unk *)var_v1->unk84)->unk8)->unk5C != 0x63) {
            var_a0 = var_v1;
            var_v1 = var_v1->unk0;
            if (var_v1 == NULL) {

            } else {
                goto loop_2;
            }
        } else {
            if (var_a0 != NULL) {
                *var_a0 = var_v1->unk0;
                return;
            }
            gTrackNodePtr = var_v1->unk0;
        }
    }
}
