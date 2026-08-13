#include "ultra64.h"

/*
 * entityUpdateDispatch (func_8005566C) / func_80055900 — frame dispatch loop.
 *
 * entityUpdateDispatch initialises shared state and calls func_80055900.
 * func_80055900 is an infinite loop: osRecvMesg on gPiMesgQueue, then
 * dispatch on the received state word via a 28-entry jump table.
 *
 * func_80056414 and func_8005641C are jump-table entries (jtbl_8004BCE8[17]
 * and [24]) that modify shared state flags and re-enter the loop.
 *
 * Shared state is held in static file-scope variables because the original
 * SN64 code used callee-saved registers ($s2–$s6) that persisted across
 * the alabel entry points.
 *
 * Nonmatching: ABI difference (SN64 vs IDO calling convention).
 * Sizes: entityUpdateDispatch 0xDA8, func_80056414 0x8, func_8005641C 0x8.
 */

/* ------------------------------------------------------------------ */
/* External functions                                                   */
/* ------------------------------------------------------------------ */
/* osRecvMesg, osSendMesg, osCreateMesgQueue declared in ultra64.h    */
void osWritebackInvalDCache(void *, s32);
void gameStateSync(void);
void dlResetPtr(void);
void mainPoolAlloc(void);
void func_8005C0BC(void);
void rdpDataLoad(void);
void frameHeapInit(void);
void rdpSetFillColor(s32, s32, s32);
void viSetRefresh(f32);
void viSetGamma(f32);
void viSetOutput(s32);
void viSetFieldBit(s32);
void viSetResolution(s32, s32);
void gfxDLEnd(void);
void gameThreadInit(Unk *);
void frameThreadInit(Unk *);
void contPakThreadInit(Unk *);
void audioRspDoneGetter(void);
void audioFrameBuild(void);
void audioSetChanA(s32);
void audioSetChanB(s32);
void audioSetRates(s32, s32);
void audioResetCallback(void);
void rspHalt(void);
void func_80087EAC(void *);
void func_800A85BC(void *);
void func_800701C8(void);
void func_80087318(void *);
void func_80087548(f32);
void func_80087678(f32);
void func_800876D8(s32);
void func_80087A88(s32);
void func_80086D28(void);
void func_80086D48(s32);
void func_80086A44(void *, s32);
void func_8006CE9C(void *, s32);
void func_8005C538(void);
void func_8005C688(void);
void func_8005CF84(s32);
void func_8005CF9C(s32);
void func_8005C8EC(s32, s32);
void func_8005C8B8(void);
void func_8004D8C0(s32, s32);
void func_80060834(OSMesgQueue *);
void func_80070B24(OSMesgQueue *);
void func_80066C44(void);
void func_8004D358(void);
void func_80052BB0(void);
void func_8004EC54(void);
void func_80063CD8(void);
void func_800555D8(OSMesgQueue *);
void func_8006CF98(void *, void *, s32);

