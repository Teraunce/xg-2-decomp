#include "ultra64.h"
s32 osSiRawStartDma(s32, s32);                          /* extern */
s32 __siLock();                                  /* extern */
void __siUnlock();                                  /* extern */
void siInitControllerCmds();                                  /* extern */
extern s32 gSiCmdBuf;
extern s32 gSiWriteReady;
extern u8 gSiLocked;
extern u8 gSfxVoiceCount;

s32 siDmaReset(s32 arg0) {
    s32 sp1C;
    s32 sp18;
    s32 temp_t1;
    s32 temp_v0;

    sp1C = 0;
    __siLock();
    if (gSiLocked != 1) {
        siInitControllerCmds();
        sp1C = osSiRawStartDma(1, &gSiCmdBuf);
        osRecvMesg(arg0, 0, 1);
    }
    sp18 = 0;
    do {
        *(&gSiCmdBuf + (sp18 * 4)) = 0xFF;
        temp_t1 = sp18 + 1;
        sp18 = temp_t1;
    } while (temp_t1 < 0x10);
    gSiWriteReady = 0;
    temp_v0 = osSiRawStartDma(0, &gSiCmdBuf);
    sp1C = temp_v0;
    gSiLocked = 1;
    __siUnlock();
    return temp_v0;
}

void func_80087EAC(void) {

}
