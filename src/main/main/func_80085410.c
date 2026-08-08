#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x2];
    /* 0x02 */ s32 unk2;
    /* 0x06 */ u8 pad06[0x22];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_arg3;
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
} UnkStruct_sp18;

s32 osVirtualToPhysical(u32);                             /* extern */

char *audioGeomRspCmd(UnkStruct_arg0 *arg0, s32 arg1, s32 arg2, UnkStruct_arg3 *arg3) {
    char *sp24;
    UnkStruct_sp18 *sp18;
    s32 temp_v0;
    char *temp_v1;

    temp_v0 = arg1 & 0xFFFF;
    arg3->unk4 = (s32) ((temp_v0 << 0x10) | ((arg2 * 2) & 0xFFFF));
    arg3->unk0 = (s32) (temp_v0 | 0x08000000);
    arg3->unk8 = 0x0B000020;
    temp_v1 = arg3 + 0x10;
    arg3->unkC = osVirtualToPhysical(arg0 + 8);
    sp24 = temp_v1 + 8;
    arg3->unk10 = (s32) (((arg0->unk2C & 0xFF) << 0x10) | 0x0E000000 | (arg0->unk2 & 0xFFFF));
    sp18 = temp_v1;
    sp18->unk4 = osVirtualToPhysical(arg0->unk28);
    arg0->unk2C = 0;
    return sp24;
}
