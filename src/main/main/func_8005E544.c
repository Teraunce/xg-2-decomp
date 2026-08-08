#include "ultra64.h"
s32 sfxQueueCmd(s32, s32, s32, s32, s32);               /* extern */
s32 entityFindNearest(s32, s32, s32, s32 *, s32 *);           /* extern */

void sfxPlayAtNearest(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp18;

    sp18 = 0;
    if (entityFindNearest(arg1, arg2, arg3, &arg4, &sp18) != 0) {
        sfxQueueCmd(arg0, 0x3F800000, arg4, 0x40, 0);
    }
}
