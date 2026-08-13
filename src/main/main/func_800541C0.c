#include "ultra64.h"

/*
 * gameThreadEntry — main game thread message loop (permanently nonmatching).
 *
 * PERMANENTLY NONMATCHING — SN64 vs IDO ABI difference ($ra at sp+frame-8).
 *
 * Outer loop receives messages on a queue.  Messages:
 *   0x13 = init: call gameStateInit(), reply on output queue
 *   0x14 = frame update
 *   0x15 = no-op
 *   0x16 = frame update with gGameDirty = 1
 *   0x17 = full physics/render tick, reply on output queue
 *
 * Frame: 0xB0 bytes.  Saves $ra/$fp/$s0-$s7/$fs0.
 * $fs0 — persistent f32 frame-timer accumulator (gFrameTimerInit on entry).
 */

/* ---- Forward declarations -------------------------------------------------*/
void gameStateInit(void);
void gameLoopDispatch(void);
s32  func_8007C948(Unk *buf);        /* initialise game timing counters     */
void func_8005C8D4(s32 a0);          /* audio timer set A                   */
void func_8005CF84(s32 a0);          /* audio timer set B                   */
void func_8005CF9C(s32 a0);          /* audio timer set C                   */
void func_8012A290(Unk *entry, s32 mode, f32 v1, f32 v2, s32 flag);
void func_80134C30(void);            /* LOD update                          */
void func_8013BD04(void);            /* frame state update                  */
void func_8013BD90(void);            /* frame dispatch step                 */
void func_8013D7E0(void);            /* gSceneTransFlag callback                 */
void func_800EFF00(void);            /* scene object pre-update             */
void func_80097430(void);            /* scene render dispatch               */
void func_8012A408(void);            /* render frame submit                 */
void func_8005E8AC(void);
void func_800A6844(void);
void func_800AD138(void);
void func_8005D0C8(void);            /* game cleanup tick                   */
void func_80097F10(Unk *a0, s32 a1); /* render-node flush                  */
void func_8009B2BC(void);            /* render dispatch complete            */
void func_800F3F74(Unk *a0, s32 a1, s32 a2, s32 a3,
                   Unk *sp10, s32 sp14, s32 sp18);
void func_80100A04(Unk *a0, Unk *a1, Unk *a2, Unk *a3);
void func_800F8088(Unk *a0, Unk *a1, Unk *a2);
s32  func_80052C04(Unk *a0, s32 a1);
void func_80144DA0(Unk *a0, s32 a1, s32 a2);
void func_80101CC0(Unk *a0, Unk *a1, Unk *a2, Unk *a3);
void func_8005E04C(Unk *a0, s32 a1, f32 a2, s32 a3);
void func_800ED21C(Unk *a0, Unk *a1);
void func_8005CCE0(s32 a0, f32 a1, s32 a2, s32 a3, s32 sp10);
void func_800F2958(Unk *a0, Unk *a1, s32 a2, Unk *a3);
void func_80053F00(s32 a0);

