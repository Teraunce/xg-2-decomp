#include "ultra64.h"
#include "audio.h"
s32 audioHeapAlloc(s32, s32, s32, s32, s32);
void audioNodeInit(Unk *, s32, s32, s32);
extern s32 audioAdpcmNodeCmd;
extern s32 audioAdpcmCmd;

void audioAdpcmNodeInit(AudioAdpcmNode *arg0, s32 (*arg1)(void *), s32 arg2) {
    audioNodeInit((Unk *)arg0, &audioAdpcmCmd, &audioAdpcmNodeCmd, AUDIO_NODE_ADPCM);
    arg0->inBufPtr    = audioHeapAlloc(0, 0, arg2, 1, 0x20);
    arg0->outBufPtr   = audioHeapAlloc(0, 0, arg2, 1, 0x20);
    arg0->initResult  = arg1(arg0->decodeCtx);
    arg0->unk3C       = 0;
    arg0->unk40       = 1;
    arg0->unk44       = 0;
}
