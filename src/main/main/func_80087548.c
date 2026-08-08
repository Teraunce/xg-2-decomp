#include "ultra64.h"
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
extern Unk *gVIConfig;

void viSetRefresh(f32 arg0) {
    s32 temp_v0;

    temp_v0 = osDisableInt();
    gVIConfig->unk18 = arg0;
    gVIConfig->unk0 = (u16) (gVIConfig->unk0 | 2);
    gVIConfig->unk20 = (s32) ((u32) (gVIConfig->unk18 * (f32) (((Unk *)gVIConfig->unk8)->unk20 & 0xFFF)) & 0xFFF);
    osRestoreInt(temp_v0);
}
