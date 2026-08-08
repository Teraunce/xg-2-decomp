#include "ultra64.h"
#include "audio.h"

/*
 * sfxFrameStateMachine — SFX per-frame state machine (nonmatching).
 *
 * Entry conditions:
 *   entity — the "master" sound-source entity pointer ($a0, saved to $s1).
 *   arg1   — nonzero if the caller has an active SFX entity to process.
 *
 * -------------------------------------------------------------------------
 * QUICK PATH (arg1 == 0, or master entity found in heap):
 *   If gSfxBlockedFlag (D_801823C4) is nonzero, decrement gSfxTimerD
 *   (D_801823C8) by 8.  If still > 0, return (leaving timer in place).
 *   Otherwise write zero to gSfxTimerD and return.
 *   This path is shared between:
 *     a) arg1 == 0  (caller has nothing active)
 *     b) sfxHasEntity(gHandlerTable) returns nonzero  (master entity is
 *        already in the heap — normal frame-to-frame ticking)
 *
 * -------------------------------------------------------------------------
 * STATE MACHINE (arg1 != 0 AND master entity NOT in heap):
 *   Dispatches on gSfxFrameState (D_801823C0), 0–7, via jtbl_8004C030.
 *   Any state that falls to func_80063438 increments gSfxFrameState by 1.
 *   States that jump directly to func_800634B4 (epilogue) do not advance.
 *
 *   State 0 — "Is the SFX system initialised?"
 *     Check sfxHasEntity(gSfxSlotEnd) (the gSfxSlotEnd sentinel).
 *     NOT found → DMA-load the audio overlay via __osInvalICache_full /
 *       osWritebackInvalDCache / osInvalICache / audioDecodeHufh / audioBootDecode
 *       (twice: once for code, once for data).  → advance state.
 *     Found → scan gSfxChannelMute[0..3]; if any byte is nonzero set
 *       gSfxBlockedFlag = 1.  → DO NOT advance state (return as-is).
 *
 *   State 1 — Schedule the state-advance callback.
 *     gameHandlerInit(entity, sfxFrameTick)
 *     → DO NOT advance state (scheduler fires sfxFrameTick on completion).
 *
 *   State 2 — Manage gSfxTimerD.
 *     If gSfxBlockedFlag:
 *       Decrement gSfxTimerD by 8.  If still > 0, return.
 *       Else: clear gSfxTimerD and gSfxBlockedFlag; snapshot D_80173D08 →
 *       D_801823CC; return (stay in state 2 to wait for timer to recover).
 *     Else (not blocked):
 *       Increment gSfxTimerD by 4.  If < 0xFF, return.
 *       Else: set gSfxTimerD = 0xFF, advance gSfxFrameState; snapshot
 *       D_80173D08 → D_801823CC; return.
 *
 *   State 3 — Compute and store SFX block volumes (12 × 3 nested loop).
 *     Outer (s1 = 0..11, s5 += 0xD8), inner (s2 = 0..2, s3 += 0x10):
 *       trackSegmentOffset(outer, inner) → result
 *       sfxGetFrameOutput(result) → id_word
 *       s0 = id_word & 0xFFFF
 *       def = sfxGetEntry(s0)
 *       vol = def[+0xC]   (raw s32)
 *       vol = (vol * 3 + sign_bit) >> 1  [round-to-zero *1.5]
 *       if vol >= 0x1519: vol = 0x1518
 *       D_80182EA8[s5 + s3 + 0x1C] = vol  (write 1, s3=s5+inner*0x10)
 *       D_80182EA8[s5 + 0x30 + inner*0x10 + 0x1C] = vol  (write 2)
 *       sfxPlay(s0)   [a0 = sound id, not vol]
 *     → advance state.
 *
 *   State 4 — Audio engine tick + scheduled CD4 dispatch.
 *     result = entityFindActive()
 *     if result < 0: call sfxFrameTick(); return.
 *     extra = func_800DD984(entity)
 *     handlerSetupLooped(entity, sfxFrameTick, result, extra)
 *     → DO NOT advance state.
 *
 *   State 5 — Audio engine tick + D50 dispatch.
 *     result = entityFindActive()
 *     if result < 0: call sfxFrameTick(); return.
 *     handlerSetupTable(entity, sfxFrameTick, result, D_800DDC5C)
 *     → DO NOT advance state.
 *
 *   State 6 — Timing gate + trigger output.
 *     if (D_801823CC + 0xB4) >= D_80173D08: return (not yet time).
 *     audioSetTrack(D_801839A8)
 *     D_80092B64 = 1
 *     func_800C0810(0, 0)
 *     → DO NOT advance state.
 *
 *   State 7 — (jump table entry; direct return / no-op).
 *
 * -------------------------------------------------------------------------
 * Globals referenced (all overlay unless noted):
 *   D_801823C0  0x801823C0  s32   gSfxFrameState
 *   D_801823C4  0x801823C4  s32   gSfxBlockedFlag
 *   D_801823C8  0x801823C8  s32   gSfxTimerD
 *   D_801823CC  0x801823CC  s32   DL timing reference
 *   D_80182EA8  0x80182EA8  u8[]  SFX block data
 *   D_80173D08  0x80173D08  s32   audio frame timer (overlay)
 *   D_801839A8  0x801839A8  void* output context pointer (overlay)
 *   gSfxSlotEnd  0x80092CE0  void* gSfxSlotEnd sentinel (main BSS)
 *   gSfxChannelMute  0x80092CD0  u8[4] gSfxChannelMute (main BSS)
 *   D_80092B64  0x80092B64  s32   sound-output-active flag (main BSS)
 *   gHandlerTable  0x80093EE4  void* master handler entity (main BSS)
 *   D_80096540  0x80096540  void* DMA destination buffer (main BSS)
 *   D_8004BA14  0x8004BA14  void* heap-init pointer (rodata)
 *   D_800DDC5C  0x800DDC5C  void* audio callback table (rodata)
 *   D_1F080     0x0001F080  u32   DMA length constant
 */

