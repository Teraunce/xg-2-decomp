#include "ultra64.h"
#include "entity.h"
#include "render.h"

/*
 * gameStateInit  (func_80052F5C)
 *
 * PERMANENTLY NONMATCHING — 58 alabel markers + jtbl_8004BC80 switch.
 * Sets up all game state for a race: clears globals, computes viewport
 * layout, initialises the entity pool, calls subsystem inits, then builds
 * per-player render-pool entries (gRenderPool, stride 0x668).
 *
 * Frame: 0x60 bytes.  Saves $ra, $s0–$s4.
 * Sets gRenderSyncB = -1 at the very end.
 * Size: 0xFA4 bytes.
 */

/* ---- overlay / subsystem functions ---- */
void func_8004D358(void);
void func_8004E4B0(void *a0);
void func_8007BCA8(void);
void func_8007BA98(void *a0, void *a1);
void func_8007BB48(void *a0, void *a1);
void func_8005B224(void *a0, void *a1, void *a2);
void func_8010AAC8(void);
void func_800ABA58(s32 a0);
void func_8004D3A8(void *a0, void *a1);
void func_800AC1E8(void);
void func_800A6C30(s32 a0);
void func_800A666C(s32 a0);
void func_800A9AE8(s32 a0);
void entityPhysicsInit(Entity *a0, RenderNode *a1);
void func_800AE1C8(void);
void func_800AE368(s32 a0);
void func_8004E670(s32 a0, void *a1, void *a2);
void func_8004E5F0(s32 a0, void *a1);
void func_8004E6C8(s32 a0);
void func_8004E830(void);
void func_8009B230(void);
void func_8004D7A0(void);
void func_8005CFC4(void *a0);
void func_8005E5A4(s32 a0);
void func_80102850(void);
s32  func_8004D4A8(s32 a0);
void func_80097040(void);
void func_800EAFE8(s32 a0);
void func_801342B8(void);
void func_8013C2A0(void);
void func_800521BC(s32 a0);
void func_80146CFC(void);
void func_80097430(void);
void func_801343BC(void);
void func_8014AFC8(void);
void func_8013C334(void);
void func_80134A44(void);

/* ---- game-state globals zeroed / set at entry ---- */
extern s32  gGameDirty;
extern s32  gFadeCounter;
extern s32  gSkipFrameFlag;
extern s32  gFrameSkipShadow;
extern s32  gRenderFade;
extern s32  gFrameSyncCountB;
extern s32  gLodShadow;
extern s32  gRenderCompleteFlag;
extern s32  gActiveEntityIdx;
extern s32  gFrameSyncCountA;
extern s32  gFrameAccumB;
extern s32  gRenderInitFlag;
extern s32  gFrameSyncFlag;
extern s32  gRaceRestartFlag;
extern s32  gSfxLodFlag;
extern s32  gDeferredFlag;

/* ---- race configuration ---- */
extern void *gTrackNodePtr;
extern s32   gMultiPlayerFlag;   /* 1 if player_count >= 3 */
extern s32   gPlayerCountBit;    /* 1 << (player_count % 3) */
extern s32   gTrackNodeCount;
extern s32   gRaceCtrlCount;     /* number of human players */
extern s32   gSceneTransFlag;    /* 1 if race mode == 2 */
extern s32   gRaceMax;           /* active viewport count */
extern s32   gSplitScreenMode;
extern s32   gLodFlag;
extern s32   gControllerCount;
extern s32   gGameTypeCode;
extern s32   gSplitTypeFlag;
extern s32   gGameFlags2;
extern s32   gRaceCtrlPtr;       /* race controller context ptr */
extern Unk   gRaceCtx;           /* large ROM race config block */

/* ---- entity / render pools ---- */
extern Entity     gEntityPool[];     /* entity pool base, stride 0x228 */
extern Unk        gButtonTable[];    /* per-player config table, stride 0x2C */
extern RenderNode gRenderPool[];     /* render pool, stride 0x668 */
extern Unk  *gVehicleTable[];    /* vehicle handle table */
extern s32   gCameraSlotCache[]; /* camera-object slot cache */
extern Unk   gVelStateBlock[];   /* velocity state block, stride 0x34 */
extern s32   gViewportWatermark;