/* ------------------------------------------------------------------ */
/* Named globals                                                        */
/* ------------------------------------------------------------------ */
extern OSMesgQueue gPiMesgQueue;   /* 0x80174708  PI/AI DMA event message queue  */
extern s32  gOverlayState;         /* 0x80173BC4  overlay dispatch state (0/1/2) */
extern s32  gLoopCount;            /* 0x80173D08  game loop tick counter          */
extern s32  gContPakUpdateFlag;    /* 0x80173C0C  controller pak update enable    */
extern s32  gMainHeapBase;         /* 0x80170390  main memory pool heap base      */
extern s32  gRspDL;                /* 0x80173BC0  RSP display list pointer        */
extern s32  gScreenWidth;          /* 0x8017CA44  screen width in pixels          */
extern s32  gScreenHeight;         /* 0x80173C18  screen height in pixels         */
extern OSMesgQueue gSiMesgQueue;   /* 0x80173C48  SI/DMA event message queue      */
extern s32  gEventQueueSize;       /* 0x80173C40  OS event queue size parameter   */
extern OSMesgQueue gFrameMesgQueue;/* 0x80174730  frame dispatch thread msg queue */
extern OSMesgQueue gGameMesgQueue; /* 0x80174BD0  game thread message queue       */
extern s32  gEntityRenderDone;     /* 0x801786B8  entity render pass complete     */
extern s32  gContPakInitFlag;      /* 0x800925C8  controller pak init state flag  */
extern s32  gHandlerAuxFlag;       /* 0x80093EE0  entity handler auxiliary flag   */
extern s32  gHandlerMainFlag;      /* 0x80093EDC  entity handler main flag        */
extern Unk  gRaceCtx;              /* 0x80182EA8  large game/race state struct    */
extern s32  gDLPtr;                /* 0x80173CC0  display list write pointer      */
extern s32  gSiCmdBuf;             /* 0x8018AD28  SI command DMA buffer           */
extern s32  gViInited;             /* 0x80174724  VI subsystem initialized flag   */
extern Unk  gContInputBuf;         /* 0x80192840  controller input buffer         */
extern OSMesgQueue gEntityMesgQueue; /* 0x801887B8  entity handler sync msg queue */
extern OSMesgQueue gRspDmaMesgQueue; /* 0x8016DF70  RSP DMA completion msg queue  */
extern OSMesg gRspDmaMsgBuf;       /* 0x8016E290  RSP DMA msg buffer (0x20 slots) */
extern s32  gDLBufEnd;             /* 0x803DA400  display list buffer end addr    */

/* PI event message slot globals (OSMesg = void*: stores state-code pointers) */
extern OSMesg gPiMsgSlotA;          /* PI event msg slot A (value 0x13)  */
extern OSMesg gPiMsgSlotB;          /* PI event msg slot B (value 0x16)  */
extern OSMesg gPiMsgSlotC;          /* PI event msg slot C (value 0x17)  */
extern OSMesg gHandlerMsgBufA;          /* PI event msg slot G (value 0x1B)  */
extern OSMesg gRaceEndMsg;          /* PI event msg slot   (value 0x1C)  */
extern OSMesg gEntityHandlerMsg;   /* 0x8017C948  entity handler msg (0x14)       */
extern OSMesg gPiEvtMsgD;          /* 0x8017CC50  PI event msg slot D (value 3)   */
extern OSMesg gPiEvtMsgE;          /* 0x8017CA48  PI event msg slot E (val 0x1A)  */
extern OSMesg gPiEvtMsgF;          /* 0x8017C960  PI event msg slot F (value 7)   */
extern OSMesg gPiEvtMsgM;          /* 0x80174C30  PI event msg slot M (val 0x18)  */
extern OSMesg gPiEvtMsgO;          /* 0x801747C8  PI event msg slot O (val 0xB)   */

/* Unnamed globals */
extern OSMesg gPiMsgBuf;          /* 0x8017CDDC  PI msg receive buffer (void* to state)  */
extern OSMesgQueue gInitMsgQueue2;     /* 0x80173CE8  second init message queue               */
extern s32  gFrameFlipSync;            /* 0x8017CCD0  frame flip sync flag                    */
extern s32  gFrameFlipBackup;            /* 0x8017CCCC  frame flip state backup                 */
extern s32  gFrameDbIdx;            /* 0x800924B4  double-buffer frame index               */
extern Unk *gHandlerObjPtr;            /* 0x800924C4  handler object pointer                  */
extern s32  gFrameStateCount;            /* 0x800924D0  frame/state counter                     */
extern s32  gAudioSfxReady;            /* 0x800925C4  audio/sfx ready flag                    */
extern s32  gAudioBufState;            /* 0x80091E54  audio buffer state                      */
extern s32  gAudioStateFlag;            /* 0x80091E80  audio state flag                        */
extern s32  gAudioCallbackFlag;            /* 0x80091E84  audio callback flag                     */
extern s32  gGameFlags2;            /* 0x80092B88  resolution mode flags                   */
extern s32  gDLBufSaveA;            /* 0x80090CF8  DL buffer save A                        */
extern s32  gDLBufSaveB;            /* 0x80090CFC  DL buffer save B                        */
extern void *gViModeNtsc;           /* 0x80095B50  VI mode table ptr (NTSC?)               */
extern void *gViModePal60;           /* 0x800956F0  VI mode table ptr (PAL-60?)             */
extern void *gViModeMpal;           /* 0x80095FB0  VI mode table ptr (MPAL?)               */
extern s32  gHwVersion;            /* 0x80000300  N64 hardware version/region             */
extern f32  gFloatOne;            /* 0x8004BD58  float constant 1.0                      */
extern f32  gFloatOneFive;            /* 0x8004BD5C  float constant ~1/128                   */
extern s32  D_801747C8_msgO;       /* duplicate name workaround — same as gPiEvtMsgO      */
extern s32  gContInputCache;            /* 0x8017CA08  SFX input table base                    */

