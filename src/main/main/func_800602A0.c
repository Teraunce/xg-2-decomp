#include "ultra64.h"

/*
 * frameDispatchThread (func_800602A0) — frame-event polling loop.
 *
 * PERMANENTLY NONMATCHING — SN64 vs IDO ABI + alabel entry points.
 *
 * The assembly file is one large body whose stack frame persists across all
 * the alabel targets (func_8006030C, func_80060310, func_800607D4, etc.).
 * In C, the cross-label register state is modelled with static variables.
 *
 * Message dispatch (msg received from inQueue):
 *   0x0B → set phase=6, re-enter receive loop
 *   0x0C-0x12 → no-op, re-enter loop
 *   0x13 → race countdown init; send &gRaceCountdownMsg reply
 *   0x14 → race state machine (func_80060378 body)
 *   0x15-0x16 → no-op
 *   0x17 → physics tick; send &gEventQueueSize reply
 *   0x18-0x1A → no-op
 *   0x1B → end-of-race; send &gRaceEndMsg reply
 *
 * Phase state machine (s1):
 *   0 = idle       2 = intro countdown   4 = wait overlay
 *   1 = race live  3 = transition        5/6 = loading   7 = intro running
 */

/* ---- Forward declarations -------------------------------------------------*/
void func_8005F6B8(void);
void func_8005F980(s32 a0);
void func_8005C88C(s32 a0);
void func_8005C8D4(s32 a0);
void func_8005C8B8(void);
void func_8005C8EC(s32 a0, s32 a1);
void func_8005CF84(s32 a0);
void func_8005CF9C(s32 a0);
void func_8005CFB4(void);
void func_800600D8(s32 a0, s32 a1);
s32  func_800625C0(void);
void func_800B0F10(void);
void func_80072E00(s32 a0);

/* ---- External data --------------------------------------------------------*/
extern f32  gAudioVolScale;           /* audio volume scale (fs1 initial value) */
extern s32  gAudioBufState;           /* audio buffer state                     */
extern s32  gFrameEventCount;           /* frame-event counter                    */
extern s32  gRaceReadyFlag;           /* race-ready flag                        */
extern s32  gGameFlags2;           /* game-flags/resolution                  */
extern s32  gRaceTriggerFlag;           /* race-trigger flag                      */
extern s32  gContPakUpdateFlag;           /* game-over flag                         */
extern Unk  gRaceStartMsg;           /* race-start msg token                   */
extern s32  gRaceRestartFlag;           /* race-restart flag                      */
extern Unk  gEventQueueSize;           /* physics-tick reply token               */
extern Unk  gRaceCountdownMsg;           /* race-countdown reply token             */
extern s32  gLoopCount;           /* overlay entry index                    */
extern s32  gFrameSyncFlag;           /* frame sync flag                        */
extern Unk  gOverlayReadyMsg;           /* overlay-ready msg token                */
extern Unk  gRaceIntroDoneMsg;           /* race-intro-done msg token              */
extern Unk  gFrameSyncMsg;           /* frame-sync msg token                   */
extern Unk  gRaceEndMsg;           /* end-of-race msg token                  */
extern Unk  gRaceTriggerMsg;           /* race-trigger msg token                 */
extern s32  gSceneOverlaySlot;           /* scene overlay slot                     */
extern Unk  gRaceCtx;           /* race config ROM block                  */

/* ---- Static shared state (lives in func_800602A0's stack frame in asm) ---*/
static OSMesgQueue *sRecvQueue;   /* s2: message source queue (from args[0])*/
static OSMesgQueue *sSendQueue;   /* s6: reply destination queue (args[4])  */
static s32  sPhase;               /* s1: game phase (0-7)                   */
static s32  sRaceProgress;        /* s0: race progress/countdown counter    */
static s32  sTickCount;           /* s4: physics tick counter               */
static f32  sVolScale;            /* fs1: audio volume scale                */

/* ---- Internal helpers -----------------------------------------------------*/
static void frameRecvAndDispatch(void);       /* the polling loop body      */
static void frameHandle14(void);              /* msg 0x14: race state mach. */
static void frameSendAndLoop(Unk *reply);     /* osSendMesg then loop       */

