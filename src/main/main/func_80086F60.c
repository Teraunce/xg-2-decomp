#include "ultra64.h"
s32 __osGetCount();                                /* extern */
s32 osRecvMesg(Unk*, s32*, s32);                    /* extern */
s32 osSendMesg(Unk*, s32, s32);                       /* extern */
void osTimerHandlerGetter();                                  /* extern */
char *osViGetCurrentFramebuffer();                              /* extern */
void osViSwapBuffer();                                  /* extern */
extern char *__osRunningThread;
extern s32 D_80189A88;
extern u32 D_80189A8C;
extern u32 D_80189A90;
extern s32 D_80189A94;
extern u16 D_8018ACF8;

void func_80086F60(char *arg0) {
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
    D_8018ACF8 = temp_t7;
    if (temp_t7 == 0) {
        D_8018ACF8 = 1;
    }
    sp30 = arg0;
loop_3:
    osRecvMesg(sp30->unkC, &sp2C, 1);
    temp_s0 = *sp2C;
    if (temp_s0 == 0xD) {
        osViSwapBuffer();
        temp_t3 = D_8018ACF8 - 1;
        D_8018ACF8 = temp_t3;
        if (!(temp_t3 & 0xFFFF)) {
            sp34 = osViGetCurrentFramebuffer();
            temp_t6 = sp34->unk10;
            if (temp_t6 != 0) {
                osSendMesg(temp_t6, sp34->unk14, 0);
            }
            D_8018ACF8 = sp34->unk2;
        }
        D_80189A94 += 1;
        if (sp28 != 0) {
            sp24 = __osGetCount();
            D_80189A88 = 0;
            D_80189A8C = sp24;
            sp28 = 0;
        }
        sp24 = D_80189A90;
        D_80189A90 = __osGetCount();
        temp_t8 = D_80189A90 - sp24;
        temp_t5 = temp_t8 + D_80189A8C;
        D_80189A88 += temp_t5 < (u32) D_80189A8C;
        sp24 = temp_t8;
        D_80189A8C = temp_t5;
        goto loop_3;
    }
    if (temp_s0 != 0xE) {
        goto loop_3;
    }
    osTimerHandlerGetter();
    goto loop_3;
}

s32 func_80087138(char *arg0) {
    Unk *var_a0;

    var_a0 = arg0;
    if (var_a0 == NULL) {
        var_a0 = __osRunningThread;
    }
    return var_a0->unk4;
}
