#include "ultra64.h"
#include "vi.h"

s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
extern ViOutConfig *gVIConfig;

void viSetOutput(s32 arg0) {
    s32 sp1C;

    sp1C = osDisableInt();
    gVIConfig->output = arg0;
    gVIConfig->ctrl = (u16) (gVIConfig->ctrl | 0x10);
    osRestoreInt(sp1C);
}
