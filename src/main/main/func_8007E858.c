#include "ultra64.h"
s32 osSetIntMask(s32);                             /* extern */
void __osTimerUnlink(Unk*);                            /* extern */
void __osTimerInsert(Unk*, void**);                    /* extern */
void memcpyBytes(Unk*, char*, s32);                  /* extern */

s32 osStopTimer(Unk *arg0, s16 *arg1) {
    s32 sp28;
    s32 sp24;
    s32 var_v1;
    Unk *temp_s0;

    sp24 = osSetIntMask(1);
    temp_s0 = arg0->unk8;
    var_v1 = 0;
    if (temp_s0 != NULL) {
        __osTimerUnlink(temp_s0);
        memcpyBytes(temp_s0 + 0xC, arg1, 0x10);
        __osTimerInsert(temp_s0, arg0);
        var_v1 = temp_s0->unk8;
    } else {
        *arg1 = -1;
    }
    sp28 = var_v1;
    osSetIntMask(sp24);
    return sp28;
}
