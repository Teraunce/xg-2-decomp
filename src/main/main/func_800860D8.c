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
    /* 0x00 */ u8 pad00[0xD8];
    /* 0xD8 */ s32 unkD8;
} UnkStruct_temp_a2;
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
} UnkStruct_temp_v0;

void audioTimerRelink(s32, s32);                    /* extern */
char *sfxEventDequeue(void *, void *);                /* extern */

void sfxStopAtEntity(UnkStruct_arg0 *arg0, UnkStruct_arg1 *arg1) {
    UnkStruct_temp_a0 *temp_a0;
    UnkStruct_temp_a2 *temp_a2;
    UnkStruct_temp_v0 *temp_v0;

    temp_a2 = arg1->unk8;
    if (temp_a2 != NULL) {
        if (temp_a2->unkD8 != 0) {
            temp_v0 = sfxEventDequeue(temp_a2, arg1);
            if (temp_v0 != NULL) {
                temp_v0->unk8 = 0;
                temp_v0->unk4 = (s32) (arg0->unk1C + ((Unk *)arg1->unk8)->unkD8);
                temp_v0->unkC = (void *) arg1->unk8;
                temp_a0 = ((Unk *)arg1->unk8)->unkC;
                ((s32(*)())(s32)temp_a0->unk8)(temp_a0, 3, temp_v0, arg1);
                goto block_5;
            }
        } else {
            audioTimerRelink(arg0, temp_a2);
block_5:
            arg1->unk8 = NULL;
        }
    }
}
