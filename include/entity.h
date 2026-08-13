#ifndef ENTITY_H
#define ENTITY_H
#include "ultra64.h"

/* Forward-declare RenderNode to avoid circular include with render.h */
struct RenderNode_s;

/*
 * Entity — one game entity / player-vehicle descriptor (0x228 bytes).
 *
 * Stored in gEntityPool as a flat array, stride 0x228.
 * Each entity represents one racer (human or AI).
 *
 * The first 0x1E8 bytes overlap with CameraView so that camera functions
 * can receive a CameraView* pointing directly into the entity pool.
 *
 * Known field layout (partial — unknown regions left as u8 pads):
 *
 *   0x000–0x008  eye position   (front contact point / camera eye)
 *   0x00C–0x014  at position    (rear contact point / camera look-at)
 *   0x018–0x020  up vector      (matches CameraView layout)
 *   0x024–0x02F  flags/counters (unk024/028/02C — set by entityPhysicsInit)
 *   0x030–0x0AF  unknown
 *   0x0B0–0x0B8  timers / countdown values
 *   0x0BC–0x0BF  unknown
 *   0x0C0–0x0C8  SFX spatial reference vector (f32×3)
 *   0x0CC        nearClip  (fog / depth reference; matches CameraView)
 *   0x0D0        renderObj (pointer to paired render pool entry)
 *   0x0D4–0x0DB  AI/race per-slot counters
 *   0x0DC–0x0E3  unknown
 *   0x0E4        raceFlags
 *   0x0E5–0x103  unknown
 *   0x104        unk104
 *   0x105–0x123  unknown
 *   0x124        viewDepth
 *   0x125–0x12B  unknown
 *   0x12C        unk12C       (-1 sentinel)
 *   0x130        velParamF    (physics parameter F)
 *   0x134–0x143  unknown
 *   0x144        unk144
 *   0x148        velParamG    (physics parameter G)
 *   0x14C–0x1D3  physics sub-struct (passed as void* to entitySlotReset)
 *   0x1D4        unk1D4       (0xFF sentinel)
 *   0x1D5–0x1DB  unknown
 *   0x1DC        raceSlotType (race-mode position code: 0/1/4/5)
 *   0x1E0        unk1E0
 *   0x1E4        hiliteFlag   (0 = normal DL, nonzero = hilite DL; matches CameraView)
 *   0x1E8–0x1FB  race slot / physics init data
 *   0x1FC–0x207  init counters
 *   0x204        velParamL    (f32 physics param)
 *   0x208–0x217  init counters (cont.)
 *   0x218        raceSlotCount (/ 3 used for race-slot packing)
 *   0x21C        velParamM    (f32 physics param)
 *   0x220–0x227  unknown
 *   0x228        (end)
 */
typedef struct Entity_s {
    /* 0x000 */ f32 eyeX;          /* camera eye / front contact point X */
    /* 0x004 */ f32 eyeY;          /* camera eye / front contact point Y */
    /* 0x008 */ f32 eyeZ;          /* camera eye / front contact point Z */
    /* 0x00C */ f32 atX;           /* camera look-at / rear contact point X */
    /* 0x010 */ f32 atY;           /* camera look-at / rear contact point Y */
    /* 0x014 */ f32 atZ;           /* camera look-at / rear contact point Z */
    /* 0x018 */ f32 upX;           /* up-vector X (init 0) */
    /* 0x01C */ f32 upY;           /* up-vector Y (init gVelInitParamE) */
    /* 0x020 */ f32 upZ;           /* up-vector Z (init 0) */
    /* 0x024 */ s32 unk024;
    /* 0x028 */ s32 unk028;
    /* 0x02C */ s32 unk02C;
    /* 0x030 */ u8  unk030[0x80];
    /* 0x0B0 */ s32 timerA;        /* countdown timer A (init 0x1770 = 6000) */
    /* 0x0B4 */ s32 timerB;        /* countdown timer B (init 0x398 = 920) */
    /* 0x0B8 */ s32 timerEnable;   /* timer active flag (init 1) */
    /* 0x0BC */ u8  colorR;         /* entity color R (for race-color blend) */
    /* 0x0BD */ u8  colorG;         /* entity color G */
    /* 0x0BE */ u8  colorB;         /* entity color B */
    /* 0x0BF */ u8  unk0BF;
    /* 0x0C0 */ f32 unkC0;         /* SFX spatial reference X */
    /* 0x0C4 */ f32 unkC4;         /* SFX spatial reference Y */
    /* 0x0C8 */ f32 unkC8;         /* SFX spatial reference Z */
    /* 0x0CC */ f32 nearClip;      /* camera near-clip / fog depth */
    /* 0x0D0 */ struct RenderNode_s *renderObj; /* paired render pool entry */
    /* 0x0D4 */ s32 unkD4;         /* per-slot counter A */
    /* 0x0D8 */ u8  unk0D8[0x4];
    /* 0x0DC */ s32 unkDC;         /* per-slot counter B */
    /* 0x0E0 */ u8  unk0E0[0x4];
    /* 0x0E4 */ s32 raceFlags;     /* race status flags (0xFFFF = no race) */
    /* 0x0E8 */ u8  unk0E8[0x1C];
    /* 0x104 */ s32 unk104;
    /* 0x108 */ u8  unk108[0x1C];
    /* 0x124 */ s32 viewDepth;     /* camera view depth / slot */
    /* 0x128 */ u8  unk128[0x4];
    /* 0x12C */ s32 unk12C;        /* -1 sentinel */
    /* 0x130 */ f32 velParamF;
    /* 0x134 */ s32 unk134;
    /* 0x138 */ u8  unk138[0xC];
    /* 0x144 */ s32 unk144;
    /* 0x148 */ f32 velParamG;
    /* 0x14C */ u8  physicsSlot[0x88]; /* physics sub-struct (entitySlotReset target) */
    /* 0x1D4 */ s32 unk1D4;        /* 0xFF sentinel */
    /* 0x1D8 */ u8  unk1D8;        /* func_800AAEFC arg0 */
    /* 0x1D9 */ u8  unk1D9;        /* func_800AAEFC arg1 */
    /* 0x1DA */ u8  unk1DA;        /* func_800AAFD0 arg0 */
    /* 0x1DB */ u8  unk1DB;        /* func_800AAFD0 arg1 */
    /* 0x1DC */ s32 raceSlotType;  /* race-mode position code */
    /* 0x1E0 */ s32 unk1E0;
    /* 0x1E4 */ s32 hiliteFlag;    /* 0 = normal DL, nonzero = hilite DL */
    /* 0x1E8 */ s32 unk1E8;
    /* 0x1EC */ s32 unk1EC;
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
    /* 0x1F8 */ f32 raceSlotF;     /* race-slot float (speed/position param) */
    /* 0x1FC */ s32 unk1FC;
    /* 0x200 */ s32 unk200;
    /* 0x204 */ f32 velParamL;
    /* 0x208 */ s32 unk208;
    /* 0x20C */ s32 unk20C;
    /* 0x210 */ s32 unk210;
    /* 0x214 */ s32 unk214;
    /* 0x218 */ s32 raceSlotCount; /* race slot count (/ 3 for packing) */
    /* 0x21C */ f32 velParamM;
    /* 0x220 */ s32 unk220;         /* set by trackEntityRender (arg1) */
    /* 0x224 */ u16 unk224;         /* perspective frac (sp130 in gameCameraSetup) */
    /* 0x226 */ u8  unk226[0x2];
    /* 0x228 */
} Entity;

#endif /* ENTITY_H */
