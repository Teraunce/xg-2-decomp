#include "ultra64.h"
#include "audio.h"

/*
 * func_80062B0C — SFX 3-phase playback state machine.
 *
 * Manages three phases stored in gSfxPhase (D_801823A8):
 *
 *   Phase 0 — SCAN / RAMP-IN:
 *     Increments gSfxFadeTimer (D_801823B0) by gSfxRampStep (D_80092CF8)
 *     each call until the timer reaches 0xFF.  Simultaneously walks every
 *     heap entry, stores any "interesting" entity in gSfxCurrentSlot
 *     (D_80092CCC), and marks each entry active via func_800620CC.
 *     Transitions to phase 1 when the scan is complete.
 *
 *   Phase 1 — PLAY / TRIGGER:
 *     Retrieves the first heap slot (slot -4 = index 0) and the last slot
 *     (slot -1 = gSfxAllocCount).  If both resolve to the same entity it
 *     triggers secondary logic (func_8006394C / func_80061884 / func_80061800).
 *     Then either re-inserts gSfxEntity (D_801823AC) at the top of the heap
 *     via func_80061FB4 (priority -3, flags 1), or re-marks the current
 *     highest-priority entity via func_80062240 + func_800620CC.
 *     Sets gSfxFadeTimer = 0xFF and advances to phase 2.
 *
 *   Phase 2 — DECAY / RAMP-OUT:
 *     Decrements gSfxFadeTimer by gSfxDecayStep (D_80092D00) each call.
 *     When the timer expires (reaches or crosses zero) it triggers
 *     func_800620CC on the top-priority entity to mark it done, then returns.
 *     If gSfxDecayStep == 0 the decay is effectively instantaneous.
 *
 * Globals (main BSS unless noted):
 *   gSfxPhase         0x801823A8  s32   phase 0/1/2 (overlay)
 *   gSfxFadeTimer     0x801823B0  s32   ramp/fade counter 0–0xFF (overlay)
 *   gSfxEntity        0x801823AC  void* entity to (re-)insert in phase 1 (overlay)
 *   gSfxCurrentSlot   0x80092CCC  void* last "interesting" entity seen in scan
 *   gSfxRampStep      0x80092CF8  s32   per-call increment used in phase 0
 *   gSfxDecayStep     0x80092D00  s32   per-call decrement used in phase 2
 *   gSfxSavedState    0x80092B58  s32   saves gSfxPhase value at phase-1 entry
 *   D_80092CD8        0x80092CD8  void* secondary entity ptr (phase 1)
 *   gSfxSlotEnd       0x80092CE0  void* past-end sentinel for the heap iterator
 *   D_800E4118        0x800E4118  void* special handler-table sentinel pointer
 *   D_80093EE4        0x80093EE4  void* handler-table base pointer
 *   D_801823B0        0x801823B0  s32   same as gSfxFadeTimer (overlay alias)
 */

extern s32   gSfxPhase;        /* 0x801823A8 */
extern void *gSfxEntity;       /* 0x801823AC */
extern s32   gSfxFadeTimer;    /* 0x801823B0 */
extern void *gSfxCurrentSlot;  /* 0x80092CCC */
extern s32   gSfxRampStep;     /* 0x80092CF8 */
extern s32   gSfxDecayStep;    /* 0x80092D00 */
extern s32   gSfxSavedState;   /* 0x80092B58 */
extern void *D_80092CD8;       /* secondary entity ptr */
extern void *gSfxSlotEnd;      /* 0x80092CE0 past-end sentinel */
extern void *D_800E4118;       /* handler-table sentinel */
extern void *D_80093EE4;       /* handler-table base */
extern void *D_801823B0;       /* overlay alias: same storage as gSfxFadeTimer */

void func_800620CC(void *entity);                    /* mark active (func_80061FB4.c) */
void func_80061FB4(void *entity, s32 slot, s32 flags); /* heap insert (func_80061FB4.c) */
void *func_800621C0(s32 slotSpec, s32 *outType);    /* slot lookup (func_800621C0.c) */
void *func_80062240(void);                           /* entity at gSfxMaxIndex */
void func_8006394C(void);                            /* secondary trigger (asm) */
void *func_80061884(void);                           /* secondary query A (asm) */
void func_80061800(void);                            /* secondary trigger B (asm) */

/* -------------------------------------------------------------------------
 * func_80062B0C
 * SFX playback state machine — called once per audio frame.
 * ------------------------------------------------------------------------- */
void func_80062B0C(void) {
    s32    phase = gSfxPhase;
    s32    i;
    void  *slot;
    void  *firstSlot;

    /* Dispatch on current phase. */
    if (phase == 1) {
        goto phase1;
    }
    if (phase == 0) {
        goto phase0;
    }
    if (phase == 2) {
        goto phase2;
    }
    return;   /* unknown phase — no-op */

    /* ------------------------------------------------------------------
     * Phase 0: ramp-in scan.
     * Advance the fade timer; iterate heap entries and mark them active.
     * ------------------------------------------------------------------ */
phase0:
    {
        s32 timer = (s32)D_801823B0 + gSfxRampStep;
        D_801823B0 = (void *)(intptr_t)timer;
        if (timer < 0xFF) {
            phase = 0;
            if (gSfxRampStep != 0) {
                return;
            }
        }

        /* Walk every active heap entry. */
        {
            void *endSentinel = gSfxSlotEnd;
            void *handlerSentinel = D_800E4118;
            void *handlerBase = D_80093EE4;
            s32  *currentSlotPtr = (s32 *)&gSfxCurrentSlot;

            for (i = 0; ; i++) {
                slot = func_800621C0(i, NULL);
                if (slot == endSentinel) {
                    break;
                }
                /* Record if "interesting" (not a sentinel pointer). */
                if (slot != handlerSentinel && slot != handlerBase) {
                    gSfxCurrentSlot = slot;
                }
                func_800620CC(slot);
            }
        }

        /* Scan complete — set timer to max and advance to phase 1. */
        gSfxFadeTimer = 0xFF;
        gSfxPhase     = 1;
        return;
    }

    /* ------------------------------------------------------------------
     * Phase 1: trigger / play.
     * ------------------------------------------------------------------ */
phase1:
    firstSlot = func_800621C0(-4, NULL);   /* slot 0 (first) */
    if (firstSlot == gSfxSlotEnd) {
        return;
    }

    gSfxSavedState = phase;   /* save current phase value (= 1) */

    slot = func_800621C0(-1, NULL);   /* last slot = gSfxAllocCount */
    if (slot == firstSlot) {
        /* Both ends resolve to the same entity — trigger secondary logic. */
        func_8006394C();
        if (D_80092CD8 != NULL) {
            void *secondary = func_80061884();
            if (D_80092CD8 != secondary) {
                func_80061800();
            }
        }
    }

    /* Re-insert the pending entity or mark the top-priority slot active. */
    if (gSfxEntity != NULL) {
        func_80061FB4(gSfxEntity, -3, 1);
    } else {
        void *top = func_80062240();
        func_800620CC(top);
    }

    gSfxFadeTimer = 0xFF;
    gSfxPhase     = 2;
    return;

    /* ------------------------------------------------------------------
     * Phase 2: decay / ramp-out.
     * ------------------------------------------------------------------ */
phase2:
    {
        s32 timer = gSfxFadeTimer - gSfxDecayStep;
        if (timer > 0) {
            gSfxFadeTimer = timer;
            if (gSfxDecayStep != 0) {
                return;
            }
        }

        /* Timer expired — mark the top entity done and return. */
        {
            void *top = func_80062240();
            func_800620CC(top);
        }
        return;
    }
}
