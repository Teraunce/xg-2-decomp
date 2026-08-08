#include "ultra64.h"
s32 osVirtualToPhysical(u32);                             /* extern */
extern char *gViModePtr;
extern char *gVIConfig;
extern s32 VI_CTRL;
extern s32 VI_ORIGIN;
extern s32 VI_WIDTH;
extern s32 VI_V_CURRENT;
extern s32 VI_BURST;
extern s32 VI_V_SYNC;
extern s32 VI_H_SYNC;
extern s32 VI_V_START;
extern s32 VI_X_SCALE;
extern u32 VI_Y_SCALE;

void osViSwapBuffer(void) {
    s32 sp3C;
    s32 sp38;
    u32 sp34;
    s32 sp30;
    u32 temp_t6;
    Unk *temp_s0;
    Unk *temp_s1;

    sp30 = 0;
    temp_s1 = gVIConfig;
    temp_s0 = temp_s1->unk8;
    sp30 = VI_V_CURRENT & 1;
    sp3C = (temp_s0 + (sp30 * 0x14))->unk28 + osVirtualToPhysical(temp_s1->unk4);
    if (temp_s1->unk0 & 2) {
        temp_s1->unk20 = (s32) (temp_s1->unk20 | (temp_s0->unk20 & ~0xFFF));
    } else {
        temp_s1->unk20 = (s32) temp_s0->unk20;
    }
    if (temp_s1->unk0 & 4) {
        temp_t6 = (temp_s0 + (sp30 * 0x14))->unk2C & 0xFFF;
        sp34 = temp_t6;
        temp_s1->unk2C = (u32) (temp_s1->unk24 * (f32) temp_t6);
        temp_s1->unk2C = (u32) (temp_s1->unk2C | ((temp_s0 + (sp30 * 0x14))->unk2C & ~0xFFF));
    } else {
        temp_s1->unk2C = (u32) (temp_s0 + (sp30 * 0x14))->unk2C;
    }
    sp38 = temp_s0->unk1C;
    if (temp_s1->unk0 & 0x20) {
        sp38 = 0;
    }
    if (temp_s1->unk0 & 0x40) {
        temp_s1->unk2C = 0U;
        sp3C = osVirtualToPhysical(temp_s1->unk4);
    }
    if (temp_s1->unk0 & 0x80) {
        temp_s1->unk2C = (u32) ((temp_s1->unk28 << 0x10) & 0x03FF0000);
        sp3C = osVirtualToPhysical(temp_s1->unk4);
    }
    VI_ORIGIN = sp3C;
    VI_WIDTH = temp_s0->unk8;
    VI_BURST = temp_s0->unkC;
    VI_V_SYNC = temp_s0->unk10;
    VI_H_SYNC = temp_s0->unk14;
    VI_ORIGIN = temp_s0->unk18;
    VI_WIDTH = sp38;
    VI_V_START = (temp_s0 + (sp30 * 0x14))->unk30;
    VI_WIDTH = (temp_s0 + (sp30 * 0x14))->unk34;
    VI_V_START = (temp_s0 + (sp30 * 0x14))->unk38;
    VI_X_SCALE = temp_s1->unk20;
    VI_Y_SCALE = temp_s1->unk2C;
    VI_CTRL = temp_s1->unkC;
    gVIConfig = gViModePtr;
    gViModePtr = temp_s1;
    M2C_MEMCPY_ALIGNED(gVIConfig, gViModePtr, 0x30);
}
