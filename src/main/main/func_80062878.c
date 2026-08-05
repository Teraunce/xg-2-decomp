#include "ultra64.h"
#include "audio.h"

/*
 * sfxUpdateHeap — Per-frame SFX output dispatch.
 * sfxFlushInactive — Tick all active heap entries (decrement state counters).
 * func_80062ACC — Reset SFX state machine phase and fade timer.
 *
 * sfxUpdateHeap iterates over every active heap entry (0 .. gSfxActiveCount-1)
 * looking for entries whose type does NOT have bits 0x2 or 0x4 set
 * (i.e. entries that have been inserted but not yet assigned a channel).
 * For each such entry it:
 *   1. Selects a channel function from D_80181EF0[] indexed by gPlayerList.
 *   2. Saves gSfxMaxIndex, writes a display-list command pair into the
 *      RSP DL buffer (D_80173CC0).
 *   3. Calls the selected channel function (indirect) with the entry's
 *      type flags masked to bit 0.
 *   4. Writes a G_ENDDL (0xE7000000) terminator into the DL buffer.
 * After the loop, if s1 (the saved D_80178690 value) is non-zero it is
 * restored; if the caller-supplied flag (sp+0x38) is set and no active
 * entries were found, calls rdpSetFillColor(0xFF, 0xFF, 0xFF).
 *
 * sfxFlushInactive iterates the heap, decrementing each active entry's state
 * counter (heap[i].state) until it reaches zero, then OR-ing 0x8 into type.
 *
 * func_80062ACC resets gSfxPhase = 0, gSfxFadeTimer = 0, and writes the
 * two initialiser values D_80092CB0 / D_80092CB4 into D_801823B8 / D_801823BC.
 *
 * Globals:
 *   gSfxActiveCount  0x80092CB8  s32
 *   gSfxMaxIndex     0x80092CBC  s32
 *   gSfxHeap         0x80182348  SfxSortEntry[]
 *   gSfxPhase        0x801823A8  s32
 *   gSfxFadeTimer    0x801823B0  s32
 *   D_80092CB0       0x80092CB0  s32  init value A for D_801823B8
 *   D_80092CB4       0x80092CB4  s32  init value B for D_801823BC
 *   D_801823B8       0x801823B8  s32  SFX parameter B
 *   D_801823BC       0x801823BC  s32  SFX parameter C
 *   gPlayerList       0x80091E70  s32  channel selector index
 *   D_80173CC0       0x80173CC0  u32* RSP display-list write pointer
 *   D_80178690       0x80178690  s32  saved channel pointer
 *   D_80181EF0       0x80181EF0  void*[] channel function table
 *   D_80182078       0x80182078  void* channel state base (passed to DL cmd)
 *   gSfxChannelState       0x801820D8  SfxChannelState[]  (gSfxChannelState)
 *   D_800E412C       0x800E412C  void* effect table A
 *   D_800E4220       0x800E4220  void* effect table B
 */

extern s32           gSfxActiveCount;   /* 0x80092CB8 */
extern s32           gSfxMaxIndex;      /* 0x80092CBC */
extern SfxSortEntry  gSfxHeap[];        /* 0x80182348 */
extern s32           gSfxPhase;         /* 0x801823A8 */
extern s32           gSfxFadeTimer;     /* 0x801823B0 */
extern s32           D_80092CB0;        /* init value A */
extern s32           D_80092CB4;        /* init value B */
extern s32           D_801823B8;        /* SFX param B */
extern s32           D_801823BC;        /* SFX param C */
extern s32           gPlayerList;        /* channel selector */
extern u32          *D_80173CC0;        /* RSP DL write ptr */
extern s32           D_80178690;        /* saved channel ptr */
extern void        **D_80181EF0;        /* channel fn table */
extern void         *D_80182078;        /* channel state base */
extern SfxChannelState gSfxChannelState[];    /* gSfxChannelState */
extern void         *D_800E412C;        /* effect table A sentinel */
extern void         *D_800E4220;        /* effect table B sentinel */
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
            void (*chanFn)(void) = (void (*)(void))D_80181EF0[chanIdx];
            savedChannel = D_80178690;

            /* Emit G_ENDDL + pad into DL buffer. */
            {
                u32 *dl = D_80173CC0;
                dl[0] = G_ENDDL;
                dl[1] = 0;
                D_80173CC0 = dl + 2;
            }

            /* Emit channel setup commands. */
            {
                u32 *dl = D_80173CC0;
                dl[0] = 0xDA380007u;   /* G_DL with channel setup */
                dl[1] = (u32)(uintptr_t)D_80182078;
                D_80173CC0 = dl + 2;
            }

            D_80178690 = (s32)(intptr_t)chanFn;
        }

        anyActive = 1;

        /* Set gSfxMaxIndex = -5 temporarily so the channel fn sees no heap. */
        gSfxMaxIndex = -5;

        /* Call the channel handler with (entry->entity, type & 1). */
        {
            void (*fn)(void *, s32) = (void (*)(void *, s32))D_80178690;
            fn(entry->entity, typeFlags & 1);
        }

        /* Restore gSfxMaxIndex = -5 (already set above — write back). */
        gSfxMaxIndex = -5;

        /* Emit G_ENDDL terminator. */
        {
            u32 *dl = D_80173CC0;
            dl[0] = G_ENDDL;
            dl[1] = 0;
            D_80173CC0 = dl + 2;
        }
    }

done:
    if (anyActive) {
        D_80178690 = savedChannel;
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
 * func_80062ACC
 * Reset the SFX state machine to phase 0 and clear the fade timer.
 * Writes the two init values into the SFX parameter slots B/C.
 * ------------------------------------------------------------------------- */
void func_80062ACC(void) {
    s32 initB = D_80092CB0;
    s32 initC = D_80092CB4;

    gSfxPhase     = 0;
    gSfxFadeTimer = 0;
    D_801823B8    = initB;
    D_801823BC    = initC;
}
