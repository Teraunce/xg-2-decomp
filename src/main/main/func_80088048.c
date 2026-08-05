#include "ultra64.h"
void func_80088240(s32, s32);
/* Warning: missing "jr $ra" in last block of func_80088240 (initial). */

void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
s32 osGetTime();                                /* extern */
s32 osRecvMesg(Unk*, s32*, s32);                       /* extern */
s32 osSiRawStartDma(s32, s32);                          /* extern */
void siInitControllerReadCmd(s32);                                 /* extern */
s32 func_80088408(void *, s32, s32, s32, s32, s32, s32);       /* extern */
u64 __udivdi3(s32, u32, s32, s32);                  /* extern */
s32 __muldi3(s32, s32, s32, s32);                  /* extern */
extern s32 gCpuClockHi;
extern s32 gCpuClock;
extern s32 D_80096380;
extern s32 D_8018AD28;
extern s8 D_8018AD68;
extern u8 D_8018AD69;
extern s32 D_8018AD90;
extern s32 D_8018ADA8;

s32 func_80088048(char *arg0, s32 arg1, s32 arg2) {
    s32 sp7C;
    s32 sp78;
    u32 sp74;
    u32 sp70;
    s32 sp50;
    s32 sp38;
    u32 sp34;
    s32 sp30;
    u32 sp2C;
    s32 sp28;
    s32 temp_ret_2;
    s32 temp_ret_4;
    u32 temp_ret;
    u64 temp_ret_3;
    u64 temp_ret_5;
    u64 temp_v0;

    sp78 = 0;
    if (D_80096380 != 0) {
        return 0;
    }
    D_80096380 = 1;
    temp_ret = osGetTime();
    sp70 = temp_ret;
    sp74 = (u32) (u64) temp_ret;
    temp_ret_2 = __muldi3(0, 0x7A120, gCpuClockHi, gCpuClock);
    sp30 = temp_ret_2;
    sp34 = (u32) (u64) temp_ret_2;
    temp_ret_3 = __udivdi3(sp30, sp34, 0, 0xF4240);
    temp_v0 = temp_ret_3;
    if ((temp_v0 >= sp70) && ((sp70 < temp_v0) || (sp74 < (u32) temp_ret_3))) {
        osCreateMesgQueue(&sp38, &sp7C, 1);
        temp_ret_4 = __muldi3(0, 0x7A120, gCpuClockHi, gCpuClock);
        sp28 = temp_ret_4;
        sp2C = (u32) (u64) temp_ret_4;
        temp_ret_5 = __udivdi3(sp28, sp2C, 0, 0xF4240);
        sp30 = temp_ret_5;
        sp34 = (u32) temp_ret_5;
        func_80088408(&sp50, sp30 - (s32)sp70, sp34 - sp74, 0, 0, (s32)&sp38, (s32)&sp7C);
        osRecvMesg(&sp38, &sp7C, 1);
    }
    D_8018AD69 = 4;
    siInitControllerReadCmd(0);
    sp78 = osSiRawStartDma(1, &D_8018AD28);
    osRecvMesg(arg0, &sp7C, 1);
    sp78 = osSiRawStartDma(0, &D_8018AD28);
    osRecvMesg(arg0, &sp7C, 1);
    func_80088240(arg1, arg2);
    D_8018AD68 = 0;
    __siInit();
    osCreateMesgQueue(&D_8018AD90, &D_8018ADA8, 1);
    return sp78;
}

void func_80088248(void);  /* forward: GETTER_NOJR fallthrough */
void func_80088240(s32 arg1, s32 arg2) {
    func_80088248();
}
