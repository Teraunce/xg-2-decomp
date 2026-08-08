#include "ultra64.h"
void osWritebackInvalDCache(u32, s32);                       /* extern */
s32 spTaskSubmit(Unk*, s32, s32, s32, s32, s32, s32);  /* extern */
extern s32 gRspDmaMesgQueue;
extern s32 gAudioDecodeCount;
extern s32 gAudioRspTask;
extern s32 gAudioDmaBuf;

void audioRspSubmit(Unk *arg0) {
    s32 temp_s1;
    u32 temp_a0;
    u32 var_s1;

    var_s1 = arg0->unk4;
    if (var_s1 >= 0x401U) {
        var_s1 = 0x400;
    }
    arg0->unk14 = var_s1;
    if (var_s1 != 0) {
        temp_s1 = (var_s1 + 7) & ~7;
        osWritebackInvalDCache(((1 - arg0->unk8) << 0xA) + &gAudioDmaBuf, temp_s1);
        spTaskSubmit(&gAudioRspTask, 0, 0, arg0->unk0, ((1 - arg0->unk8) << 0xA) + &gAudioDmaBuf, temp_s1, &gRspDmaMesgQueue);
        temp_a0 = arg0->unk14;
        gAudioDecodeCount += 1;
        arg0->unk0 = (s32) (arg0->unk0 + temp_a0);
        arg0->unk4 = (u32) (arg0->unk4 - temp_a0);
    }
}
