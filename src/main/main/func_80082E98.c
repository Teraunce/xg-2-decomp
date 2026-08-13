#include "ultra64.h"
#include "audio.h"
void audioNodeInit(Unk *, s32, s32, s32);
extern s32 audioNodeSetProp;
extern s32 audioTimerNodeCmd;

void audioTimerNodeInit(AudioTimerNode *arg0) {
    audioNodeInit((Unk *)arg0, &audioTimerNodeCmd, &audioNodeSetProp, AUDIO_NODE_TIMER);
    arg0->unk14 = 0;
    arg0->unk18 = 1;
}
