#include "ultra64.h"
s32 func_8008EEEC(void *, u8);                         /* extern */
void func_8008EF38();                                  /* extern */
extern s32 D_8004CFD8;
extern s32 D_8004CFDC;
extern s32 D_8004CFE4;
extern u8 D_800964C0;
extern u8 D_800964E4;

s32 func_8008F5A8(s32 (*arg0)(s32, u8 *, s32, u8 *), s32 arg1, u8 *arg2, s32 arg3) {
    u8 spD4;
    s32 spD0;
    s32 spCC;
    s32 spC8;
    s32 spC4;
    s32 spA0;
    s32 spAC; s32 spB0; s32 spB4; s32 spB8; s32 spBC; s32 spC0;
    u8 *spA8;
    u8 sp74;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_t6_3;
    s32 temp_t7_2;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 temp_t8_3;
    s32 temp_t9;
    s32 temp_t9_3;
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_12;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s0_6;
    s32 var_s0_7;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s3;
    u8 *var_a3;
    Unk *var_s2;
    Unk *var_s2_2;
    u8 temp_t7;
    u8 temp_t9_2;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 var_a1;
    u8 var_a1_2;
    u8 var_s0;

    var_a3 = arg2;
    var_s3 = arg1;
    spCC = 0;
loop_1:
    temp_v0 = *var_a3;
    var_s2 = var_a3;
    var_s0 = temp_v0;
    if ((temp_v0 != 0) && (temp_v0 != 0x25)) {
loop_3:
        temp_v0_2 = var_s2->unk1;
        var_s2 += 1;
        var_s0 = temp_v0_2;
        if (temp_v0_2 != 0) {
            if (temp_v0_2 != 0x25) {
                goto loop_3;
            }
        }
    }
    temp_v0_3 = (char*)var_s2 - (char*)var_a3;
    if (temp_v0_3 > 0) {
        temp_v0_4 = arg0(var_s3, var_a3, temp_v0_3, var_a3);
        var_s3 = temp_v0_4;
        if (temp_v0_4 != 0) {
            spCC += temp_v0_3;
            goto block_9;
        }
        return spCC;
    }
block_9:
    var_s2_2 = var_s2 + 1;
    if (var_s0 == 0) {
        return spCC;
    }
    spD0 = 0;
    temp_v0_5 = func_8008EEEC(&D_8004CFDC, var_s2->unk1);
    var_s0_2 = temp_v0_5;
    if (temp_v0_5 != 0) {
        do {
            var_s2_2 += 1;
            spD0 |= *(&D_8004CFE4 + ((s32*)(s32)var_s0_2 - &D_8004CFDC));
            temp_v0_6 = func_8008EEEC(&D_8004CFDC, var_s2_2->unk0);
            var_s0_2 = temp_v0_6;
        } while (temp_v0_6 != 0);
    }
    if (var_s2_2->unk0 == 0x2A) {
        temp_t9 = (arg3 + 3) & ~3;
        arg3 = temp_t9 + 4;
        temp_t8 = *(s32*)(s32)temp_t9;
        var_s2_2 += 1;
        spC8 = temp_t8;
        if (temp_t8 < 0) {
            spC8 = -temp_t8;
            spD0 |= 4;
        }
        var_a1 = var_s2_2->unk0;
    } else {
        spC8 = 0;
        var_a1 = var_s2_2->unk0;
        if (((s32) var_a1 >= 0x30) && ((s32) var_a1 < 0x3A)) {
loop_19:
            if (spC8 < 0x3E7) {
                spC8 = (var_a1 + (spC8 * 0xA)) - 0x30;
            }
            var_a1 = var_s2_2->unk1;
            var_s2_2 += 1;
            if (((s32) var_a1 >= 0x30) && ((s32) var_a1 < 0x3A)) {
                goto loop_19;
            }
        }
    }
    if (var_a1 != 0x2E) {
        spC4 = -1;
        var_a1_2 = var_s2_2->unk0;
    } else {
        temp_t7 = var_s2_2->unk1;
        var_s2_2 += 1;
        if (temp_t7 == 0x2A) {
            temp_t8_2 = (arg3 + 3) & ~3;
            arg3 = temp_t8_2 + 4;
            var_s2_2 += 1;
            spC4 = *(s32*)(s32)temp_t8_2;
            var_a1_2 = var_s2_2->unk0;
        } else {
            spC4 = 0;
            var_a1_2 = var_s2_2->unk0;
            if (((s32) var_a1_2 >= 0x30) && ((s32) var_a1_2 < 0x3A)) {
loop_29:
                if (spC4 < 0x3E7) {
                    spC4 = (var_a1_2 + (spC4 * 0xA)) - 0x30;
                }
                var_a1_2 = var_s2_2->unk1;
                var_s2_2 += 1;
                if (((s32) var_a1_2 >= 0x30) && ((s32) var_a1_2 < 0x3A)) {
                    goto loop_29;
                }
            }
        }
    }
    if (func_8008EEEC(&D_8004CFD8, var_a1_2) != 0) {
        temp_t9_2 = var_s2_2->unk0;
        var_s2_2 += 1;
        spD4 = temp_t9_2;
    } else {
        spD4 = 0;
    }
    if ((spD4 == 0x6C) && (var_s2_2->unk0 == 0x6C)) {
        spD4 = 0x4C;
        var_s2_2 += 1;
    }
    func_8008EF38();
    temp_t9_3 = (((((spC8 - spAC) - spB0) - spB4) - spB8) - spBC) - spC0;
    spC8 = temp_t9_3;
    temp_t6 = temp_t9_3 > 0;
    if (!(spD0 & 4) && (temp_t6 != 0)) {
        var_s1 = temp_t9_3;
        if (temp_t6 != 0) {
loop_42:
            var_s0_3 = var_s1;
            if ((u32) var_s1 >= 0x21U) {
                var_s0_3 = 0x20;
            }
            if (var_s0_3 > 0) {
                temp_v0_7 = arg0(var_s3, &D_800964C0, var_s0_3, NULL);
                var_s3 = temp_v0_7;
                if (temp_v0_7 != 0) {
                    spCC += var_s0_3;
                    goto block_48;
                }
                return spCC;
            }
block_48:
            var_s1 -= var_s0_3;
            if (var_s1 <= 0) {
                goto block_49;
            }
            goto loop_42;
        }
    }
block_49:
    if (spAC > 0) {
        temp_v0_8 = arg0(var_s3, &sp74, spAC, NULL);
        var_s3 = temp_v0_8;
        if (temp_v0_8 != 0) {
            spCC += spAC;
            goto block_53;
        }
        return spCC;
    }
block_53:
    temp_t6_2 = spB0 > 0;
    if (temp_t6_2 != 0) {
        var_s1_2 = spB0;
        if (temp_t6_2 != 0) {
loop_55:
            var_s0_4 = var_s1_2;
            if ((u32) var_s1_2 >= 0x21U) {
                var_s0_4 = 0x20;
            }
            if (var_s0_4 > 0) {
                temp_v0_9 = arg0(var_s3, &D_800964E4, var_s0_4, NULL);
                var_s3 = temp_v0_9;
                if (temp_v0_9 != 0) {
                    spCC += var_s0_4;
                    goto block_61;
                }
                return spCC;
            }
block_61:
            var_s1_2 -= var_s0_4;
            if (var_s1_2 <= 0) {
                goto block_62;
            }
            goto loop_55;
        }
    }
block_62:
    if (spB4 > 0) {
        temp_v0_10 = arg0(var_s3, spA8, spB4, NULL);
        var_s3 = temp_v0_10;
        if (temp_v0_10 != 0) {
            spCC += spB4;
            goto block_66;
        }
        return spCC;
    }
block_66:
    temp_t6_3 = spB8 > 0;
    if (temp_t6_3 != 0) {
        var_s1_3 = spB8;
        if (temp_t6_3 != 0) {
loop_68:
            var_s0_5 = var_s1_3;
            if ((u32) var_s1_3 >= 0x21U) {
                var_s0_5 = 0x20;
            }
            if (var_s0_5 > 0) {
                temp_v0_11 = arg0(var_s3, &D_800964E4, var_s0_5, NULL);
                var_s3 = temp_v0_11;
                if (temp_v0_11 != 0) {
                    spCC += var_s0_5;
                    goto block_74;
                }
                return spCC;
            }
block_74:
            var_s1_3 -= var_s0_5;
            if (var_s1_3 <= 0) {
                goto block_75;
            }
            goto loop_68;
        }
    }
block_75:
    if (spBC > 0) {
        temp_v0_12 = arg0(var_s3, &spA8[spB4], spBC, NULL);
        var_s3 = temp_v0_12;
        if (temp_v0_12 != 0) {
            spCC += spBC;
            goto block_79;
        }
        return spCC;
    }
block_79:
    temp_t8_3 = spC0 > 0;
    if (temp_t8_3 != 0) {
        var_s1_4 = spC0;
        if (temp_t8_3 != 0) {
loop_81:
            var_s0_6 = var_s1_4;
            if ((u32) var_s1_4 >= 0x21U) {
                var_s0_6 = 0x20;
            }
            if (var_s0_6 > 0) {
                temp_v0_13 = arg0(var_s3, &D_800964E4, var_s0_6, NULL);
                var_s3 = temp_v0_13;
                if (temp_v0_13 != 0) {
                    spCC += var_s0_6;
                    goto block_87;
                }
                return spCC;
            }
block_87:
            var_s1_4 -= var_s0_6;
            if (var_s1_4 <= 0) {
                goto block_88;
            }
            goto loop_81;
        }
    }
block_88:
    temp_t7_2 = spC8 > 0;
    if ((spD0 & 4) && (temp_t7_2 != 0)) {
        var_s1_5 = spC8;
        if (temp_t7_2 != 0) {
loop_91:
            var_s0_7 = var_s1_5;
            if ((u32) var_s1_5 >= 0x21U) {
                var_s0_7 = 0x20;
            }
            if (var_s0_7 > 0) {
                temp_v0_14 = arg0(var_s3, &D_800964C0, var_s0_7, NULL);
                var_s3 = temp_v0_14;
                if (temp_v0_14 != 0) {
                    spCC += var_s0_7;
                    goto block_97;
                }
                return spCC;
            }
block_97:
            var_s1_5 -= var_s0_7;
            if (var_s1_5 <= 0) {
                goto block_98;
            }
            goto loop_91;
        }
    }
block_98:
    var_a3 = var_s2_2 + 1;
    goto loop_1;
}
