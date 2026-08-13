#include "ultra64.h"
#include "audio.h"
void audioNodeInit(Unk *, s32, s32, s32);
extern s32 audioMixNodeCmd;
extern s32 audioMixCmd;

void audioMixNodeInit(AudioMixNode *arg0, s32 arg1, s32 arg2) {
    audioNodeInit((Unk *)arg0, &audioMixCmd, &audioMixNodeCmd, AUDIO_NODE_MIX);
    arg0->unk14      = 0;
    arg0->voiceCount = arg2;
    arg0->voiceBufPtr = arg1;
}
