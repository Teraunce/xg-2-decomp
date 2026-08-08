#include "ultra64.h"
void guLookAtHiliteF(Unk *, Unk *, f32, f32, f32, f32, f32, f32, f32, f32, f32); /* extern */
void guMtxF2L(char *arg0, char *arg1);            /* static */

void guLookAtHilite(char *arg0, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10) {
    s32 sp38;

    guLookAtHiliteF(arg3, &sp38, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
    guMtxF2L(&sp38, arg0);
}

void guMtxF2L(char *arg0, char *arg1) {
    char *var_a3;
    Unk *var_t0;
    f32 var_ft4;
    f32 var_ft5;
    s32 temp_fa0;
    s32 temp_fa0_2;
    s32 temp_fa1;
    s32 temp_fa1_2;
    s32 var_a0;
    s32 var_a2;
    Unk *var_v0;
    Unk *var_v1;

    var_v0 = arg1;
    var_v1 = arg1 + 0x20;
    var_a2 = 0;
    var_a3 = arg0;
    do {
        var_t0 = var_a3;
        var_a0 = 1;
        var_ft5 = var_t0->unk0;
        var_ft4 = var_t0->unk4 * 65536.0f;
        if (1 != 2) {
            do {
                var_a0 += 1;
                var_v0 += 4;
                var_v1 += 4;
                var_t0 += 8;
                temp_fa0 = (s32) var_ft4;
                temp_fa1 = (s32) (var_ft5 * 65536.0f);
                *(f32*)((char*)var_v0 - 4)= (s32) ((temp_fa1 & 0xFFFF0000) | ((temp_fa0 >> 0x10) & 0xFFFF));
                *(f32*)((char*)var_v1 - 4)= (s32) (((temp_fa1 << 0x10) & 0xFFFF0000) | (temp_fa0 & 0xFFFF));
                var_ft5 = var_t0->unk0;
                var_ft4 = var_t0->unk4 * 65536.0f;
            } while (var_a0 != 2);
        }
        var_v0 += 4;
        var_v1 += 4;
        temp_fa0_2 = (s32) var_ft4;
        temp_fa1_2 = (s32) (var_ft5 * 65536.0f);
        *(f32*)((char*)var_v0 - 4)= (s32) ((temp_fa1_2 & 0xFFFF0000) | ((temp_fa0_2 >> 0x10) & 0xFFFF));
        *(f32*)((char*)var_v1 - 4)= (s32) (((temp_fa1_2 << 0x10) & 0xFFFF0000) | (temp_fa0_2 & 0xFFFF));
        var_a2 += 1;
        var_a3 += 0x10;
    } while (var_a2 != 4);
}

void guMtxIdent(char *arg0) {
    s32 var_v0;
    Unk *var_v1;

    var_v1 = arg0;
    var_v0 = 0;
    do {
        if (var_v0 == 0) {
            var_v1->unk0 = 1.0f;
        } else {
            var_v1->unk0 = 0.0f;
        }
        if (var_v0 == 1) {
            var_v1->unk4 = 1.0f;
        } else {
            var_v1->unk4 = 0.0f;
        }
        if (var_v0 == 2) {
            var_v1->unk8 = 1.0f;
        } else {
            var_v1->unk8 = 0.0f;
        }
        if (var_v0 == 3) {
            var_v1->unkC = 1.0f;
        } else {
            var_v1->unkC = 0.0f;
        }
        var_v0 += 1;
        var_v1 += 0x10;
    } while (var_v0 != 4);
}
