#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x1C];
    /* 0x1C */ s32 unk1C;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ char *unk8;
} UnkStruct_arg1;
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ s32 unk8;
} UnkStruct_temp_a0;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ f32 unkC;
} UnkStruct_temp_v0;

char *sfxEventDequeue();                              /* extern */

void sfxPlayLoopAtEntity(UnkStruct_arg0 *arg0, UnkStruct_arg1 *arg1, f32 arg2) {
    UnkStruct_temp_a0 *temp_a0;
    UnkStruct_temp_v0 *temp_v0;

    if (arg1->unk8 != 0) {
        temp_v0 = sfxEventDequeue();
        if (temp_v0 != NULL) {
            temp_v0->unk8 = 7;
            temp_v0->unk4 = (s32) (arg0->unk1C + ((Unk *)arg1->unk8)->unkD8);
            temp_v0->unk0 = 0;
            temp_v0->unkC = arg2;
            temp_a0 = ((Unk *)arg1->unk8)->unkC;
            ((s32(*)())(s32)temp_a0->unk8)(temp_a0, 3, temp_v0, arg1);
        }
    }
}
