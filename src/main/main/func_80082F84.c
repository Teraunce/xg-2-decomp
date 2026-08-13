#include "ultra64.h"
#include "audio.h"
s32 audioHeapAlloc(s32, s32, s32, s32, s32);
void audioNodeInit(Unk *, s32, s32, s32);
extern s32 audioNodeCmdGetter;
extern s32 audioVoiceNodeCmd;

void audioVoiceNodeInit(AudioVoiceNode *arg0, s32 arg1) {
    audioNodeInit((Unk *)arg0, &audioVoiceNodeCmd, &audioNodeCmdGetter, AUDIO_NODE_VOICE);
    arg0->pcmBufPtr = audioHeapAlloc(0, 0, arg1, 1, 0x20);
    arg0->unk24     = 1;
    arg0->unk30     = 0;
    arg0->unk1C     = 0;
    arg0->unk28     = 0;
    arg0->unk2C     = 0;
    arg0->unk20     = 0.0f;
    arg0->gain      = 1.0f;
}
