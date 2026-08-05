#include "ultra64.h"
#include "audio.h"

/*
 * func_80062CE8 — Build and submit an RSP audio colour/mixer command.
 *
 * Reads phase / timer from gSfxPhase (gSfxPhase) and gSfxFadeTimer
 * (gSfxFadeTimer) to derive volume/pan byte arguments, then calls
 * func_80062F4C which writes the RSP display-list words for an audio
 * mix/colour command.
 *
 * Logic summary:
 *   arg_bytes = low bytes of D_80092D04  (byte0 = bits[7:0], byte2 = bits[23:16])
 *
 *   if gSfxPhase == 0 and gSfxRampStep == 0:
 *       if gSfxFadeTimer < 0:   a0 = 0                 (silence)
 *       if gSfxFadeTimer >= 0:  a0 = 0xFF              (full)
 *                               a2 = (byte2 & 0xFF)
 *
 *   if gSfxPhase == 2:
 *       if gSfxDecayStep == 0:  fall through to default
 *       else:                   use gSfxFadeTimer as a0
 *
 *   default (phase == 1, or phase != 0/2):
 *       if gSfxPhase == 1:  a0 = 0xFF,  a1 = (byte0 & 0xFF)
 *
 *   Then calls func_80062F4C(a0, a1, a2, a3) where a1/a2/a3 come from
 *   the bytes of D_80092D04.
 *
 * Globals:
 *   gSfxPhase        0x801823A8  s32
 *   gSfxFadeTimer    0x801823B0  s32
 *   gSfxRampStep     0x80092CF8  s32   (phase-0 ramp increment)
 *   gSfxDecayStep    0x80092D00  s32   (phase-2 decay decrement)
 *   D_80092D04       0x80092D04  u32   packed RGBA audio params
 */

extern s32 gSfxPhase;       /* 0x801823A8 */
extern s32 gSfxFadeTimer;   /* 0x801823B0 */
extern s32 gSfxRampStep;    /* 0x80092CF8 */
extern s32 gSfxDecayStep;   /* 0x80092D00 */
extern u32 D_80092D04;      /* packed audio params: bytes used as RGBA */

void func_80062F4C(s32 a0, s32 a1, s32 a2, s32 a3);  /* RSP DL audio command */

void func_80062CE8(void) {
    u32  packed = D_80092D04;
    s32  byte1  = (s32)((packed >> 8)  & 0xFF);   /* mid-low byte  → a2 */
    s32  byte2  = (s32)((packed >> 16) & 0xFF);   /* mid-high byte → a3 */
    s32  byte0  = (s32)(packed & 0xFF);            /* low byte      → a1 (phase-1) */
    s32  phase  = gSfxPhase;
    s32  a0, a1, a2, a3;

    a1 = 0;
    a2 = byte1 & 0xFF;
    a3 = byte2 & 0xFF;

    if (phase == 0) {
        /* Phase 0 — ramp in. */
        if (gSfxRampStep != 0) {
            /* Still ramping: use fade timer as attenuation. */
            s32 timer = gSfxFadeTimer;
            if (timer < 0) {
                a0 = 0;
                goto call;
            }
            if (timer < 0x100) {
                a0 = 0xFF;
                a2 = byte1 & 0xFF;
                goto call;
            }
        }
        /* gSfxRampStep == 0 or timer >= 0x100 → fall through to default. */
    }

    if (phase == 2) {
        /* Phase 2 — decay out. */
        if (gSfxDecayStep != 0) {
            s32 timer = gSfxFadeTimer;
            if (timer < 0) {
                a0 = 0;
                goto call;
            }
            if (timer < 0x100) {
                a0 = 0xFF;
                a2 = byte1 & 0xFF;
                goto call;
            }
        }
        /* gSfxDecayStep == 0 → fall through to default. */
    }

    /* Default / phase-1: full volume. */
    if (phase != 1) {
        return;   /* unknown phase: do nothing */
    }
    a0 = 0xFF;
    a1 = byte0 & 0xFF;

call:
    func_80062F4C(a0, a1, a2, a3);
}
