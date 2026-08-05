#include "ultra64.h"
#include "audio.h"

/*
 * func_80062D98 — SFX trigger: start playing a new sound effect.
 * func_80062F1C — write audio engine parameter block.
 *
 * func_80062D98(entity, soundId):
 *   1. Checks whether 'entity' already exists in the D_800E1F30 effect list
 *      via sfxHasEntity.  If it does and D_800E1F74 == 0, either:
 *        a. entity == D_80092BA0 (Probe mode table): play a specific cue
 *           (priority 0xF, volume 0.9, pitch 0xC350, extra 0x40) via
 *           sfxQueueCmd and set D_80092B60 = 1.
 *        b. Otherwise: clear D_80092B60.
 *   2. If 'entity' is NOT in the list (or D_800E1F74 != 0): tries to find
 *      'entity' in the main SFX heap (gSfxSlotEnd check via sfxHasEntity),
 *      optionally marks it active (sfxMarkEntityActive), then saves the current
 *      audio engine parameters, writes new ones
 *      [6, 4, 2, 4, 0xFFFFFF] into D_80092D08–D_80092D18, stores gSfxEntity
 *      (gSfxEntity) = soundId, searches the heap for 'entity' via
 *      sfxGetEntity, and inserts soundId at the found position via
 *      sfxHeapInsert.
 *
 * func_80062F1C — write five audio parameters from the function arguments
 *   directly into D_80092D08–D_80092D18.
 *
 * Globals:
 *   gSfxEntity       0x801823AC  void*  entity to insert in phase 1
 *   gSfxSlotEnd      0x80092CE0  void*  heap past-end sentinel
 *   D_800E1F30       0x800E1F30  void*  active effects list head
 *   D_800E1F74       0x800E1F74  s32    effect-list state flag
 *   D_80092BA0       0x80092BA0  void*  Probe mode function table (see symbol_addrs)
 *   D_80092B60       0x80092B60  s32    sound-active flag
 *   D_80092CF4       0x80092CF4  s32    saved audio param 0 (step/tick)
 *   gSfxRampStep       0x80092CF8  s32    saved audio param 1 (ramp step)
 *   D_80092CFC       0x80092CFC  s32    saved audio param 2
 *   gSfxDecayStep       0x80092D00  s32    saved audio param 3 (decay step)
 *   D_80092D04       0x80092D04  s32    saved audio param 4
 *   D_80092D08       0x80092D08  s32    audio engine param 0  (set to 6)
 *   D_80092D0C       0x80092D0C  s32    audio engine param 1  (set to 4)
 *   D_80092D10       0x80092D10  s32    audio engine param 2  (set to 2)
 *   D_80092D14       0x80092D14  s32    audio engine param 3  (set to 4)
 *   D_80092D18       0x80092D18  s32    audio engine param 4  (set to 0xFFFFFF)
 */

extern void *gSfxEntity;    /* 0x801823AC */
extern void *gSfxSlotEnd;   /* 0x80092CE0 */
extern void *D_800E1F30;    /* active-effects list */
extern s32   D_800E1F74;    /* effect-list state flag */
extern void *D_80092BA0;    /* Probe mode function table */
extern s32   D_80092B60;    /* sound-active flag */
extern s32   D_80092CF4;    /* saved param 0 */
extern s32   gSfxRampStep;    /* saved param 1 / gSfxRampStep */
extern s32   D_80092CFC;    /* saved param 2 */
extern s32   gSfxDecayStep;    /* saved param 3 / gSfxDecayStep */
extern s32   D_80092D04;    /* saved param 4 */
extern s32   D_80092D08;    /* engine param 0 */
extern s32   D_80092D0C;    /* engine param 1 */
extern s32   D_80092D10;    /* engine param 2 */
extern s32   D_80092D14;    /* engine param 3 */
extern s32   D_80092D18;    /* engine param 4 */

s32   sfxHasEntity(void *entity);                   /* contains check */
void  sfxMarkEntityActive(void *entity);                   /* mark-active */
void *sfxGetEntity(s32 slotSpec, s32 *outType);     /* slot lookup */
void  sfxHeapInsert(void *entity, s32 slot, s32 flags); /* heap insert */
void  sfxQueueCmd(s32 prio, s32 vol, s32 pitch,   /* audio cue trigger */
                    s32 extra, s32 flags);

/* -------------------------------------------------------------------------
 * func_80062F1C
 * Write the five audio engine parameters from the supplied arguments.
 * The sixth argument comes from the caller's stack (arg4 → D_80092D18).
 * ------------------------------------------------------------------------- */