/* ---- camera / render params ---- */
extern Unk   gCameraObj;
extern f32   gViewScaleF;
extern s32   gRenderSlotCount;
extern f32   gViewInitF;
extern s32   gRenderCamSlot;
extern s32   gViewportInitTable[];   /* f32 table: per-viewport-slot init */
extern Entity gCameraData;    /* single-player camera data (Entity layout) */
extern s32   gRenderParamA;
extern s32   gRenderParamB;

/* ---- subsystem / misc globals ---- */
extern Unk   gAudioSynthState;
extern s32   gViewportCountB;
extern s32   gViewportCountA;
extern s32   gUnkFlag_173BC8;
extern s32   gFrameTick;
extern s32   gSubTickCounter;
extern s32   gPrevFrameTick;
extern s32   gFrameCounter;
extern void *gEntityInputBuf;
extern s32   gRenderFlagC;
extern s32   gTimerHiCopy;
extern s32   gPlayerCount;
extern s32   gSfxSampleTable;
extern s32   gTrackRenderEntries[];
extern s32   gRenderPoolCount;
extern s32   gFrameLockFlag;
extern s32   gRenderSyncB;
extern s32   gDLBufSaveA;
extern s32   gSceneLoadBuf;

/* ---- float ROM constants ---- */
extern f32   gViewInitA;
extern f32   gViewInitB;
extern f32   gViewInitC;
extern f32   gViewInitD;
extern f32   gViewInitE;
extern f32   gViewInitG;
extern f32   gFrameTimerF;
extern f32   gFrameTimerF2;

/* ---- ROM-offset pointers / misc ---- */
extern Unk   D_31880;
extern Unk   D_85388;
extern s32   gSfxUcodeBase;
extern void *gRomHeader;
extern s32   gAudioUcodeBase2;

