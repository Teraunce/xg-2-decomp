#include "ultra64.h"
void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);    /* extern */
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
void osSetEventMesg(s32, s32, s32);                     /* extern */
void osSetThreadPri(Unk*, s32);                            /* extern */
void osStartThread(Unk*);                               /* extern */
void osMsgQueueInit();                                  /* extern */
s32 osGetThreadPri(char*);                               /* extern */
void osViInit();                                  /* extern */
extern char *gViCfgPtr;
extern s32 gViFrameState;
extern s32 gViThread;
extern s32 gViStack;
extern s32 gNmiMesgQueue;
extern s32 gNmiMsgBuf;
extern s16 gNmiMsg;
extern s16 gNmiMsg2;
extern s32 viMgrThread;

void viMgrInit(s32 arg0) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 temp_v0;

    if ((s32)0 /* implicit $t6 from caller */ == 0) {
        osMsgQueueInit();
        osCreateMesgQueue(&gNmiMesgQueue, &gNmiMsgBuf, 5);
        gNmiMsg = 0xD;
        gNmiMsg = 0;
        gNmiMsg = 0;
        gNmiMsg2 = 0xE;
        gNmiMsg2 = 0;
        gNmiMsg2 = 0;
        osSetEventMesg(7, &gNmiMesgQueue, &gNmiMsg);
        osSetEventMesg(3, &gNmiMesgQueue, &gNmiMsg2);
        sp28 = -1;
        sp24 = osGetThreadPri(0);
        if (sp24 < arg0) {
            sp28 = sp24;
            osSetThreadPri(0, arg0);
        }
        temp_v0 = osDisableInt();
        gViCfgPtr = (void *)1;
        gViCfgPtr = &gViThread;
        gViCfgPtr = &gNmiMesgQueue;
        gViCfgPtr = &gNmiMesgQueue;
        sp2C = temp_v0;
        gViFrameState = 0;
        gViFrameState = 0;
        gViFrameState = 0;
        osCreateThread(&gViThread, 0, &viMgrThread, &gViCfgPtr, &gViStack + 0x1000, arg0);
        osViInit();
        osStartThread(&gViThread);
        osRestoreInt(sp2C);
        if (sp28 != -1) {
            osSetThreadPri(0, sp28);
        }
    }
}
