#include "ultra64.h"
s32 osRecvMesg(Unk*, s32*, s32);                         /* extern */
s32 osSiRawStartDma(s32, s32);                          /* extern */
s32 __siLock();                                  /* extern */
void __siUnlock();                                  /* extern */
void func_80087F54();                                  /* extern */
extern s32 D_8018AD28;
extern s32 D_8018AD64;
extern u8 D_8018AD68;
extern u8 D_8018AD69;

s32 func_80087DE8(s32 arg0) {
    s32 sp1C;
    s32 sp18;
    s32 temp_t1;
    s32 temp_v0;

    sp1C = 0;
    __siLock();
    if (D_8018AD68 != 1) {
        func_80087F54();
        sp1C = osSiRawStartDma(1, &D_8018AD28);
        osRecvMesg(arg0, 0, 1);
    }
    sp18 = 0;
    do {
        *(&D_8018AD28 + (sp18 * 4)) = 0xFF;
        temp_t1 = sp18 + 1;
        sp18 = temp_t1;
    } while (temp_t1 < 0x10);
    D_8018AD64 = 0;
    temp_v0 = osSiRawStartDma(0, &D_8018AD28);
    sp1C = temp_v0;
    D_8018AD68 = 1;
    __siUnlock();
    return temp_v0;
}

void func_80087EAC(void) {

}
