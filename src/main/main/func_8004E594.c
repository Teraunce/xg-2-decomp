#include "ultra64.h"
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 pad0C[0xE4];
    /* 0xF0 */ s32 unkF0;
    /* 0xF4 */ s32 unkF4;
    /* 0xF8 */ s32 unkF8;
    /* 0xFC */ s32 unkFC;
} UnkStruct_arg0;

void sfxChannelClear(char*);                               /* extern */
extern f32 D_8004BB18;

void sfxEntityInit(UnkStruct_arg0 *arg0) {
    sfxChannelClear(0);
    sfxChannelClear(arg0 + 0x78);
    arg0->unkF0 = 1;
    arg0->unkF4 = 0;
    arg0->unkF8 = 7;
    arg0->unkFC = 7;
}

void velStateInit(UnkStruct_arg0 *arg0) {
    arg0->unk0 = 0;
    arg0->unk8 = 0;
    arg0->unk4 = (f32) D_8004BB18;
}
