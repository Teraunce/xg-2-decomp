#include "ultra64.h"
#include "camera.h"
#include "entity.h"
#include "render.h"

/*
 * renderSceneDispatch — per-frame scene rendering dispatcher (nonmatching).
 *
 * PERMANENTLY NONMATCHING — multiple reasons:
 * 1. Ten internal alabel markers (func_8006C1AC/548/63C/704/8A0/8A8/CB78/CBEC/CC68/CCD4):
 *    spimdisasm treats them as external entry points; all confirmed to have NO
 *    external callers (grep checked). They are purely internal control-flow labels.
 * 2. Jump table dispatch via jtbl_8004C448 (6 entries, index = entity->0x588 state).
 * 3. Several jal targets (func_8013F3BC, func_800AD77C, func_800A69B4,
 *    func_800974CC, func_80068D2C, func_800A84D4, func_8012A4CC) are in overlay
 *    address ranges outside src/main/main/, requiring extern declarations.
 *
 * Arguments:
 *   player_idx : player/camera index (0-based), used to index into entity pool
 *   param_f    : f32 scale/LOD parameter (arrives in $a1 via mtc1)
 *   param_a2   : additional pointer (saved to sp+0x70)
 *
 * Register allocation (key):
 *   s5 = player_idx
 *   fs2 = param_f
 *   s4 = gEntityPool base (gEntityPoolBase)
 *   s2 = player stride = player_idx * 0x228
 *   s1 = CameraView slot = gEntityPool + player_idx * 0x228
 *   t4 = s1 (aliased for field loads)
 *   s0 = current entity in loop (from gRenderPool, stride 0x668)
 *   s3 = loop counter
 *   fp = 1 (constant sentinel)
 *   s6 = hi(gPlayerList) for lw-halfword loads
 *   s7 = entity render table + 0x190 (track node lookup base)
 *
 * Size: 0xC64 bytes.
 */

/* Overlay functions — not in src/main/main/ */
void func_8013F3BC(Entity *entity);
void func_800AD77C(Entity *entity);
void func_800A69B4(Unk *a0, s32 a1);
void func_800974CC(s32 a0, s32 a1);
s32  func_80068D2C(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp10);
void func_800A84D4(s32 a0);
void func_8012A4CC(Unk *a0);

/* Rendering functions */
void cameraViewRender(RenderNode *arg0, CameraView *arg1, s32 arg2, s32 arg3,
                      f32 arg4, f32 arg5, s32 arg6, s32 arg7);
void cameraHiliteRender(RenderNode *arg0, CameraView *arg1, s32 arg2, s32 arg3, s32 arg4);
void cameraMatrixBuild(RenderNode *arg0, CameraView *arg1);
void gameRaceRender(s32 arg0);

/* Globals */
extern Unk *gDLPtr;            /* D_80173CC0 — write ptr into current DL buffer */
extern Entity gEntityPool[];   /* entity pool, stride 0x228 */
extern s32   gTrackNodeCount;  /* gTrackNodeCount — active track/AI node count */
extern s32   gPlayerList;      /* D_80091E70 — player linked list head */
extern s32   gRenderBase;      /* gRenderBufBase — current render DL buffer base ptr */
extern Unk  *gCurRenderNode;   /* used by nearby track/render code */

/* LOD distance thresholds (rodata at gLodDistClose..C480) */
extern f32 gLodDistClose;  /* close LOD threshold */
extern f32 gLodDistMid;  /* mid LOD threshold */
extern f32 gLodDistFar;  /* far LOD threshold */
extern f32 gTexLodNear;  /* tex-lod near threshold */
extern f32 gTexLodMid;  /* tex-lod mid threshold */
extern f32 gLodDistD;  /* horiz scale bound */
extern f32 gLodDistC;  /* vert scale bound */
extern f32 gLodDistB;  /* depth scale bound */
extern f32 gLodDistE;  /* tile scale bound */

