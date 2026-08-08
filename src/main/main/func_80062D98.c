#include "ultra64.h"
#include "audio.h"

/*
 * sfxPlayCue — SFX trigger: start playing a new sound effect.
 * sfxSetCueParams — write audio engine parameter block.
 *
 * sfxPlayCue(entity, soundId):
 *   1. Checks whether 'entity' already exists in the gSfxEffectList effect list
 *      via sfxHasEntity.  If it does and gSfxEffectFlag == 0, either:
 *        a. entity == gSfxProbeTable (Probe mode table): play a specific cue
 *           (priority 0xF, volume 0.9, pitch 0xC350, extra 0x40) via
 *           sfxQueueCmd and set gSfxActive = 1.
 *        b. Otherwise: clear gSfxActive.
 *   2. If 'entity' is NOT in the list (or gSfxEffectFlag != 0): tries to find
 *      'entity' in the main SFX heap (gSfxSlotEnd check via sfxHasEntity),
 *      optionally marks it active (sfxMarkEntityActive), then saves the current
 *      audio engine parameters, writes new ones
 *      [6, 4, 2, 4, 0xFFFFFF] into gAudioParam0–gAudioParam4, stores gSfxEntity
 *      (gSfxEntity) = soundId, searches the heap for 'entity' via
 *      sfxGetEntity, and inserts soundId at the found position via
 *      sfxHeapInsert.
 *
 * sfxSetCueParams — write five audio parameters from the function arguments
 *   directly into gAudioParam0–gAudioParam4.
 *
 * Globals:
 *   gSfxEntity       0x801823AC  void*  entity to insert in phase 1
 *   gSfxSlotEnd      0x80092CE0  void*  heap past-end sentinel
 *   gSfxEffectList       0x800E1F30  void*  active effects list head
 *   gSfxEffectFlag       0x800E1F74  s32    effect-list state flag
 *   gSfxProbeTable       0x80092BA0  void*  Probe mode function table (see symbol_addrs)
 *   gSfxActive       0x80092B60  s32    sound-active flag
 *   gAudioSavedParam0       0x80092CF4  s32    saved audio param 0 (step/tick)
 *   gSfxRampStep       0x80092CF8  s32    saved audio param 1 (ramp step)
 *   gAudioSavedParam2       0x80092CFC  s32    saved audio param 2
 *   gSfxDecayStep       0x80092D00  s32    saved audio param 3 (decay step)
 *   gAudioPackedParams       0x80092D04  s32    saved audio param 4
 *   gAudioParam0       0x80092D08  s32    audio engine param 0  (set to 6)
 *   gAudioParam1       0x80092D0C  s32    audio engine param 1  (set to 4)
 *   gAudioParam2       0x80092D10  s32    audio engine param 2  (set to 2)
 *   gAudioParam3       0x80092D14  s32    audio engine param 3  (set to 4)
 *   gAudioParam4       0x80092D18  s32    audio engine param 4  (set to 0xFFFFFF)
 */

extern void *gSfxEntity;    /* 0x801823AC */
extern void *gSfxSlotEnd;   /* 0x80092CE0 */
extern void *gSfxEffectList;    /* active-effects list */
extern s32   gSfxEffectFlag;    /* effect-list state flag */
extern void *gSfxProbeTable;    /* Probe mode function table */
extern s32   gSfxActive;    /* sound-active flag */
extern s32   gAudioSavedParam0;    /* saved param 0 */
extern s32   gSfxRampStep;    /* saved param 1 / gSfxRampStep */
extern s32   gAudioSavedParam2;    /* saved param 2 */
extern s32   gSfxDecayStep;    /* saved param 3 / gSfxDecayStep */
extern s32   gAudioPackedParams;    /* saved param 4 */
extern s32   gAudioParam0;    /* engine param 0 */
extern s32   gAudioParam1;    /* engine param 1 */
extern s32   gAudioParam2;    /* engine param 2 */
extern s32   gAudioParam3;    /* engine param 3 */
extern s32   gAudioParam4;    /* engine param 4 */

s32   sfxHasEntity(void *entity);                   /* contains check */
void  sfxMarkEntityActive(void *entity);                   /* mark-active */
void *sfxGetEntity(s32 slotSpec, s32 *outType);     /* slot lookup */
void  sfxHeapInsert(void *entity, s32 slot, s32 flags); /* heap insert */
void  sfxQueueCmd(s32 prio, s32 vol, s32 pitch,   /* audio cue trigger */
                    s32 extra, s32 flags);

/* -------------------------------------------------------------------------
 * sfxSetCueParams
 * Write the five audio engine parameters from the supplied arguments.
 * The sixth argument comes from the caller's stack (arg4 → gAudioParam4).
 * ------------------------------------------------------------------------- */
void sfxSetCueParams(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4) {
    gAudioParam0 = p0;
    gAudioParam1 = p1;
    gAudioParam2 = p2;
    gAudioParam3 = p3;
    gAudioParam4 = p4;
}

/* -------------------------------------------------------------------------
 * sfxPlayCue
 * Start playing a new SFX cue.
 *
 *   entity   — sound-source entity (used as a heap lookup key)
 *   soundId  — the cue to insert / trigger
 * ------------------------------------------------------------------------- */
