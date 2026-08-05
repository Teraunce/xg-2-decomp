#include "ultra64.h"
s32 osRecvMesg(Unk*, s32*, s32);                    /* extern */
s32 osSendMesg(Unk*, s32, s32);                     /* extern */
s32 func_80087DE8(s32);                                  /* extern */
extern s32 D_80173C48;
extern s32 D_80174708;

void func_8004E1B8(void) {
    s32 *sp10;

loop_1:
    osRecvMesg(&D_80173C48, &sp10, 1);
    if (*sp10 == 0x18) {
        func_80087DE8(&D_80173C48);
        goto loop_1;
    }
    osSendMesg(&D_80174708, sp10, 0);
    goto loop_1;
}
