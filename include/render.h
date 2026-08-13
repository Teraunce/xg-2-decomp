#ifndef RENDER_H
#define RENDER_H
#include "ultra64.h"

/*
 * RenderNode — per-entity render pool entry (0x668 bytes).
 *
 * Stored in gTrackNodePool / gRenderPool / gRenderPool2 as flat arrays,
 * stride 0x668.  One entry per entity/vehicle (up to gTrackNodeCount entries).
 *
 * Each Entity->renderObj points to the corresponding RenderNode.
 * Each RenderNode->entity back-points to the Entity (set by entityPhysicsInit).
 *
 * Field layout (partial — unknown regions are u8 pads):
 *
 *   0x000–0x008  world position     (posX/Y/Z — updated each frame)
 *   0x00C        modelObj           (current vehicle/camera model object ptr)
 *   0x010–0x018  camera eye pos     (eyeX/Y/Z — used by cameraViewRender)
 *   0x01C–0x024  camera look-at pos (atX/Y/Z)
 *   0x034–0x03C  reference pos      (refX/Y/Z — alternate camera target)
 *   0x040–0x048  up vector          (upX/Y/Z)
 *   0x054        vehicleSlot        (bike / configuration slot index)
 *   0x06C        bikeObj            (bike mesh object ptr)
 *   0x114        vehicleEntry       (vehicle table entry value)
 *   0x2DC        speedParam         (speed / LOD f32 parameter)
 *   0x30C        distRef            (distance reference for LOD/fog)
 *   0x398–0x3A0  velocity           (velX/Y/Z)
 *   0x440        raceIdx            (race slot / position index)
 *   0x450        active             (0 = visible/active in race)
 *   0x558        alphaParam         (distance alpha-blend parameter)
 *   0x560        entityIdx          (index into gEntityPool — backref)
 *   0x568        entity             (Entity * backref, set by entityPhysicsInit)
 *   0x57C        viewScaleX         (f32 — cameraViewRender arg4, horiz FOV/scale)
 *   0x580        viewScaleY         (f32 — cameraViewRender arg5, vert FOV/scale)
 *   0x588        state              (render state: 0=inactive, 1=LOD-A, 2=LOD-B, 3=fade)
 *   0x598        activeFlag         (1 = skip this entry in scene render loop)
 *   0x648        speed              (speed magnitude — drives SFX pitch)
 *   0x64C        cameraFlag         (0=in-cockpit camera, 1=external/race camera)
 *   0x668        (end)
 */

/* Forward-declare Entity so render.h can use Entity* without a circular include.
   Include entity.h before render.h if you need the full Entity definition. */
struct Entity_s;