/* DL buffer selectors / render nodes */
extern s32 gDLBufBase;  /* primary DL buffer base */
extern s32 gDLBufBaseB;  /* secondary DL buffer base (reflection pass) */
extern s32 gDLSegAddr;  /* DL display list base for render node */
extern s32 gDLSegAddrB;  /* additional DL segment base */

/* Texture/material tables for LOD selection */
extern s32 gTexLodTableA;  /* tex-LOD table A (used when entity->0x1E0 != 0) */
extern s32 gTexLodTableB;  /* tex-LOD table B (primary viewpoint) */
extern s32 gTexLodTableC;  /* tex-LOD table C (secondary viewpoint) */

/* Misc render flags */
extern s32 gRaceMax;  /* render flag: primary/secondary viewpoint active */
extern s32 gLodFlag;  /* render flag: LOD enable */
extern s32 gSceneTransFlag;  /* overlay post-render flag */
extern s32 gGameFlags2;  /* half-step flag for dist computation */

/* Viewport/resolution data */
extern s32 gViewportTable;  /* viewport table base (per-player, stride 0x20) */
extern f32 gHorizScaleF;  /* horiz scale factor */
extern f32 gVertScaleF;  /* vert scale factor */

/* Entity render pool (stride 0x668, up to gTrackNodeCount entries) */
extern RenderNode gTrackNodePool[]; /* render entity pool, stride 0x668 */
extern s32 gVelStateBlock;  /* entity render auxiliary table */

/* Particle system */
extern s32 gParticleCount;  /* particle count */
extern u8  gParticleColorR;  /* particle color R */
extern u8  gParticleColorG;  /* particle color G */
extern u8  gParticleColorB;  /* particle color B */