/* ------------------------------------------------------------------ */
/* Static (shared) loop state — corresponds to $s2–$s6, stack locals  */
/* ------------------------------------------------------------------ */
static s32 sP1Flags;      /* $s2  player-1 channel state flags */
static s32 sP2Flags;      /* $s3  player-2 channel state flags */
static s32 sDirtyFlag;    /* $s4  flush-needed flag            */
static s32 sP2Count;      /* $s5  player-2 active frame count  */
static s32 sP1Count;      /* $s6  player-1 active frame count  */
static s32 sFirstFrame;   /* sp+0x20  first-frame flag         */
static s32 sFrameFlipped; /* sp+0x24  frame-flip flag          */
static s32 sPakRetry;     /* sp+0x28  pak retry pending        */
static s32 sPakReady;     /* sp+0x2C  pak ready flag           */
static s32 sChanFlipDone; /* sp+0x30  channel flip done        */
static s32 sInit;         /* sp+0x34  init flag (starts 1)     */
static s32 sFrameBase;    /* sp+0x38  current DL frame base    */
static s32 sFrameSize;    /* sp+0x3C  current DL frame size    */
static s32 sNeedFlush;    /* sp+0x40  full flush needed        */

/* ------------------------------------------------------------------ */
/* func_80055900 — infinite frame dispatch loop                        */
/* ------------------------------------------------------------------ */
void func_80055900(void) {
    u32 state;
    s32 targetW;
    s32 *raceUnk;
    s32 *p1buf;
    s32 *p2buf;
    s32 base;
    s32 idx;
    s32 stride;

    for (;;) {
        /* Block until next PI DMA event message arrives. */
        osRecvMesg(&gPiMesgQueue, &gPiMsgBuf, 1);

        /* Extract 0-based state index from the received message pointer. */
        state = (u32)(*(s32 *)gPiMsgBuf - 1);
        if (state >= 0x1Cu) {
            continue; /* invalid state — wait again */
        }

        switch (state) {

        /* ---------------------------------------------------------- */
        case 0: /* 0x80056298 — audio DL flush + player-side dispatch  */
            osWritebackInvalDCache(&gSiCmdBuf, 0x40);
            func_80087EAC(&gContInputBuf);
            if (sP1Flags & 7) {
                gFrameFlipSync = 1;
                gAudioCallbackFlag = 0;
            } else {
                gContPakInitFlag = !((u32)sP2Flags & 1u);
                osSendMesg(&gFrameMesgQueue, &gHandlerMsgBufA, 0);
            }
            continue;

        /* ---------------------------------------------------------- */
        case 1: /* 0x8005594C — VI mode / timing update                */
            gLoopCount++;
            if (gContPakUpdateFlag != 0) {
                gContPakUpdateFlag++;
                if (gContPakUpdateFlag == 24) {
                    switch (gHwVersion) {
                    case 0: func_80087318(&gViModeNtsc); break;
                    case 1: func_80087318(&gViModePal60); break;
                    case 2: func_80087318(&gViModeMpal); break;
                    default: break;
                    }
                    /* func_800559D4 */
                    func_80087548(gFloatOne);
                    func_80087678(gFloatOne);
                    func_80087A88(1);
                }
            }
            /* .L800559F4: compute target width and check for change */
            raceUnk = (s32 *)((char *)&gRaceCtx + 0xB1C);
            if (sP1Flags & 3) {
                targetW = (*raceUnk != 0) ? 0x1C0 : 0x140;
            } else {
                if (gGameFlags2 & 0x1000) {
                    targetW = 0xC0;
                } else {
                    targetW = (*raceUnk != 0) ? 0x1C0 : 0x140;
                }
            }
            if (gScreenWidth != targetW && sInit) {
                gEntityRenderDone = (targetW >= 0x141) ? 1 : 0;
                func_8004D8C0(targetW, (targetW * 15) / 16);
                base = gMainHeapBase + 0x18000;
                if (!gEntityRenderDone) {
                    gRspDL   = (s32)&gDLBufEnd;
                    *(s32 *)(base + 0x7540) = (s32)0x80000400;
                    *(s32 *)(base + 0x7548 + 0x18000 + 0x7540) = (s32)0x80025C00;
                } else {
                    gRspDL   = (s32)0x8076A000u;
                    *(s32 *)(base + 0x7540) = (s32)0x80400000u;
                    *(s32 *)(base + 0x7548 + 0x18000 + 0x7540) = (s32)0x80496000u;
                }
                sFrameFlipped = 1;
                sFirstFrame   = 1;
                if (gAudioStateFlag) {
                    osSendMesg(&gSiMesgQueue, &gPiEvtMsgM, 0);
                    gAudioCallbackFlag = 1;
                    gFrameFlipSync = 0;
                } else if (!gHandlerMainFlag && gHandlerAuxFlag) {
                    osSendMesg(&gEntityMesgQueue, &gEntityHandlerMsg, 0);
                }
            }
            if (sPakReady) {
                osSendMesg(&gFrameMesgQueue, &gPiEvtMsgD, 0);
            }
            if (!sDirtyFlag && gAudioSfxReady) {
                if (gHandlerObjPtr) {
                    func_80086D28();
                    sDirtyFlag = 1;
                    sPakReady  = 1;
                } else {
                    osSendMesg(&gFrameMesgQueue, &gPiEvtMsgD, 0);
                    sPakReady  = 1;
                    sDirtyFlag = 1;
                }
            }
            continue;

        /* ---------------------------------------------------------- */
        case 2: /* 0x800561C4 — pak/handler state                      */
            if (sPakReady) {
                if (gHandlerObjPtr) {
                    gHandlerObjPtr = 0;
                    func_80086D48(0);
                }
                sPakRetry = 0;
                if (sFrameBase) {
                    func_8006CE9C((Unk *)sFrameBase, sFrameSize);
                    gHandlerObjPtr = (Unk *)(s32)sFrameBase;
                    sFrameBase = 0;
                }
                func_8005C688();
                osSendMesg(&gFrameMesgQueue, &gPiEvtMsgO, 0);
            }
            continue;

        /* ---------------------------------------------------------- */
        case 3: /* 0x800560E0 — double-buffer index toggle + DL submit  */
            if (!(sP1Flags & 3)) {
                func_800A85BC((Unk *)&gDLBufEnd);
            }
            idx    = gFrameDbIdx ^ 1;
            stride = idx * 31;
            stride = (stride * 4 + idx) * 4 + idx;
            stride = (stride * 4 + idx) * 8 + idx;
            stride = stride * 8;
            func_8006CF98((Unk *)(gMainHeapBase + stride),
                          &gPiMsgBuf, idx);
            gFrameDbIdx = idx;
            continue;

        /* ---------------------------------------------------------- */
        case 4:
        case 5:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 25:
        case 26:
            continue; /* "continue loop" jump-table entries */

        /* ---------------------------------------------------------- */
        case 6: /* 0x800560C4 — overlay state step                     */
            if (gOverlayState != 0) {
                sInit = 1;
                gOverlayState++;
            }
            continue;

        /* ---------------------------------------------------------- */
        case 7: /* 0x800562F8 — reinit: pak flag + audio reset         */
            gContPakUpdateFlag = 1;
            func_8005CF84(0);
            func_8005CF9C(0);
            func_8005C8EC(0xF, 0);
            func_8005C8B8();
            osSendMesg(&gFrameMesgQueue, &gPiMsgSlotA, 0);
            gFrameFlipSync = 1;
            gAudioCallbackFlag = 0;
            continue;

        /* ---------------------------------------------------------- */
        case 8: /* 0x8005604C — resolution-based DL buffer switch      */
            if ((sP1Flags & 8) && sP1Count < 2) {
                osSendMesg(&gGameMesgQueue, &gPiMsgSlotC, 0);
            } else if ((sP2Flags & 8) && sP2Count < 2) {
                osSendMesg(&gGameMesgQueue, &gPiMsgSlotC, 0);
            }
            base  = gMainHeapBase + 0x18000;
            p1buf = (s32 *)(base + 0x7540);
            p2buf = (s32 *)(base + 0x7548 + 0x18000 + 0x7540);
            if (!gEntityRenderDone) {
                gRspDL   = (s32)&gDLBufEnd;
                *p1buf   = (s32)0x80025C00;
                *p2buf   = (s32)0x80025C00;
            } else {
                gRspDL   = (s32)0x8076A000u;
                *p1buf   = (s32)0x80400000u;
                *p2buf   = (s32)0x80496000u;
            }
            sFrameFlipped = 1;
            sFirstFrame   = 1;
            osSendMesg(&gFrameMesgQueue, &gPiMsgSlotC, 0);
            continue;

        /* ---------------------------------------------------------- */
        case 9: /* 0x80056330 — player-1 count decrement / flag clear  */
            sP1Count--;
            if (sP1Count == 0) {
                sP1Flags &= ~0x11;
            }
            continue;

        /* ---------------------------------------------------------- */
        case 10: /* 0x80056348 — P1 flags: clear bits 0–1, set bit 2   */
            sP1Flags = (sP1Flags & ~3) | 4;
            continue;

        /* ---------------------------------------------------------- */
        case 11: /* 0x80056374 — player-2 count decrement / flag clear  */
            sP2Count--;
            if (sP2Count == 0) {
                sP2Flags &= ~0x11;
            }
            continue;

        /* ---------------------------------------------------------- */
        case 12: /* 0x8005638C — P2 flags: clear bits 0–1              */
            sP2Flags &= ~3;
            continue;

        /* ---------------------------------------------------------- */
        case 13: /* 0x80056398 — submit P1 DL task if P1 slot active   */
            if (sP1Flags & 1) {
                osSendMesg(&gGameMesgQueue, &gPiMsgSlotA, 0);
                sP1Flags = (sP1Flags & ~1) | 2;
            }
            continue;

        /* ---------------------------------------------------------- */
        case 14: /* 0x800563CC — set P2 bit 0                          */
            sP2Flags |= 1;
            continue;

        /* ---------------------------------------------------------- */
        case 15: /* 0x800563D4 — clear P1 bit 2                        */
            sP1Flags &= ~4;
            continue;

        /* ---------------------------------------------------------- */
        case 16: /* 0x800563E0 — submit P2 DL task if P2 slot active   */
            if (sP2Flags & 1) {
                osSendMesg(&gFrameMesgQueue, &gPiMsgSlotA, 0);
                sP2Flags = (sP2Flags & ~1) | 2;
            }
            continue;

        /* ---------------------------------------------------------- */
        case 17: /* func_80056414 — set P2 bit 0 (external entry)      */
            sP2Flags |= 1;
            continue;

        /* ---------------------------------------------------------- */
        case 24: /* func_8005641C — clear overlay state (external entry) */
            gOverlayState = 0;
            continue;

        /* ---------------------------------------------------------- */
        case 27: /* 0x80056280 — audio done: set sync flag              */
            gFrameFlipSync = 1;
            gAudioCallbackFlag = 0;
            continue;

        default:
            continue;
        }
    }
}

