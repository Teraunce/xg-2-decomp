#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x14];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
} UnkStruct_arg0;

void audioNodeInit(void *, void *, void *, s32);
extern s32 audioNoteWrite;
extern s32 func_80084F48;

void func_80082EDC(UnkStruct_arg0 *arg0, s32 arg1, s32 arg2) {
    audioNodeInit(arg0, &func_80084F48, &audioNoteWrite, 7);
    arg0->unk14 = 0;
    arg0->unk18 = arg2;
    arg0->unk1C = arg1;
}
