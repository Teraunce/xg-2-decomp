#include "ultra64.h"
void viInit(Unk*, s32, s32, s32, s32, s32, s32);       /* extern */
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);          /* extern */
void osSetThreadPri(Unk*, s32);                              /* extern */
void osStartThread(Unk*);                               /* extern */
void viMgrInitGetter(s32);                                 /* extern */
void osViSetMode(char*);                               /* extern */
void osViSetYScale(s32);                                 /* extern */
void viSetFieldBit(u8);                                 /* extern */
void osEPiLoad(s32, char*, char*, s32);                    /* extern */
extern s32 gGameLoopStack;
extern s32 gViModeStruct;
extern s32 gEPiLoadSrc;
extern s32 gEPiLoadDst;
extern s32 gGameLoopThread;
extern s32 gameMainLoop_setup;

void gameMainThread(void) {
    viMgrInitGetter(0xFE);
    viInit(&gViModeStruct, 0x140, 0xF0, 0, 0, 0, 0);
    osViSetMode(&gViModeStruct);
    osViSetYScale(0x42);
    viSetFieldBit(1);
    osEPiLoad(0x96, &gEPiLoadSrc, &gEPiLoadDst, 0xC8);
    osCreateThread(&gGameLoopThread, 3, &gameMainLoop_setup, 0, &gGameLoopStack, 0xA);
    osStartThread(&gGameLoopThread);
    osSetThreadPri(0, 0);
loop_1:
    goto loop_1;
}
