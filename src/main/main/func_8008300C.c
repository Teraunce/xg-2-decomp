#include "ultra64.h"
s32 audioHeapAlloc(s32, s32, s32, s32, s32);               /* extern */
void audioNodeInit(Unk*, s32, s32, s32);              /* extern */
extern s32 audioAdpcmNodeCmd;
extern s32 audioAdpcmCmd;

void audioAdpcmNodeInit(Unk *arg0, s32 (*arg1)(void *), s32 arg2) {
    audioNodeInit(arg0, &audioAdpcmCmd, &audioAdpcmNodeCmd, 0);
    arg0->unk14 = audioHeapAlloc(0, 0, arg2, 1, 0x20);
    arg0->unk18 = audioHeapAlloc(0, 0, arg2, 1, 0x20);
    arg0->unk30 = arg1(arg0 + 0x34);
    arg0->unk3C = 0;
    arg0->unk40 = 1;
    arg0->unk44 = 0;
}