/* ---- externs ------------------------------------------------------------ */
extern s32   D_801823C0;        /* gSfxFrameState */
extern s32   D_801823C4;        /* gSfxBlockedFlag */
extern s32   D_801823C8;        /* gSfxTimerD */
extern s32   D_801823CC;        /* DL timing reference (used as s32 for arithmetic) */
extern u8    D_80182EA8[];      /* SFX block data base */
extern s32   D_80173D08;        /* audio frame timer */
extern void *D_801839A8;        /* output context */
extern void *gSfxSlotEnd;        /* gSfxSlotEnd sentinel */
extern u8    gSfxChannelMute[4];     /* gSfxChannelMute[4] */
extern s32   D_80092B64;        /* sound-output-active flag */
extern void *gHandlerTable;        /* master handler entity */
extern s32   D_80096540;        /* DMA destination buffer */
extern void *D_8004BA14;        /* heap-init pointer (loaded as pointer) */
extern void *D_800DDC5C;        /* audio callback table */
extern u32   D_1F080;           /* DMA length */

/* ---- forward declarations for called functions ------------------------- */
s32   sfxHasEntity(void *entity);
void  __osInvalICache_full(void);
void  osWritebackInvalDCache(void *dst, u32 len);
void  osInvalICache(void *dst, u32 len);
void  audioDecodeHufh(void *src, void *dst, u32 len, s32 unk);
void  audioBootDecode(void);
void  sfxFrameTick(void);
void  trackSegmentOffset(s32 outer, s32 inner);
s32   sfxGetFrameOutput(void);
void *sfxGetEntry(s32 id);
void  sfxPlay(s32 soundId);
s32   gameHandlerInit(void *entity, void (*cb)(void));
s32   entityFindActive(void);
s32   func_800DD984(void *entity);
void  handlerSetupLooped(void *entity, void (*cb)(void), s32 result, s32 extra);
void  handlerSetupTable(void *entity, void (*cb)(void), s32 result, void *tbl);
void  audioSetTrack(void *ctx);
void  func_800C0810(s32 a0, s32 a1);

/* -------------------------------------------------------------------------
 * sfxFrameStateMachine
 * nonmatching
 * ------------------------------------------------------------------------- */
