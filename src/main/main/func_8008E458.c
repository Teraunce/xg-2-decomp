#include "ultra64.h"
void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
s32 osSendMesg(Unk*, s32, s32);                         /* extern */
extern s32 D_800964B0;
extern s32 D_8018D308;
extern s32 D_8018D310;

void piMgrInit(void) {
    D_800964B0 = 1;
    osCreateMesgQueue(&D_8018D310, &D_8018D308, 1);
    osSendMesg(&D_8018D310, 0, 0);
}
