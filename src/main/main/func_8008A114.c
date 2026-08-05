#include "ultra64.h"
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad04[0x24];
    /* 0x28 */ s32 unk28;
} UnkStruct_sp44;
typedef struct {
    /* 0x00 */ s32 unk0;
} UnkStruct_var_t2;

s32 func_80089018(s32);                             /* extern */
extern s32 D_8018ADB8;
extern s32 D_8018ADF4;

void func_8008A114(s32 arg0, u16 arg1) {
    Unk *sp = (Unk*)0;
    UnkStruct_sp44 *sp44;
    s8 sp42;
    s16 sp20;
    s8 sp1F;
    s8 sp1E;
    s8 sp1D;
    s8 sp1C;
    s32 sp18;
    UnkStruct_var_t2 *var_t2;
    s32 temp_at;
    s32 temp_t0;
    s32 temp_t0_2;
    s32 temp_t4;
    s32 temp_v0;
    s8 *temp_t5;
    Unk *var_t3;

    sp44 = &D_8018ADB8;
    sp18 = 0;
    do {
        *(&D_8018ADB8 + (sp18 * 4)) = 0;
        temp_t0 = sp18 + 1;
        sp18 = temp_t0;
    } while (temp_t0 < 0x10);
    D_8018ADF4 = 1;
    sp1C = 0xFF;
    sp1D = 3;
    sp1E = 0x21;
    sp1F = 2;
    temp_v0 = func_80089018(arg1);
    sp42 = 0xFF;
    sp20 = temp_v0 | (arg1 << 5);
    sp18 = 0;
    do {
        ((Unk *)(sp + sp18))->unk22 = 0xFF;
        temp_t4 = sp18 + 1;
        sp18 = temp_t4;
    } while (temp_t4 < 0x20);
    if (arg0 != 0) {
        sp18 = 0;
        if (arg0 > 0) {
            do {
                sp44->unk0 = 0;
                temp_t0_2 = sp18 + 1;
                sp18 = temp_t0_2;
                sp44 += 1;
            } while (temp_t0_2 < arg0);
        }
    }
    var_t3 = &sp1C;
    temp_t5 = var_t3 + 0x24;
    var_t2 = sp44;
    do {
        temp_at = var_t3->unk0;
        var_t3 += 0xC;
        var_t2 += 0xC;
        (*(f32 *)((char *)(var_t2) - 0xC)) = (s32) temp_at;
        (*(f32 *)((char *)(var_t2) - 0x8)) = (s32) (*(f32 *)((char *)(var_t3) - 0x8));
        (*(f32 *)((char *)(var_t2) - 0x4)) = (s32) (*(f32 *)((char *)(var_t3) - 0x4));
    } while ((char*)var_t3 != (char*)temp_t5);
    var_t2->unk0 = (s32) var_t3->unk0;
    sp44 += 0x28;
    sp44->unk28 = 0xFE;
}
