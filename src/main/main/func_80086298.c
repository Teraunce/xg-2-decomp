#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x1C];
    /* 0x1C */ s32 unk1C;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ char *unk8;
    /* 0x0C */ u8 pad0C[0xE];
    /* 0x1A */ s32 unk1A;
} UnkStruct_arg1;
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ s32 unk8;
} UnkStruct_temp_a0;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x12 */ s32 unk12;
    /* 0x13 */ s32 unk13;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_temp_v0;

s32 func_800827C0(UnkStruct_arg0*, s32);                      /* extern */
char *sfxEventDequeue();                              /* extern */

void func_80086298(UnkStruct_arg0 *arg0, UnkStruct_arg1 *arg1, s32 arg2, f32 arg3, s16 arg4, u8 arg5, u8 arg6, s32 arg7) {
    char *sp1C;
    u8 var_v1;
    UnkStruct_temp_a0 *temp_a0;
    UnkStruct_temp_v0 *temp_v0;

    if (arg1->unk8 != 0) {
        temp_v0 = sfxEventDequeue();
        if (temp_v0 != NULL) {
            var_v1 = arg6;
            if ((s32) var_v1 < 0) {
                var_v1 = -(s32) var_v1 & 0xFF;
            }
            temp_v0->unk0 = 0;
            temp_v0->unk8 = 0xD;
            temp_v0->unk4 = (s32) (arg0->unk1C + ((Unk *)arg1->unk8)->unkD8);
            temp_v0->unkA = (s16) arg1->unk1A;
            temp_v0->unk12 = arg5;
            temp_v0->unk13 = var_v1;
            temp_v0->unk10 = arg4;
            temp_v0->unkC = arg3;
            sp1C = temp_v0;
            temp_v0->unk14 = func_800827C0(arg0, arg7);
            temp_v0->unk18 = arg2;
            temp_a0 = ((Unk *)arg1->unk8)->unkC;
            ((s32(*)())(s32)temp_a0->unk8)(temp_a0, 3, temp_v0, arg1);
        }
    }
}