/* nonmatching: jump table + alabel markers + overlay calls (permanently) */
void renderSceneDispatch(s32 player_idx, f32 param_f, Unk *param_a2) {
    /*
     * Compute camera/entity slot pointer: stride = player_idx * 0x228
     * s4 = gEntityPool, s2 = stride, s1/t4 = gEntityPool + stride
     */
    Entity *cam = &gEntityPool[player_idx];

    /* sp+0x70 = param_a2 (passed through to func_80068D2C) */

    /* ------------------------------------------------------------------ */
    /* Phase 1: DL buffer selection and GBI frame setup (alabel C1AC)     */
    /* ------------------------------------------------------------------ */

    /*
     * Select DL buffer: if cam->hiliteFlag (0x1E4) != 0 use secondary
     * (reflection) buffer gDLBufBaseB; else use primary gDLBufBase.
     * Store selected ptr to gRenderBase (gRenderBufBase).
     * alabel func_8006C1AC is the merge point after selection.
     */
    if (cam->hiliteFlag != 0) {
        gRenderBase = gDLBufBaseB;
    } else {
        gRenderBase = gDLBufBase;
    }
    /* alabel func_8006C1AC: */

    /* Emit GBI_DL (0xDE000000) + segment-table ptr to gDLPtr */
    {
        Unk **dl = (Unk **)&gDLPtr;
        Unk  *cur = *dl;
        *(s32 *)cur       = 0xDE000000; /* GBI_DL / display list call */
        *(s32 *)((u8 *)cur + 4) = gDLSegAddr; /* DL segment address */
        *dl = (Unk *)((u8 *)cur + 8);
    }

    /*
     * Compute distance-scaled integer from entity->0xB0:
     *   f  = (f32)(s32)(cam+stride->0xB0) * param_f
     *   if gGameFlags2 & 1: dist_int >>= 1   (arithmetic right shift)
     *   s3 = 0x3E3 - cam+stride->0xB4        (max distance remaining)
     *   if s3 < 0: s3 += 0xF                 (round up)
     *   s3 >>= 4                              (quantise)
     *   dist_denom = 0x3E8 - s3              (divisor)
     *   a2 = 0x1F400 / dist_denom            (scale)
     */
    {
        Entity *ent = cam;   /* same slot */
        f32   f     = (f32)ent->timerA * param_f;
        s32   dist  = (s32)f;
        s32   base_dist;
        s32   denom, scale;
        s32   r, g, b;       /* s1, s0, s6 */

        if (gGameFlags2 & 1) {
            dist >>= 1; /* arithmetic half */
        }

        base_dist = ent->unk134;

        /* RGB multiply: entity->0xBC * (0xFF - base_dist), div by 0x80808081 trick */
        r = (s32)(ent->colorR) * (0xFF - base_dist);
        g = (s32)(ent->colorG) * (0xFF - base_dist);
        b = (s32)(ent->colorB) * (0xFF - base_dist);
        /* SN64 fast /255 approximation (mult+shift by 0x80808081>>23): */
        r = (r * (s32)0x80808081) >> (32+7);  r -= (r>>31); r += base_dist;
        g = (g * (s32)0x80808081) >> (32+7);  g -= (g>>31); g += base_dist;
        b = (b * (s32)0x80808081) >> (32+7);  b -= (b>>31); b += base_dist;

        /* fs1 = entity->0x148 (f32 stored at 0x148) */
        /* dist_int stored to sp+0x20 */

        denom = 0x3E3 - ent->timerB;
        if (denom < 0) denom += 0xF;
        denom >>= 4;
        denom = 0x3E8 - (0x3E3 - denom);
        scale = 0x1F400 / denom; /* IDO div idiom; BREAK 7 on denom==0 */

        /*
         * Emit GBI viewport / geometry-mode / fog commands into gDLPtr.
         * (Large inline GBI command block — see asm 8006C32C..8006C454
         *  for exact 0xE2/0xE3/0xD7/0xDB/0xF8/0xDA/0xDB etc. constants.)
         *
         * Slots written:
         *   +0x00  0xDB080000       G_SETIMG or similar
         *   +0x04  scale<<16 | (0x1F4-denom)<<8 & 0xFFFF
         *   +0x08  0xF8000000       G_SETFOGCOLOR
         *   +0x0C  r<<24 | g<<16 | b<<8 | 0xFF
         *   +0x10  0xE2001E01       G_SETOTHERMODE_H
         *   +0x14  0  (pad)
         *   +0x18  0xE3001001       G_SETOTHERMODE_L
         *   +0x1C  0x80008000
         *   +0x20  0xD7000002       G_TEXTURE
         *   +0x24  cam->0x224 (u16)
         *   +0x28  0xDB0E000x       ...
         *   +0x2C  matrix block copy (gEntityPool entries → DL)
         */
        (void)scale; (void)r; (void)g; (void)b;
    }

    /* ------------------------------------------------------------------ */
    /* Phase 2: Secondary DL node emit (alabel C548)                      */
    /* ------------------------------------------------------------------ */
    /*
     * Check if entity->0x1E4 (reflection flag) is set; write 0xD9FFFFFF
     * (GBI_ENDDL-like) + size word (0x200 if set, 0x400 otherwise) to
     * gDLPtr slot.  alabel func_8006C548 is the merge point.
     */

    /* ------------------------------------------------------------------ */
    /* Phase 3: Entity render loop                                         */
    /* ------------------------------------------------------------------ */
    /*
     * Iterate gTrackNodeCount entities from gRenderPool (render pool,
     * stride 0x668).  For each entity:
     *
     *   entity->0x598: active flag (1 = skip this entity entirely)
     *   entity->0x588: state index, dispatch via jtbl_8004C448 (6 entries)
     *     states 2,3,5 → skip (advance s0 and s2 by 0x668)
     *     states 0,1,4 → active render path (below)
     *
     * Active render path:
     *   dx = entity->0x10 - cam->eyeX (f32)
     *   dy = entity->0x14 - cam->eyeY
     *   dz = entity->0x18 - cam->eyeZ
     *
     *   Select LOD texture table ptr (v1):
     *     if entity->0x1E0 != 0: v1 = gTexLodTableA
     *     elif gRaceMax == 1 or gLodFlag != 0: v1 = gTexLodTableB
     *     else: v1 = gTexLodTableC
     *
     *   dist² = dx*dx + dy*dy + dz*dz
     *   dist  = sqrt(dist²)  (if gLodFlag != 0; else use dist² threshold)
     *
     *   LOD select (alabel func_8006C704, merge):
     *     if dist < gLodDistClose: a3 = 0
     *     elif dist < gLodDistMid: a3 = 1
     *     elif dist < gLodDistFar: a3 = 2
     *     else: a3 = 3
     *   (or if !LOD: a3 = v1[0/4/8] based on dist² thresholds D_C46C/C470)
     *
     *   if dist < (f32)dist_int: skip to next entity
     *
     *   if entity == cam->0xD0 (player entity == camera target):
     *     -- special "self" path --
     *     if entity->0x1DC == 1: skip
     *     if entity->0x64C == 0 or entity->0xC->0 == 0:
     *       cameraViewRender(entity, cam, entity->0x558, track_addr,
     *                        entity->0x57C, entity->0x580, entity->0x560, a3)
     *     elif entity->0x64C == 1 and entity->0xC->0 != 0:
     *       cameraHiliteRender(entity, cam, entity->0x558, track_addr, a3)
     *   else:
     *     if entity->0x64C == 0: cameraViewRender(...)
     *     elif entity->0x64C == 1: jump to cameraHiliteRender path
     *     else: skip
     *
     *   alabel func_8006C8A0: jal cameraHiliteRender(entity, cam, ...)
     *   alabel func_8006C8A8: check dist < dist_int; if so continue
     *     if entity == cam->0xD0: cameraMatrixBuild(entity, cam)
     *
     * Loop epilogue: s0 += 0x668, s2 += 0x668, s3++
     */
    {
        s32   n     = gTrackNodeCount;
        s32   loop  = 0;
        RenderNode *ent = gTrackNodePool;
        Unk  *aux   = (Unk *)((u8 *)&gVelStateBlock);
        Unk  *ent_s7 = (Unk *)((u8 *)gTrackNodePool + 0x190); /* render table + 0x190 */
        s32   dist_int = 0; /* sp+0x20, computed in phase 1 */
        s32   a3_lod;
        (void)aux;

        while (loop < n) {
            s32 skip_flag = ent->activeFlag;
            if (skip_flag != 1) {
                s32 state = ent->state;

                /* jump table: states 0,1,4 active; 2,3,5 skip */
                if (state < 6 &&
                    (state == 0 || state == 1 || state == 4)) {

                    /* Compute camera-relative offset */
                    f32 dx = ent->eyeX - cam->eyeX;
                    f32 dy = ent->eyeY - cam->eyeY;
                    f32 dz = ent->eyeZ - cam->eyeZ;
                    f32 dist2 = dx*dx + dy*dy + dz*dz;
                    Unk *lod_tbl;
                    f32 dist;
                    s32 track_addr;

                    /* LOD table selection */
                    if (cam->unk1E0 != 0) {
                        lod_tbl = (Unk *)&gTexLodTableA;
                    } else if (gRaceMax == 1 || gLodFlag != 0) {
                        lod_tbl = (Unk *)&gTexLodTableB;
                    } else {
                        lod_tbl = (Unk *)&gTexLodTableC;
                    }

                    /* Compute track/node address from loop index and player table */
                    track_addr = (gPlayerList * 15 + (s32)((u8 *)ent_s7 - (u8 *)gTrackNodePool) + loop * 0x668);
                    a3_lod = 0;

                    if (gLodFlag != 0) {
                        /* LOD with sqrt */
                        dist = 0.0f; /* sqrt(dist2) — FPU sqrt.s */
                        if (dist < gLodDistClose) {
                            a3_lod = 0;
                        } else if (dist < gLodDistMid) {
                            a3_lod = 1;
                        } else if (dist < gLodDistFar) {
                            a3_lod = 2;
                        } else {
                            a3_lod = 3;
                        }
                        /* alabel func_8006C704: */
                        if (dist >= (f32)dist_int) {
                            /* alabel func_8006C8A8 check merged here */
                            goto next_entity;
                        }
                    } else {
                        /* LOD without sqrt: threshold on dist² */
                        if (dist2 < gTexLodNear) {
                            a3_lod = *(s32 *)lod_tbl;
                        } else if (dist2 < gTexLodMid) {
                            a3_lod = *(s32 *)((u8 *)lod_tbl + 4);
                        } else {
                            a3_lod = *(s32 *)((u8 *)lod_tbl + 8);
                        }
                        /* alabel func_8006C704 merge */
                        if (dist2 >= (f32)dist_int) {
                            goto next_entity;
                        }
                    }

                    /* Dispatch based on whether this entity is the camera target */
                    if (ent == (RenderNode *)cam->renderObj) {
                        /* Camera target entity: "self" render */
                        if (cam->raceSlotType == 1) {
                            goto next_entity; /* flagged to skip */
                        }
                        if (ent->cameraFlag == 0) {
                            /* Standard view render */
                            if (*(s32 *)ent->modelObj == 0) {
                                /* No attached node: cameraViewRender path */
                                cameraViewRender(ent, (CameraView *)cam,
                                    ent->alphaParam,
                                    track_addr,
                                    ent->viewScaleX,
                                    ent->viewScaleY,
                                    ent->entityIdx,
                                    a3_lod);
                            } else {
                                /* Has attached node: cameraHiliteRender path */
                                /* alabel func_8006C8A0 → jal cameraHiliteRender */
                                cameraHiliteRender(ent, (CameraView *)cam,
                                    ent->alphaParam,
                                    track_addr,
                                    a3_lod);
                            }
                        } else if (ent->cameraFlag == 1) {
                            if (*(s32 *)ent->modelObj == 0) {
                                cameraViewRender(ent, (CameraView *)cam,
                                    ent->alphaParam,
                                    track_addr,
                                    ent->viewScaleX,
                                    ent->viewScaleY,
                                    ent->entityIdx,
                                    a3_lod);
                            } else {
                                /* alabel func_8006C8A0 */
                                cameraHiliteRender(ent, (CameraView *)cam,
                                    ent->alphaParam,
                                    track_addr,
                                    a3_lod);
                            }
                        } else {
                            /* entity->0x64C skip */
                        }
                    } else {
                        /* Non-target entity */
                        if (ent->cameraFlag == 0) {
                            /* No special mode */
                            cameraViewRender(ent, (CameraView *)cam,
                                ent->alphaParam,
                                track_addr,
                                ent->viewScaleX,
                                ent->viewScaleY,
                                ent->entityIdx,
                                a3_lod);
                        } else if (ent->cameraFlag == 1) {
                            /* alabel func_8006C8A0 */
                            cameraHiliteRender(ent, (CameraView *)cam,
                                ent->alphaParam,
                                track_addr,
                                a3_lod);
                        }
                        /* alabel func_8006C8A8 */
                        /* If dist < dist_int: advance without cameraMatrixBuild */
                        if (ent == (RenderNode *)cam->renderObj) {
                            cameraMatrixBuild(ent, (CameraView *)cam);
                        }
                    }
                }
            }
next_entity:
            ent++;
            loop++;
            /* s4 (aux table) advances 0xD4 per entity */
        }
    }

    /* ------------------------------------------------------------------ */
    /* Phase 4: Post-loop overlay calls and camera viewport setup         */
    /* ------------------------------------------------------------------ */

    /*
     * If gSceneTransFlag (post-render flag): call overlay func_8013F3BC
     * with the player entity slot.
     */
    if (gSceneTransFlag != 0) {
        Entity *pe = cam;
        func_8013F3BC(pe);
    }

    /*
     * func_800AD77C: overlay render setup for player entity.
     * Then emit GBI viewport / scissor / camera transform commands via gDLPtr.
     */
    {
        Entity *pe = cam;
        func_800AD77C(pe);

        /* Check cam->0x1E0; if 0 and gLodFlag == 0: call func_8013595C */
        if (cam->unk1E0 == 0) {
            if (gLodFlag == 0) {
                /* func_8013595C(pe); -- overlay, prototype unavailable */
            }
        }

        /*
         * Emit GBI_ENDDL (0xE7000000) marker + load null word into gDLPtr,
         * then call func_800A69B4 and func_800974CC to submit DL task.
         */
        {
            Unk **dl  = (Unk **)&gDLPtr;
            Unk  *cur = *dl;
            *(s32 *)cur       = 0xE7000000; /* GBI_ENDDL */
            *(s32 *)((u8 *)cur + 4) = 0;
            *dl = (Unk *)((u8 *)cur + 8);
        }

        func_800A69B4((Unk *)pe, 0);
        func_800974CC(player_idx, gPlayerList);
    }

    /*
     * Build camera transform: func_80068D2C with fog/perspective args,
     * then call gameRaceRender and func_800A84D4 for HUD/overlay.
     */
    func_80068D2C(player_idx, gPlayerList, (s32)param_a2,
                  0 /* a3 from sp+0x10 */, 0 /* sp+0x10 = sp save */);
    gameRaceRender(player_idx);
    func_800A84D4(player_idx);

    /* ------------------------------------------------------------------ */
    /* Phase 5: Particle system (gParticleCount count check)                  */
    /* ------------------------------------------------------------------ */
    /*
     * If particle count (gParticleCount) > 0:
     *   Call func_8012A4CC(ent->0x560).
     *   Emit particle GBI commands to gDLPtr:
     *     GBI_SETOTHERMODE_H (0xE3000A01)
     *     GBI_SETOTHERMODE_L (0xE3001801)
     *     GBI_SETCOMBINE     (0xE200001C)
     *     color (RGBA from gParticleColorR/BD/BE and particle count)
     *     GBI_ENDDL markers and render calls.
     *
     * The particle count check and GBI block spans asm 8006CA14..8006CD3C.
     */
    {
        s32 pcount = gParticleCount;
        if (pcount > 0) {
            /* cam->renderObj == NULL check: if NULL, skip func_8012A4CC */
            if (cam->renderObj != NULL) {
                func_8012A4CC((Unk *)cam->renderObj->entityIdx);
            }
            /* GBI particle command block emitted inline here (see asm) */
        }
    }

    /* ------------------------------------------------------------------ */
    /* Epilogue: restore primary DL buffer ptr                            */
    /* ------------------------------------------------------------------ */
    /*
     * gRenderBase = gDLBufBase  (always restore to primary at end)
     * Restore callee-saved regs and return.
     */
    gRenderBase = gDLBufBase;

    /* ------------------------------------------------------------------ */
    /* Viewport GBI commands (alabel func_8006CB78/CBEC/CC68/CCD4)        */
    /* ------------------------------------------------------------------ */
    /*
     * These four alabel markers are part of the viewport scissor/tile
     * computation block (asm 8006CB78..8006CD3C).  They compute:
     *   horiz scale: (viewport[s5].w + viewport[s5].w2) * 4 * gHorizScale
     *   vert  scale: similar for height
     *   tile scale:  similar for depth
     * and assemble GBI_TEXRECT / G_SETSCISSOR word pairs.
     * The result is written to the DL slot just before calling
     * func_800A69B4 above; expressed inline there.
     */
}
