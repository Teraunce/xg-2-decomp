#include "ultra64.h"
s32 byteCopy(s32, void *, s32);                       /* extern */
s32 intDiv(s32, s32);                            /* extern */
void vsprintfFloat();                                  /* extern */
extern s32 D_8004D0D8;
extern s32 D_8004D120;
extern s32 D_8004D124;
extern f64 D_8004D130;

void vsprintfGHandler(Unk *arg0, u8 arg1) {
    s32 sp78;
    u8 spB1;
    s8 spB0;
    s16 sp9A;
    s32 sp74;
    s32 sp48;
    char *var_a1;
    Unk *var_v0_6;
    f64 var_fs0;
    f64 var_fv0;
    s16 temp_t7;
    s16 temp_t8_2;
    s16 var_s3;
    s16 var_s4_2;
    s16 var_v0;
    s16 var_v0_2;
    s16 var_v0_3;
    s32 temp_t6;
    s32 temp_t8;
    s32 temp_t9;
    s32 temp_v0;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_4;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s4;
    s32 var_v0_4;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    u16 temp_a0;
    u8 *temp_v0_2;
    u8 *var_s5;
    u8 *var_s5_2;
    u8 *var_s5_3;
    Unk *var_v0_5;
    u8 temp_t9_2;

    temp_v0 = arg0->unk24;
    var_fs0 = arg0->unk0;
    if (temp_v0 < 0) {
        arg0->unk24 = 6;
    } else if ((temp_v0 == 0) && ((sp48 = (s32) arg1, (arg1 == 0x67)) || (arg1 == 0x47))) {
        arg0->unk24 = 1;
    }
    temp_a0 = (u16) arg0->unk0;
    temp_t8 = (s32) (temp_a0 & 0x7FF0) >> 4;
    if ((s16) temp_t8 == 0x7FF) {
        sp9A = 0;
        if (((u16) arg0->unk0 & 0xF) || (arg0->unk2 != 0) || (arg0->unk4 != 0) || (arg0->unk6 != 0)) {
            var_v0 = 2;
        } else {
            var_v0 = 1;
        }
    } else if ((s16) temp_t8 > 0) {
        arg0->unk0 = (s16) ((temp_a0 & 0x800F) | 0x3FF0);
        sp9A = (s16) temp_t8 - 0x3FE;
        var_v0 = -1;
    } else {
        var_v0 = 0;
        if ((s16) temp_t8 < 0) {
            var_v0 = 2;
        } else {
            sp9A = 0;
        }
    }
    if (var_v0 > 0) {
        if (var_v0 == 2) {
            var_a1 = &D_8004D120;
        } else {
            var_a1 = &D_8004D124;
        }
        arg0->unk14 = 3;
        byteCopy(arg0->unk8, var_a1, 3);
        return;
    }
    if (var_v0 == 0) {
        sp9A = 0;
    } else {
        var_v1 = 0;
        var_s5 = &spB1;
        sp48 = (s32) arg1;
        if (var_fs0 < 0.0) {
            var_fs0 = -var_fs0;
        }
        var_a1_2 = 6;
        temp_t7 = ((s32) (sp9A * 0x7597) / 100000) - 4;
        sp9A = temp_t7;
        if (temp_t7 < 0) {
            var_v0_2 = (3 - temp_t7) & ~3;
            sp9A = -var_v0_2;
            if (var_v0_2 > 0) {
                do {
                    temp_t9 = var_v0_2 >> 1;
                    if (var_v0_2 & 1) {
                        var_fs0 *= *(&D_8004D0D8 + (var_v1 * 8));
                    }
                    var_v0_2 = (s16) temp_t9;
                    var_v1 += 1;
                } while (temp_t9 > 0);
            }
        } else {
            var_v1_2 = 0;
            temp_t8_2 = sp9A & 0xFFFC;
            if (sp9A > 0) {
                var_fv0 = 0.0;
                sp9A = temp_t8_2;
                var_v0_3 = temp_t8_2;
                if (temp_t8_2 > 0) {
                    do {
                        temp_t6 = var_v0_3 >> 1;
                        if (var_v0_3 & 1) {
                            var_fv0 *= *(&D_8004D0D8 + (var_v1_2 * 8));
                        }
                        var_v0_3 = (s16) temp_t6;
                        var_v1_2 += 1;
                    } while (temp_t6 > 0);
                }
                var_fs0 /= var_fv0;
            }
        }
        if (sp48 == 0x66) {
            var_a1_2 = sp9A + 0xA;
        }
        var_s4 = var_a1_2 + arg0->unk24;
        if (var_s4 >= 0x14) {
            var_s4 = 0x13;
        }
        spB0 = 0x30;
        if ((var_s4 > 0) && (var_fs0 > 0.0)) {
loop_47:
            var_s4 -= 8;
            var_s5_2 = var_s5 + 8;
            var_s1 = (s32) var_fs0;
            if (var_s4 > 0) {
                var_fs0 = (var_fs0 - (f64) var_s1) * D_8004D130;
            }
            var_s0 = 8;
            if (var_s1 > 0) {
                var_s0 = 7;
                if (7 >= 0) {
loop_51:
                    intDiv(var_s1, 0xA);
                    var_s5_2 -= 1;
                    *var_s5_2 = sp78 + 0x30;
                    var_s1 = sp74;
                    if (var_s1 > 0) {
                        var_s0 -= 1;
                        if (var_s0 >= 0) {
                            goto loop_51;
                        }
                    }
                }
            }
            var_s0_2 = var_s0 - 1;
            if (var_s0_2 >= 0) {
                do {
                    var_s0_2 -= 1;
                    var_s5_2 -= 1;
                    *var_s5_2 = 0x30;
                } while (var_s0_2 >= 0);
            }
            var_s5 = var_s5_2 + 8;
            if ((var_s4 > 0) && (var_fs0 > 0.0)) {
                goto loop_47;
            }
        }
        var_s4_2 = (var_s5 - (u8 *)&spB0) - 1;
        sp9A += 7;
        var_s5_3 = &spB1;
        if (spB1 == 0x30) {
            do {
                var_s5_3 += 1;
                var_s4_2 -= 1;
                sp9A -= 1;
            } while (*var_s5_3 == 0x30);
        }
        if (sp48 == 0x66) {
            var_a1_3 = sp9A + 1;
        } else {
            if ((sp48 == 0x65) || (var_v0_4 = 0, (sp48 == 0x45))) {
                var_v0_4 = 1;
            }
            var_a1_3 = var_v0_4;
        }
        var_s3 = var_a1_3 + arg0->unk24;
        if (var_s4_2 < var_s3) {
            var_s3 = var_s4_2;
        }
        if (var_s3 > 0) {
            var_v0_5 = &var_s5_3[var_s3];
            if ((var_s3 < var_s4_2) && ((s32) var_v0_5->unk0 >= 0x35)) {
                var_a1_4 = 0x39;
            } else {
                var_a1_4 = 0x30;
                var_v0_5 = &var_s5_3[var_s3];
            }
            var_v1_3 = var_s3 - 1;
            if (var_a1_4 == *(u8*)((char*)var_v0_5 - 1) {
                var_v0_6 = (Unk*)&var_s5_3[var_s3];
                do {
                    temp_t9_2 = *(u8*)((char*)var_v0_6 - 1)
                    var_v1_3 -= 1;
                    var_v0_6 -= 1;
                } while (var_a1_4 == temp_t9_2);
            }
            temp_v0_2 = &var_s5_3[var_v1_3];
            if (var_a1_4 == 0x39) {
                *temp_v0_2 += 1;
            }
            if (var_v1_3 < 0) {
                sp9A += 1;
            }
        }
    }
    vsprintfFloat();
}
