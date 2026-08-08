#include "ultra64.h"
s32 osSetIntMask(s32);                             /* extern */
void __osTimerUnlink(Unk*);                               /* extern */
void __osTimerInsert(Unk*, void**);                       /* extern */

void osTimerQueueReload(Unk *arg0) {
    s32 sp2C;
    char *temp_s1;
    char *var_s0;

    sp2C = osSetIntMask(1);
    var_s0 = arg0->unk8;
    if (var_s0 != NULL) {
        do {
            temp_s1 = *var_s0;
            __osTimerUnlink(var_s0);
            __osTimerInsert(var_s0, arg0);
            var_s0 = temp_s1;
        } while (temp_s1 != NULL);
    }
    osSetIntMask(sp2C);
}
