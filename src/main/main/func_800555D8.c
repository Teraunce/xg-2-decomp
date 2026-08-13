#include "ultra64.h"
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);        /* extern */
void osStartThread(Unk*);                               /* extern */
extern s32 gGameMesgQueue;
extern s32 gGameThread;
extern s32 gGameMsgBuf;
extern Unk gGameThreadArgs;
extern s32 gameThreadEntry;

void gameThreadInit(s32 arg0) {
    osCreateMesgQueue(&gGameMesgQueue, &gGameMsgBuf, 0x20);
    gGameThreadArgs.unk0 = arg0;
    gGameThreadArgs.unk4 = &gGameMesgQueue;
    osCreateThread(&gGameThread, 4, &gameThreadEntry, &gGameThreadArgs, &gGameThread, 7);
    osStartThread(&gGameThread);
}
