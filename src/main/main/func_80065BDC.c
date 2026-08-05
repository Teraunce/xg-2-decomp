#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of sfxGetVolLevel (initial). */

u16 renderCurveStrip(void**, Unk*, u32, s16, s32, u32);   /* extern */
s32 gfxAddPoint(s32, s32, s16, s16, s32);        /* extern */
s32 trackComputeLen(s32, s16, s16);                   /* extern */
extern s16 D_80182E68;
extern u16 D_80182E74;
extern s16 D_80182E76;
extern Unk D_80182E88;
extern s16 D_80182E90;
extern s16 D_80182E92;
extern u16 D_80182E94;
extern s16 D_80182E96;
extern u8 D_80182E9C;
extern s32 D_80182EA0;
extern s32 D_80182EA4;

void func_80065BDC(s32 arg0, u8 **arg1, s32 arg2) {
    s16 *var_v1_2;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_v1;
    s32 var_a0;
    s32 var_s2;
    s32 var_s4;
    s32 var_s4_2;
    s32 var_s4_3;
    s32 var_s6;
    s32 var_s7;
    s32 var_v0_3;
    u16 *var_v0_4;
    u16 var_v0;
    u16 var_v0_2;
    u32 temp_v0;
    u32 var_v1;
    u8 **var_s0;
    u8 **var_s0_2;
    u8 **var_v1_3;

    var_s6 = trackComputeLen(arg1, 0, D_80182E68);
    if ((u16) D_80182E68 != 0) {
        if ((D_80182E76 >= (D_80182E96 + D_80182E90)) || (D_80182E76 >= 0xFF)) {
            D_80182E68 = 0;
            return;
        }
        if ((arg2 == 0) || (var_a0 = 0, ((D_80182E9C & 6) != 6))) {
            temp_v1 = D_80182E9C & 6;
            if (temp_v1 == 4) {
                D_80182E74 = (D_80182E94 + (u16) D_80182E92) - var_s6;
            } else if (temp_v1 == 0) {
                temp_v0 = D_80182E92 - var_s6;
                D_80182E74 = D_80182E94 + ((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1);
            }
            var_s4 = 0;
            if ((u16) D_80182E68 != 0) {
                var_s0 = arg1;
                do {
                    if (((Unk *)var_s0)->unk0 != 0) {
                        if ((D_80182EA0 != 0) && (gfxAddPoint(((Unk *)var_s0)->unk0, ((Unk *)var_s0)->unk8, (s16) D_80182E74, D_80182E76, ((Unk *)var_s0)->unkC) != 0)) {
                            if ((((Unk *)var_s0)->unk4 != 0) && (gfxAddPoint(((Unk *)var_s0)->unk4, ((Unk *)var_s0)->unk8, (s16) D_80182E74, D_80182E76, ((Unk *)var_s0)->unkC) == 0)) {
                                renderCurveStrip(arg0, ((Unk *)var_s0)->unk4, ((Unk *)var_s0)->unk8, (s16) D_80182E74, (s32) D_80182E76, ((Unk *)var_s0)->unkC);
                            }
                            var_v0 = D_80182E74;
                            var_v1 = (u32) (*(u8*)(s32)((Unk *)var_s0)->unk0 * ((Unk *)var_s0)->unk8) >> 0x10;
                            goto block_26;
                        }
                        temp_s1 = renderCurveStrip(arg0, ((Unk *)var_s0)->unk0, ((Unk *)var_s0)->unk8, (s16) D_80182E74, (s32) D_80182E76, ((Unk *)var_s0)->unkC) & 0xFFFF;
                        if (((Unk *)var_s0)->unk4 != 0) {
                            renderCurveStrip(arg0, ((Unk *)var_s0)->unk4, ((Unk *)var_s0)->unk8, (s16) D_80182E74, (s32) D_80182E76, ((Unk *)var_s0)->unkC);
                        }
                        var_v0_2 = D_80182E74 + temp_s1;
                    } else {
                        var_v0_3 = D_80182EA4;
                        var_v1 = D_80182E74 + 6;
                        if (var_v0_3 < 0) {
                            var_v0_3 += 3;
                        }
                        var_v0 = (u16) (var_v0_3 >> 2);
block_26:
                        var_v0_2 = var_v1 + var_v0;
                    }
                    D_80182E74 = var_v0_2;
                    var_s0 += 0x10;
                    var_s4 += 1;
                    D_80182E74 += D_80182E88.unk2;
                } while (var_s4 < (s32) (u16) D_80182E68);
            }
            var_v0_4 = (u16 *)0x80180000;
            if (D_80182E9C & 4) {
                var_v1_2 = (s16 *)0x80180000;
                goto block_55;
            }
        } else {
            var_s4_2 = 0;
            if ((u16) D_80182E68 != 0) {
                var_v1_3 = arg1;
                do {
                    if (*var_v1_3 == NULL) {
                        var_a0 += 1;
                    }
                    var_s4_2 += 1;
                    var_v1_3 += 0x10;
                } while (var_s4_2 < (s32) (u16) D_80182E68);
            }
            if (var_a0 > 0) {
                var_s7 = (s32) ((s32) (D_80182E92 - var_s6) / 4) / var_a0;
                var_s6 += var_s7 * var_a0;
            } else {
                var_s7 = 0;
            }
            var_s4_3 = 0;
            if ((u16) D_80182E68 != 0) {
                var_s0_2 = arg1;
                do {
                    var_s2 = 0;
                    if ((u16) D_80182E68 >= 2U) {
                        var_s2 = (s32) ((D_80182E92 - var_s6) * var_s4_3) / (s32) ((u16) D_80182E68 - 1);
                    }
                    if (((Unk *)var_s0_2)->unk0 != 0) {
                        if ((D_80182EA0 != 0) && (gfxAddPoint(((Unk *)var_s0_2)->unk0, ((Unk *)var_s0_2)->unk8, (s16) (D_80182E74 + var_s2), D_80182E76, ((Unk *)var_s0_2)->unkC) != 0)) {
                            if ((((Unk *)var_s0_2)->unk4 != 0) && (gfxAddPoint(((Unk *)var_s0_2)->unk4, ((Unk *)var_s0_2)->unk8, (s16) (D_80182E74 + var_s2), D_80182E76, ((Unk *)var_s0_2)->unkC) == 0)) {
                                renderCurveStrip(arg0, ((Unk *)var_s0_2)->unk4, ((Unk *)var_s0_2)->unk8, (s16) (D_80182E74 + var_s2), (s32) D_80182E76, ((Unk *)var_s0_2)->unkC);
                            }
                            D_80182E74 += (u32) (*(u8*)(s32)((Unk *)var_s0_2)->unk0 * ((Unk *)var_s0_2)->unk8) >> 0x10;
                        } else {
                            temp_s1_2 = renderCurveStrip(arg0, ((Unk *)var_s0_2)->unk0, ((Unk *)var_s0_2)->unk8, (s16) (D_80182E74 + var_s2), (s32) D_80182E76, ((Unk *)var_s0_2)->unkC) & 0xFFFF;
                            if (((Unk *)var_s0_2)->unk4 != 0) {
                                renderCurveStrip(arg0, ((Unk *)var_s0_2)->unk4, ((Unk *)var_s0_2)->unk8, (s16) (D_80182E74 + var_s2), (s32) D_80182E76, ((Unk *)var_s0_2)->unkC);
                            }
                            D_80182E74 += temp_s1_2;
                        }
                    } else {
                        D_80182E74 += ((s32) D_80182EA4 / 4) + (var_s7 + 6);
                    }
                    var_s0_2 += 0x10;
                    var_s4_3 += 1;
                    D_80182E74 += D_80182E88.unk2;
                } while (var_s4_3 < (s32) (u16) D_80182E68);
            }
            var_v0_4 = &D_80182E94;
            var_v1_2 = &D_80182E92;
block_55:
            D_80182E74 = *var_v0_4 + (u16) *var_v1_2;
        }
        D_80182E68 = 0;
    }
}

u8 sfxGetVolLevel(void) {
    return D_80182E9C;
}
