#include "ultra64.h"
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);          /* extern */
void osInitialize();                                  /* extern */
void osStartThread(Unk*);                               /* extern */
extern s32 gRspGeomBuf;
extern s32 gMainThread;
extern s32 gEntityRenderDone;
extern s32 gameMainThread;

void gameInit(void) {
    osInitialize();
    gEntityRenderDone = 0;
    osCreateThread(&gMainThread, 1, &gameMainThread, 0, &gRspGeomBuf, 0xA);
    osStartThread(&gMainThread);
}
