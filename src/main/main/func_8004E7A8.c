#include "ultra64.h"
s32 *overlayDecompress(void *);                         /* extern */
extern s32 gOverlayTable;

s32 overlayGetEntry(s32 arg0) {
    return *overlayDecompress((arg0 * 0x10) + &gOverlayTable);
}

void sfxChannelClear(char *arg0) {
    s32 var_v1;
    Unk *var_a0;

    var_a0 = arg0;
    var_v1 = 0;
    var_a0->unk0 = 0;
    var_a0->unk1 = 0;
    var_a0->unk2 = 0;
    var_a0->unk4 = 0;
    var_a0->unk5 = 0;
    var_a0->unk6 = 0;
    do {
        var_a0->unk8 = 0;
        var_a0->unk9 = 0;
        var_a0->unkA = 0;
        var_a0->unkC = 0;
        var_a0->unkD = 0;
        var_a0->unkE = 0;
        var_a0->unk10 = 0x49;
        var_a0->unk11 = 0x49;
        var_a0->unk12 = 0x49;
        var_v1 += 1;
        var_a0 += 0x10;
    } while (var_v1 < 7);
}

/* -------------------------------------------------------------------------
 * viModeConfig — video mode configuration dispatch.
 *
 * Reads gGameState (0-6), jumps via jtbl_8004BB20, and fills the
 * gVideoMode VideoModeConfig struct with resolution/FP-scale values.
 * Each of the 7 cases writes different dimensions and float coefficients.
 *
 *   mode 0: 320×240 (NTSC standard)
 *   mode 1: 320×120 (half-height)
 *   mode 2: 160×240 (half-width)
 *   mode 3: 160×120 with 4 viewports (unk40-unk7C used)
 *   mode 4: 160×120 with 2 viewports (unk40-unk5C used)
 *   mode 5: 320×120 alternate coefficients (unk40-unk5C used)
 *   mode 6: 160×240 alternate (unk40-unk5C used)
 * ------------------------------------------------------------------------- */

typedef struct {
    /* +00 */ s32 unk00;
    /* +04 */ s32 unk04;
    /* +08 */ s32 unk08;
    /* +0C */ s32 unk0C;
    /* +10 */ f32 unk10;
    /* +14 */ f32 unk14;
    /* +18 */ f32 unk18;
    /* +1C */ f32 unk1C;
    /* +20 */ s32 unk20;
    /* +24 */ s32 unk24;
    /* +28 */ s32 unk28;
    /* +2C */ s32 unk2C;
    /* +30 */ f32 unk30;
    /* +34 */ f32 unk34;
    /* +38 */ f32 unk38;
    /* +3C */ f32 unk3C;
    /* +40 */ s32 unk40;
    /* +44 */ s32 unk44;
    /* +48 */ s32 unk48;
    /* +4C */ s32 unk4C;
    /* +50 */ f32 unk50;
    /* +54 */ f32 unk54;
    /* +58 */ f32 unk58;
    /* +5C */ f32 unk5C;
    /* +60 */ s32 unk60;
    /* +64 */ s32 unk64;
    /* +68 */ s32 unk68;
    /* +6C */ s32 unk6C;
    /* +70 */ f32 unk70;
    /* +74 */ f32 unk74;
    /* +78 */ f32 unk78;
    /* +7C */ f32 unk7C;
} VideoModeConfig;

extern s32 gGameState;          /* current video mode index (0-6) */
extern VideoModeConfig gVideoMode; /* video mode config struct */

/* fp scale constants per mode, stored in rodata (entry.s dlabel section) */
extern f32 gViTimingE, gViTimingF, gViRegPair2A, gViRegPair2B, gViRegPair2C, gViRegPair2D;
extern f32 gViRegPair0A, gViRegPair0B2, gViRegPair2E;
extern f32 gViRegPair0A2, gViRegPair0B, gViRegPair2F;
extern f32 gViTimingA, gViTimingB, gViTimingG, gViTimingH;
extern f32 gViTimingC, gViTimingD, gViRegPair2G, gViRegPair2H;
extern f32 gViRegPair1A, gViRegPair0C, gViRegPair0C2, gViRegPair1B, gViRegPair2I;
extern f32 gViRegPair0D, gViRegPair1C, gViRegPair0E, gViRegPair1D, gViRegPair2J;

