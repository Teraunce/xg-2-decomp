#include "ultra64.h"
s32 func_80061ADC();                                  /* extern */
s32 func_80061B28();                                  /* extern */
s32 sfxGetEntry(s32);                             /* extern */
extern u16 gLocaleIdx;
extern Unk gRandState;
extern s32 gRandInitB;

s32 sfxMapId(s32 arg0) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = arg0;
    if (var_s0 == 0x11) {
        var_s0 = 0x22;
    } else if (var_s0 == 0x1E) {
        var_s0 = 0x23;
    }
    if (var_s0 < 0) {
        return var_s0;
    }
    if (gLocaleIdx == 0) {
        return 0;
    }
    temp_v0 = sfxGetEntry(gLocaleIdx);
    return temp_v0 + *(s32 *)((char *)(s32)temp_v0 + var_s0 * 4);
}

void func_80061904(s32 arg0) {
    gRandState.unk0 = 0;
    gRandState.unk4 = 0;
    gRandInitB = arg0;
}

s32 sfxRandNext(void) {
    u32 temp_a0;
    u32 temp_a1;
    u32 temp_v0;
    u32 temp_v1;

    temp_v1 = (gRandState.unk4 * 0x41C64E6D) + 0x3039;
    temp_v0 = MULTU_HI(gRandState.unk4, 0x41C64E6D) + (gRandState.unk0 * 0x41C64E6D) + (temp_v1 < 0x3039U);
    temp_a0 = ((temp_v0 << 0xF) | (temp_v1 >> 0x11)) ^ (temp_v0 >> 0x1B);
    temp_a1 = (temp_v1 << 0xF) ^ ((temp_v1 >> 0x1B) | (temp_v0 << 5));
    gRandState.unk0 = temp_a0;
    gRandState.unk4 = temp_a1;
    return (temp_a1 >> 4) | (temp_a0 << 0x1C);
}

void safeCopy(u32 arg0, u32 arg1, u32 arg2) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_a2_4;
    u32 var_a0;
    u32 var_a1;
    u32 var_a2;
    u32 var_v0;
    u8 *var_a0_2;
    u8 *var_a1_2;
    u8 temp_v0_3;
    u8 temp_v0_4;
    u8 temp_v0_5;

    var_a0 = arg0;
    var_a1 = arg1;
    var_a2 = arg2;
    if ((var_a1 >= var_a0) || (temp_v0 = var_a2 - 1, ((var_a0 < (u32) (var_a1 + var_a2)) == 0))) {
        if (!(var_a0 & 3) && !(var_a1 & 3)) {
            var_v0 = var_a2;
            if (var_a2 >= 4U) {
                do {
                    temp_v0_2 = *(s32 *)var_a1;
                    var_a1 += 4;
                    var_a2 -= 4;
                    *(s32 *)var_a0 = temp_v0_2;
                    var_a0 += 4;
                } while (var_a2 >= 4U);
                var_v0 = var_a2;
            }
            var_a2_2 = var_a2 - 1;
            if (var_v0 != 0) {
                do {
                    temp_v0_3 = *(u8 *)var_a1;
                    var_a1 += 1;
                    temp_v1 = var_a2_2;
                    var_a2_2 -= 1;
                    *(u8 *)var_a0 = temp_v0_3;
                    var_a0 += 1;
                } while (temp_v1 != 0);
            }
        } else {
            var_a2_3 = var_a2 - 1;
            if (var_a2 != 0) {
                do {
                    temp_v0_4 = *(u8 *)var_a1;
                    var_a1 += 1;
                    temp_v1_2 = var_a2_3;
                    var_a2_3 -= 1;
                    *(u8 *)var_a0 = temp_v0_4;
                    var_a0 += 1;
                } while (temp_v1_2 != 0);
            }
        }
    } else {
        var_a0_2 = var_a0 + temp_v0;
        var_a1_2 = var_a1 + temp_v0;
        var_a2_4 = temp_v0;
        if (var_a2 != 0) {
            do {
                temp_v0_5 = *var_a1_2;
                var_a1_2 -= 1;
                temp_v1_3 = var_a2_4;
                var_a2_4 -= 1;
                *var_a0_2 = temp_v0_5;
                var_a0_2 -= 1;
            } while (temp_v1_3 != 0);
        }
    }
}

