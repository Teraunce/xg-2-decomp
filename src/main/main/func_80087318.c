#include "ultra64.h"
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
extern Unk *gVIConfig;

void osViSetMode(char *arg0) {
    s32 temp_v0;

    temp_v0 = osDisableInt();
    gVIConfig->unk8 = arg0;
    gVIConfig->unk0 = 1;
    gVIConfig->unkC = (s32) ((Unk *)gVIConfig->unk8)->unk4;
    osRestoreInt(temp_v0);
}
