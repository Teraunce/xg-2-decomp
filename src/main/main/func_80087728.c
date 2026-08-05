#include "ultra64.h"
s32 osVirtualToPhysical(u32);                             /* extern */
extern char *D_80095640;
extern char *gVIConfig;
extern s32 D_A4400000;
extern s32 D_A4400004;
extern s32 D_A4400008;
extern s32 D_A4400010;
extern s32 D_A4400014;
extern s32 D_A4400018;
extern s32 D_A440001C;
extern s32 D_A4400028;
extern s32 D_A4400030;
extern u32 D_A4400034;

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
    sp30 = D_A4400010 & 1;
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
    D_A4400004 = sp3C;
    D_A4400008 = temp_s0->unk8;
    D_A4400014 = temp_s0->unkC;
    D_A4400018 = temp_s0->unk10;
    D_A440001C = temp_s0->unk14;
    D_A4400004 = temp_s0->unk18;
    D_A4400008 = sp38;
    D_A4400028 = (temp_s0 + (sp30 * 0x14))->unk30;
    D_A4400008 = (temp_s0 + (sp30 * 0x14))->unk34;
    D_A4400028 = (temp_s0 + (sp30 * 0x14))->unk38;
    D_A4400030 = temp_s1->unk20;
    D_A4400034 = temp_s1->unk2C;
    D_A4400000 = temp_s1->unkC;
    gVIConfig = D_80095640;
    D_80095640 = temp_s1;
    M2C_MEMCPY_ALIGNED(gVIConfig, D_80095640, 0x30);
}