/* nonmatching: permanently — 58 alabel markers + jtbl_8004BC80 */
void gameStateInit(void) {
    s32  s2, s4;
    s32  numViewports;
    s32  playerCount, quotient;
    s32  raceMode;
    s32  bikeId, vehicleSlot, vslot, override;
    s32  ctrlMod9;
    s32  excess, i;
    f32  posX, posStep, posZ, curPos, nextPos, slotF;
    RenderNode *renderEnt;
    Entity     *entityEnt;
    Unk        *configPtr;
    Unk        *vhandle, *bikeObj;
    Unk       **cacheEntry;
    u8         *src, *dst, *conf, *p8;
    u8         *psrc, *pend, *pdst;
    Entity     *ep;
    RenderNode *rp;
    Unk        *rc;
    s32        *pi;
    s32  trackIdx;

    /* ---- Stage 1: Zero game-state globals --------------------------------------- */
    gGameDirty = 1;
    gFadeCounter = 0;
    gSkipFrameFlag = 0;
    gFrameSkipShadow = 0;
    gRenderFade = 0;
    gFrameSyncCountB = 0;
    gLodShadow = 0;
    gRenderCompleteFlag = 0;
    gActiveEntityIdx = 0;
    gFrameSyncCountA = 0;
    gFrameAccumB = 0;
    gRenderInitFlag = 0;
    gFrameSyncFlag = 0;
    gRaceRestartFlag = 0;
    gSfxLodFlag = 0;
    gDeferredFlag = 0;

    /* ---- Stage 2: Load race config from ROM block gRaceCtx ------------------- */
    gTrackNodePtr  = *(void **)((u8 *)&gRaceCtx + 0x16DC);
    playerCount = *(s32  *)((u8 *)&gRaceCtx + 0x16E0);

    /* gMultiPlayerFlag = 1 if player_count >= 3 */
    gMultiPlayerFlag = (playerCount >= 3) ? 1 : 0;

    /* gPlayerCountBit = 1 << (player_count % 3) */
    quotient   = playerCount / 3;
    gPlayerCountBit = 1 << (playerCount - quotient * 3);

    gRaceCtrlCount     = *(s32 *)((u8 *)&gRaceCtx + 0x16E8);
    gTrackNodeCount = *(s32 *)((u8 *)&gRaceCtx + 0x16E4);

    /* ---- Stage 3: Race-format flag and LOD-enable ------------------------------ */
    raceMode = *(s32 *)((u8 *)&gRaceCtx + 0x16D8);
    gSceneTransFlag = (raceMode == 2) ? 1 : 0;

    /* LOD: enable when trackNodePtr index >= 13, or vehicle-set code == 5 */
    trackIdx = (s32)(uintptr_t)gTrackNodePtr;
    if (trackIdx >= 13 || gGameTypeCode == 5) {
        gLodFlag = 1;
    } else {
        gLodFlag = 0;
    }

    /* ---- Stage 4: Compute active viewport count (gRaceMax) ------------------- */
    if (gRaceCtrlCount != 0) {
        gRaceMax = gRaceCtrlCount;
    } else {
        ctrlMod9 = gControllerCount % 9;
        if (ctrlMod9 == 0 || ctrlMod9 == 4 || ctrlMod9 == 6) {
            gRaceMax = 2;
        } else {
            gRaceMax = 1;
        }
    }

    /* ---- Stage 5: Split-screen mode switch (jtbl_8004BC80) --------------------
     * idx 0/1 → gSplitScreenMode = 0
     * idx 2   → 1 or 2 from gSplitTypeFlag
     * idx 3   → 4/5/6 from ROM B10/B0C
     * idx 4   → 3
     * idx >=5 → no-op
     * ---------------------------------------------------------------------- */
    numViewports = gRaceMax;
    if (numViewports == 0 || numViewports == 1) {
        gSplitScreenMode = 0;
    } else if (numViewports == 2) {
        gSplitScreenMode = gSplitTypeFlag ? 2 : 1;
    } else if (numViewports == 3) {
        if (*(s32 *)((u8 *)&gRaceCtx + 0xB10) == 0) {
            gSplitScreenMode = 4;
        } else if (*(s32 *)((u8 *)&gRaceCtx + 0xB0C) == 0) {
            gSplitScreenMode = 5;
        } else {
            gSplitScreenMode = 6;
        }
    } else if (numViewports == 4) {
        gSplitScreenMode = 3;
    }

    /* ---- Stage 6: Entity pool init loop (gEntityPool, stride 0x228) ----------- */
    posX    = gViewInitA;
    posStep = gViewInitB;
    posZ    = gViewInitC;
    curPos  = posX;

    if (gRaceMax > 0) {
        entityEnt = gEntityPool;
        for (s2 = 0; s2 < gRaceMax; s2++) {
            nextPos = curPos + posStep;
            entityEnt->eyeX       = posX;
            entityEnt->eyeY       = posX;
            entityEnt->eyeZ       = posX;
            entityEnt->atX        = posX;
            entityEnt->atY        = curPos;
            entityEnt->atZ        = nextPos;
            entityEnt->upX        = 0.0f;
            entityEnt->upY        = posZ;
            entityEnt->upZ        = 0.0f;
            entityEnt->timerA     = 0x1770;
            entityEnt->timerB     = 0x398;
            entityEnt->timerEnable = 1;
            entityEnt->renderObj  = NULL;
            entityEnt->unk1E0     = 0;
            entityEnt->hiliteFlag = 0;
            curPos = nextPos;
            entityEnt++;
        }
    }

    /* ---- Stage 7: Subsystem init calls ---------------------------------------- */
    func_8004D358();
    func_8004E4B0(&gAudioSynthState);
    gViewScaleF = 0.0f;
    func_8007BCA8();
    func_8007BA98(&gAudioSynthState, &D_85388);
    func_8007BB48(&gAudioSynthState, &D_85388);
    func_8005B224((u8 *)gRomHeader + 0x18, &gAudioSynthState, &D_85388);
    func_8007BCA8();
    func_8007BA98(&gAudioSynthState, &D_85388);
    func_8007BB48(&gAudioSynthState, &D_85388);

    if (*(s32 *)((u8 *)&gRaceCtx + 0x16D8) == 0xE) {
        func_8010AAC8();
    }

    func_800ABA58(0);
    func_8004D3A8((void *)&gSfxUcodeBase, &D_31880);
    func_800AC1E8();
    func_800A6C30(0);

    /* Zero camera param blocks; write dist constant into block B */
    *(s32 *)((u8 *)&gRenderParamA + 0)  = 0;
    *(s32 *)((u8 *)&gRenderParamA + 4)  = 0;
    *(s32 *)((u8 *)&gRenderParamA + 8)  = 0;
    *(s32 *)((u8 *)&gRenderParamB + 0)  = 0;
    *(s32 *)((u8 *)&gRenderParamB + 4)  = 0;
    *(f32 *)((u8 *)&gRenderParamB + 8)  = gViewInitD;

    func_800A666C((s32)gTrackNodePtr);
    func_800A9AE8(0);

    /* ---- Stage 8: Copy per-player config structs to gButtonTable (stride 0x2C) --- */
    if (gRaceCtrlCount > 0) {
        conf = (u8 *)&gRaceCtx;
        src  = conf + 0x16F8;        /* array of player config ptrs */
        pdst = (u8 *)gButtonTable;

        for (s2 = 0; s2 < gRaceCtrlCount; s2++) {
            configPtr = *(Unk **)src;
            psrc = (u8 *)configPtr + 0x28;
            pend = (u8 *)configPtr + 0x48;
            while (psrc != pend) {
                *(s32 *)(pdst + 0x00) = *(s32 *)(psrc + 0x00);
                *(s32 *)(pdst + 0x04) = *(s32 *)(psrc + 0x04);
                *(s32 *)(pdst + 0x08) = *(s32 *)(psrc + 0x08);
                *(s32 *)(pdst + 0x0C) = *(s32 *)(psrc + 0x0C);
                psrc += 0x10;
                pdst += 0x10;
            }
            /* Tail: 12 bytes remaining */
            *(s32 *)(pdst + 0x00) = *(s32 *)(psrc + 0x00);
            *(s32 *)(pdst + 0x04) = *(s32 *)(psrc + 0x04);
            *(s32 *)(pdst + 0x08) = *(s32 *)(psrc + 0x08);
            src  += 4;
            pdst += 0x0C;
            conf += 4;
        }
    }

    /* ---- Stage 9: Zero gCameraSlotCache camera cache (21 words downward from +0x54) -- */
    pi = (s32 *)((u8 *)gCameraSlotCache + 0x54);
    for (i = 0x15; i >= 0; i--) {
        *pi-- = 0;
    }

    /* ---- Stage 10: Pre-scan — human player bike-id >= 13 → call func_800AE1C8 -- */
    if (gRaceCtrlCount > 0) {
        for (s2 = 0; s2 < gRaceCtrlCount; s2++) {
            configPtr = *(Unk **)((u8 *)&gRaceCtx + 0x16F8 + s2 * 4);
            if (*(s32 *)((u8 *)configPtr + 0x8) >= 13) {
                func_800AE1C8();
                break;
            }
        }
    }

    /* Additional vehicle-type init if game type == 1 and track large */
    if (gGameTypeCode == 1) {
        rc = *(Unk **)gRaceCtrlPtr;
        if ((s8)(*(u8 *)((u8 *)rc + 4)) >= 13) {
            func_800AE368(*(s8 *)((u8 *)rc + 4));
        } else {
            /* check further vehicle slots already done by pre-scan loop */
        }
    }

    /* ---- Stage 11: Main render-pool init loop ----------------------------------
     * For each player slot 0..min(gTrackNodeCount-1, 7):
     *   Compute vehicle slot, set entity state, look up / build camera object.
     * -------------------------------------------------------------------- */
    if (gTrackNodeCount > 0) {
        for (s2 = 0; s2 < gTrackNodeCount && s2 < 8; s2++) {
            renderEnt = &gRenderPool[s2];
            configPtr = *(Unk **)((u8 *)&gRaceCtx + 0x16F8 + s2 * 4);
            bikeId    = *(s32 *)((u8 *)configPtr + 0x8);
            vehicleSlot = bikeId / 13;

            if (s2 < gRaceCtrlCount) {
                /* ---- Human player ---- */
                raceMode = *(s32 *)((u8 *)&gRaceCtx + 0x16D8);
                if (s2 < gRaceMax) {
                    /* Active viewport */
                    if (raceMode == 0xE || raceMode == 0xA) {
                        renderEnt->state = 1;
                        s4 = bikeId + 13;
                    } else {
                        slotF = *(f32 *)((u8 *)gViewportInitTable + (s2 - gRaceMax) * 4);
                        renderEnt->speedParam = slotF;
                        renderEnt->state = 1;
                        s4 = bikeId + 13;
                    }
                } else {
                    /* No active viewport */
                    renderEnt->speedParam = gLodFlag ? gFrameTimerF : gViewInitE;
                    renderEnt->state = 0;
                    s4 = vehicleSlot;
                }
            } else {
                /* ---- AI player ---- */
                renderEnt->state = 3;
                s4 = vehicleSlot;
            }

            /* ---- Camera / render-object setup ---- */
            if (bikeId < 13) {
                vhandle = gVehicleTable[s4];
                vslot   = *(s32 *)((u8 *)vhandle + 0x20);

                if (gLodFlag) {
                    cacheEntry = (Unk **)((u8 *)gCameraSlotCache + vslot * 4);
                    if (*cacheEntry != 0) {
                        renderEnt->bikeObj = (Unk *)*cacheEntry;
                    } else {
                        bikeObj = (Unk *)((u8 *)gVelStateBlock + vslot * 0x34);
                        func_8004E670(vslot, (void *)renderEnt, bikeObj);
                        *cacheEntry = *(Unk **)((u8 *)bikeObj + 0x6C);
                        renderEnt->bikeObj = (Unk *)*cacheEntry;
                    }
                    renderEnt->cameraFlag = 1;
                    *(f32 *)((u8 *)&gCameraObj + 0x5C) = gFrameTimerF;
                    *(f32 *)((u8 *)&gCameraObj + 0x68) = gFrameTimerF;
                    *(f32 *)((u8 *)&gCameraObj + 0xA4) = gFrameTimerF2;
                    *(f32 *)((u8 *)&gCameraObj + 0xB0) = gFrameTimerF2;
                    renderEnt->modelObj = (Unk *)&gCameraObj;
                } else {
                    cacheEntry = (Unk **)((u8 *)gCameraSlotCache + vslot * 4);
                    if (*cacheEntry != 0) {
                        renderEnt->modelObj = (Unk *)*cacheEntry;
                    } else {
                        override = (gGameFlags2 & 0x400) ? 0xE : vslot;
                        func_8004E5F0(override, (void *)renderEnt);
                        *cacheEntry = (Unk *)renderEnt->modelObj;
                    }
                    renderEnt->cameraFlag  = 0;
                    renderEnt->vehicleSlot = *(s32 *)((u8 *)gVehicleTable[s4] + 0x20);
                }
            } else {
                /* Large bike index (>= 13) */
                vhandle = gVehicleTable[s4];
                vslot   = *(s32 *)((u8 *)vhandle + 0x20);
                if (vslot >= 13) { vslot = 13; }

                cacheEntry = (Unk **)((u8 *)gCameraSlotCache + vslot * 4);

                if (gLodFlag) {
                    if (*cacheEntry != 0) {
                        renderEnt->bikeObj    = (Unk *)*cacheEntry;
                        renderEnt->cameraFlag = 1;
                    } else {
                        override = (gGameFlags2 & 0x400) ? 0xE : vslot;
                        func_8004E6C8(override);
                        *cacheEntry           = (Unk *)renderEnt->modelObj;
                        renderEnt->cameraFlag = 0;
                        renderEnt->vehicleSlot = vslot;
                    }
                } else {
                    if (*cacheEntry != 0) {
                        renderEnt->bikeObj    = (Unk *)*cacheEntry;
                        renderEnt->cameraFlag = 1;
                    } else {
                        bikeObj = (Unk *)((u8 *)gVelStateBlock + vslot * 0x34);
                        func_8004E670(vslot, (void *)renderEnt, bikeObj);
                        *cacheEntry           = *(Unk **)((u8 *)bikeObj + 0x6C);
                        renderEnt->cameraFlag = 1;
                    }
                }
            }

            /* Tail: clear unk594; store vehicle table entry */
            renderEnt->unk594       = 0;
            renderEnt->vehicleEntry = *(s32 *)gVehicleTable[s4];
        }

        /* Zero render-pool entries for slots [s2, 10) */
        for (; s2 < 10; s2++) {
            renderEnt = &gRenderPool[s2];
            renderEnt->modelObj = NULL;
        }
    }

    /* ---- Stage 12: Final setup calls ------------------------------------------ */
    gViewInitF = gViewInitF;
    gRenderSlotCount = 0;

    func_80097040();
    func_800EAFE8(7);
    func_800EAFE8(4);

    if (!gLodFlag) {
        func_801342B8();
    }
    if (gSceneTransFlag) {
        func_8013C2A0();
    }

    gSfxSampleTable = 0;
    func_800521BC((s32)gTrackNodePtr);
    func_80146CFC();
    func_80097430();

    if (!gLodFlag) {
        func_801343BC();
        if (gGameFlags2 & 0x400) {
            func_8014AFC8();
        }
    }
    if (gSceneTransFlag) {
        func_8013C334();
    }

    /* Copy gRaceMax into gViewportWatermark; single-player: link first camera */
    gViewportWatermark = gRaceMax;
    if (gRaceMax == 1) {
        entityPhysicsInit(&gCameraData, gRenderPool);
        gCameraData.unk1E0 = 1;
    }

    /* Per-player entity-to-render linkage */
    if (gRaceMax > 0) {
        ep = gEntityPool;
        rp = gRenderPool;
        for (s2 = 0; s2 < gRaceMax; s2++) {
            entityPhysicsInit(ep, rp);
            rp++;
            ep++;
        }
    }

    func_8004E830();
    func_8009B230();

    /* Zero track-render entries beyond human-player count */
    excess = gTrackNodeCount - gRaceCtrlCount;
    if (excess > 0) {
        p8 = (u8 *)gTrackRenderEntries;
        for (i = 0; i < excess; i++) {
            *(s16 *)(p8 + 0) = 0;
            *(s8  *)(p8 + 2) = 0;
            *(s8  *)(p8 + 3) = 0;
            p8 += 6;
        }
    }

    /* ---- Stage 13: Race-state flags and timer setup --------------------------- */
    gUnkFlag_173BC8 = 3;
    if (gLodFlag) {
        gViewportCountA = 0;
        gUnkFlag_173BC8 = 0;
    }

    if (gGameTypeCode == 0xE) {
        gFrameTick = 0x295;
    } else if (gLodFlag) {
        /* preserve existing value — do nothing */
    } else {
        gFrameTick = 0;
    }

    gSubTickCounter = 0;
    gFrameCounter = 0;
    gViewportCountB = 0;

    gPrevFrameTick = gFrameTick;
    func_8004D7A0();
    gRenderFlagC = *(s32 *)&gPrevFrameTick;

    gEntityInputBuf = (void *)((u8 *)&gTimerHiCopy + gPlayerCount * 0x18);
    func_8005CFC4(gEntityInputBuf);
    func_8005E5A4(0);
    func_80102850();

    if (gRaceMax >= 3) {
        gRenderPoolCount = func_8004D4A8(0xFA00);
    }
    gFrameLockFlag = 0;

    if (!gLodFlag) {
        gRenderCamSlot = 1;
        func_80134A44();
    }

    gRenderSyncB = -1;
}
