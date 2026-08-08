#include "ultra64.h"
s32 __osGetCount();                                /* extern */
s32 osRecvMesg(Unk*, s32*, s32);                    /* extern */
s32 osSendMesg(Unk*, s32, s32);                       /* extern */
void osTimerHandlerGetter();                                  /* extern */
char *osViGetCurrentFramebuffer();                              /* extern */
void osViSwapBuffer();                                  /* extern */
extern char *__osRunningThread;
extern s32 gTimerHi;
extern u32 gTimerCount;
extern u32 gTimerPrev;
extern s32 gOsTimerLen;
extern u16 gTimerElapsed;

void viMgrThread(char *arg0) {
    Unk *sp34;
    Unk *sp30;
    u16 *sp2C;
    s32 sp28;
    u32 sp24;
    s32 temp_t6;
    u16 temp_s0;
    u16 temp_t3;
    u16 temp_t7;
    u32 temp_t5;
    u32 temp_t8;

    sp2C = NULL;
    sp28 = 0;
    sp34 = osViGetCurrentFramebuffer();
    temp_t7 = sp34->unk2;
    gTimerElapsed = temp_t7;
    if (temp_t7 == 0) {
        gTimerElapsed = 1;
    }
    sp30 = arg0;
loop_3:
    osRecvMesg(sp30->unkC, &sp2C, 1);
    temp_s0 = *sp2C;
    if (temp_s0 == 0xD) {
        osViSwapBuffer();
        temp_t3 = gTimerElapsed - 1;
        gTimerElapsed = temp_t3;
        if (!(temp_t3 & 0xFFFF)) {
            sp34 = osViGetCurrentFramebuffer();
            temp_t6 = sp34->unk10;
            if (temp_t6 != 0) {
                osSendMesg(temp_t6, sp34->unk14, 0);
            }
            gTimerElapsed = sp34->unk2;
        }
        gOsTimerLen += 1;
        if (sp28 != 0) {
            sp24 = __osGetCount();
            gTimerHi = 0;
            gTimerCount = sp24;
            sp28 = 0;
        }
        sp24 = gTimerPrev;
        gTimerPrev = __osGetCount();
        temp_t8 = gTimerPrev - sp24;
        temp_t5 = temp_t8 + gTimerCount;
        gTimerHi += temp_t5 < (u32) gTimerCount;
        sp24 = temp_t8;
        gTimerCount = temp_t5;
        goto loop_3;
    }
    if (temp_s0 != 0xE) {
        goto loop_3;
    }
    osTimerHandlerGetter();
    goto loop_3;
}

s32 osGetThreadPri(char *arg0) {
    Unk *var_a0;

    var_a0 = arg0;
    if (var_a0 == NULL) {
        var_a0 = __osRunningThread;
    }
    return var_a0->unk4;
}
