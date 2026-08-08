#include "ultra64.h"
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8 pad20[0x8];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ u8 pad2C[0x4];
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ s32 unk3C;
} UnkStruct_var_v0;

void guMtxIdent(char *);                         /* extern */

void guOrthoF(char *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 temp_fa0;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft3;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_ft4;
    f32 var_ft5;
    s32 var_v1;
    char *temp_v0;
    UnkStruct_var_v0 *var_v0;

    guMtxIdent(arg0);
    temp_fv0 = arg2 - arg1;
    var_v0 = arg0;
    temp_fa0 = arg6 - arg5;
    var_v0->unk0 = (f32) (2.0f / temp_fv0);
    temp_fv1 = arg4 - arg3;
    var_v0->unk28 = (f32) (-2.0f / temp_fa0);
    var_v0->unk14 = (f32) (2.0f / temp_fv1);
    var_v0->unk30 = (f32) (-(arg2 + arg1) / temp_fv0);
    var_v0->unk34 = (f32) (-(arg4 + arg3) / temp_fv1);
    var_v0->unk3C = 1.0f;
    var_v0->unk38 = (f32) (-(arg6 + arg5) / temp_fa0);
    var_v1 = 1;
    var_ft5 = var_v0->unk4;
    var_fa0 = var_v0->unk0 * arg7;
    var_fa1 = var_v0->unk8;
    var_ft4 = var_v0->unkC;
    if (1 != 4) {
        do {
            temp_ft3 = var_ft5 * arg7;
            var_ft5 = var_v0->unk14;
            temp_ft1 = var_fa1 * arg7;
            var_fa1 = var_v0->unk18;
            var_v1 += 1;
            temp_ft0 = var_ft4 * arg7;
            var_ft4 = var_v0->unk1C;
            var_v0->unk0 = var_fa0;
            var_fa0 = var_v0->unk10 * arg7;
            var_v0->unk4 = temp_ft3;
            var_v0->unk8 = temp_ft1;
            var_v0 += 0x10;
            (*(f32 *)((char *)(var_v0) - 0x4)) = temp_ft0;
        } while (var_v1 != 4);
    }
    temp_v0 = var_v0 + 0x10;
    (*(f32 *)((char *)(temp_v0) - 0x10)) = var_fa0;
    (*(f32 *)((char *)(temp_v0) - 0xC)) = (f32) (var_ft5 * arg7);
    (*(f32 *)((char *)(temp_v0) - 0x8)) = (f32) (var_fa1 * arg7);
    (*(f32 *)((char *)(temp_v0) - 0x4)) = (f32) (var_ft4 * arg7);
}
