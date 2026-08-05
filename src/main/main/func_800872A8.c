#include "ultra64.h"
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
extern Unk *gVIConfig;

void func_800872A8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = osDisableInt();
    gVIConfig->unk10 = arg0;
    gVIConfig->unk14 = arg1;
    gVIConfig->unk2 = (s16) arg2;
    osRestoreInt(temp_v0);
}
