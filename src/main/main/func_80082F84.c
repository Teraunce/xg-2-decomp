#include "ultra64.h"
s32 audioHeapAlloc(s32, s32, s32, s32, s32);               /* extern */
void audioNodeInit(Unk*, s32, s32, s32);              /* extern */
extern s32 audioNodeCmdGetter;
extern s32 audioVoiceNodeCmd;

void audioVoiceNodeInit(Unk *arg0, s32 arg1) {
    audioNodeInit(arg0, &audioVoiceNodeCmd, &audioNodeCmdGetter, 1);
    arg0->unk14 = audioHeapAlloc(0, 0, arg1, 1, 0x20);
    arg0->unk24 = 1;
    arg0->unk30 = 0;
    arg0->unk1C = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk20 = 0.0f;
    arg0->unk18 = 1.0f;
}
