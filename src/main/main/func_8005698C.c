#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ f32 unk3C;
} UnkStruct_arg0;

f32 func_80079DB8(f32);                             /* extern */
f32 func_8007B5A8(f32);                             /* extern */
extern f32 D_8004BD8C;

void func_8005698C(UnkStruct_arg0 *arg0) {
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fv0;

    temp_fs0 = (s32)M2C_ERROR(/* Read from unset register $f6 */) * (s32)M2C_ERROR(/* Read from unset register $f0 */);
    temp_fs0_2 = func_8007B5A8(temp_fs0);
    temp_fv0 = func_80079DB8(temp_fs0);
    arg0->unk0 = temp_fv0;
    arg0->unk4 = (f32) -temp_fs0_2;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk10 = temp_fs0_2;
    arg0->unk14 = temp_fv0;
    arg0->unk18 = 0;
    arg0->unk1C = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk30 = 0;
    arg0->unk34 = 0;
    arg0->unk38 = 0;
    arg0->unk28 = (f32) D_8004BD8C;
    arg0->unk3C = (f32) D_8004BD8C;
}
