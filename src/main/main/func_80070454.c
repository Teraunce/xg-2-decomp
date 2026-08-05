#include "ultra64.h"
u16 func_80070268(u8);                              /* extern */

void func_80070454(s32 arg0, Unk *arg1) {
    s32 var_s0;
    u16 *var_s2;
    u16 *var_v1;
    u8 temp_a0;

    var_s0 = 0;
    var_s2 = arg1;
    do {
        temp_a0 = *((u8 *)(s32)arg0 + var_s0);
        var_s0 += 1;
        *var_s2 = func_80070268(temp_a0);
        var_s2 += 2;
    } while (var_s0 < 0x10);
    *(u16 *)((char *)arg1 + var_s0 * 2) = 0;
    if (arg1->unk0 != 0) {
        var_v1 = arg1;
loop_4:
        if (*var_v1 != 0x7E) {
            var_v1 += 2;
            if (*var_v1 == 0) {

            } else {
                goto loop_4;
            }
        } else {
            arg1->unk0 = 0x4F;
            arg1->unk2 = 0x54;
            arg1->unk4 = 0x48;
            arg1->unk6 = 0x45;
            arg1->unk8 = 0x52;
            arg1->unkA = 0x20;
            arg1->unkC = 0x47;
            arg1->unkE = 0x41;
            arg1->unk10 = 0x4D;
            arg1->unk12 = 0x45;
            arg1->unk14 = 0x2E;
            arg1->unk16 = 0;
            arg1->unk18 = 0;
            arg1->unk1A = 0;
            arg1->unk1C = 0;
            arg1->unk1E = 0;
            arg1->unk20 = 0;
        }
    }
}

s32 func_80070560(u8 *arg0, s32 arg1) {
    s32 temp_a0_2;
    s32 temp_v1;
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;
    s32 var_t2;
    u8 *var_t1;
    u8 temp_a0;

    var_t1 = arg0;
    var_t2 = 0x1F;
    var_a3 = 0;
    var_a2 = 0;
    var_t0 = arg1 - 1;
    if (arg1 != 0) {
        do {
            temp_a0 = *var_t1;
            var_t1 += 1;
            temp_v1 = var_a2 >> 9;
            var_a2 = (var_a2 + 5) * 0xD;
            temp_a0_2 = (temp_a0 ^ (temp_v1 & 0xFF)) << var_a3;
            var_a3 += 1;
            var_t2 += temp_a0_2;
            if (var_a3 >= 0x11) {
                var_a3 = 0;
            }
            var_t0 -= 1;
        } while (var_t0 != -1);
    }
    return var_t2;
}

s32 func_800705D0(s32 arg0) {
    return (arg0 + 0x103) & ~0xFF;
}

void func_800705E0(void) {

}