void viModeConfig(void) {
    VideoModeConfig *p;
    u32 mode;

    mode = (u32) gGameState;
    if (mode >= 7U) {
        return;
    }

    p = &gVideoMode;

    switch (mode) {
    case 0: /* 320x240 NTSC */
        p->unk00 = 0;
        p->unk04 = 0;
        p->unk08 = 0x140;
        p->unk0C = 0xF0;
        p->unk10 = gViTimingE; p->unk14 = gViTimingF;
        p->unk18 = gViTimingE; p->unk1C = gViTimingF;
        p->unk20 = 0x79; p->unk24 = 0xC0;
        p->unk28 = 0x4C; p->unk2C = 0x24;
        p->unk30 = gViRegPair2A; p->unk34 = gViRegPair2B;
        p->unk38 = gViRegPair2C; p->unk3C = gViRegPair2D;
        break;
    case 1: /* 320x120 half-height */
        p->unk00 = 0; p->unk04 = 0;
        p->unk08 = 0x140; p->unk0C = 0x78;
        p->unk10 = gViRegPair0A; p->unk14 = gViRegPair0B2;
        p->unk18 = gViRegPair0A; p->unk1C = gViRegPair0B2;
        p->unk20 = 0;
        p->unk24 = 0x78; p->unk28 = 0x140; p->unk2C = 0x78;
        p->unk30 = gViRegPair0A; p->unk34 = gViRegPair0B2;
        p->unk38 = gViRegPair0A; p->unk3C = gViRegPair2E;
        break;
    case 2: /* 160x240 half-width */
        p->unk00 = 0; p->unk04 = 0;
        p->unk08 = 0xA0; p->unk0C = 0xF0;
        p->unk10 = gViRegPair0A2; p->unk14 = gViRegPair0B;
        p->unk18 = gViRegPair0A2; p->unk1C = gViRegPair0B;
        p->unk20 = 0xA0; p->unk24 = 0;
        p->unk28 = 0xA0; p->unk2C = 0xF0;
        p->unk30 = gViRegPair0A2; p->unk34 = gViRegPair0B;
        p->unk38 = gViRegPair2F; p->unk3C = gViRegPair0B;
        break;
    case 3: /* 160x120 quad-viewport */
        p->unk00 = 0; p->unk04 = 0;
        p->unk08 = 0xA0; p->unk0C = 0x78;
        p->unk10 = gViTimingA; p->unk14 = gViTimingB;
        p->unk18 = gViTimingA; p->unk1C = gViTimingB;
        p->unk20 = 0xA0; p->unk24 = 0;
        p->unk28 = 0xA0; p->unk2C = 0x78;
        p->unk30 = gViTimingA; p->unk34 = gViTimingB;
        p->unk38 = gViTimingG; p->unk3C = gViTimingB;
        p->unk40 = 0;
        p->unk44 = 0x78; p->unk48 = 0xA0; p->unk4C = 0x78;
        p->unk50 = gViTimingA; p->unk54 = gViTimingB;
        p->unk58 = gViTimingA; p->unk5C = gViTimingH;
        p->unk60 = 0xA0; p->unk64 = 0x78;
        p->unk68 = 0xA0; p->unk6C = 0x78;
        p->unk70 = gViTimingA; p->unk74 = gViTimingB;
        p->unk78 = gViTimingG; p->unk7C = gViTimingH;
        break;
    case 4: /* 160x120 dual-viewport */
        p->unk00 = 0; p->unk04 = 0;
        p->unk08 = 0xA0; p->unk0C = 0x78;
        p->unk10 = gViTimingC; p->unk14 = gViTimingD;
        p->unk18 = gViTimingC; p->unk1C = gViTimingD;
        p->unk20 = 0xA0; p->unk24 = 0;
        p->unk28 = 0xA0; p->unk2C = 0x78;
        p->unk30 = gViTimingC; p->unk34 = gViTimingD;
        p->unk38 = gViRegPair2G; p->unk3C = gViTimingD;
        p->unk40 = 0;
        p->unk44 = 0x78; p->unk48 = 0xA0; p->unk4C = 0x78;
        p->unk50 = gViTimingC; p->unk54 = gViTimingD;
        p->unk58 = gViTimingC; p->unk5C = gViRegPair2H;
        break;
    case 5: /* 320x120 alt */
        p->unk00 = 0; p->unk04 = 0;
        p->unk08 = 0x140; p->unk0C = 0x78;
        p->unk10 = gViRegPair1A; p->unk14 = gViRegPair0C;
        p->unk18 = gViRegPair1A; p->unk1C = gViRegPair0C;
        p->unk20 = 0; p->unk24 = 0x78;
        p->unk28 = 0xA0; p->unk2C = 0x78;
        p->unk30 = gViRegPair0C2; p->unk34 = gViRegPair0C;
        p->unk38 = gViRegPair0C2; p->unk3C = gViRegPair1B;
        p->unk40 = 0xA0; p->unk44 = 0x78;
        p->unk48 = 0xA0; p->unk4C = 0x78;
        p->unk50 = gViRegPair0C2; p->unk54 = gViRegPair0C;
        p->unk58 = gViRegPair2I; p->unk5C = gViRegPair1B;
        break;
    case 6: /* 160x240 alt */
        p->unk00 = 0; p->unk04 = 0;
        p->unk08 = 0xA0; p->unk0C = 0xF0;
        p->unk10 = gViRegPair0D; p->unk14 = gViRegPair1C;
        p->unk18 = gViRegPair0D; p->unk1C = gViRegPair1C;
        p->unk20 = 0xA0; p->unk24 = 0;
        p->unk28 = 0xA0; p->unk2C = 0x78;
        p->unk30 = gViRegPair0D; p->unk34 = gViRegPair0E;
        p->unk38 = gViRegPair1D; p->unk3C = gViRegPair0E;
        p->unk40 = 0xA0; p->unk44 = 0x78;
        p->unk48 = 0xA0; p->unk4C = 0x78;
        p->unk50 = gViRegPair0D; p->unk54 = gViRegPair0E;
        p->unk58 = gViRegPair1D; p->unk5C = gViRegPair2J;
        break;
    }
}
