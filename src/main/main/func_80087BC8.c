#include "ultra64.h"
s32 osSiRawStartDma(s32, s32);                          /* extern */
s32 __siLock();                                  /* extern */
void __siUnlock();                                  /* extern */
void siInitControllerReadCmd(s32);                                 /* extern */
extern s32 gSiCmdBuf;
extern u8 gSiLocked;

s32 siReadBlocking(s32 arg0) {
    s32 sp1C;
    s32 temp_v0;

    sp1C = 0;
    __siLock();
    if (gSiLocked != 0) {
        siInitControllerReadCmd(0);
        sp1C = osSiRawStartDma(1, &gSiCmdBuf);
        osRecvMesg(arg0, 0, 1);
    }
    temp_v0 = osSiRawStartDma(0, &gSiCmdBuf);
    sp1C = temp_v0;
    gSiLocked = 0;
    __siUnlock();
    return temp_v0;
}
