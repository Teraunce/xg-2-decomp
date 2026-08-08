#include "ultra64.h"
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
void bzero(s32, s32);                           /* extern */
extern char *gSramDmaHead;
extern char *gSramPiDmaCtx;
extern u8 gSramState;
extern u8 gSramRelease;
extern u8 gSramPwdInit;
extern s8 gSramCtrlB;
extern char *gSramPiHandle;
extern s32 PI_BSD_DOM1_LAT;
extern s32 PI_BSD_DOM1_PWD;
extern s32 PI_BSD_DOM1_PGS;
extern s32 PI_BSD_DOM1_RLS;

void **aiDmaInit(void) {
    s32 sp1C;
    s32 temp_v0;

    gSramCtrlB = 1;
    PI_BSD_DOM1_LAT = 3;
    PI_BSD_DOM1_PWD = (s32) gSramPwdInit;
    PI_BSD_DOM1_PGS = (s32) gSramState;
    PI_BSD_DOM1_RLS = (s32) gSramRelease;
    bzero(&gSramPiDmaCtx + 0x14, 0x60);
    temp_v0 = osDisableInt();
    gSramPiDmaCtx = gSramDmaHead;
    gSramDmaHead = &gSramPiDmaCtx;
    sp1C = temp_v0;
    gSramPiHandle = &gSramPiDmaCtx;
    osRestoreInt(sp1C);
    return &gSramPiDmaCtx;
}

void func_8008D5A8(void) {

}
