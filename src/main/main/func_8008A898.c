#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x60];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x01 */ s32 unk1;
} UnkStruct_arg3;

s32 contPakReadWriteNote(Unk*, Unk*, u8, u8);              /* extern */

s32 contPakWriteNote(UnkStruct_arg0 *arg0, u8 *arg1, s32 arg2, UnkStruct_arg3 *arg3) {
    s32 sp1C;
    u8 temp_t7;
    u8 temp_t9;

    temp_t9 = arg3->unk0;
    if (*arg1 != temp_t9) {
        *arg1 = temp_t9;
        sp1C = contPakReadWriteNote(arg0, arg2, 0, *arg1);
        if (sp1C != 0) {
            return sp1C;
        }
    }
    arg3->unk0 = (u16) *(u16*)(s32)(arg2 + (arg3->unk1 * 2));
    if (((s32) (u16) arg3->unk0 < arg0->unk60) || ((s32) arg3->unk0 >= (s32) arg0->unk64) || (temp_t7 = arg3->unk1, ((s32) temp_t7 <= 0)) || ((s32) temp_t7 >= 0x80)) {
        if ((u16) arg3->unk0 == 1) {
            return 5;
        }
        return 3;
    }
    return 0;
}
