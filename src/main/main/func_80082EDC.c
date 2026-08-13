#include "ultra64.h"
#include "audio.h"
void audioNodeInit(Unk *, s32, s32, s32);
extern s32 audioNoteWrite;
extern s32 audioNoteWriteCmd;

void audioNoteWriteNodeInit(AudioNoteWriteNode *arg0, s32 arg1, s32 arg2) {
    audioNodeInit((Unk *)arg0, &audioNoteWriteCmd, &audioNoteWrite, AUDIO_NODE_NOTEWRITE);
    arg0->writeIdx   = 0;
    arg0->voiceCount = arg2;
    arg0->bufPtr     = arg1;
}
