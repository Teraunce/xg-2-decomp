#include "ultra64.h"
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
} UnkStruct_temp_v0;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
} UnkStruct_temp_v0_2;

s32 func_8006541C();                                  /* extern */

void func_80065274(void **arg0) {
    UnkStruct_temp_v0 *temp_v0;
    UnkStruct_temp_v0_2 *temp_v0_2;

    func_8006541C();
    temp_v0 = *arg0;
    *arg0 = temp_v0 + 8;
    temp_v0->unk0 = 0xE7000000;
    temp_v0->unk4 = 0;
    temp_v0_2 = *arg0;
    *arg0 = temp_v0_2 + 8;
    temp_v0_2->unk0 = 0xE3000C00;
    temp_v0_2->unk4 = 0x80000;
}