void memsetBytes(s8 *arg0, s8 arg1, s32 arg2) {
    s32 var_v1;
    s8 *var_a3;

    var_a3 = arg0;
    var_v1 = arg2 - 1;
    if (arg2 != 0) {
        do {
            *var_a3 = arg1;
            var_v1 -= 1;
            var_a3 += 1;
        } while (var_v1 != -1);
    }
}

void sfxEntryWrite(void) {
    func_80061ADC();
}

/* -------------------------------------------------------------------------
 * memsetWord — word-fill loop (memset-word variant).
 *
 * Fills arg2+1 consecutive words at arg0 with value arg1.
 * Branch-back-to-self pattern (bnez memsetWord) caused m2c to fail;
 * translated as do-while with post-decrement check.
 * ------------------------------------------------------------------------- */
void memsetWord(s32 *arg0, s32 arg1, s32 arg2) {
    do {
        *arg0++ = arg1;
    } while (arg2-- != 0);
}

void memcmp(void) {
    func_80061B28();
}

/* -------------------------------------------------------------------------
 * memcmpImpl — byte-by-byte compare (memcmp variant).
 *
 * Compares up to arg2+1 bytes at arg0 vs arg1.
 * Returns -1 if *arg0 < *arg1, +1 if *arg0 > *arg1, 0 if all equal.
 * Branch-back-to-self pattern caused m2c to fail; loop is a do-while.
 * ------------------------------------------------------------------------- */
s32 memcmpImpl(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 a, b;
    do {
        a = *arg0;
        b = *arg1;
        if (a < b) return -1;
        if (a > b) return 1;
        arg0++;
        arg1++;
    } while (arg2-- != 0);
    return 0;
}

u32 u64DivImpl(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    s32 var_a1;
    s32 var_v0;
    u32 var_t0;
    u32 var_t1;
    u32 var_t2;
    u32 var_t3;
    u32 var_t4;
    u32 var_t5;

    var_t4 = arg0;
    var_t5 = arg1;
    var_t0 = 0;
    var_t1 = 0;
    var_t2 = 0;
    var_t3 = 0;
    var_a1 = 0x3F;
    do {
        var_t2 = (var_t2 * 2) | (var_t3 >> 0x1F);
        var_t3 *= 2;
        var_t0 = (var_t0 * 2) | (var_t1 >> 0x1F) | 0;
        var_t1 = (var_t1 * 2) | (var_t4 >> 0x1F);
        var_t4 = (var_t4 * 2) | (var_t5 >> 0x1F);
        var_t5 *= 2;
        if (var_t0 >= arg2) {
            var_v0 = var_t1 < arg3;
            if (arg2 == var_t0) {
                if (var_v0 == 0) {
                    var_v0 = var_t1 < arg3;
                    goto block_5;
                }
            } else {
block_5:
                var_t1 -= arg3;
                var_t0 = (var_t0 - arg2) - var_v0;
                var_t2 |= 0;
                var_t3 |= 1;
            }
        }
        var_a1 -= 1;
    } while (var_a1 >= 0);
    return var_t2;
}

u32 func_80061BE8(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    s32 var_a1;
    s32 var_v0;
    u32 var_t0;
    u32 var_t1;
    u32 var_t2;
    u32 var_t3;

    var_t2 = arg0;
    var_t3 = arg1;
    var_t0 = 0;
    var_t1 = 0;
    var_a1 = 0x3F;
    do {
        var_t0 = (var_t0 * 2) | (var_t1 >> 0x1F) | 0;
        var_t1 = (var_t1 * 2) | (var_t2 >> 0x1F);
        var_t2 = (var_t2 * 2) | (var_t3 >> 0x1F);
        var_t3 *= 2;
        if (var_t0 >= arg2) {
            var_v0 = var_t1 < arg3;
            if (arg2 == var_t0) {
                if (var_v0 == 0) {
                    var_v0 = var_t1 < arg3;
                    goto block_5;
                }
            } else {
block_5:
                var_t1 -= arg3;
                var_t0 = (var_t0 - arg2) - var_v0;
            }
        }
        var_a1 -= 1;
    } while (var_a1 >= 0);
    return var_t0;
}