/* ---------------------------------------------------------------------------
 * func_800602A0 — entry: extract queues from args, init state, start loop.
 * ---------------------------------------------------------------------------*/
void frameDispatchThread(Unk *args) {
    sPhase        = 0;
    sRaceProgress = 0;
    sTickCount    = 0;
    sRecvQueue    = *(OSMesgQueue **)((u8 *)args + 0);
    sSendQueue    = *(OSMesgQueue **)((u8 *)args + 4);
    sVolScale     = gAudioVolScale;
    frameRecvAndDispatch();
}

/* ---------------------------------------------------------------------------
 * func_8006030C — alabel entry: restart the receive loop.
 * ---------------------------------------------------------------------------*/
void func_8006030C(void) {
    frameRecvAndDispatch();
}

/* ---------------------------------------------------------------------------
 * func_80060310 — alabel entry: same; used by jtbl_8004BF80[1..7] etc.
 * ---------------------------------------------------------------------------*/
void func_80060310(void) {
    frameRecvAndDispatch();
}

/* ---------------------------------------------------------------------------
 * frameRecvAndDispatch — blocking message receive + dispatch.
 * ---------------------------------------------------------------------------*/
static void frameRecvAndDispatch(void) {
    OSMesg msgBuf;
    s32    msgType;
    s32    idx;

    while (1) {
        osRecvMesg(sSendQueue, &msgBuf, 1);
        msgType = *(s32 *)&msgBuf;
        idx     = msgType - 0xB;
        if ((u32)idx >= 0x11u) {
            continue;  /* out-of-range: loop */
        }

        switch (msgType) {
        case 0xB:
            sPhase = 6;
            /* loop back (func_8006030C) */
            break;

        case 0x13:
            func_8005F6B8();
            if (sPhase != 0) {
                sPhase = 2;
            } else {
                func_8005F980(1);
                sPhase = 4;
            }
            sRaceProgress = 0;
            frameSendAndLoop(&gRaceCountdownMsg);
            return; /* frameSendAndLoop loops forever */

        case 0x14:
            frameHandle14();
            return; /* frameHandle14 always calls frameSendAndLoop */

        case 0x17:
            func_800600D8(sPhase, sRaceProgress);
            sTickCount++;
            frameSendAndLoop(&gEventQueueSize);
            return;

        case 0x1B:
            func_80072E00((u32)gContPakUpdateFlag > 0u ? 1 : 0);
            frameSendAndLoop(&gRaceEndMsg);
            return;

        default:
            /* 0xC-0x12, 0x15-0x16, 0x18-0x1A: loop without action */
            break;
        }
    }
}

/* ---------------------------------------------------------------------------
 * frameSendAndLoop — send a reply message, then resume the receive loop.
 * func_80060824 / func_800607D4 / func_800607D8 all converge here.
 * ---------------------------------------------------------------------------*/
static void frameSendAndLoop(Unk *reply) {
    osSendMesg(sRecvQueue, reply, 0);
    frameRecvAndDispatch();
}

/* ---------------------------------------------------------------------------
 * frameHandle14 — msg 0x14: race phase state machine.
 * Implements func_80060378 and its internal sub-cases.
 * ---------------------------------------------------------------------------*/