/* ------------------------------------------------------------------ */
/* entityUpdateDispatch — one-time init, then enter dispatch loop      */
/* ------------------------------------------------------------------ */
void entityUpdateDispatch(void) {
    s32 base;

    /* Initialise shared state. */
    sDirtyFlag    = 0;
    sP1Flags      = 1;
    sP2Flags      = 0;
    sP1Count      = 0;
    sP2Count      = 0;
    sFirstFrame   = 0;
    sFrameFlipped = 0;
    sPakRetry     = 0;
    sPakReady     = 0;
    sChanFlipDone = 0;
    sInit         = 1;
    sFrameBase    = 0;
    sFrameSize    = 0;
    sNeedFlush    = 0;
    gContPakUpdateFlag = 0;
    gOverlayState      = 0;

    /* Sync audio/game state, reset DL pointer, allocate pools. */
    func_80066C44();
    func_8004D358();
    func_80052BB0();
    func_8005C0BC();
    func_80063CD8();
    func_8004EC54();

    /* Create RSP DMA message queue (0x20 slots). */
    osCreateMesgQueue(&gRspDmaMesgQueue, &gRspDmaMsgBuf, 0x20);

    /* Save DL buffer pointer around init. */
    gDLBufSaveB = gDLBufSaveA;

    /* Block until initial PI message arrives (loop 1: D_80174708). */
    while (osRecvMesg(&gPiMesgQueue, &gPiMsgBuf, 0) != 0) {}

    /* Block until second sync queue (loop 2: gInitMsgQueue2). */
    while (osRecvMesg(&gInitMsgQueue2, &gPiMsgBuf, 0) != 0) {}

    /* Assign PI event message state integer codes (stored as OSMesg = void*). */
    gPiMsgSlotA     = (OSMesg)0x13;
    gEntityHandlerMsg = (OSMesg)0x14;
    gPiMsgSlotB     = (OSMesg)0x16;
    gPiMsgSlotC     = (OSMesg)0x17;
    gHandlerMsgBufA     = (OSMesg)0x1B;
    gRaceEndMsg     = (OSMesg)0x1C;

    /* Configure RSP geometry buffer based on RDRAM layout. */
    base = gMainHeapBase + 0x18000;
    if (!gEntityRenderDone) {
        /* Standard RDRAM layout */
        gRspDL = (s32)&gDLBufEnd;
        *(s32 *)(base + 0x7540) = (s32)0x80000400;
        *(s32 *)(base + 0x7548 + 0x18000 + 0x7540) = (s32)0x80025C00;
    } else {
        /* High-RDRAM layout */
        gRspDL = (s32)0x8076A000u;
        *(s32 *)(base + 0x7540) = (s32)0x80400000u;
        *(s32 *)(base + 0x7548 + 0x18000 + 0x7540) = (s32)0x80496000u;
    }

    /* Configure frame flip state from gViInited. */
    if (gViInited < 0) {
        gFrameFlipBackup = gViInited;
        gFrameFlipSync = 0;
    } else {
        gFrameFlipSync = 1;
    }

    /* Begin main loop setup (func_8005587C): */
    sP2Flags   = 2;
    gFrameDbIdx = 0;

    /* Set up first DL frame. */
    func_8006CF98(&gPiMesgQueue, &gPiMsgBuf, 0);
    rdpSetFillColor(0, 0, 0);
    func_800701C8();

    /* Start subsystem threads. */
    func_800555D8(&gPiMesgQueue);
    func_80060834(&gPiMesgQueue);
    func_80070B24(&gSiMesgQueue);

    /* Send first frame message and start audio. */
    osSendMesg(&gFrameMesgQueue, &gPiMsgSlotA, 0);
    func_8005C538();
    func_8005C688();

    /* Enter infinite dispatch loop (never returns). */
    func_80055900();
}

/* ------------------------------------------------------------------ */
/* func_80056414 — jtbl_8004BCE8[17]: set P2 bit 0, re-enter loop    */
/* ------------------------------------------------------------------ */
void func_80056414(void) {
    sP2Flags |= 1;
    func_80055900();
}

/* ------------------------------------------------------------------ */
/* func_8005641C — jtbl_8004BCE8[24]: clear overlay state, re-enter  */
/* ------------------------------------------------------------------ */
void func_8005641C(void) {
    gOverlayState = 0;
    func_80055900();
}
