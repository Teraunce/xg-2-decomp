#include "ultra64.h"
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
extern Unk *gVIConfig;

void viSetGamma(f32 arg0) {
    s32 temp_s0;

    temp_s0 = osDisableInt();
    gVIConfig->unk24 = arg0;
    gVIConfig->unk0 = (u16) (gVIConfig->unk0 | 4);
    osRestoreInt(temp_s0);
}