static void frameHandle14(void) {
    s32  phaseIdx;
    s32  raceMode;
    s32  altMode;
    s32  v0;
    f32  fv0;
    f32  fs0;
    f32  scaledVol;

    gFrameEventCount++;
    phaseIdx = sPhase - 2;
    if ((u32)phaseIdx >= 6u) {
        frameSendAndLoop(&gFrameSyncMsg);
        return;
    }

    switch (sPhase) {

    /* ---- phase 2: race intro countdown ----------------------------------- */
    case 2:
        sRaceProgress += 0x888;
        if ((u32)sRaceProgress > 0xFFFFu && gRaceTriggerFlag != 0) {
            /* race triggered — transition to phase 3 */
            osSendMesg(sRecvQueue, &gRaceTriggerMsg, 0);
            gGameFlags2 = 0;
            func_8005CFB4();
            sPhase        = 3;
            sTickCount    = 0;
            sRaceProgress = 0x10000;
            frameSendAndLoop(&gFrameSyncMsg);
            return;
        }
        /* still counting — check flags */
        if (gFrameSyncFlag != 0) {
            frameSendAndLoop(&gFrameSyncMsg);
            return;
        }
        if (gRaceRestartFlag != 0) {
            frameSendAndLoop(&gFrameSyncMsg);
            return;
        }
        /* compute audio fade based on progress */
        fv0 = (f32)(*(s32 *)((u8 *)&gRaceCtx + 0xAFC));
        fs0 = (f32)(0x10000 - sRaceProgress);
        fv0 = fv0 * fs0 * sVolScale;
        func_8005CF84((s32)fv0);
        fv0 = (f32)(*(s32 *)((u8 *)&gRaceCtx + 0xB04));
        fv0 = fv0 * fs0 * sVolScale;
        func_8005CF9C((s32)fv0);
        frameSendAndLoop(&gFrameSyncMsg);
        return;

    /* ---- phase 3: wait for tick count >= 6 --------------------------------*/
    case 3:
        if (sTickCount < 6) {
            frameSendAndLoop(&gFrameSyncMsg);
            return;
        }
        func_8005CFB4();
        sPhase = 4;
        func_8005CF84(*(s32 *)((u8 *)&gRaceCtx + 0xAFC));
        func_8005CF9C(*(s32 *)((u8 *)&gRaceCtx + 0xB04));
        func_8005F980(0);
        if (gContPakUpdateFlag != 0) {
            frameSendAndLoop(&gFrameSyncMsg);
            return;
        }
        gRaceTriggerFlag = 0;
        frameSendAndLoop(&gFrameSyncMsg);
        return;

    /* ---- phase 4: wait for overlay load to complete ----------------------*/
    case 4:
        v0 = func_800625C0();
        if (*(s32 *)((u8 *)&gRaceCtx + 0x1E48 - 0x80182EA8 + 0x80180000) == 1) {
            gAudioBufState = 0;
        }
        if (v0 == 0) {
            /* overlay not done */
            if (sRaceProgress <= 0) {
                frameSendAndLoop(&gFrameSyncMsg);
                return;
            }
            sRaceProgress -= 0x2492;
            if (sRaceProgress < 0) {
                sRaceProgress = 0;
                frameSendAndLoop(&gFrameSyncMsg);
                return;
            }
            frameSendAndLoop(&gFrameSyncMsg);
            return;
        }
        /* overlay done — advance to phase 5 */
        *(s32 *)((u8 *)&gRaceCtx + 0x1E48 - 0x80182EA8 + 0x80180000) = 2;
        gSceneOverlaySlot  = gLoopCount;
        func_800B0F10();
        osSendMesg(sRecvQueue, &gOverlayReadyMsg, 0);
        if (gRaceReadyFlag != 0) {
            frameSendAndLoop(&gFrameSyncMsg);
            return;
        }
        sPhase = 5;
        func_8005C8EC(0xF0, 0);
        func_8005C8B8();
        frameSendAndLoop(&gFrameSyncMsg);
        return;

    /* ---- phase 5,6: overlay loading, wait for state 3 -------------------*/
    case 5:
    case 6:
        if (*(s32 *)((u8 *)&gRaceCtx + 0x1E48 - 0x80182EA8 + 0x80180000) != 3) {
            frameSendAndLoop(&gFrameSyncMsg);
            return;
        }
        if (sPhase != 6) {
            frameSendAndLoop(&gFrameSyncMsg);
            return;
        }
        /* phase 6: trigger race start */
        osSendMesg(sRecvQueue, &gRaceStartMsg, 0);
        *(s32 *)((u8 *)&gRaceCtx + 0x1E48 - 0x80182EA8 + 0x80180000) = 0;
        gAudioBufState = 1;
        func_8005C8EC(0, 0);
        func_8005C8D4(*(s32 *)((u8 *)&gRaceCtx + 0xB00));
        sPhase = 7;
        if (*(s32 *)((u8 *)&gRaceCtx + 0xB00) <= 0) {
            func_8005C8B8();
            frameSendAndLoop(&gFrameSyncMsg);
            return;
        }
        sRaceProgress = 0x10000;
        raceMode      = *(s32 *)((u8 *)&gRaceCtx + 0x16DC);
        if (raceMode >= 0xD) {
            altMode = raceMode - 0xD;
            if ((u32)altMode < 6u) {
                /* dispatch via jtbl_8004BFE0 (mode-specific music) */
                switch (altMode) {
                case 0: func_8005C88C(2);  break;
                case 1: func_8005C88C(3);  break;
                case 2: func_8005C88C(4);  break;
                case 3: func_8005C88C(5);  break;
                case 4: func_8005C88C(6);  break;
                case 5: func_8005C88C(7);  break;
                }
                frameSendAndLoop(&gFrameSyncMsg);
                return;
            }
            func_8005C88C(0x12);
            frameSendAndLoop(&gFrameSyncMsg);
            return;
        }
        /* raceMode < 0xD — dispatch via jtbl_8004BFF8 (vehicle class music) */
        {
            s32 trackIdx;
            s32 trackMode = *(s32 *)((u8 *)&gRaceCtx + 0x16E8);
            if (trackMode >= 3) {
                func_8005C88C(0x12);
                frameSendAndLoop(&gFrameSyncMsg);
                return;
            }
            trackIdx = gLoopCount;
            if (*(s32 *)((u8 *)&gRaceCtx + 0xB08) == 0) {
                /* trackIdx already loaded */
            } else {
                /* compute trackIdx mod 3 */
                s32 q  = (s32)(((s64)trackIdx * 0x2AAAAAABLL) >> 32);
                s32 s  = trackIdx >> 31;
                s32 d  = (q >> 1) - s;
                trackIdx = trackIdx - d * 3;
            }
            if ((u32)trackIdx >= 0xCu) {
                func_8005C88C(0x12);
                frameSendAndLoop(&gFrameSyncMsg);
                return;
            }
            /* dispatch via jtbl_8004BFF8 */
            switch (trackIdx) {
            case  0: func_8005C88C(0);  break;
            case  1: func_8005C88C(1);  break;
            case  2: func_8005C88C(0xC); break;
            case  3: func_8005C88C(0xD); break;
            case  4: func_8005C88C(0xE); break;
            case  5: func_8005C88C(0xF); break;
            case  6: func_8005C88C(8);  break;
            case  7: func_8005C88C(9);  break;
            case  8: func_8005C88C(0xA); break;
            case  9: func_8005C88C(0xB); break;
            case 10: func_8005C88C(0x13); break;
            case 11: func_8005C88C(0x14); break;
            }
            frameSendAndLoop(&gFrameSyncMsg);
            return;
        }

    /* ---- phase 7: intro audio running (countdown to sRaceProgress==0) ---*/
    case 7:
        sRaceProgress -= 0x444;
        if (sRaceProgress > 0) {
            frameSendAndLoop(&gFrameSyncMsg);
            return;
        }
        sRaceProgress = 0;
        sPhase        = 1;
        osSendMesg(sRecvQueue, &gRaceIntroDoneMsg, 0);
        frameSendAndLoop(&gFrameSyncMsg);
        return;

    default:
        frameSendAndLoop(&gFrameSyncMsg);
        return;
    }
}

/* ---------------------------------------------------------------------------
 * func_800607E0 — msg 0x17 handler stub (referenced in jtbl_8004BF80).
 * ---------------------------------------------------------------------------*/
void func_800607E0(void) {
    func_800600D8(sPhase, sRaceProgress);
    sTickCount++;
    frameSendAndLoop(&gEventQueueSize);
}

/* ---------------------------------------------------------------------------
 * func_80060800 — msg 0xB handler stub.
 * ---------------------------------------------------------------------------*/
void func_80060800(void) {
    sPhase = 6;
    frameRecvAndDispatch();
}

/* ---------------------------------------------------------------------------
 * func_80060808 — msg 0x1B handler stub.
 * ---------------------------------------------------------------------------*/
void func_80060808(void) {
    func_80072E00((u32)gContPakUpdateFlag > 0u ? 1 : 0);
    frameSendAndLoop(&gRaceEndMsg);
}

/* ---------------------------------------------------------------------------
 * func_80060824 — send reply + restart loop (alabel used from jtbl / jmp).
 * ---------------------------------------------------------------------------*/
void func_80060824(OSMesgQueue *queue, Unk *reply, s32 flags) {
    osSendMesg(queue, reply, flags);
    frameRecvAndDispatch();
}
