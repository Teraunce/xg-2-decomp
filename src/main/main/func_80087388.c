#include "ultra64.h"
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
extern Unk *gVIConfig;

void osViSetYScale(s32 arg0) {
    s32 temp_s0;

    temp_s0 = osDisableInt();
    if (arg0 & 1) {
        gVIConfig->unkC = (s32) (gVIConfig->unkC | 8);
    }
    if (arg0 & 2) {
        gVIConfig->unkC = (s32) (gVIConfig->unkC & ~8);
    }
    if (arg0 & 4) {
        gVIConfig->unkC = (s32) (gVIConfig->unkC | 4);
    }
    if (arg0 & 8) {
        gVIConfig->unkC = (s32) (gVIConfig->unkC & ~4);
    }
    if (arg0 & 0x10) {
        gVIConfig->unkC = (s32) (gVIConfig->unkC | 0x10);
    }
    if (arg0 & 0x20) {
        gVIConfig->unkC = (s32) (gVIConfig->unkC & ~0x10);
    }
    if (arg0 & 0x40) {
        gVIConfig->unkC = (s32) (gVIConfig->unkC | 0x10000);
        gVIConfig->unkC = (s32) (gVIConfig->unkC & ~0x300);
    }
    if (arg0 & 0x80) {
        gVIConfig->unkC = (s32) (gVIConfig->unkC & 0xFFFEFFFF);
        gVIConfig->unkC = (s32) (gVIConfig->unkC | (((Unk *)gVIConfig->unk8)->unk4 & 0x300));
    }
    gVIConfig->unk0 = (u16) (gVIConfig->unk0 | 8);
    osRestoreInt(temp_s0);
}
