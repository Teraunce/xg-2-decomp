#include "ultra64.h"
void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);        /* extern */
void osStartThread(Unk*);                               /* extern */
extern s32 gLineTexPtr;
extern s32 gFrameInitFlag;
extern s32 gFrameMesgQueue;
extern s32 gFrameStack;
extern s32 gFrameThread;
extern s32 gFrameMsgBuf;
extern Unk gFrameThreadArg;
extern Unk *gLineTexBase;
extern s32 frameDispatchThread;

void frameThreadInit(s32 arg0) {
    osCreateMesgQueue(&gFrameMesgQueue, &gFrameMsgBuf, 0x20);
    gFrameThreadArg.unk0 = arg0;
    gFrameThreadArg.unk4 = &gFrameMesgQueue;
    osCreateThread(&gFrameThread, 5, &frameDispatchThread, &gFrameThreadArg, &gFrameStack, 8);
    osStartThread(&gFrameThread);
}

void gfxAddLineTex(s32 arg1, s8 arg2, s8 arg3, u16 arg4, u16 arg5, u16 arg6) {
    Unk *var_v1;
    u32 var_a0;
    Unk *temp_v0;
    Unk *temp_v0_2;

    if (gFrameInitFlag != 0) {
        var_a0 = 0;
        var_v1 = gLineTexBase;
        do {
            *(s32 *)var_v1 = 0;
            var_a0 += 1;
            var_v1 += 0x10;
        } while (var_a0 < 0x20U);
        gFrameInitFlag = 0;
    }
    temp_v0 = (gLineTexPtr * 0x10) + gLineTexBase;
    temp_v0->unk0 = arg1;
    temp_v0->unkA = arg2;
    ((gLineTexPtr * 0x10) + gLineTexBase)->unkB = arg3;
    temp_v0_2 = (gLineTexPtr * 0x10) + gLineTexBase;
    temp_v0_2->unk4 = arg4;
    temp_v0_2->unk6 = arg5;
    temp_v0_2->unk8 = arg6;
}
