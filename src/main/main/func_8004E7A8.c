#include "ultra64.h"
#include "vi.h"
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
 *   mode 0: 320×240 (NTSC standard)          — 1 viewport
 *   mode 1: 320×120 (half-height)             — 2 viewports (top/bottom)
 *   mode 2: 160×240 (half-width)              — 2 viewports (left/right)
 *   mode 3: 160×120 quad-split               — 4 viewports
 *   mode 4: 160×120 dual split               — 2 viewports
 *   mode 5: 320×120 alternate coefficients   — 2 viewports
 *   mode 6: 160×240 alternate               — 2 viewports
 * ------------------------------------------------------------------------- */

extern s32 gGameState;           /* current video mode index (0-6) */
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
    ViewportEntry *p;
    u32 mode;

    mode = (u32) gGameState;
    if (mode >= 7U) {
        return;
    }

    p = gVideoMode.vp;

    switch (mode) {
    case 0: /* 320x240 NTSC */
        p[0].x = 0;       p[0].y = 0;
        p[0].w = 0x140;   p[0].h = 0xF0;
        p[0].scaleX = gViTimingE;   p[0].scaleY = gViTimingF;
        p[0].centerX = gViTimingE;  p[0].centerY = gViTimingF;
        p[1].x = 0x79;    p[1].y = 0xC0;
        p[1].w = 0x4C;    p[1].h = 0x24;
        p[1].scaleX = gViRegPair2A; p[1].scaleY = gViRegPair2B;
        p[1].centerX = gViRegPair2C; p[1].centerY = gViRegPair2D;
        break;
    case 1: /* 320x120 half-height */
        p[0].x = 0;       p[0].y = 0;
        p[0].w = 0x140;   p[0].h = 0x78;
        p[0].scaleX = gViRegPair0A;  p[0].scaleY = gViRegPair0B2;
        p[0].centerX = gViRegPair0A; p[0].centerY = gViRegPair0B2;
        p[1].x = 0;
        p[1].y = 0x78;    p[1].w = 0x140; p[1].h = 0x78;
        p[1].scaleX = gViRegPair0A;  p[1].scaleY = gViRegPair0B2;
        p[1].centerX = gViRegPair0A; p[1].centerY = gViRegPair2E;
        break;
    case 2: /* 160x240 half-width */
        p[0].x = 0;       p[0].y = 0;
        p[0].w = 0xA0;    p[0].h = 0xF0;
        p[0].scaleX = gViRegPair0A2; p[0].scaleY = gViRegPair0B;
        p[0].centerX = gViRegPair0A2; p[0].centerY = gViRegPair0B;
        p[1].x = 0xA0;   p[1].y = 0;
        p[1].w = 0xA0;    p[1].h = 0xF0;
        p[1].scaleX = gViRegPair0A2; p[1].scaleY = gViRegPair0B;
        p[1].centerX = gViRegPair2F; p[1].centerY = gViRegPair0B;
        break;
    case 3: /* 160x120 quad-split */
        p[0].x = 0;       p[0].y = 0;
        p[0].w = 0xA0;    p[0].h = 0x78;
        p[0].scaleX = gViTimingA;  p[0].scaleY = gViTimingB;
        p[0].centerX = gViTimingA; p[0].centerY = gViTimingB;
        p[1].x = 0xA0;   p[1].y = 0;
        p[1].w = 0xA0;    p[1].h = 0x78;
        p[1].scaleX = gViTimingA;  p[1].scaleY = gViTimingB;
        p[1].centerX = gViTimingG; p[1].centerY = gViTimingB;
        p[2].x = 0;
        p[2].y = 0x78;    p[2].w = 0xA0; p[2].h = 0x78;
        p[2].scaleX = gViTimingA;  p[2].scaleY = gViTimingB;
        p[2].centerX = gViTimingA; p[2].centerY = gViTimingH;
        p[3].x = 0xA0;   p[3].y = 0x78;
        p[3].w = 0xA0;    p[3].h = 0x78;
        p[3].scaleX = gViTimingA;  p[3].scaleY = gViTimingB;
        p[3].centerX = gViTimingG; p[3].centerY = gViTimingH;
        break;
    case 4: /* 160x120 dual split */
        p[0].x = 0;       p[0].y = 0;
        p[0].w = 0xA0;    p[0].h = 0x78;
        p[0].scaleX = gViTimingC;  p[0].scaleY = gViTimingD;
        p[0].centerX = gViTimingC; p[0].centerY = gViTimingD;
        p[1].x = 0xA0;   p[1].y = 0;
        p[1].w = 0xA0;    p[1].h = 0x78;
        p[1].scaleX = gViTimingC;  p[1].scaleY = gViTimingD;
        p[1].centerX = gViRegPair2G; p[1].centerY = gViTimingD;
        p[2].x = 0;
        p[2].y = 0x78;    p[2].w = 0xA0; p[2].h = 0x78;
        p[2].scaleX = gViTimingC;  p[2].scaleY = gViTimingD;
        p[2].centerX = gViTimingC; p[2].centerY = gViRegPair2H;
        break;
    case 5: /* 320x120 alt */
        p[0].x = 0;       p[0].y = 0;
        p[0].w = 0x140;   p[0].h = 0x78;
        p[0].scaleX = gViRegPair1A;  p[0].scaleY = gViRegPair0C;
        p[0].centerX = gViRegPair1A; p[0].centerY = gViRegPair0C;
        p[1].x = 0;       p[1].y = 0x78;
        p[1].w = 0xA0;    p[1].h = 0x78;
        p[1].scaleX = gViRegPair0C2; p[1].scaleY = gViRegPair0C;
        p[1].centerX = gViRegPair0C2; p[1].centerY = gViRegPair1B;
        p[2].x = 0xA0;   p[2].y = 0x78;
        p[2].w = 0xA0;    p[2].h = 0x78;
        p[2].scaleX = gViRegPair0C2; p[2].scaleY = gViRegPair0C;
        p[2].centerX = gViRegPair2I; p[2].centerY = gViRegPair1B;
        break;
    case 6: /* 160x240 alt */
        p[0].x = 0;       p[0].y = 0;
        p[0].w = 0xA0;    p[0].h = 0xF0;
        p[0].scaleX = gViRegPair0D;  p[0].scaleY = gViRegPair1C;
        p[0].centerX = gViRegPair0D; p[0].centerY = gViRegPair1C;
        p[1].x = 0xA0;   p[1].y = 0;
        p[1].w = 0xA0;    p[1].h = 0x78;
        p[1].scaleX = gViRegPair0D;  p[1].scaleY = gViRegPair0E;
        p[1].centerX = gViRegPair1D; p[1].centerY = gViRegPair0E;
        p[2].x = 0xA0;   p[2].y = 0x78;
        p[2].w = 0xA0;    p[2].h = 0x78;
        p[2].scaleX = gViRegPair0D;  p[2].scaleY = gViRegPair0E;
        p[2].centerX = gViRegPair1D; p[2].centerY = gViRegPair2J;
        break;
    }
}
