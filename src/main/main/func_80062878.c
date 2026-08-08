#include "ultra64.h"
#include "audio.h"

/*
 * sfxUpdateHeap — Per-frame SFX output dispatch.
 * sfxFlushInactive — Tick all active heap entries (decrement state counters).
 * sfxResetPhase — Reset SFX state machine phase and fade timer.
 *
 * sfxUpdateHeap iterates over every active heap entry (0 .. gSfxActiveCount-1)
 * looking for entries whose type does NOT have bits 0x2 or 0x4 set
 * (i.e. entries that have been inserted but not yet assigned a channel).
 * For each such entry it:
 *   1. Selects a channel function from gSfxChanFuncs[] indexed by gPlayerList.
 *   2. Saves gSfxMaxIndex, writes a display-list command pair into the
 *      RSP DL buffer (gDLPtr).
 *   3. Calls the selected channel function (indirect) with the entry's
 *      type flags masked to bit 0.
 *   4. Writes a G_ENDDL (0xE7000000) terminator into the DL buffer.
 * After the loop, if s1 (the saved gLineVtxBase value) is non-zero it is
 * restored; if the caller-supplied flag (sp+0x38) is set and no active
 * entries were found, calls rdpSetFillColor(0xFF, 0xFF, 0xFF).
 *
 * sfxFlushInactive iterates the heap, decrementing each active entry's state
 * counter (heap[i].state) until it reaches zero, then OR-ing 0x8 into type.
 *
 * sfxResetPhase resets gSfxPhase = 0, gSfxFadeTimer = 0, and writes the
 * two initialiser values gRandState / gRandInitB into gRandStateA / gRandStateB.
 *
 * Globals:
 *   gSfxActiveCount  0x80092CB8  s32
 *   gSfxMaxIndex     0x80092CBC  s32
 *   gSfxHeap         0x80182348  SfxSortEntry[]
 *   gSfxPhase        0x801823A8  s32
 *   gSfxFadeTimer    0x801823B0  s32
 *   gRandState       0x80092CB0  s32  init value A for gRandStateA
 *   gRandInitB       0x80092CB4  s32  init value B for gRandStateB
 *   gRandStateA       0x801823B8  s32  SFX parameter B
 *   gRandStateB       0x801823BC  s32  SFX parameter C
 *   gPlayerList       0x80091E70  s32  channel selector index
 *   gDLPtr       0x80173CC0  u32* RSP display-list write pointer
 *   gLineVtxBase       0x80178690  s32  saved channel pointer
 *   gSfxChanFuncs       0x80181EF0  void*[] channel function table
 *   gOrthoMtx       0x80182078  void* channel state base (passed to DL cmd)
 *   gSfxChannelState       0x801820D8  SfxChannelState[]  (gSfxChannelState)
 *   gSfxEffectTableA       0x800E412C  void* effect table A
 *   gSfxEffectTableB       0x800E4220  void* effect table B
 */

extern s32           gSfxActiveCount;   /* 0x80092CB8 */
extern s32           gSfxMaxIndex;      /* 0x80092CBC */
extern SfxSortEntry  gSfxHeap[];        /* 0x80182348 */
extern s32           gSfxPhase;         /* 0x801823A8 */
extern s32           gSfxFadeTimer;     /* 0x801823B0 */
extern s32           gRandState;        /* init value A */
extern s32           gRandInitB;        /* init value B */
extern s32           gRandStateA;        /* SFX param B */
extern s32           gRandStateB;        /* SFX param C */
extern s32           gPlayerList;        /* channel selector */
extern u32          *gDLPtr;        /* RSP DL write ptr */
extern s32           gLineVtxBase;        /* saved channel ptr */
extern void        **gSfxChanFuncs;        /* channel fn table */
extern void         *gOrthoMtx;        /* channel state base */
extern SfxChannelState gSfxChannelState[];    /* gSfxChannelState */
extern void         *gSfxEffectTableA;        /* effect table A sentinel */
extern void         *gSfxEffectTableB;        /* effect table B sentinel */
extern void         *gHandlerTable;        /* handler table base */

void rdpSetFillColor(s32 a0, s32 a1, s32 a2);   /* audio volume set */

