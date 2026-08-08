#include "ultra64.h"
void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);        /* extern */
void osStartThread(Unk*);                               /* extern */
extern s32 gContPakThread;
extern s32 gContPakMesgQueue;
extern s32 gEntityMsg;
extern s32 gHandlerMsgBuf;
extern s32 gHandlerMsgQueue;
extern s32 gEntityMesgQueue;
extern Unk gHandlerCtx;
extern s32 contPakHandlerWait;

void contPakThreadInit(s32 arg0) {
    gContPakMesgQueue = arg0;
    osCreateMesgQueue(&gHandlerMsgQueue, &gHandlerMsgBuf, 8);
    osCreateMesgQueue(&gEntityMesgQueue, &gEntityMsg, 1);
    osCreateThread(&gContPakThread, 5, &contPakHandlerWait, 0, &gContPakMesgQueue, 5);
    gHandlerCtx.unk16C = 1;
    gHandlerCtx.unk160 = -1;
    osStartThread(&gContPakThread);
}
