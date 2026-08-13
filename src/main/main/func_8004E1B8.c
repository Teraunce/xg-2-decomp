#include "ultra64.h"
s32 siDmaReset(s32);                                  /* extern */
extern s32 gSiMesgQueue;
extern s32 gPiMesgQueue;

void siMsgDispatch(void) {
    s32 *sp10;

loop_1:
    osRecvMesg(&gSiMesgQueue, &sp10, 1);
    if (*sp10 == 0x18) {
        siDmaReset(&gSiMesgQueue);
        goto loop_1;
    }
    osSendMesg(&gPiMesgQueue, sp10, 0);
    goto loop_1;
}