void func_80062F1C(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4) {
    D_80092D08 = p0;
    D_80092D0C = p1;
    D_80092D10 = p2;
    D_80092D14 = p3;
    D_80092D18 = p4;
}

/* -------------------------------------------------------------------------
 * func_80062D98
 * Start playing a new SFX cue.
 *
 *   entity   — sound-source entity (used as a heap lookup key)
 *   soundId  — the cue to insert / trigger
 * ------------------------------------------------------------------------- */
void func_80062D98(void *entity, void *soundId) {
    s32 slot;
    s32 savedP0, savedP1, savedP2, savedP3, savedP4;

    /* --- Check if entity is already in the "active effects" list --- */
    if (sfxHasEntity(D_800E1F30)) {
        /* Entity is in the D_800E1F30 list. */
        if (D_800E1F74 == 0) {
            D_800E1F74 = (s32)(intptr_t)entity;   /* record entity */

            if (entity == D_80092BA0) {
                /* Probe mode entity — play a specific hard-coded cue. */
                D_80092B60 = 1;
                sfxQueueCmd(0xF,                  /* priority */
                              0x3F666666,            /* volume ≈ 0.9 (IEEE f32) */
                              0xC350,                /* pitch = 50000 */
                              0x40,                  /* extra */
                              0);                    /* stack flags */
            } else {
                D_80092B60 = 0;
            }
            return;
        }
        /* D_800E1F74 != 0 — fall through to heap insertion below. */
    }

    /* --- Entity not in the list (or list check skipped) --- */

    /* Optional: if entity is at the heap end sentinel, mark it active. */
    {
        void *slotEnd = gSfxSlotEnd;
        if (sfxHasEntity(slotEnd)) {
            sfxMarkEntityActive(slotEnd);
        }
    }

    /*
     * Save current audio engine parameters, install new ones for this cue:
     *   [6, 4, 2, 4, 0xFFFFFF]
     */
    savedP0 = D_80092D08;
    savedP1 = D_80092D0C;
    savedP2 = D_80092D10;
    savedP3 = D_80092D14;
    savedP4 = D_80092D18;

    D_80092D08 = 6;
    D_80092D10 = 2;
    D_80092D0C = 4;
    D_80092D14 = 4;
    D_80092D18 = 0xFFFFFF;

    /* Archive the old params into the "saved" slots. */
    D_80092CF4 = D_80092D08;   /* saved before overwrite above */
    gSfxRampStep = savedP1;
    D_80092CFC = savedP2;
    gSfxDecayStep = savedP3;
    D_80092D04 = savedP4;

    /* Store soundId as the entity to re-insert during phase 1. */
    gSfxEntity = soundId;

    /* Search the heap for 'entity'; insert 'soundId' at the found slot. */
    for (slot = 0; ; slot++) {
        void *found = sfxGetEntity(slot, NULL);
        if (found == soundId) {
            break;
        }
        if (found == gSfxSlotEnd) {
            /* Reached the end without finding — insert at end. */
            break;
        }
    }

    sfxHeapInsert(gSfxSlotEnd, slot, 1);
}

/* =========================================================================
 * func_800630FC
 * 0x18-byte block at 0x800630FC.  The first instruction is `sdc1 $ft1,
 * -0x7F80($t8)` which stores FPU reg $f3 into an audio output buffer.
 * The code then falls through to sfxFrameTick.  Marked nonmatching;
 * the exact C form is unknown.
 * sfxFrameTick is a sub-entry (alabel) 4 bytes in; it is the callback
 * form that callers (func_80070C3C etc.) invoke directly.
 * ========================================================================= */
extern s32   D_801823C0;   /* gSfxFrameState */
extern s32   D_801823C4;   /* gSfxBlockedFlag */
extern s32   D_801823C8;   /* gSfxTimerD */
extern void *D_801823CC;   /* DL timing reference */
extern s32   D_80173D08;   /* audio frame timer reference */
extern u8    D_80182EA8[]; /* SFX block data base */

void sfxFrameTick(void);
/* nonmatching */
void func_800630FC(void) {
    /* sdc1 ft1, -0x7F80(t8): stores audio FP output — not representable in C */
    sfxFrameTick();
}

/* Increment gSfxFrameState.  Called directly and via scheduler callbacks. */
void sfxFrameTick(void) {
    D_801823C0++;
}