void sfxPlayCue(void *entity, void *soundId) {
    s32 slot;
    s32 savedP0, savedP1, savedP2, savedP3, savedP4;

    /* --- Check if entity is already in the "active effects" list --- */
    if (sfxHasEntity(gSfxEffectList)) {
        /* Entity is in the gSfxEffectList list. */
        if (gSfxEffectFlag == 0) {
            gSfxEffectFlag = (s32)(intptr_t)entity;   /* record entity */

            if (entity == gSfxProbeTable) {
                /* Probe mode entity — play a specific hard-coded cue. */
                gSfxActive = 1;
                sfxQueueCmd(0xF,                  /* priority */
                              0x3F666666,            /* volume ≈ 0.9 (IEEE f32) */
                              0xC350,                /* pitch = 50000 */
                              0x40,                  /* extra */
                              0);                    /* stack flags */
            } else {
                gSfxActive = 0;
            }
            return;
        }
        /* gSfxEffectFlag != 0 — fall through to heap insertion below. */
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
    savedP0 = gAudioParam0;
    savedP1 = gAudioParam1;
    savedP2 = gAudioParam2;
    savedP3 = gAudioParam3;
    savedP4 = gAudioParam4;

    gAudioParam0 = 6;
    gAudioParam2 = 2;
    gAudioParam1 = 4;
    gAudioParam3 = 4;
    gAudioParam4 = 0xFFFFFF;

    /* Archive the old params into the "saved" slots. */
    gAudioSavedParam0 = gAudioParam0;   /* saved before overwrite above */
    gSfxRampStep = savedP1;
    gAudioSavedParam2 = savedP2;
    gSfxDecayStep = savedP3;
    gAudioPackedParams = savedP4;

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
 * form that callers (gameHandlerInit etc.) invoke directly.
 * ========================================================================= */
extern s32   gSfxFrameState;   /* gSfxFrameState */
extern s32   gSfxBlockedFlag;   /* gSfxBlockedFlag */
extern s32   gSfxTimer;   /* gSfxTimerD */
extern void *gSfxTimerRef;   /* DL timing reference */
extern s32   gLoopCount;   /* audio frame timer reference */
extern u8    gRaceCtx[]; /* SFX block data base */

void sfxFrameTick(void);
/* nonmatching */
void func_800630FC(void) {
    /* sdc1 ft1, -0x7F80(t8): stores audio FP output — not representable in C */
    sfxFrameTick();
}

/* Increment gSfxFrameState.  Called directly and via scheduler callbacks. */
void sfxFrameTick(void) {
    gSfxFrameState++;
}

/* =========================================================================
 * func_80063114
 * Reset SFX per-frame state:
 *   gSfxBlockedFlag = 0, gSfxTimerD = 0xFF, gSfxFrameState = 0,
 *   gSfxTimerRef = gLoopCount (current audio timer snapshot).
 * ========================================================================= */
void func_80063114(void) {
    gSfxBlockedFlag = 0;
    gSfxTimer = 0xFF;
    gSfxFrameState = 0;
    gSfxTimerRef = (void *)(intptr_t)gLoopCount;
}

/* =========================================================================
 * func_80063144
 * Slide one DL-pointer word within the SFX block data buffer:
 *   gRaceCtx[0xB1C/4] = gRaceCtx[0xB20/4]
 * ========================================================================= */
void func_80063144(void) {
    u32 *base = (u32 *)gRaceCtx;
    base[0xB1C / 4] = base[0xB20 / 4];
}

/* =========================================================================
 * rdpSetFogColor — build RDP display list setup sequence.
 *
 * Writes 12 × 8-byte GBI entries (96 bytes total) to *gDLPtr and
 * advances the pointer.  Commands emitted in order:
 *   ENDDL, SETOTHERMODE_L (fog on/off), SETCOMBINE (reset),
 *   SETFOGCOLOR (packed from args), SETOTHERMODE_H ×2,
 *   scissor value (derived from gScreenWidth / gScreenHeight),
 *   RDPFULLSYNC, RDPTILESYNC, ENDDL, SETOTHERMODE_H ×2.
 *
 * Arguments (packed as RGBA-ish bytes in the fog colour word):
 *   arg0 — alpha / blue selector; also selects fog mode (< 0xFF = fog on)
 *   arg1 — red component (shifted to byte 3)
 *   arg2 — green component (byte 2)
 *   arg3 — blue component (byte 1)
 * ========================================================================= */
extern u32 *gDLPtr;   /* RDP display-list write pointer */
extern s32  gScreenWidth;   /* scissor / tile width  */
extern s32  gScreenHeight;   /* scissor / tile height */

void rdpSetFogColor(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 *dl = gDLPtr;
    u32 fog_rgba;
    u32 mode_data;
    u32 ca44_part, c18_part, scissor;

    /* 1. gsSPEndDisplayList — terminate whatever came before */
    dl[0] = 0xE7000000U;
    dl[1] = 0U;
    gDLPtr = dl + 2;

    /* 2. G_SETOTHERMODE_L — enable or disable fog */
    mode_data = (arg0 < 0xFF) ? 0x5041C8U : 0xF0A4000U;
    dl[2] = 0xE200001CU;
    dl[3] = mode_data;
    gDLPtr = dl + 4;

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
    ca44_part = (u32)(((gScreenWidth - 1) << 2) & 0xFFF) << 12;
    c18_part  = (u32)(((gScreenHeight - 1) << 2) & 0xFFF) | 0xE4000000U;
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

    gDLPtr = dl + 24;
}
