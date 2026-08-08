#include "ultra64.h"
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8 pad20[0x8];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ u8 pad30[0x8];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ s32 unk3C;
} UnkStruct_var_v0;

f32 cosf(f32);                             /* extern */
void guMtxIdent(f32);                               /* extern */
f32 sinf(f32);                             /* extern */
extern f64 gAudioPeriodConst;

void guPerspectiveF(char *arg0, s16 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 sp20;
    f32 sp1C;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa1;
    f32 temp_ft0;
    f32 temp_ft2;
    f32 temp_ft5;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_ft3;
    f32 var_ft4;
    f64 temp_fv0;
    s32 var_v1;
    u32 temp_t8;
    char *temp_v0;
    UnkStruct_var_v0 *var_v0;

    guMtxIdent(arg2);
    temp_fa1 = (f32) ((f64) arg2 * gAudioPeriodConst);
    temp_fa0 = temp_fa1 / 2.0f;
    sp1C = temp_fa0;
    sp20 = cosf(temp_fa0);
    temp_fv1 = sp20 / sinf(temp_fa0);
    temp_ft5 = arg4 + arg5;
    var_v0 = arg0;
    temp_fa0_2 = arg4 - arg5;
    var_v0->unk2C = -1.0f;
    var_v0->unk14 = temp_fv1;
    var_v0->unk28 = (f32) (temp_ft5 / temp_fa0_2);
    var_v0->unk0 = (f32) (temp_fv1 / arg3);
    var_v0->unk3C = 0.0f;
    var_v0->unk38 = (f32) ((2.0f * arg4 * arg5) / temp_fa0_2);
    var_v1 = 1;
    var_ft4 = var_v0->unk4;
    var_ft3 = var_v0->unk0 * arg6;
    var_fa0 = var_v0->unk8;
    var_fa1 = var_v0->unkC;
    if (1 != 4) {
        do {
            temp_ft2 = var_ft4 * arg6;
            var_ft4 = var_v0->unk14;
            temp_ft0 = var_fa0 * arg6;
            var_fa0 = var_v0->unk18;
            var_v1 += 1;
            temp_fv1_2 = var_fa1 * arg6;
            var_fa1 = var_v0->unk1C;
            var_v0->unk0 = var_ft3;
            var_ft3 = var_v0->unk10 * arg6;
            var_v0->unk4 = temp_ft2;
            var_v0->unk8 = temp_ft0;
            var_v0 += 0x10;
            (*(f32 *)((char *)(var_v0) - 0x4)) = temp_fv1_2;
        } while (var_v1 != 4);
    }
    temp_v0 = var_v0 + 0x10;
    (*(f32 *)((char *)(temp_v0) - 0x10)) = var_ft3;
    (*(f32 *)((char *)(temp_v0) - 0xC)) = (f32) (var_ft4 * arg6);
    (*(f32 *)((char *)(temp_v0) - 0x8)) = (f32) (var_fa0 * arg6);
    (*(f32 *)((char *)(temp_v0) - 0x4)) = (f32) (var_fa1 * arg6);
    if (arg1 != NULL) {
        temp_fv0 = (f64) temp_ft5;
        if (temp_fv0 <= 2.0) {
            *arg1 = 0xFFFF;
            return;
        }
        temp_t8 = (u32) (131072.0 / temp_fv0);
        *arg1 = (s16) temp_t8;
        if ((temp_t8 & 0xFFFF) <= 0) {
            *arg1 = 1;
        }
    }
}