void sfxFrameStateMachine(void *entity, s32 arg1) {
    s32 state;

    /* ------------------------------------------------------------------ */
    /* Quick path A: no active entity from caller                          */
    /* ------------------------------------------------------------------ */
    if (arg1 == 0) {
        goto lbl_blocked_check;
    }

    /* ------------------------------------------------------------------ */
    /* Quick path B: master entity is already in the heap → just tick      */
    /* ------------------------------------------------------------------ */
    if (sfxHasEntity(gHandlerTable)) {
        goto lbl_blocked_check;
    }

    /* ------------------------------------------------------------------ */
    /* State machine dispatch                                               */
    /* ------------------------------------------------------------------ */
    state = D_801823C0;
    if ((u32)state >= 8u) {
        return;
    }

    switch (state) {

    /* ------------------------------------------------------------------
     * State 0: check whether the audio overlay is already loaded
     *          (gSfxSlotEnd / gSfxSlotEnd will be in the heap once DMA'd).
     * ------------------------------------------------------------------ */
    case 0:
        if (!sfxHasEntity(gSfxSlotEnd)) {
            /* Sentinel NOT found → DMA-load the audio overlay twice. */
            __osInvalICache_full();
            osWritebackInvalDCache(&D_80096540, D_1F080);
            osInvalICache(&D_80096540, D_1F080);
            audioDecodeHufh((u8 *)D_8004BA14 + 0x18,
                          &D_80096540,
                          D_1F080,
                          0);
            __osInvalICache_full();
            osWritebackInvalDCache(&D_80096540, D_1F080);
            osInvalICache(&D_80096540, D_1F080);
            audioBootDecode();
            /* → advance state */
            goto lbl_advance_state;
        } else {
            /* Sentinel found → check channel mute flags. */
            s32 i;
            for (i = 0; i < 4; i++) {
                if (gSfxChannelMute[i] != 0) {
                    D_801823C4 = 1;
                    break;
                }
            }
            /* DO NOT advance state. */
            return;
        }

    /* ------------------------------------------------------------------
     * State 1: schedule the state-advance callback via the audio engine.
     * ------------------------------------------------------------------ */
    case 1:
        gameHandlerInit(entity, sfxFrameTick);
        return;  /* scheduler fires sfxFrameTick on completion */

    /* ------------------------------------------------------------------
     * State 2: manage gSfxTimerD countdown / warm-up.
     * ------------------------------------------------------------------ */
    case 2:
        if (D_801823C4 != 0) {
            /* Blocked: count down. */
            s32 timer = D_801823C8 - 8;
            if (timer > 0) {
                D_801823C8 = timer;
                return;
            }
            /* Timer expired: clear state. */
            D_801823C8 = timer;   /* store (≤ 0) then clear */
            D_801823C8 = 0;
            D_801823C4 = 0;
            D_801823CC = D_80173D08;
        } else {
            /* Not blocked: warm up. */
            s32 timer = D_801823C8 + 4;
            D_801823C8 = timer;
            if (timer < 0xFF) {
                return;
            }
            D_801823C8 = 0xFF;
            D_801823C0++;
            D_801823CC = D_80173D08;
        }
        return;

    /* ------------------------------------------------------------------
     * State 3: compute and store SFX block volumes (12 × 3 loop).
     * ------------------------------------------------------------------ */
    case 3: {
        s32  outer, inner;
        u8  *base = D_80182EA8;
        s32  s5   = 0;   /* outer stride accumulator (× 0xD8) */

        for (outer = 0; outer < 12; outer++, s5 += 0xD8) {
            s32 s3 = s5;    /* inner stride within this outer (× 0x10) */
            s32 s4 = 0x30;  /* secondary inner offset */

            for (inner = 0; inner < 3; inner++, s3 += 0x10, s4 += 0x10) {
                s32 id, vol;
                void *def;

                trackSegmentOffset(outer, inner);
                id  = sfxGetFrameOutput();  /* nonmatching: compiler passes $v0 from prior call */
                id  = (u16)id;                      /* andi 0xFFFF */
                def = sfxGetEntry(id);

                {
                    /* vol = def[+0xC] * 3/2, round toward zero */
                    s32 v = *(s32 *)((u8 *)def + 0xC);
                    s32 v3 = v + (v << 1);          /* v*3 */
                    v = (v3 + (v3 >> 31)) >> 1;     /* arithmetic round-half-to-zero */
                    vol = (v >= 0x1519) ? 0x1518 : v;
                }

                /* Write vol at two locations in the block data. */
                *(s32 *)(base + s5 + s3 + 0x1C)        = vol;
                *(s32 *)(base + s5 + s4 + 0x1C)        = vol;

                sfxPlay(id);  /* a0 = sound id (not vol) */
            }
        }
        goto lbl_advance_state;
    }

    /* ------------------------------------------------------------------
     * State 4: audio engine tick → CD4 scheduled dispatch.
     * ------------------------------------------------------------------ */
    case 4: {
        s32 result = entityFindActive();
        if (result < 0) {
            goto lbl_error;
        }
        {
            s32 extra = func_800DD984(entity);
            handlerSetupLooped(entity, sfxFrameTick, result, extra);
        }
        return;
    }

    /* ------------------------------------------------------------------
     * State 5: audio engine tick → D50 table dispatch.
     * ------------------------------------------------------------------ */
    case 5: {
        s32 result = entityFindActive();
        if (result < 0) {
            goto lbl_error;
        }
        handlerSetupTable(entity, sfxFrameTick, result, D_800DDC5C);
        return;
    }

    /* ------------------------------------------------------------------
     * State 6: timing gate — wait until D_80173D08 has advanced enough.
     * ------------------------------------------------------------------ */
    case 6: {
        s32 ref = D_801823CC + 0xB4;
        if (ref >= D_80173D08) {
            return;  /* too soon */
        }
        audioSetTrack(D_801839A8);
        D_80092B64 = 1;
        func_800C0810(0, 0);
        return;
    }

    case 7:
    default:
        return;
    }

lbl_error:
    /* Error path: increment state by 1 and return. */
    sfxFrameTick();
    return;

lbl_advance_state:
    /* Shared tail (alabel func_80063438): increment gSfxFrameState. */
    D_801823C0++;
    return;

lbl_blocked_check:
    /* Quick-path handler (alabel func_800634B4 entry): */
    if (D_801823C4 != 0) {
        s32 timer = D_801823C8 - 8;
        if (timer > 0) {
            D_801823C8 = timer;
            return;
        }
        D_801823C8 = timer;
        D_801823C8 = 0;
    }
}
