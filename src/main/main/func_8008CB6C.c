#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x3C];
    /* 0x3C */ s32 unk3C;
} UnkStruct_arg3;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad04[0x24];
    /* 0x28 */ s32 unk28;
} UnkStruct_sp44;
typedef struct {
    /* 0x00 */ s32 unk0;
} UnkStruct_var_t7;

s32 func_80089018(s32);                             /* extern */

void func_8008CB6C(s32 arg0, u16 arg1, u8 *arg2, UnkStruct_arg3 *arg3) {
    char sp_buf[64];
    char *sp = sp_buf; /* $sp base — local stack byte-pointer */
    UnkStruct_sp44 *sp44;
    s8 sp42;
    s16 sp20;
    s8 sp1F;
    s8 sp1E;
    s8 sp1D;
    s8 sp1C;
    s32 sp18;
    s32 temp_at;
    s32 temp_t0;
    s32 temp_t2;
    s32 temp_t6;
    s32 temp_v0;
    s8 *temp_t1;
    Unk *var_t9;
    UnkStruct_var_t7 *var_t7;

    sp18 = 0;
    sp44 = arg3;
    do {
        ((s32*)arg3)[sp18] = 0;
        temp_t2 = sp18 + 1;
        sp18 = temp_t2;
    } while (temp_t2 < 0xF);
    arg3->unk3C = 1;
    sp1C = 0xFF;
    sp1D = 0x23;
    sp1E = 1;
    sp1F = 3;
    temp_v0 = func_80089018(arg1);
    sp42 = 0xFF;
    sp20 = temp_v0 | (arg1 << 5);
    sp18 = 0;
    do {
        ((Unk *)(sp + sp18))->unk22 = (u8) *arg2;
        temp_t0 = sp18 + 1;
        sp18 = temp_t0;
        arg2 += 1;
    } while (temp_t0 < 0x20);
    if (arg0 != 0) {
        sp18 = 0;
        if (arg0 > 0) {
            do {
                sp44->unk0 = 0;
                temp_t6 = sp18 + 1;
                sp18 = temp_t6;
                sp44 += 1;
            } while (temp_t6 < arg0);
        }
    }
    var_t9 = &sp1C;
    temp_t1 = var_t9 + 0x24;
    var_t7 = sp44;
    do {
        temp_at = var_t9->unk0;
        var_t9 += 0xC;
        var_t7 += 0xC;
        (*(f32 *)((char *)(var_t7) - 0xC)) = (s32) temp_at;
        (*(f32 *)((char *)(var_t7) - 0x8)) = (s32) (*(f32 *)((char *)(var_t9) - 0x8));
        (*(f32 *)((char *)(var_t7) - 0x4)) = (s32) (*(f32 *)((char *)(var_t9) - 0x4));
    } while ((void*)var_t9 != (void*)temp_t1);
    var_t7->unk0 = (s32) var_t9->unk0;
    sp44 += 0x28;
    sp44->unk28 = 0xFE;
}
