#include "ultra64.h"
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
extern s32 D_801899E8;

void osSetEventMesg(s32 arg0, s32 arg1, s32 arg2) {
    Unk *sp20;
    s32 *temp_t9;
    s32 temp_v0;

    temp_v0 = osDisableInt();
    temp_t9 = (arg0 * 8) + &D_801899E8;
    sp20 = temp_t9;
    *temp_t9 = arg1;
    sp20->unk4 = arg2;
    osRestoreInt(temp_v0);
}
