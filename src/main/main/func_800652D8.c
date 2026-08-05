#include "ultra64.h"
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
} UnkStruct_temp_v0;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
} UnkStruct_temp_v0_2;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
} UnkStruct_temp_v0_3;

s32 sfxGetState();                                  /* extern */
extern s32 D_80182E78;
extern s32 D_80182E80;

void func_800652D8(void **arg0) {
    UnkStruct_temp_v0 *temp_v0;
    UnkStruct_temp_v0_2 *temp_v0_2;
    UnkStruct_temp_v0_3 *temp_v0_3;

    sfxGetState();
    temp_v0 = *arg0;
    *arg0 = temp_v0 + 8;
    temp_v0->unk0 = 0xE7000000;
    temp_v0->unk4 = 0;
    temp_v0_2 = *arg0;
    *arg0 = temp_v0_2 + 8;
    temp_v0_2->unk0 = 0xE3000C00;
    temp_v0_2->unk4 = 0;
    temp_v0_3 = *arg0;
    *arg0 = temp_v0_3 + 8;
    temp_v0_3->unk0 = 0xFC119623;
    temp_v0_3->unk4 = 0xFF2FFFFF;
    D_80182E80 = 0;
    D_80182E78 = 0;
}
