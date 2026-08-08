#include "ultra64.h"
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad04[0x24];
    /* 0x28 */ s32 unk28;
} UnkStruct_sp44;
typedef struct {
    /* 0x00 */ s32 unk0;
} UnkStruct_var_t5;

s32 crc5Calc(s32);                             /* extern */
extern s32 D_8018ADB8;
extern s32 D_8018ADF4;

void siSetupWriteCmd(s32 arg0, u16 arg1, u8 *arg2) {
    Unk *sp = (Unk*)0;
    UnkStruct_sp44 *sp44;
    s8 sp42;
    s16 sp20;
    s8 sp1F;
    s8 sp1E;
    s8 sp1D;
    s8 sp1C;
    s32 sp18;
    UnkStruct_var_t5 *var_t5;
    s32 temp_at;
    s32 temp_t0;
    s32 temp_t3;
    s32 temp_t7;
    s32 temp_v0;
    s8 *temp_t8;
    Unk *var_t6;

    sp44 = &D_8018ADB8;
    sp18 = 0;
    do {
        *(&D_8018ADB8 + (sp18 * 4)) = 0;
        temp_t0 = sp18 + 1;
        sp18 = temp_t0;
    } while (temp_t0 < 0x10);
    D_8018ADF4 = 1;
    sp1C = 0xFF;
    sp1D = 0x23;
    sp1E = 1;
    sp1F = 3;
    temp_v0 = crc5Calc(arg1);
    sp42 = 0xFF;
    sp20 = temp_v0 | (arg1 << 5);
    sp18 = 0;
    do {
        ((Unk *)(sp + sp18))->unk22 = (u8) *arg2;
        temp_t7 = sp18 + 1;
        sp18 = temp_t7;
        arg2 += 1;
    } while (temp_t7 < 0x20);
    if (arg0 != 0) {
        sp18 = 0;
        if (arg0 > 0) {
            do {
                sp44->unk0 = 0;
                temp_t3 = sp18 + 1;
                sp18 = temp_t3;
                sp44 += 1;
            } while (temp_t3 < arg0);
        }
    }
    var_t6 = &sp1C;
    temp_t8 = var_t6 + 0x24;
    var_t5 = sp44;
    do {
        temp_at = var_t6->unk0;
        var_t6 += 0xC;
        var_t5 += 0xC;
        (*(f32 *)((char *)(var_t5) - 0xC)) = (s32) temp_at;
        (*(f32 *)((char *)(var_t5) - 0x8)) = (s32) (*(f32 *)((char *)(var_t6) - 0x8));
        (*(f32 *)((char *)(var_t5) - 0x4)) = (s32) (*(f32 *)((char *)(var_t6) - 0x4));
    } while ((char*)var_t6 != temp_t8);
    var_t5->unk0 = (s32) var_t6->unk0;
    sp44 += 0x28;
    sp44->unk28 = 0xFE;
}
