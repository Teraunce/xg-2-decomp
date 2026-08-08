#include "ultra64.h"
void osCreateMesgQueue(Unk*, s32, s32);                     /* extern */
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);    /* extern */
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
void osSetEventMesg(s32, s32, s32);                         /* extern */
void osSetThreadPri(Unk*, s32);                            /* extern */
void osStartThread(Unk*);                               /* extern */
s32 osGetThreadPri(char*);                               /* extern */
void piMgrInit();                                  /* extern */
extern char *gFontData;
extern char *gDmaCallbackPtr;
extern s32 gFontInitDone;
extern s32 gGfxDmaThread;
extern s32 gGfxDmaStack;
extern s32 gGfxDmaMesgQueue;
extern s32 gGfxDmaMsg;
extern s32 gFontMesgQueue;
extern s32 osEPiStartDma_simple;
extern s32 osEPiStartDma;
extern s32 gfxDmaEventLoop;

void osEPiLoad(s32 arg0, char *arg1, char *arg2, s32 arg3) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 temp_v0;

    if (gFontData == NULL) {
        osCreateMesgQueue(arg1, arg2, arg3);
        osCreateMesgQueue(&gGfxDmaMesgQueue, &gGfxDmaMsg, 1);
        if (gFontInitDone == 0) {
            piMgrInit();
        }
        osSetEventMesg(8, &gGfxDmaMesgQueue, 0x22222222);
        sp28 = -1;
        sp24 = osGetThreadPri(0);
        if (sp24 < arg0) {
            sp28 = sp24;
            osSetThreadPri(0, arg0);
        }
        temp_v0 = osDisableInt();
        gFontData = (void *)1;
        gFontData = &gGfxDmaThread;
        gFontData = &gGfxDmaMesgQueue;
        gFontData = arg1;
        sp2C = temp_v0;
        gDmaCallbackPtr = &gFontMesgQueue;
        gDmaCallbackPtr = &osEPiStartDma_simple;
        gDmaCallbackPtr = &osEPiStartDma;
        osCreateThread(&gGfxDmaThread, 0, &gfxDmaEventLoop, &gFontData, &gGfxDmaStack + 0x1000, arg0);
        osStartThread(&gGfxDmaThread);
        osRestoreInt(sp2C);
        if (sp28 != -1) {
            osSetThreadPri(0, sp28);
        }
    }
}