/* ---- External globals -----------------------------------------------------*/
extern f32  gFrameTimerInit;      /* initial frame timer (float)                */
extern f32  gFrameTimerCap;      /* frame timer cap (float)                    */
extern f32  gFrameTimerInc;      /* frame timer increment (float)              */
extern f32  gSkipFrameDecr;      /* skip-frame timer decrement (float)         */
extern f32  gPhysTickOne;      /* 1.0f constant used in physics tick         */
extern Unk  gInitReplyToken;      /* init-complete reply token                  */
extern Unk  gEventQueueSize;      /* physics-tick reply token                   */
extern Unk  gRenderFlagB;      /* deferred-dispatch reply token              */
extern Unk  gRenderStateReply;      /* render-state reply token                   */
extern Unk  gRaceCtx;      /* race config ROM block                      */
extern Unk  gVelStateBlock;      /* velocity state block (per-entity)          */
extern Unk  gAudioStreamStatus;      /* audio streaming status words               */
/* render / entity / player arrays */
extern Unk  gRenderPool;      /* render pool (stride 0x668)                 */
extern Unk  gEntityPool;      /* entity pool base — Entity[], stride 0x228  */
extern Unk  gButtonTable;     /* per-player config table, stride 0x2C       */
extern Unk  gPlayerConfigTable;      /* player-config table (stride 4)             */
extern Unk  gEntityRenderFlags;      /* per-entity render flag array (stride 4)    */
extern Unk  gEntityTrackState;      /* per-entity track-state array (stride 0xD4) */
extern Unk  gTrackRenderEntries;      /* track-render entries (stride 6)            */
extern Unk  gContInputCache;      /* controller input cache (stride 6)          */
extern Unk  gRenderPool2;      /* secondary render pool (stride 0x668)       */
extern Unk  gHandlerMsgBufB;      /* render slot table                          */
extern Unk  gRenderSlotCount;      /* active render slot count                   */
extern Unk  gViewportTileBuf;      /* per-viewport tile buffer (0x80 bytes)      */
extern Unk  gRenderNodeBuf;      /* circular render-node buffer (32 entries)   */
extern Unk  gEntityScratch;      /* entity pool scratch area                   */
/* frame / game-state globals */
extern s32  gFadeCounter;      /* fade counter                               */
extern s32  gFrameLockFlag;      /* frame lock flag                            */
extern s32  gGameDirty;      /* game-state dirty flag                      */
extern s32  gSkipFrameFlag;      /* skip-frame flag                            */
extern s32  gLodShadow;      /* LOD viewport shadow                        */
extern s32  gLodFlag;      /* LOD-enable flag                            */
extern s32  gRaceMax;      /* active viewport count (gRaceMax)           */
extern s32  gFrameAccumA;      /* frame accumulator A                        */
extern s32  gFrameAccumB;      /* frame accumulator B                        */
extern s32  gFrameSkipShadow;      /* frame skip shadow                          */
extern s32  gViewportWatermark;      /* viewport-pool watermark                    */
extern s32  gFrameSyncCountA;      /* frame sync counter A                       */
extern s32  gActiveEntityIdx;      /* active entity index                        */
extern s32  gFrameSyncFlag;      /* frame sync flag                            */
extern s32  gFrameSyncCountB;      /* frame sync counter B                       */
extern s32  gRenderCompleteFlag;      /* render-complete flag                       */
extern s32  gRenderFade;      /* render fade counter                        */
extern s32  gDeferredFlag;      /* deferred-dispatch flag                     */
extern s32  gCurEntityPtr;      /* current entity pointer cache               */
extern s32  gEntityRenderCount;      /* entity render-slot count                   */
extern s32  gFrameTick;      /* frame tick counter                         */
extern s32  gSubTickCounter;      /* sub-tick counter                           */
extern s32  gPrevFrameTick;      /* prev frame tick                            */
extern s32  gContSnapshot;      /* controller state snapshot                  */
extern s32  gTimerLo;      /* timing counter (from osGetTime)            */
extern s32  gTimerLoCopy;      /* timing counter copy                        */
extern s32  gTrackNodeCount;      /* active entity count                        */
extern s32  gSfxLodFlag;      /* sfx-lod flag                               */
extern s32  gSceneTransFlag;      /* scene-transition flag                      */
extern s32  gRaceCtrlCount;      /* human-player count                         */
extern s32  gRaceRestartFlag;      /* race-restart flag                          */
extern s32  gUnkFlag_173BC8;      /* ??? */
extern s32  gFrameCounter;      /* frame counter                              */
extern s32  gControllerCount;      /* controller-select state                    */
extern s32  gRenderSyncFlag;      /* render-sync flag                           */

