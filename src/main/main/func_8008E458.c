#include "ultra64.h"
extern s32 gFontInitDone;
extern s32 gFontMsg;
extern s32 gFontMesgQueue;

void piMgrInit(void) {
    gFontInitDone = 1;
    osCreateMesgQueue(&gFontMesgQueue, &gFontMsg, 1);
    osSendMesg(&gFontMesgQueue, 0, 0);
}
