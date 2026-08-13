#include "ultra64.h"
void dlResetPtr();                                  /* extern */
s32 contInit();                                /* extern */
void entityUpdateDispatch(void);                              /* extern */
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);          /* extern */
void osSetEventMesg(s32, s32, s32);                     /* extern */
void osStartThread(Unk*);                               /* extern */
void viSetDisplay(s32, s32, s32);                     /* extern */
extern s32 gGameSetupDone;
extern s32 gGameBuf;
extern s32 gRspDmaMesgQueue;
extern s32 gRspDmaMsgBuf;
extern s32 gPiEvtMsgQ;
extern s32 gEventQueueSize;
extern s32 gSiMesgQueue;
extern Unk gVideoModeCfg;
extern s32 gPiEvtMsgP;
extern s32 gSiStack;
extern s32 gSiThread;
extern s32 gPiMesgQueue;
extern s32 gViInited;
extern s32 gPiEvtMsgO;
extern s32 gPiEvtMsgN;
extern s32 gPiEvtMsgM;
extern s32 gPiEvtMsgL;
extern s32 gFrameStack;
extern s32 gSiMsgBuf;
extern s32 gPiEvtMsgK;
extern s32 gPiEvtMsgA;
extern s32 gPiEvtMsgJ;
extern s32 gPiEvtMsgI;
extern s32 gPiMsgBuf;
extern s32 gPiEvtMsgH;
extern s32 gViMsg;
extern s32 gPiEvtMsgG;
extern s32 gPiEvtMsgF;
extern s32 gPiEvtMsgB;
extern s32 gViEvtMsg;
extern s32 gPiEvtMsgC;
extern s32 gPiEvtMsgE;
extern s32 gPiEvtMsgD;
extern s32 siMsgDispatch;

void gameMainLoop_setup(s32 arg0) {
    s32 temp_v0;

    osCreateMesgQueue(&gRspDmaMesgQueue, &gRspDmaMsgBuf, 0x20);
    dlResetPtr();
    temp_v0 = contInit();
    gViMsg = 1;
    gViInited = temp_v0;
    gPiEvtMsgB = 4;
    gPiEvtMsgL = 5;
    gPiEvtMsgC = 6;
    gPiEvtMsgA = 8;
    gEventQueueSize = 9;
    gPiEvtMsgF = 7;
    gPiEvtMsgG = 0xA;
    gPiEvtMsgO = 0xB;
    gPiEvtMsgI = 0x19;
    gPiEvtMsgJ = 0xC;
    gPiEvtMsgP = 0xD;
    gFrameStack = 0xE;
    gPiEvtMsgH = 0xF;
    gPiEvtMsgQ = 0x10;
    gPiEvtMsgE = 0x1A;
    gPiEvtMsgN = 0x11;
    gPiEvtMsgK = 0x12;
    gPiEvtMsgD = 3;
    gViEvtMsg = 2;
    gPiEvtMsgM = 0x18;
    osCreateMesgQueue(&gPiMesgQueue, &gPiMsgBuf, 0x20);
    osSetEventMesg(4, &gPiMesgQueue, &gPiEvtMsgD);
    osSetEventMesg(9, &gPiMesgQueue, &gPiEvtMsgB);
    osSetEventMesg(6, &gPiMesgQueue, &gPiEvtMsgC);
    osSetEventMesg(0xE, &gPiMesgQueue, &gPiEvtMsgA);
    viSetDisplay(&gPiMesgQueue, &gViEvtMsg, 1);
    osCreateMesgQueue(&gSiMesgQueue, &gSiMsgBuf, 0x20);
    osSetEventMesg(5, &gSiMesgQueue, &gViMsg);
    osCreateThread(&gSiThread, 9, &siMsgDispatch, 0, &gSiStack, 0xE);
    osStartThread(&gSiThread);
    gVideoModeCfg.unk0 = 0;
    gVideoModeCfg.unk4 = 1;
    gVideoModeCfg.unkC = 3;
    gVideoModeCfg.unk14 = 1;
    gVideoModeCfg.unk1C = 3;
    gVideoModeCfg.unk8 = 2;
    gVideoModeCfg.unk10 = 0;
    gVideoModeCfg.unk18 = 2;
    gVideoModeCfg.unk20 = 0;
    gVideoModeCfg.unk24 = 1;
loop_1:
    entityUpdateDispatch();
    goto loop_1;
}

void func_8004E4B0(void) {
    s32 *var_v0;
    s32 var_v1;

    var_v1 = 0xFE;
    var_v0 = &gGameBuf + 0x3F8;
    do {
        *var_v0 = 0;
        var_v1 -= 1;
        var_v0 -= 4;
    } while (var_v1 >= 0);
    gGameSetupDone = 0;
}

void func_8004E4DC(void) {

}