/* nonmatching */
void gameThreadEntry(Unk *args) {
    /* All variable declarations at function scope (IDO C89).        */

    OSMesgQueue *outQueue;   /* sp+0x5C: reply queue  (from args->0)       */
    OSMesgQueue *inQueue;    /* sp+0x60: receive queue (from args->4)      */
    OSMesg       msgBuf;     /* sp+0x58: message receive buffer            */
    s32          msgType;

    /* Per-entity inner-loop pointers — all advanced at the loop tail */
    Unk *s2;                 /* render pool entry (stride 0x668)           */
    s32  s3;                 /* entity index                               */
    s32  fp_off;             /* entity index * 4 (stack-table byte offset) */
    Unk *s6;                 /* track-render entry ptr (stride 6)          */
    Unk *s7_loc;             /* player-config ptr (stride 4)               */
    Unk *sp68;               /* render-pool byte offset (0 → incr 0x668)  */
    Unk *sp6C;               /* gButtonTable ptr (stride 0x2C)             */
    Unk *sp70;               /* gContInputCache ptr (stride 6)                  */
    Unk *sp74;               /* gEntityRenderFlags ptr (stride 4)                  */
    Unk *sp78;               /* gEntityTrackState ptr (stride 0xD4)               */
    Unk *sp7C;               /* gRenderPool2 ptr (stride 0x668)              */

    /* Per-entity stack table (5 slots * 4 bytes, at sp+0x28..0x3C)  */
    s32  entityFlags[5];

    /* State-4 physics scratch (sp+0x38..0x50)                       */
    f32  phys0, phys1, phys2, phys3, phys4, phys5;

    /* Persistent frame-timer accumulator (== $fs0)                  */
    f32  fs0;

    /* Temporaries                                                    */
    Unk *renderEntry;
    Unk *entryPtr;
    s32  i;
    s32  v0t;
    s32  savedFrame;         /* sp+0x64                                    */
    Unk *renderNode;
    Unk *renderNodeNext;
    s32  renderDir;
    s32  renderSlot;
    s32  packed;
    s32  slot;
    s32  dir;
    s32  state;
    s32  stepResult;
    s32  tick;
    u16  ctrlWord;
    s32  notMask;
    f32  inc;
    Unk *vstate;
    s32  raceMode;
    s32  active;
    s32  cnt;
    s32  diff;
    s32  a_val, b_val, d_val;

    /* Initialise per-entity stack table */
    entityFlags[0] = 0;
    entityFlags[1] = 0;
    entityFlags[2] = 0;
    entityFlags[3] = 0;
    entityFlags[4] = 0;

    /* Load initial frame-timer accumulator */
    fs0 = gFrameTimerInit;

    /* Timing init; result packed into gTimerLo (done in asm) */
    func_8007C948(NULL);

    /* Unpack queues from args struct */
    outQueue = *(OSMesgQueue **)((u8 *)args + 0);
    inQueue  = *(OSMesgQueue **)((u8 *)args + 4);

    /* ================================================================
     * Outer dispatch loop (func_80054258)
     * ================================================================ */
    while (1) {
        osRecvMesg(inQueue, &msgBuf, 1);
        msgType = *(s32 *)&msgBuf;

        if (msgType == 0x13) {
            gameStateInit();
            gGameDirty = 1;
            osSendMesg(outQueue, &gInitReplyToken, 0);
            continue;
        }
        if (msgType == 0x14) {
            goto frame_update;
        }
        if (msgType == 0x15) {
            continue;
        }
        if (msgType == 0x16) {
            gGameDirty = 1;
            goto frame_update;
        }
        if (msgType == 0x17) {
            goto big_update;
        }
        continue;

        /* ---- Frame update path (.L800542E8) --------------------------------*/
    frame_update:
        gFrameLockFlag = 0;

        /* Fade-in countdown */
        if (gFadeCounter != 0 && gGameDirty != 0) {
            if (gFadeCounter == 4 && gRaceCtrlCount > 0) {
                renderEntry = &gRenderPool;
                for (i = 0; i < gRaceCtrlCount; i++) {
                    func_8012A290(renderEntry, 4, 1.0f, 8.0f, 0);
                    renderEntry = (Unk *)((u8 *)renderEntry + 0x668);
                }
            }
            gFadeCounter--;
            if (gFadeCounter == 0) {
                gFrameTick = 0x1A4;
            }
        }

        if (!gLodFlag) {
            func_80134C30();
        }

        gFrameSkipShadow = gSkipFrameFlag;
        if (gSkipFrameFlag != 0) {
            goto skip_frame;
        }

        /* ---- Main frame path -----------------------------------------------*/
        gFrameAccumA++;
        gFrameCounter++;
        gPrevFrameTick = gFrameTick;
        gFrameTick++;

        if (!gGameDirty) {
            func_8013BD04();
            goto timer_check;
        }
        gSubTickCounter++;
        func_8013BD04();
        savedFrame = gFrameCounter;

    timer_check:
        if (fs0 < gFrameTimerCap) {
            fs0 += gFrameTimerInc;
            if (fs0 > gFrameTimerCap) {
                fs0 = gFrameTimerCap;
            }
            func_8005C8D4((s32)((f32)(*(s32 *)((u8 *)&gRaceCtx + 0xB00)) * fs0));
            func_8005CF84((s32)((f32)(*(s32 *)((u8 *)&gRaceCtx + 0xAFC)) * fs0));
            func_8005CF9C((s32)((f32)(*(s32 *)((u8 *)&gRaceCtx + 0xB04)) * fs0));
        }

        if (gSceneTransFlag != 0) {
            func_8013D7E0();
        }

        /* Clear render-pool slot 0x570 for each entity */
        if (gTrackNodeCount > 0) {
            entryPtr = &gRenderPool;
            for (i = 0; i < gTrackNodeCount; i++) {
                *(s32 *)((u8 *)entryPtr + 0x570) = 0;
                entryPtr = (Unk *)((u8 *)entryPtr + 0x668);
            }
        }

        /* ---- Per-entity state machine (.L80054504) -------------------------*/
        if (gTrackNodeCount <= 0) {
            goto post_entity_loop;
        }

        s3     = 0;
        fp_off = 0;
        s2     = &gRenderPool;
        s7_loc = &gPlayerConfigTable;
        sp68   = NULL;
        sp6C   = &gButtonTable;
        sp70   = &gContInputCache;
        sp74   = &gEntityRenderFlags;
        sp78   = NULL;
        sp7C   = &gRenderPool2;

        while (1) {
            gEntityRenderCount = 1;
            state = *(s32 *)((u8 *)s2 + 0x588);

            if (state >= 6) {
                goto entity_tail;
            }

            switch (state) {
            case 0:
                gCurEntityPtr = (s32)sp70;
                ctrlWord   = *(u16 *)sp70;
                notMask    = ~entityFlags[fp_off / 4];
                if ((ctrlWord & (u16)notMask & 0x1000) != 0) {
                    if (gDeferredFlag == 0 && gFrameTick >= 0x10 &&
                        *(s32 *)((u8 *)s2 + 0x450) == 0) {
                        gSkipFrameFlag  = 1;
                        gRenderFade  = 0;
                        gFrameSyncCountB  = 0;
                        gLodShadow  = 0;
                        gRenderCompleteFlag  = 0;
                        gActiveEntityIdx  = s3;
                        gFrameSyncCountA  = 0;
                        gFrameAccumB  = 0;
                        gRaceRestartFlag  = 0;
                        gSfxLodFlag  = 1;
                        func_8005CCE0(0x19, 1.0f,   0x10000, 0x40, 0x20);
                        func_8005CCE0(0x10, 0.25f,  0xC350,  0x40, 0);
                        gGameDirty  = 1;
                    }
                }
                entryPtr = (Unk *)gCurEntityPtr;
                if (*(s32 *)((u8 *)s2 + 0x450) == 0) {
                    func_800F3F74(entryPtr, s3, s3,
                                  *(s32 *)s7_loc, sp6C,
                                  gGameDirty, gFrameCounter);
                    if (gUnkFlag_173BC8 == 0 && *(s32 *)((u8 *)s2 + 0x450) == 0) {
                        func_80100A04(entryPtr, s2, sp6C, NULL);
                    } else {
                        func_80100A04(s2, NULL, NULL, sp6C);
                    }
                } else {
                    if (gGameDirty != 0) {
                        gCurEntityPtr = (s32)s6;
                        func_800F8088(s6, s2, &gEntityScratch);
                    }
                    func_800F3F74((Unk *)gCurEntityPtr, s3, s3,
                                  gGameDirty, &gEntityScratch,
                                  gFrameCounter, *(s32 *)s7_loc);
                    if (gUnkFlag_173BC8 == 0 && *(s32 *)((u8 *)s2 + 0x450) == 0) {
                        func_80100A04((Unk *)gCurEntityPtr, s2,
                                      sp6C, NULL);
                    } else {
                        func_80100A04(s2, NULL, NULL, sp6C);
                    }
                }
                *(s32 *)s7_loc = *(u16 *)sp70;
                *(s32 *)sp74   = *(s8 *)((u8 *)sp70 + 2);
                goto entity_tail_counter;

            case 1:
                if (gGameDirty != 0) {
                    gCurEntityPtr = (s32)s6;
                    func_800F8088(s6, s2, &gEntityScratch);
                }
                func_800F3F74((Unk *)gCurEntityPtr, s3, s3,
                              gGameDirty, &gEntityScratch,
                              gFrameCounter, *(s32 *)s7_loc);
                if (gUnkFlag_173BC8 == 0 && *(s32 *)((u8 *)s2 + 0x450) == 0) {
                    func_80100A04((Unk *)gCurEntityPtr, s2, NULL, &gEntityScratch);
                } else {
                    func_80100A04(s2, NULL, NULL, &gEntityScratch);
                }
                *(s32 *)s7_loc = *(u16 *)s6;
                *(s32 *)sp74   = *(s8 *)((u8 *)s6 + 2);
                goto state_machine_step;

            case 4:
                phys0 = *(f32 *)((u8 *)s2 + 0);
                phys1 = *(f32 *)((u8 *)s2 + 4);
                phys2 = *(f32 *)((u8 *)s2 + 8);
                phys3 = -(*(f32 *)((u8 *)s2 + 0x40));
                phys4 = -(*(f32 *)((u8 *)s2 + 0x44));
                phys5 = -(*(f32 *)((u8 *)s2 + 0x48));

                if (*(s32 *)((u8 *)s2 + 0x558) < 0xFF) {
                    goto state4_slow;
                }
                func_80101CC0(s2,
                              (Unk *)&phys0,
                              (Unk *)((u8 *)&gRenderPool + 0x398 + (s32)sp68),
                              sp7C);
                if (*(s32 *)((u8 *)s2 + 0x450) == 0) {
                    i = *(s32 *)&gRenderSlotCount;
                    *(s32 *)((u8 *)&gHandlerMsgBufB + i * 8 + 0) = s3;
                    *(s32 *)((u8 *)&gHandlerMsgBufB + i * 8 + 4) = gFrameTick;
                    *(s32 *)&gRenderSlotCount = i + 1;
                    *(s32 *)((u8 *)s2 + 0x450) = 1;
                    *(s32 *)((u8 *)s2 + 0x454) = gFrameTick;
                    *(s32 *)((u8 *)s2 + 0x458) = 0xFF;
                    *(s32 *)((u8 *)s2 + 0x45C) = gFrameTick -
                                                  *(s32 *)((u8 *)s2 + 0x2A4);
                }
                if (*(s32 *)((u8 *)s2 + 0x568) != 0) {
                    *(s32 *)(*(s32 *)((u8 *)s2 + 0x568) + 0x1DC) = 0;
                }
                *(s32 *)((u8 *)s2 + 0x588) = 5;
                *(s32 *)((u8 *)s2 + 0x558) = 0xFF;
                inc = *(f32 *)&gPhysTickOne;
                *(f32 *)((u8 *)s2 + 0x04) += inc;
                *(f32 *)((u8 *)s2 + 0x14) += inc;
                *(f32 *)((u8 *)s2 + 0x20) += inc;
                *(f32 *)((u8 *)s2 + 0x2C) += inc;
                *(f32 *)((u8 *)s2 + 0x38) += inc;
                if (*(s32 *)((u8 *)s2 + 0x64C) == 1) {
                    vstate = (Unk *)((u8 *)&gVelStateBlock + (s32)sp78);
                    *(f32 *)((u8 *)vstate + 0x04) += inc;
                    *(f32 *)((u8 *)vstate + 0x10) += inc;
                    *(f32 *)((u8 *)vstate + 0x1C) += inc;
                    *(f32 *)((u8 *)vstate + 0x28) += inc;
                    *(f32 *)((u8 *)vstate + 0x34) += inc;
                    *(f32 *)((u8 *)vstate + 0x40) += inc;
                    *(f32 *)((u8 *)vstate + 0x4C) += inc;
                    *(f32 *)((u8 *)vstate + 0x58) += inc;
                }
                goto entity_tail;

            state4_slow:
                if (*(s32 *)((u8 *)s2 + 0x560) < gRaceCtrlCount) {
                    if (gGameDirty != 0) {
                        gCurEntityPtr = (s32)s6;
                        func_800F8088(s6, s2, &gEntityScratch);
                    }
                    func_800F3F74((Unk *)gCurEntityPtr, s3, s3,
                                  gGameDirty, &gEntityScratch,
                                  gFrameCounter, *(s32 *)s7_loc);
                    *(s32 *)s7_loc = *(u16 *)s6;
                    *(s32 *)sp74   = *(s8 *)((u8 *)s6 + 2);
                } else {
                    if (gGameDirty != 0) {
                        gCurEntityPtr = (s32)s6;
                        func_800F8088(s6, s2, &gEntityScratch);
                    }
                    func_800F3F74((Unk *)gCurEntityPtr, s3, s3,
                                  gGameDirty, &gEntityScratch,
                                  gFrameCounter, *(s32 *)s7_loc);
                    *(s32 *)s7_loc = *(u16 *)s6;
                    *(s32 *)sp74   = *(s8 *)((u8 *)s6 + 2);
                }
                goto entity_tail_counter;

            default: /* states 2, 3, 5 */
                goto entity_tail;
            }

        state_machine_step:
            stepResult = func_80052C04(s2, 0);
            if (stepResult != 0) {
                *(s32 *)((u8 *)s2 + 0x588) = 4;
                func_80144DA0(s2, 0, 0);
                func_80144DA0(s2, 0, 1);
                goto entity_tail;
            }

        entity_tail_counter:
            tick = *(s32 *)((u8 *)s2 + 0x558) + 1;
            *(s32 *)((u8 *)s2 + 0x558) = tick;
            if ((tick & 0xF) == 0) {
                func_8005E04C(s2, 0xB, 0.4375f, 0x10000);
            }

        entity_tail:
            /* Render-node traversal */
            if (*(s32 *)((u8 *)s2 + 0x568) != 0 && gEntityRenderCount > 0) {
                for (i = 0; i < gEntityRenderCount; i++) {
                    func_80097F10(*(Unk **)((u8 *)s2 + 0x568), 0);
                }
            }

            /* Circular render-buffer advance */
            packed = *(s32 *)((u8 *)s2 + 0x430);
            slot   = (packed >> 11) & 0x1F;
            dir    = packed & 0x7FF;
            renderNode = *(Unk **)((u8 *)&gRenderNodeBuf + slot * 4);
            if (renderNode == NULL) {
                renderDir = (dir < 0x100) ? -1 : (dir >= 0x701 ? 1 : 0);
                slot = (slot + renderDir) & 0x1F;
                renderNode = *(Unk **)((u8 *)&gRenderNodeBuf + slot * 4);
            }
            if (renderNode != NULL) {
                renderNodeNext = s2;
                do {
                    func_800ED21C(renderNode, renderNodeNext);
                    renderNode = *(Unk **)((u8 *)renderNode + 0x34);
                    renderNodeNext = s2;
                } while (renderNode != NULL);

                packed = *(s32 *)((u8 *)renderNodeNext + 0x430);
                slot   = (packed >> 11) & 0x1F;
                dir    = packed & 0x7FF;
                renderSlot = slot;
                if (dir < 0x100) {
                    renderSlot = (slot - 1) & 0x1F;
                } else if (dir < 0x701) {
                    renderSlot = slot;
                } else {
                    renderSlot = (slot + 1) & 0x1F;
                }
                *(Unk **)((u8 *)&gRenderNodeBuf + renderSlot * 4) = renderNodeNext;
                s2 = (Unk *)((u8 *)s2 + 0x668);
            }

            /* Advance all 6 per-entity iteration pointers */
            s7_loc = (Unk *)((u8 *)s7_loc + 4);
            fp_off += 4;
            s6     = (Unk *)((u8 *)s6 + 6);
            s3++;
            sp68   = (Unk *)((u8 *)sp68 + 0x668);
            sp6C   = (Unk *)((u8 *)sp6C + 0x2C);
            sp70   = (Unk *)((u8 *)sp70 + 6);
            sp74   = (Unk *)((u8 *)sp74 + 4);
            sp78   = (Unk *)((u8 *)sp78 + 0xD4);
            sp7C   = (Unk *)((u8 *)sp7C + 0x668);

            if (s3 >= gTrackNodeCount) {
                break;
            }
        } /* end inner entity loop */

    post_entity_loop:
        /* Clear render-pool slot 0x56C when 0x570 is zero */
        if (gTrackNodeCount > 0) {
            entryPtr = &gRenderPool;
            for (i = 0; i < gTrackNodeCount; i++) {
                if (*(s32 *)((u8 *)entryPtr + 0x570) == 0) {
                    *(s32 *)((u8 *)entryPtr + 0x56C) = 0;
                }
                entryPtr = (Unk *)((u8 *)entryPtr + 0x668);
            }
        }

        gEntityRenderCount = gFrameAccumA;
        func_8009B2BC();

        /* Viewport-pool watermark: flush extra entity slot */
        if (gRaceMax < gViewportWatermark) {
            i = gRaceMax;
            func_80097F10((Unk *)((u8 *)&gEntityPool + (i * 0x228)), 0);
        }

        /* Frame-dirty processing */
        if (gGameDirty != 0) {
            entryPtr = (Unk *)((u8 *)&gViewportTileBuf + 0x7C);
            for (i = 0; i <= 0x1F; i++) {
                *(s32 *)entryPtr = 0;
                entryPtr = (Unk *)((u8 *)entryPtr - 4);
            }

            if (gTrackNodeCount > 0) {
                entryPtr = &gRenderPool;
                for (i = 0; i < gTrackNodeCount; i++) {
                    if (*(s32 *)((u8 *)entryPtr + 0x598) != 1) {
                        slot = ((*(s32 *)((u8 *)entryPtr + 0x430)) >> 9) & 0x7C;
                        v0t = *(s32 *)((u8 *)&gViewportTileBuf + slot);
                        *(s32 *)((u8 *)entryPtr + 0x654) = v0t;
                        *(s32 *)((u8 *)&gViewportTileBuf + slot) = (s32)entryPtr;
                    }
                    entryPtr = (Unk *)((u8 *)entryPtr + 0x668);
                }
            }

            func_800EFF00();
            func_80097430();
            func_8012A408();
            func_8005E8AC();
            func_800A6844();
            func_800AD138();
            func_8005D0C8();

            gGameDirty  = 0;
            gFrameAccumA  = 0;
        }

        if (gDeferredFlag != 0) {
            goto deferred_dispatch;
        }

        /* Race-mode completion checks */
        raceMode = *(s32 *)((u8 *)&gRaceCtx + 0x16D8);
        active   = 0;

        if (raceMode == 4) {
            if (gRaceCtrlCount > 0) {
                entryPtr = &gRenderPool;
                for (i = 0; i < gRaceCtrlCount; i++) {
                    if (*(s32 *)((u8 *)entryPtr + 0x450) != 0 &&
                        *(s32 *)((u8 *)entryPtr + 0x454) + 0xB4 < gFrameTick) {
                        active++;
                    }
                    entryPtr = (Unk *)((u8 *)entryPtr + 0x668);
                }
            }
            if (active >= gRaceCtrlCount - 1) {
                gDeferredFlag = 1;
            }
            goto deferred_dispatch;
        }

        if (gLodFlag != 0) {
            if (gRaceCtrlCount > 0) {
                entryPtr = &gRenderPool;
                for (i = 0; i < gRaceCtrlCount; i++) {
                    if (*(s32 *)((u8 *)entryPtr + 0x450) != 0 &&
                        *(s32 *)((u8 *)entryPtr + 0x588) == 5 &&
                        *(s32 *)((u8 *)entryPtr + 0x454) + 0xB4 < gFrameTick) {
                        active++;
                    }
                    entryPtr = (Unk *)((u8 *)entryPtr + 0x668);
                }
            }
            if (gRaceCtrlCount >= 2 && active >= gRaceCtrlCount - 1) {
                gDeferredFlag = 1;
            }
            goto deferred_dispatch;
        }

        if (raceMode == 1) {
            if (*(s32 *)((u8 *)&gRenderPool + 0x588) == 5 &&
                *(s32 *)((u8 *)&gRenderPool + 0x454) + 0xB4 < gFrameTick) {
                gDeferredFlag = 1;
            }
            goto deferred_dispatch;
        }

        if (raceMode == 2) {
            if (*(s32 *)((u8 *)&gRenderPool + 0x588) == 5 &&
                *(s32 *)((u8 *)&gRenderPool + 0x454) + 0x1E < gFrameTick) {
                gDeferredFlag = 1;
            }
            goto deferred_dispatch;
        }

        if (raceMode == 14) {
            /* Count active entities; check audio streaming state */
            if (gRaceCtrlCount > 0) {
                entryPtr = &gRenderPool;
                for (i = 0; i < gRaceCtrlCount; i++) {
                    if (*(s32 *)((u8 *)entryPtr + 0x450) != 0 &&
                        *(s32 *)((u8 *)entryPtr + 0x588) == 5) {
                        s32 alt = *(s32 *)((u8 *)entryPtr + 0x5A4);
                        if (alt != 0) {
                            if (*(s32 *)((u8 *)entryPtr + 0x454) + alt < gFrameTick) {
                                active++;
                            }
                        } else {
                            if (*(s32 *)((u8 *)entryPtr + 0x454) + 0x3C < gFrameTick) {
                                active++;
                            }
                        }
                    }
                    entryPtr = (Unk *)((u8 *)entryPtr + 0x668);
                }
            }
            if (active == gRaceCtrlCount) {
                gDeferredFlag = 1;
            }
        }

        if (*(s32 *)((u8 *)&gRaceCtx + 0x16D8) == 14) {
            if (gFrameTick >= 0x1C21) {
                gDeferredFlag = 1;
            }
            {
                Unk *sbuf = &gAudioStreamStatus;
                for (i = 0; i < 4; i++) {
                    if ((*(u16 *)sbuf & 0x9000) != 0) {
                        gDeferredFlag = 1;
                        gFrameSyncFlag = 1;
                        goto deferred_dispatch;
                    }
                    sbuf = (Unk *)((u8 *)sbuf + 6);
                }
            }
        }

    deferred_dispatch:
        func_8013BD90();
        if (gDeferredFlag == 1) {
            osSendMesg(outQueue, &gRenderFlagB, 0);
        }
        gRenderSyncFlag = 0;
        gContSnapshot = *(u16 *)((Unk *)gCurEntityPtr);
        osSendMesg(outQueue, &gRenderStateReply, 0);
        continue;

        /* ---- Skip-frame path (.L800551E4) ----------------------------------*/
    skip_frame:
        if (fs0 > 0.0f) {
            fs0 -= gSkipFrameDecr;
            if (fs0 < 0.0f) {
                fs0 = 0.0f;
            }
            func_8005C8D4((s32)((f32)(*(s32 *)((u8 *)&gRaceCtx + 0xB00)) * fs0));
            func_8005CF84((s32)((f32)(*(s32 *)((u8 *)&gRaceCtx + 0xAFC)) * fs0));
            func_8005CF9C((s32)((f32)(*(s32 *)((u8 *)&gRaceCtx + 0xB04)) * fs0));
        }

        /* Per-viewport render update */
        if (gRaceCtrlCount > 0) {
            Unk *ss0;
            Unk *ss1;
            Unk *ss2ent;
            Unk *ss6ent;
            Unk *ss4ent;

            s3     = 0;
            ss1    = &gContInputCache;
            s7_loc = &gEntityTrackState;
            sp74   = &gEntityRenderFlags;
            s7_loc = &gPlayerConfigTable;
            ss0    = &gRenderPool;
            ss2ent = &gButtonTable;

            for (s3 = 0; s3 < gRaceCtrlCount; s3++) {
                if (s3 == gActiveEntityIdx) {
                    func_80053F00(s3);
                }
                if (*(s32 *)((u8 *)ss0 + 0x588) == 0) {
                    if (*(s32 *)((u8 *)ss0 + 0x568) != 0) {
                        if (*(s32 *)((u8 *)ss2ent + 8)  != (s32)0x8000 &&
                            *(s32 *)((u8 *)ss2ent + 0xC) != (s32)0x8000) {
                            func_800F2958(ss0, ss1, *(s32 *)s7_loc, ss2ent);
                        }
                        func_80097F10(*(Unk **)((u8 *)ss0 + 0x568), 0);
                    }
                }
                *(s32 *)s7_loc = *(u16 *)ss1;
                *(s32 *)sp74   = *(s8 *)((u8 *)ss1 + 2);

                ss0    = (Unk *)((u8 *)ss0 + 0x668);
                ss2ent = (Unk *)((u8 *)ss2ent + 0x2C);
                ss1    = (Unk *)((u8 *)ss1 + 6);
                s7_loc = (Unk *)((u8 *)s7_loc + 4);
                sp74   = (Unk *)((u8 *)sp74 + 4);
            }
        }

        /* Frame-counter trackers */
        a_val = gFrameSyncCountB;
        b_val = gLodShadow;
        if (a_val < b_val) {
            d_val = b_val - a_val;
            gFrameSyncCountB = (d_val < 0x30) ? a_val + d_val : a_val + 0x30;
        } else if (a_val > b_val) {
            d_val = a_val - b_val;
            gFrameSyncCountB = (d_val < 0x30) ? a_val - d_val : a_val - 0x30;
        }
        a_val = gFrameSyncCountA;
        b_val = gFrameAccumB;
        if (a_val < b_val) {
            d_val = b_val - a_val;
            gFrameSyncCountA = (d_val < 0x30) ? a_val + d_val : a_val + 0x30;
        } else if (a_val > b_val) {
            d_val = a_val - b_val;
            gFrameSyncCountA = (d_val < 0x30) ? a_val - d_val : a_val - 0x30;
        }

        /* Fade counter update */
        if (gRenderCompleteFlag != 0) {
            cnt = gRenderFade;
            gRenderFade = (cnt < 8) ? 0 : cnt - 8;
        } else {
            cnt  = gRenderFade;
            diff = 0xFF - cnt;
            gRenderFade = (diff < 0xC) ? cnt + diff : cnt + 0xC;
        }

        /* Race-mode 0xE streaming check */
        if (*(s32 *)((u8 *)&gRaceCtx + 0x16D8) == 14) {
            if (gFrameTick >= 0x1C21) {
                gDeferredFlag = 1;
            }
            {
                Unk *sbuf = &gAudioStreamStatus;
                for (i = 0; i < 4; i++) {
                    if ((*(u16 *)sbuf & 0x9000) != 0) {
                        gDeferredFlag = 1;
                        gFrameSyncFlag = 1;
                        goto skip_frame_send;
                    }
                    sbuf = (Unk *)((u8 *)sbuf + 6);
                }
            }
        }

    skip_frame_send:
        if (gDeferredFlag == 1) {
            osSendMesg(outQueue, &gRenderFlagB, 0);
        }
        gRenderSyncFlag = 0;
        gContSnapshot = *(u16 *)((Unk *)gCurEntityPtr);
        osSendMesg(outQueue, &gRenderStateReply, 0);
        continue;

        /* ---- Big update path (.L80055564) ----------------------------------*/
    big_update:
        if (gSkipFrameFlag != 0) {
            /* Restore timing from saved copy */
            *(u16 *)&gTimerLo             = *(u16 *)&gTimerLoCopy;
            *(u16 *)((u8 *)&gTimerLo + 2) = *(u16 *)((u8 *)&gTimerLoCopy + 2);
        } else {
            /* Save current timing */
            *(u16 *)&gTimerLoCopy             = *(u16 *)&gTimerLo;
            *(u16 *)((u8 *)&gTimerLoCopy + 2) = *(u16 *)((u8 *)&gTimerLo + 2);
        }
        gameLoopDispatch();
        osSendMesg(outQueue, &gEventQueueSize, 0);
        continue;
    }
}
