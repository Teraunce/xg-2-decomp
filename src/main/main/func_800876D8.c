#include "ultra64.h"
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad02[0x2];
    /* 0x04 */ s32 unk4;
} UnkStruct_D_80095644;

s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
extern UnkStruct_D_80095644 *gVIConfig;

void func_800876D8(s32 arg0) {
    s32 sp1C;

    sp1C = osDisableInt();
    gVIConfig->unk4 = arg0;
    gVIConfig->unk0 = (u16) (gVIConfig->unk0 | 0x10);
    osRestoreInt(sp1C);
}