/* DL opcode constants (F3DEX) */
#define G_ENDDL       0xE7000000u
#define G_SETOTHERMODE_H  0xE3000000u

/* -------------------------------------------------------------------------
 * sfxUpdateHeap
 * Per-frame: dispatch each unassigned heap entry to its channel handler.
 *   arg0  — extra flag stored at sp+0x38; triggers rdpSetFillColor if set
 *            when no active entries are found.
 * ------------------------------------------------------------------------- */
void sfxUpdateHeap(s32 arg0) {
    s32 i;
    s32 savedChannel = 0;
    s32 anyActive = 0;
    s32 count = gSfxActiveCount;

    if (count == 0) {
        goto done;
    }

    for (i = 0; i < count; i++) {
        SfxSortEntry *entry = &gSfxHeap[i];
        s32 typeFlags = entry->type;

        /* Skip entries that already have bits 0x2 or 0x4 (pending/active). */
        if (typeFlags & 0x6) {
            continue;
        }

        /* First unassigned entry encountered — select channel function. */
        if (!anyActive) {
            s32 chanIdx = gPlayerList;
            void (*chanFn)(void) = (void (*)(void))gSfxChanFuncs[chanIdx];
            savedChannel = gLineVtxBase;

            /* Emit G_ENDDL + pad into DL buffer. */
            {
                u32 *dl = gDLPtr;
                dl[0] = G_ENDDL;
                dl[1] = 0;
                gDLPtr = dl + 2;
            }

            /* Emit channel setup commands. */
            {
                u32 *dl = gDLPtr;
                dl[0] = 0xDA380007u;   /* G_DL with channel setup */
                dl[1] = (u32)(uintptr_t)gOrthoMtx;
                gDLPtr = dl + 2;
            }

            gLineVtxBase = (s32)(intptr_t)chanFn;
        }

        anyActive = 1;

        /* Set gSfxMaxIndex = -5 temporarily so the channel fn sees no heap. */
        gSfxMaxIndex = -5;

        /* Call the channel handler with (entry->entity, type & 1). */
        {
            void (*fn)(void *, s32) = (void (*)(void *, s32))gLineVtxBase;
            fn(entry->entity, typeFlags & 1);
        }

        /* Restore gSfxMaxIndex = -5 (already set above — write back). */
        gSfxMaxIndex = -5;

        /* Emit G_ENDDL terminator. */
        {
            u32 *dl = gDLPtr;
            dl[0] = G_ENDDL;
            dl[1] = 0;
            gDLPtr = dl + 2;
        }
    }

done:
    if (anyActive) {
        gLineVtxBase = savedChannel;
    }

    if (!anyActive && arg0) {
        /* No active SFX entries — mute all channels (R=G=B=0xFF). */
        rdpSetFillColor(0xFF, 0xFF, 0xFF);
    }
}

/* -------------------------------------------------------------------------
 * sfxFlushInactive
 * Tick every active heap entry's state counter downward.
 * When state reaches 0, OR SFX_TYPE_DONE (0x8) into type.
 * ------------------------------------------------------------------------- */
void sfxFlushInactive(void) {
    s32 i;
    s32 count = gSfxActiveCount;

    for (i = 0; i < count; i++) {
        SfxSortEntry *entry = &gSfxHeap[i];
        s32 type = entry->type;

        /* Only tick entries that are active (bit 2 set). */
        if (!(type & SFX_TYPE_ACTIVE)) {
            continue;
        }

        {
            s32 state = entry->state;
            if (state > 0) {
                entry->state = state - 1;
            } else {
                /* State expired — mark done. */
                entry->type = type | SFX_TYPE_DONE;   /* |= 8 */
            }
        }
    }
}

/* -------------------------------------------------------------------------
 * sfxResetPhase
 * Reset the SFX state machine to phase 0 and clear the fade timer.
 * Writes the two init values into the SFX parameter slots B/C.
 * ------------------------------------------------------------------------- */
void sfxResetPhase(void) {
    s32 initB = gRandState;
    s32 initC = gRandInitB;

    gSfxPhase     = 0;
    gSfxFadeTimer = 0;
    gRandStateA    = initB;
    gRandStateB    = initC;
}
