#ifndef VI_H
#define VI_H
#include "ultra64.h"

/*
 * ViewportEntry — one viewport descriptor (0x20 bytes).
 *
 * Defines the screen rectangle and projection scale/centre for one player
 * view.  Up to 4 viewports are packed into VideoModeConfig.
 *
 * x/y      — pixel origin of the viewport (top-left corner)
 * w/h      — pixel dimensions
 * scaleX/Y — projection scale factors (world → screen)
 * centerX/Y — projected-space centre coordinates
 */
typedef struct {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 w;
    /* 0x0C */ s32 h;
    /* 0x10 */ f32 scaleX;
    /* 0x14 */ f32 scaleY;
    /* 0x18 */ f32 centerX;
    /* 0x1C */ f32 centerY;
    /* 0x20 */
} ViewportEntry;

/*
 * VideoModeConfig — full video-mode descriptor (0x80 bytes).
 *
 * Holds up to 4 ViewportEntry slots — one per split-screen player.
 * Written by viModeConfig() according to gGameState (0-6).
 * Read per-player as &gVideoMode.vp[playerIdx].
 */
typedef struct {
    /* 0x00 */ ViewportEntry vp[4];
    /* 0x80 */
} VideoModeConfig;

/*
 * ViOutConfig — VI output control record (0x08 bytes).
 *
 * Pointed to by gVIConfig.  viSetOutput() writes the output value and
 * sets bit 4 of the control word to signal a pending update to the VI
 * manager thread.
 *
 * ctrl   — control/status flags (bit 4 = update pending)
 * output — output mode/value to apply to the VI hardware
 */
typedef struct {
    /* 0x00 */ u16 ctrl;
    /* 0x02 */ u8  pad02[0x2];
    /* 0x04 */ s32 output;
    /* 0x08 */
} ViOutConfig;

#endif /* VI_H */
