#include "ultra64.h"
extern s32 D_80092B68;
extern s32 D_80092B6C;
extern u32 D_80092B70;
extern char *D_80173CC0;
extern s32 *D_801821E8;

void func_8006114C(void **arg0) {
    s32 *var_v1_8;
    s32 temp_v0_10;
    s32 temp_v0_12;
    s32 var_a0;
    s32 var_a2;
    s32 var_a2_3;
    s32 var_t0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;
    s32 var_v1_6;
    s32 var_v1_7;
    u16 temp_a0_4;
    u16 temp_a1_2;
    u16 temp_a1_4;
    u16 temp_a1_6;
    u16 var_a2_2;
    u16 var_v0_4;
    u32 temp_a0_3;
    u32 temp_a0_8;
    u32 var_t3;
    u32 var_t3_2;
    u8 temp_v1_2;
    Unk *temp_a0;
    Unk *temp_a0_2;
    Unk *temp_a0_5;
    Unk *temp_a0_6;
    Unk *temp_a0_7;
    Unk *temp_a0_9;
    Unk *temp_a1;
    Unk *temp_a1_3;
    Unk *temp_a1_5;
    Unk *temp_a1_7;
    Unk *temp_a1_8;
    Unk *temp_v0;
    Unk *temp_v0_11;
    Unk *temp_v0_13;
    Unk *temp_v0_14;
    Unk *temp_v0_15;
    Unk *temp_v0_16;
    Unk *temp_v0_17;
    Unk *temp_v0_18;
    Unk *temp_v0_19;
    Unk *temp_v0_20;
    Unk *temp_v0_21;
    Unk *temp_v0_2;
    Unk *temp_v0_3;
    Unk *temp_v0_4;
    Unk *temp_v0_5;
    Unk *temp_v0_6;
    Unk *temp_v0_7;
    Unk *temp_v0_8;
    Unk *temp_v0_9;
    Unk *temp_v1;
    Unk *temp_v1_3;
    Unk *temp_v1_4;

    if (D_80092B6C != 0) {
        var_t3 = 0;
        temp_v0 = *arg0;
        *arg0 = temp_v0 + 8;
        temp_v0->unk0 = (s32) (((D_80092B6C & 0xFF) << 0xC) | (((D_80092B6C & 0x7F) * 2) | 0x01000000));
        temp_v0->unk4 = (s32) D_80092B68;
        if (D_80092B70 != 0) {
            var_t0 = 0;
            do {
                temp_v1 = var_t0 + D_801821E8;
                if (temp_v1->unk0 != 0) {
                    temp_v1_2 = temp_v1->unkA;
                    if (temp_v1_2 == 4) {
                        temp_a0 = *arg0;
                        *arg0 = temp_a0 + 8;
                        temp_a1 = var_t0 + D_801821E8;
                        var_v1 = 0xFD500000;
                        if (temp_a1->unkB != 0) {
                            var_v1 = 0xFD900000;
                        }
                        temp_a0->unk0 = var_v1;
                        temp_a0->unk4 = (s32) temp_a1->unk0;
                        temp_a0_2 = *arg0;
                        *arg0 = temp_a0_2 + 8;
                        var_v1_2 = 0xF5500000;
                        if ((void *)((Unk *)(var_t0 + D_801821E8))->unkB != 0) {
                            var_v1_2 = 0xF5900000;
                        }
                        temp_a0_2->unk0 = var_v1_2;
                        temp_a0_2->unk4 = 0x07080200;
                        temp_v0_2 = *arg0;
                        *arg0 = temp_v0_2 + 8;
                        temp_v0_2->unk0 = 0xE6000000;
                        temp_v0_2->unk4 = 0;
                        temp_v0_3 = *arg0;
                        *arg0 = temp_v0_3 + 8;
                        var_a2 = 0x800;
                        temp_v0_3->unk0 = 0xF3000000;
                        temp_v0_4 = var_t0 + D_801821E8;
                        temp_a1_2 = temp_v0_4->unk4;
                        temp_a0_3 = temp_a1_2 >> 4;
                        if (temp_a0_3 != 0) {
                            var_a2 = temp_a0_3 + 0x7FF;
                        }
                        var_v1_3 = ((s32) ((temp_a1_2 * temp_v0_4->unk6) + 3) >> 2) - 1;
                        if (var_v1_3 >= 0x800) {
                            var_v1_3 = 0x7FF;
                        }
                        if (temp_a0_3 != 0) {
                            var_v0 = (var_a2 / (s32) temp_a0_3) & 0xFFF;
                        } else {
                            var_v0 = var_a2 & 0xFFF;
                        }
                        temp_v0_3->unk4 = (s32) (((var_v1_3 & 0xFFF) << 0xC) | 0x07000000 | var_v0);
                        temp_v0_5 = *arg0;
                        *arg0 = temp_v0_5 + 8;
                        temp_v0_5->unk0 = 0xE7000000;
                        temp_v0_5->unk4 = 0;
                        temp_a1_3 = *arg0;
                        *arg0 = temp_a1_3 + 8;
                        temp_v1_3 = var_t0 + D_801821E8;
                        var_v0_2 = 0xF5400000;
                        if (temp_v1_3->unkB != 0) {
                            var_v0_2 = 0xF5800000;
                        }
                        temp_a1_3->unk0 = (s32) (((((s32) (((u16) temp_v1_3->unk4 >> 1) + 7) >> 3) & 0x1FF) << 9) | var_v0_2);
                        var_v0_3 = ((Unk *)(var_t0 + D_801821E8))->unk8 & 0xF;
                        goto block_50;
                    }
                    if (temp_v1_2 != 8) {
                        if (temp_v1_2 == 0x10) {
                            temp_v0_6 = *arg0;
                            *arg0 = temp_v0_6 + 8;
                            temp_v0_6->unk0 = 0xFD100000;
                            temp_v0_6->unk4 = (s32) *(var_t0 + D_801821E8);
                            temp_v0_7 = *arg0;
                            *arg0 = temp_v0_7 + 8;
                            temp_v0_7->unk0 = 0xF5100000;
                            temp_v0_7->unk4 = 0x07080200;
                            temp_v0_8 = *arg0;
                            *arg0 = temp_v0_8 + 8;
                            temp_v0_8->unk0 = 0xE6000000;
                            temp_v0_8->unk4 = 0;
                            temp_v0_9 = *arg0;
                            *arg0 = temp_v0_9 + 8;
                            temp_v0_9->unk0 = 0xF3000000;
                            temp_a0_4 = ((Unk *)(var_t0 + D_801821E8))->unk4;
                            var_v0_4 = temp_a0_4;
                            if ((s32) temp_a0_4 < 0) {
                                var_v0_4 = temp_a0_4 + 3;
                            }
                            temp_v0_10 = (s32) var_v0_4 >> 2;
                            var_v1_4 = 0x800;
                            if (temp_v0_10 > 0) {
                                var_v1_4 = temp_v0_10 + 0x7FF;
                            }
                            temp_v0_11 = var_t0 + D_801821E8;
                            temp_a1_4 = temp_v0_11->unk4;
                            var_a0 = (temp_a1_4 * temp_v0_11->unk6) - 1;
                            if (var_a0 >= 0x800) {
                                var_a0 = 0x7FF;
                            }
                            var_a2_2 = temp_a1_4;
                            if ((s32) temp_a1_4 < 0) {
                                var_a2_2 = temp_a1_4 + 3;
                            }
                            temp_v0_12 = (s32) var_a2_2 >> 2;
                            if (temp_v0_12 <= 0) {
                                var_v0_5 = var_v1_4 & 0xFFF;
                            } else {
                                var_v0_5 = (var_v1_4 / temp_v0_12) & 0xFFF;
                            }
                            temp_v0_9->unk4 = (s32) (((var_a0 & 0xFFF) << 0xC) | 0x07000000 | var_v0_5);
                            temp_v0_13 = *arg0;
                            *arg0 = temp_v0_13 + 8;
                            temp_v0_13->unk0 = 0xE7000000;
                            temp_v0_13->unk4 = 0;
                            temp_v0_14 = *arg0;
                            *arg0 = temp_v0_14 + 8;
                            temp_a0_5 = var_t0 + D_801821E8;
                            temp_v0_14->unk0 = (s32) (((((s32) ((temp_a0_5->unk4 * 2) + 7) >> 3) & 0x1FF) << 9) | 0xF5100000);
                            var_v0_3 = temp_a0_5->unk8 & 0xF;
                            goto block_50;
                        }
                    } else {
                        temp_a0_6 = *arg0;
                        *arg0 = temp_a0_6 + 8;
                        temp_a1_5 = var_t0 + D_801821E8;
                        var_v1_5 = 0xFD500000;
                        if (temp_a1_5->unkB != 0) {
                            var_v1_5 = 0xFD900000;
                        }
                        temp_a0_6->unk0 = var_v1_5;
                        temp_a0_6->unk4 = (s32) temp_a1_5->unk0;
                        temp_a0_7 = *arg0;
                        *arg0 = temp_a0_7 + 8;
                        var_v1_6 = 0xF5500000;
                        if ((void *)((Unk *)(var_t0 + D_801821E8))->unkB != 0) {
                            var_v1_6 = 0xF5900000;
                        }
                        temp_a0_7->unk0 = var_v1_6;
                        temp_a0_7->unk4 = 0x07080200;
                        temp_v0_15 = *arg0;
                        *arg0 = temp_v0_15 + 8;
                        temp_v0_15->unk0 = 0xE6000000;
                        temp_v0_15->unk4 = 0;
                        temp_v0_16 = *arg0;
                        *arg0 = temp_v0_16 + 8;
                        var_a2_3 = 0x800;
                        temp_v0_16->unk0 = 0xF3000000;
                        temp_v0_17 = var_t0 + D_801821E8;
                        temp_a1_6 = temp_v0_17->unk4;
                        temp_a0_8 = temp_a1_6 >> 3;
                        if (temp_a0_8 != 0) {
                            var_a2_3 = temp_a0_8 + 0x7FF;
                        }
                        var_v1_7 = ((s32) ((temp_a1_6 * temp_v0_17->unk6) + 1) >> 1) - 1;
                        if (var_v1_7 >= 0x800) {
                            var_v1_7 = 0x7FF;
                        }
                        if (temp_a0_8 != 0) {
                            var_v0_6 = (var_a2_3 / (s32) temp_a0_8) & 0xFFF;
                        } else {
                            var_v0_6 = var_a2_3 & 0xFFF;
                        }
                        temp_v0_16->unk4 = (s32) (((var_v1_7 & 0xFFF) << 0xC) | 0x07000000 | var_v0_6);
                        temp_v0_18 = *arg0;
                        *arg0 = temp_v0_18 + 8;
                        temp_v0_18->unk0 = 0xE7000000;
                        temp_v0_18->unk4 = 0;
                        temp_a1_7 = *arg0;
                        *arg0 = temp_a1_7 + 8;
                        temp_v1_4 = var_t0 + D_801821E8;
                        var_v0_7 = 0xF5480000;
                        if (temp_v1_4->unkB != 0) {
                            var_v0_7 = 0xF5880000;
                        }
                        temp_a1_7->unk0 = (s32) (((((s32) (temp_v1_4->unk4 + 7) >> 3) & 0x1FF) << 9) | var_v0_7);
                        var_v0_3 = ((Unk *)(var_t0 + D_801821E8))->unk8 & 0xF;
block_50:
                        ((Unk*)*arg0)->unk4 = (s32) ((var_v0_3 << 0x14) | 0x80200);
                        temp_v0_19 = *arg0;
                        *arg0 = temp_v0_19 + 8;
                        temp_v0_19->unk0 = 0xF2000000;
                        temp_v0_20 = var_t0 + D_801821E8;
                        temp_v0_19->unk4 = (s32) (((((temp_v0_20->unk4 - 1) * 4) & 0xFFF) << 0xC) | (((temp_v0_20->unk6 - 1) * 4) & 0xFFF));
                    }
                }
                temp_v0_21 = *arg0;
                *arg0 = temp_v0_21 + 8;
                var_t3 += 1;
                temp_a1_8 = var_t0 + D_801821E8;
                var_t0 += 0x10;
                temp_v0_21->unk0 = (s32) ((((temp_a1_8->unkC * 2) & 0xFF) << 0x10) | ((temp_a1_8->unkD << 9) & 0xFE00) | ((temp_a1_8->unkE * 2) & 0xFF) | 0x06000000);
                temp_v0_21->unk4 = (s32) ((((temp_a1_8->unkE * 2) & 0xFF) << 0x10) | ((temp_a1_8->unkF << 9) & 0xFE00) | ((temp_a1_8->unkC * 2) & 0xFF));
            } while (var_t3 < (u32) D_80092B70);
        }
        D_80092B68 = 0;
        D_80092B6C = 0;
        D_80092B70 = 0;
    }
    var_t3_2 = 0;
    var_v1_8 = D_801821E8;
    do {
        *var_v1_8 = 0;
        var_t3_2 += 1;
        var_v1_8 += 0x10;
    } while (var_t3_2 < 0x20U);
    temp_a0_9 = D_80173CC0;
    D_80173CC0 += 8;
    temp_a0_9->unk0 = 0xE7000000;
    temp_a0_9->unk4 = 0;
}
