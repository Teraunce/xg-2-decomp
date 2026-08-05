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
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad04[0xC];
    /* 0x10 */ s32 unk10;
} UnkStruct_sp1C;
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ s32 unk8;
} UnkStruct_temp_a0;
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
} UnkStruct_temp_v0;

s32 sfxComputePitch(UnkStruct_arg0*, s32);                     /* extern */
char *sfxEventDequeue();                              /* extern */

void sfxPlayAtEntity(UnkStruct_arg0 *arg0, UnkStruct_arg1 *arg1, s16 arg2, s32 arg3) {
    UnkStruct_sp1C *sp1C;
    UnkStruct_temp_a0 *temp_a0;
    UnkStruct_temp_v0 *temp_v0;

    if (arg1->unk8 != 0) {
        temp_v0 = sfxEventDequeue();
        if (temp_v0 != NULL) {
            temp_v0->unk8 = 0xB;
            temp_v0->unk4 = (s32) (arg0->unk1C + ((Unk *)arg1->unk8)->unkD8);
            temp_v0->unkC = (s32) arg2;
            sp1C = temp_v0;
            sp1C->unk10 = sfxComputePitch(arg0, arg3);
            sp1C->unk0 = 0;
            temp_a0 = ((Unk *)arg1->unk8)->unkC;
            ((s32(*)())(s32)temp_a0->unk8)(temp_a0, 3, sp1C);
        }
    }
}
