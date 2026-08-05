#include "ultra64.h"
void __osTimerUnlink(Unk*);                               /* extern */
void __osTimerInsert(Unk*, void**);                          /* extern */

void func_80082818(s32 arg0, s32 arg1) {
    __osTimerUnlink(arg1);
    __osTimerInsert(arg1, arg0 + 0x14);
}
