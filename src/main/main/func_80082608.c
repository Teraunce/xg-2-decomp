#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x3C];
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
} UnkStruct_arg0;

void osSetTimer(void **, s32, s32);           /* extern */

void func_80082608(UnkStruct_arg0 *arg0, f32 arg1) {
    f32 sp28;
    s32 sp24;
    s16 sp20;

    sp20 = 4;
    sp24 = (arg0->unk3C * 0x30) + arg0->unk40;
    sp28 = arg1;
    osSetTimer((void **)(arg0 + 0x14), &sp20, 0);
}

void func_80082668(UnkStruct_arg0 *arg0, s16 arg1, s32 arg2) {
    ((Unk*)(arg0->unk40 + (arg1 * 0x30)))->unk20 = (s16) (arg2 & 0xFF);
}
