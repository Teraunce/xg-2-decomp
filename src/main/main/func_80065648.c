#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of rdpFormatFloatGetter (initial). */

void copyU16Array(void *);                            /* extern */
extern f64 gFmtScaleD;
extern s32 gHexDigits;

void u16StrTrimEnd(Unk *arg0) {
    u16 *var_a0;

    var_a0 = arg0;
    do {
        var_a0 += 2;
    } while (*var_a0 != 0);
    copyU16Array(var_a0 - 2);
}

s32 u16StrLen(Unk *arg0) {
    s32 var_v1;
    u16 *var_a0;

    var_a0 = arg0;
    var_v1 = 0;
    if (*var_a0 != 0) {
        do {
            var_a0 += 2;
            var_v1 += 1;
        } while (*var_a0 != 0);
    }
    return var_v1 & 0xFFFF;
}

void intToAsciiStr(Unk *arg0, s32 arg1) {
    s16 *var_a3;
    s32 temp_a2;
    s32 var_a1;
    s32 var_t2;
    u16 *var_a1_2;
    u16 temp_a2_2;
    u16 temp_v1;
    u32 temp_t1;
    u32 var_a3_2;
    u32 var_t0;
    Unk *temp_v0;

    var_a1 = arg1;
    var_t0 = 0;
    if (var_a1 < 0) {
        var_a1 = -var_a1;
        var_t2 = 1;
    } else {
        var_t2 = 0;
    }
    var_a3 = (0 * 2) + arg0;
    do {
        var_t0 += 1;
        temp_a2 = var_a1 % 10;
        var_a1 /= 0xA;
        *var_a3 = temp_a2 + 0x30;
        var_a3 += 2;
    } while (var_a1 != 0);
    if (var_t2 != 0) {
        *(s32 *)((var_t0 * 2) + arg0) = 0x2D;
        var_t0 += 1;
    }
    *(s32 *)((var_t0 * 2) + arg0) = 0;
    temp_t1 = var_t0 >> 1;
    var_a3_2 = 0;
    if (temp_t1 != 0) {
        var_a1_2 = arg0;
        do {
            temp_v0 = ((var_t0 - var_a3_2) * 2) + arg0;
            temp_a2_2 = *var_a1_2;
            temp_v1 = *(u16*)((char*)temp_v0 - 2);
            var_a3_2 += 1;
            *var_a1_2 = temp_v1;
            *(u16*)((char*)temp_v0 - 2)= temp_a2_2;
            var_a1_2 += 2;
        } while (var_a3_2 < temp_t1);
    }
}

void rdpFmt2Digit(Unk *arg0, s32 arg1) {
    arg0->unk4 = 0;
    arg0->unk0 = (s16) ((arg1 / 10) + 0x30);
    arg0->unk2 = (s16) ((arg1 % 10) + 0x30);
}

void func_800657A8(Unk *arg0, u32 arg1) {
    u16 *temp_a3;
    u16 *var_a1_2;
    u16 *var_v1;
    u16 temp_a0;
    u16 temp_v1;
    u32 temp_t1;
    u32 var_a1;
    u32 var_a2;
    u32 var_t0;
    u8 temp_v0;
    Unk *temp_v0_2;

    var_a1 = arg1;
    var_t0 = 0;
    arg0->unk0 = 0x24;
    temp_a3 = arg0 + 2;
    var_v1 = temp_a3;
    do {
        var_t0 += 1;
        temp_v0 = *((var_a1 & 0xF) + &gHexDigits);
        var_a1 = var_a1 >> 4;
        *var_v1 = (u16) temp_v0;
        var_v1 += 2;
    } while (var_a1 != 0);
    *((var_t0 * 2) + temp_a3) = 0;
    temp_t1 = var_t0 >> 1;
    var_a2 = 0;
    if (temp_t1 != 0) {
        var_a1_2 = temp_a3;
        do {
            temp_v0_2 = ((var_t0 - var_a2) * 2) + temp_a3;
            temp_a0 = *var_a1_2;
            temp_v1 = *(u16*)((char*)temp_v0_2 - 2);
            var_a2 += 1;
            *var_a1_2 = temp_v1;
            *(u16*)((char*)temp_v0_2 - 2)= temp_a0;
            var_a1_2 += 2;
        } while (var_a2 < temp_t1);
    }
}

void rdpFormatFloat(void);  /* forward: GETTER_NOJR fallthrough */
void rdpFormatFloatGetter(s32 arg2, f64 arg3) {
    rdpFormatFloat();
}
