#include "ultra64.h"
s32 func_8005CCE0(s32, s32, s32, s32, s32);                   /* extern */
extern s32 D_80092B88;
extern s32 D_80093F04;
extern s32 D_8016DF88;
extern s32 D_8016DFD8;
extern s32 D_80173C38;
extern s32 D_80173C3C;
extern s32 D_80174BEC;
extern s32 D_80174C28;
extern s32 D_8017C1A8;
extern s32 D_8017C940;
extern s32 D_8017C954;
extern s32 D_8017CA08;
extern s32 D_8017CDF0;

void func_80053F00(s32 arg0) {
    s32 var_a0;
    s32 var_a2;
    s32 temp_a0;
    s32 var_v0;
    s32 var_v0_2;
    s8 temp_v1;
    u16 temp_v1_2;

    var_v0 = *((arg0 * 4) + &D_8016DFD8);
    if (var_v0 < 0) {
        var_v0 = -var_v0;
    }
    if (var_v0 < 0x19) {
        temp_v1 = ((Unk*)((char*)&D_8017CA08 + (arg0 * 6)))->unk3;
        if (temp_v1 >= 0x19) {
            if (D_8017C954 > 0) {
                func_8005CCE0(0x18, 0x3F800000, 0x10000, 0x40, 0);
                var_v0_2 = D_8017C954 - 0xFF;
                goto block_9;
            }
        } else if ((temp_v1 < -0x18) && (D_8017C954 < 0xFF)) {
            func_8005CCE0(0x18, 0x3F800000, 0x10000, 0x40, 0);
            var_v0_2 = D_8017C954 + 0xFF;
block_9:
            D_8017C954 = var_v0_2;
        }
    }
    temp_v1_2 = *((arg0 * 6) + &D_8017CA08);
    temp_a0 = temp_v1_2 & ~*((arg0 * 4) + &D_8016DF88);
    if ((((temp_a0 & 0x20) && (temp_v1_2 & 0x10)) || ((temp_a0 & 0x10) && (temp_v1_2 & 0x20))) && (D_80092B88 & 0x4000)) {
        func_8005CCE0(0x19, 0x3F800000, 0x10000, 0x40, 0x20);
        D_80174BEC = D_80174BEC == 0;
        return;
    }
    if (*((arg0 * 6) + &D_8017CA08) & ~*((arg0 * 4) + &D_8016DF88) & 0x9000) {
        if (D_8017C1A8 < 0x80) {
            var_a0 = 0xF;
            if (D_8017C954 < 0x80) {
                var_a2 = 0xC350;
                D_8017C940 = 0;
                goto block_27;
            }
            var_a0 = 0x19;
            var_a2 = 0x10000;
            D_80173C38 = 0;
            D_80173C3C = 0;
            D_8017C1A8 = 0xFF;
            D_8017C954 = 0xFF;
        } else if (D_8017C954 < 0x80) {
            if (D_8017CDF0 == 0) {
                D_8017CDF0 = 1;
                if (D_80173C38 == 0) {
                    D_80174C28 = 1;
                }
            }
            var_a0 = 0x19;
            var_a2 = 0x10000;
            D_80093F04 = 0;
        } else {
            var_a0 = 0xF;
            var_a2 = 0xC350;
            D_8017C940 = 0;
            D_80173C38 = 0;
block_27:
            D_80093F04 = 0;
        }
        func_8005CCE0(var_a0, 0x3F800000, var_a2, 0x40, 0);
    }
}