typedef struct RenderNode_s {
    /* 0x000 */ f32 posX;           /* world position X */
    /* 0x004 */ f32 posY;           /* world position Y */
    /* 0x008 */ f32 posZ;           /* world position Z */
    /* 0x00C */ Unk *modelObj;      /* vehicle/camera model object pointer */
    /* 0x010 */ f32 eyeX;           /* camera eye X */
    /* 0x014 */ f32 eyeY;           /* camera eye Y */
    /* 0x018 */ f32 eyeZ;           /* camera eye Z */
    /* 0x01C */ f32 atX;            /* camera look-at X */
    /* 0x020 */ f32 atY;            /* camera look-at Y */
    /* 0x024 */ f32 atZ;            /* camera look-at Z */
    /* 0x028 */ u8  unk028[0x4];
    /* 0x02C */ f32 unk02C;          /* Y-position component incremented with posY/eyeY/atY/refY */
    /* 0x030 */ u8  unk030[0x4];
    /* 0x034 */ f32 refX;           /* reference position X (alternate camera target) */
    /* 0x038 */ f32 refY;           /* reference position Y */
    /* 0x03C */ f32 refZ;           /* reference position Z */
    /* 0x040 */ f32 upX;            /* up vector X */
    /* 0x044 */ f32 upY;            /* up vector Y */
    /* 0x048 */ f32 upZ;            /* up vector Z */
    /* 0x04C */ u8  unk04C[0x8];
    /* 0x054 */ s32 vehicleSlot;    /* bike/configuration slot index */
    /* 0x058 */ u8  unk058[0x14];
    /* 0x06C */ Unk *bikeObj;       /* bike mesh object pointer */
    /* 0x070 */ u8  unk070[0xA4];
    /* 0x114 */ s32 vehicleEntry;   /* vehicle table entry */
    /* 0x118 */ u8  unk118[0x18C];
    /* 0x2A4 */ s32 spawnTick;       /* frame-tick snapshot used for activation-age delta */
    /* 0x2A8 */ u8  unk2A8[0x34];
    /* 0x2DC */ f32 speedParam;     /* speed / LOD parameter */
    /* 0x2E0 */ u8  unk2E0[0x2C];
    /* 0x30C */ f32 distRef;        /* distance reference (LOD/fog) */
    /* 0x310 */ u8  unk310[0x88];
    /* 0x398 */ f32 velX;           /* velocity X */
    /* 0x39C */ f32 velY;           /* velocity Y */
    /* 0x3A0 */ f32 velZ;           /* velocity Z */
    /* 0x3A4 */ u8  unk3A4[0x8C];
    /* 0x430 */ s32 slotPacked;      /* packed render-slot+dir word (bits[15:11]=slot, bits[10:0]=dir) */
    /* 0x434 */ u8  unk434[0xC];
    /* 0x440 */ s32 raceIdx;        /* race slot / position index */
    /* 0x444 */ u8  unk444[0xC];
    /* 0x450 */ s32 active;         /* 0 = visible/active in race */
    /* 0x454 */ s32 activeTick;      /* gFrameTick at which active was set */
    /* 0x458 */ s32 unk458;          /* set to 0xFF at activation */
    /* 0x45C */ s32 unk45C;          /* activation age delta (gFrameTick − spawnTick) */
    /* 0x460 */ u8  unk460[0xF8];
    /* 0x558 */ s32 alphaParam;     /* distance/alpha blend parameter */
    /* 0x55C */ u8  unk55C[0x4];
    /* 0x560 */ s32 entityIdx;      /* index into gEntityPool (backref) */
    /* 0x564 */ u8  unk564[0x4];
    /* 0x568 */ struct Entity_s *entity; /* Entity backref (set by entityPhysicsInit) */
    /* 0x56C */ s32 unk56C;          /* cleared in render-pool init; conditionally zeroed */
    /* 0x570 */ s32 unk570;          /* zeroed in render-pool init */
    /* 0x574 */ u8  unk574[0x8];
    /* 0x57C */ f32 viewScaleX;     /* cameraViewRender arg4 (horiz FOV / scale) */
    /* 0x580 */ f32 viewScaleY;     /* cameraViewRender arg5 (vert FOV / scale) */
    /* 0x584 */ u8  unk584[0x4];
    /* 0x588 */ s32 state;          /* render state (0=inactive, 1/2/3=active) */
    /* 0x58C */ u8  unk58C[0x8];
    /* 0x594 */ s16 unk594;         /* zeroed during render-pool init */
    /* 0x596 */ u8  unk596[0x2];
    /* 0x598 */ s32 activeFlag;     /* 1 = skip this entry in scene render loop */
    /* 0x59C */ u8  unk59C[0x8];
    /* 0x5A4 */ s32 unk5A4;          /* alternate age threshold for activation checks */
    /* 0x5A8 */ u8  unk5A8[0xA0];
    /* 0x648 */ f32 speed;          /* speed magnitude (drives SFX pitch) */
    /* 0x64C */ s32 cameraFlag;     /* 0=in-cockpit camera, 1=external camera */
    /* 0x650 */ u8  unk650[0x4];
    /* 0x654 */ s32 unk654;          /* viewport tile slot value (written before tile-buf store) */
    /* 0x658 */ u8  unk658[0x10];
    /* 0x668 */
} RenderNode;

#endif /* RENDER_H */
