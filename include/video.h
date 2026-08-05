/**
 * video.h — XG2 video / rendering subsystem types and globals
 *
 * Sources:
 *   func_8006D1FC  — large rendering dispatch switch (commands 0–6)
 *                    source of gZBufEnabled, gMirrorMode, gColorSwapMode,
 *                    gNumViewports, gViewports (D_800933A0), gSetupDisplayList
 *   func_80052F5C  — init: writes gColorSwapMode, gTrackNodeCount, clears
 *                    gInitStateFlags
 *   G_MOVEWORD (opcode 0xDC in F3DEX) loads RSP segment 2 ← &gViewports
 *   gViewports is a Vp[] array, NOT a matrix — see os.h for the Vp type.
 *
 * Rendering flag globals (main BSS):
 *   gZBufEnabled       0x80091084  s32  non-zero = depth-buffer active
 *   gMirrorMode        0x800912AC  s32  non-zero = flip-X / mirror render
 *   gColorSwapMode     0x80091FCC  s32  non-zero = BGR channel swap
 *   gNumViewports      0x800914D4  s32  split-screen viewport count (1–4)
 *   gViewportTimestamp 0x80091F7C  s16[2] packed render timestamp
 *   gViewports         0x800933A0  Vp[] viewport array (RSP segment 2)
 *   gSetupDisplayList  0x80093578  Gfx* display-list head for scene setup
 *   gGameState         0x80091E5C  u32  game state enum 0–6 (→ jtbl_8004BB20)
 *   gPendingEventFlag  0x80091E54  s32  one-shot event flag
 */

#ifndef _VIDEO_H_
#define _VIDEO_H_

#include "ultra64.h"   /* u8, u16, u32, s16, s32, f32 */

/* ---- Game state enumeration -------------------------------------------
 * gGameState (0x80091E5C) drives a 7-case jump table at jtbl_8004BB20.
 * Confirmed from func_8004E7A8: sltiu $v0, $v1, 7 → indexed jump.
 * ----------------------------------------------------------------------- */
typedef enum {
    GAME_STATE_INIT     = 0,
    GAME_STATE_1        = 1,
    GAME_STATE_2        = 2,
    GAME_STATE_3        = 3,
    GAME_STATE_4        = 4,
    GAME_STATE_5        = 5,
    GAME_STATE_RACE     = 6,   /* tentative — highest observed value */
} GameState;

/* ---- VideoModeDesc -----------------------------------------------------
 * Stride: 0x20 bytes — suspected video mode / display configuration block.
 * No direct decompilation yet; stride inferred from array access patterns.
 * All fields are placeholder names until confirmed.
 * ----------------------------------------------------------------------- */
typedef struct {
    /* +0x00 */ u16  width;         /* framebuffer width in pixels */
    /* +0x02 */ u16  height;        /* framebuffer height in pixels */
    /* +0x04 */ u16  vStart;        /* VI vertical start */
    /* +0x06 */ u16  vEnd;          /* VI vertical end */
    /* +0x08 */ u32  xScale;        /* VI X scale */
    /* +0x0C */ u32  yScale;        /* VI Y scale */
    /* +0x10 */ u32  ctrl;          /* VI_CONTROL register value */
    /* +0x14 */ u32  burst;         /* VI_BURST register value */
    /* +0x18 */ u32  vSync;         /* VI_V_SYNC register value */
    /* +0x1C */ u32  hSync;         /* VI_H_SYNC register value */
    /* = 0x20 total */
} VideoModeDesc;  /* size: 0x20 bytes — tentative */

/* ---- Rendering flag constants ----------------------------------------- */
#define RENDER_FLAG_ZBUF    (1)   /* gZBufEnabled non-zero value */
#define RENDER_FLAG_MIRROR  (1)   /* gMirrorMode non-zero value */
#define RENDER_FLAG_BGSWAP  (1)   /* gColorSwapMode non-zero value */

#endif /* _VIDEO_H_ */
