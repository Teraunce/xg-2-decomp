#include "ultra64.h"
s32 osRecvMesg(Unk*, s32*, s32);                         /* extern */
s32 osSiRawStartDma(s32, s32);                          /* extern */
s32 __siLock();                                  /* extern */
void __siUnlock();                                  /* extern */
void siInitControllerReadCmd(s32);                                 /* extern */
extern s32 D_8018AD28;
extern u8 D_8018AD68;

s32 siReadBlocking(s32 arg0) {
    s32 sp1C;
    s32 temp_v0;

    sp1C = 0;
    __siLock();
    if (D_8018AD68 != 0) {
        siInitControllerReadCmd(0);
        sp1C = osSiRawStartDma(1, &D_8018AD28);
        osRecvMesg(arg0, 0, 1);
    }
    temp_v0 = osSiRawStartDma(0, &D_8018AD28);
    sp1C = temp_v0;
    D_8018AD68 = 0;
    __siUnlock();
    return temp_v0;
}
