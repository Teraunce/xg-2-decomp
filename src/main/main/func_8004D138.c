#include "ultra64.h"
void osWritebackInvalDCache(u32, s32);                          /* extern */
void osWritebackDCache(u32, s32);                          /* extern */
s32 spTaskSubmit(Unk*, s32, s32, s32, s32, s32, s32);     /* extern */
extern s32 gRspDmaMesgQueue;

void gfxSpTaskWait(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp38;
    s32 sp20;

    osWritebackDCache(arg1, arg2);
    spTaskSubmit(&sp20, 0, 0, arg0, arg1, arg2, &gRspDmaMesgQueue);
    osRecvMesg(&gRspDmaMesgQueue, &sp38, 1);
    osWritebackInvalDCache(arg1, arg2);
}
