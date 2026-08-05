#include "ultra64.h"
typedef struct {
    /* 0x00 */ char *unk0;
    /* 0x04 */ u8 pad04[0x1C];
    /* 0x20 */ s32 unk20;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad04[0xC];
    /* 0x10 */ s32 unk10;
} UnkStruct_arg1;

s32 osSetIntMask(s32, void *, void *);             /* extern */

void pendingFlushEnqueue(UnkStruct_arg0 *arg0, UnkStruct_arg1 *arg1) {
    s32 temp_a0;

    temp_a0 = osSetIntMask(1, arg0, NULL);
    arg1->unk10 = (s32) arg0->unk20;
    arg1->unk0 = (void *) arg0->unk0;
    arg0->unk0 = arg1;
    osSetIntMask(temp_a0, arg1, arg0);
}
