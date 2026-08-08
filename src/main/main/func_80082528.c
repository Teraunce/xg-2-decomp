#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x3C];
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
} UnkStruct_arg0;

void osSetTimer(void**, s32, s32);                  /* extern */

void midiSeqStop(UnkStruct_arg0 *arg0) {
    s32 sp24;
    s16 sp20;
    s32 temp_v0;

    temp_v0 = arg0->unk40;
    if (((Unk*)((arg0->unk3C * 0x30) + temp_v0))->unk28 == 0) {
        sp20 = 0;
        sp24 = (s32)((arg0->unk3C * 0x30) + temp_v0);
        osSetTimer(arg0 + 0x14, &sp20, 0);
    }
}