/* =========================================================================
 * func_80063114
 * Reset SFX per-frame state:
 *   gSfxBlockedFlag = 0, gSfxTimerD = 0xFF, gSfxFrameState = 0,
 *   D_801823CC = D_80173D08 (current audio timer snapshot).
 * ========================================================================= */
void func_80063114(void) {
    D_801823C4 = 0;
    D_801823C8 = 0xFF;
    D_801823C0 = 0;
    D_801823CC = (void *)(intptr_t)D_80173D08;
}

/* =========================================================================
 * func_80063144
 * Slide one DL-pointer word within the SFX block data buffer:
 *   D_80182EA8[0xB1C/4] = D_80182EA8[0xB20/4]
 * ========================================================================= */
void func_80063144(void) {
    u32 *base = (u32 *)D_80182EA8;
    base[0xB1C / 4] = base[0xB20 / 4];
}

/* =========================================================================
 * func_80062F4C — build RDP display list setup sequence.
 *
 * Writes 12 × 8-byte GBI entries (96 bytes total) to *D_80173CC0 and
 * advances the pointer.  Commands emitted in order:
 *   ENDDL, SETOTHERMODE_L (fog on/off), SETCOMBINE (reset),
 *   SETFOGCOLOR (packed from args), SETOTHERMODE_H ×2,
 *   scissor value (derived from D_8017CA44 / D_80173C18),
 *   RDPFULLSYNC, RDPTILESYNC, ENDDL, SETOTHERMODE_H ×2.
 *
 * Arguments (packed as RGBA-ish bytes in the fog colour word):
 *   arg0 — alpha / blue selector; also selects fog mode (< 0xFF = fog on)
 *   arg1 — red component (shifted to byte 3)
 *   arg2 — green component (byte 2)
 *   arg3 — blue component (byte 1)
 * ========================================================================= */
extern u32 *D_80173CC0;   /* RDP display-list write pointer */
extern s32  D_8017CA44;   /* scissor / tile width  */
extern s32  D_80173C18;   /* scissor / tile height */

void func_80062F4C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 *dl = D_80173CC0;
    u32 fog_rgba;
    u32 mode_data;
    u32 ca44_part, c18_part, scissor;

    /* 1. gsSPEndDisplayList — terminate whatever came before */
    dl[0] = 0xE7000000U;
    dl[1] = 0U;
    D_80173CC0 = dl + 2;

    /* 2. G_SETOTHERMODE_L — enable or disable fog */
    mode_data = (arg0 < 0xFF) ? 0x5041C8U : 0xF0A4000U;
    dl[2] = 0xE200001CU;
    dl[3] = mode_data;
    D_80173CC0 = dl + 4;

    /* 3. G_SETCOMBINE — reset combine mode to neutral */
    dl[4] = 0xFCFFFFFFU;
    dl[5] = 0xFFFDF6FBU;

    /* 4. G_SETFOGCOLOR — pack args into RGBA */
    fog_rgba = ((u32)(arg1 & 0xFF) << 24) |
               ((u32)(arg2 & 0xFF) << 16) |
               ((u32)(arg3 & 0xFF) <<  8) |
                (u32)(arg0 & 0xFF);
    dl[6] = 0xFA000000U;
    dl[7] = fog_rgba;

    /* 5-6. G_SETOTHERMODE_H ×2 */
    dl[8]  = 0xE3000C00U;
    dl[9]  = 0U;
    dl[10] = 0xE3001801U;
    dl[11] = 0x80U;

    /* 7. Scissor word — computed from tile dimensions */
    ca44_part = (u32)(((D_8017CA44 - 1) << 2) & 0xFFF) << 12;
    c18_part  = (u32)(((D_80173C18 - 1) << 2) & 0xFFF) | 0xE4000000U;
    scissor   = ca44_part | c18_part;
    dl[12] = scissor;
    dl[13] = 0U;

    /* 8. G_RDPFULLSYNC */
    dl[14] = 0xE1000000U;
    dl[15] = 0U;

    /* 9. G_RDPTILESYNC */
    dl[16] = 0xF1000000U;
    dl[17] = 0U;

    /* 10. gsSPEndDisplayList */
    dl[18] = 0xE7000000U;
    dl[19] = 0U;

    /* 11-12. G_SETOTHERMODE_H ×2 (second group) */
    dl[20] = 0xE3000C00U;
    dl[21] = 0x80000U;
    dl[22] = 0xE3001801U;
    dl[23] = 0U;

    D_80173CC0 = dl + 24;
}
