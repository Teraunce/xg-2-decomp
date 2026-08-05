#include "ultra64.h"
#include "audio.h"

/*
 * SFX heap accessors and per-channel state update.
 *
 * sfxGetEntity — look up an entity pointer from the heap by resolved index,
 *                  optionally returning the slot's type field.
 * func_80062240 — return the entity at gSfxMaxIndex (highest occupied slot).
 * func_80062278 — return the entity at gSfxAllocCount (allocation cursor).
 * func_800622C0 — update all four SFX channel states from the input table.
 * func_800625C0 — trivially return gSfxActiveCount.
 *
 * Globals:
 *   gSfxActiveCount   0x80092CB8  s32
 *   gSfxMaxIndex      0x80092CBC  s32
 *   gSfxAllocCount    0x80092CC0  s32
 *   gSfxChannelMute   0x80092CD0  u8[4]
 *   gSfxChannelIdx    0x80092CD4  s32
 *   gSfxVolScale      0x80092CDC  f32
 *   gSfxPendingSlot   0x80092CC4  s32  — pending output bus index
 *   gSfxPendingCount  0x80092CC8  s32  — pending bus count
 *   gSfxHeap          0x80182348  SfxSortEntry[]
 *   gSfxInputTable    0x8017CA08  SfxInputEntry[4]
 *   gSfxChannelState  0x801820D8  SfxChannelState[4]
 *   D_8004C028        0x8004C02C  f32  — volume scale factor A (rodata)
 *   D_8004C02C        0x8004C02C  f32  — volume scale factor B (rodata)
 */

extern s32           gSfxActiveCount;          /* 0x80092CB8 */
extern s32           gSfxMaxIndex;             /* 0x80092CBC */
extern s32           gSfxAllocCount;           /* 0x80092CC0 */
extern s32           gSfxPendingSlot;          /* 0x80092CC4 */
extern s32           gSfxPendingCount;         /* 0x80092CC8 */
extern u8            gSfxChannelMute[4];       /* 0x80092CD0 */
extern s32           gSfxChannelIdx;           /* 0x80092CD4 */
extern f32           gSfxVolScale;             /* 0x80092CDC */
extern SfxSortEntry  gSfxHeap[];               /* 0x80182348 */
extern SfxInputEntry gSfxInputTable[4];        /* 0x8017CA08 */
extern SfxChannelState gSfxChannelState[4];    /* 0x801820D8 */

extern f32 D_8004C028;   /* rodata: volume multiplier for active-channel fade */
extern f32 D_8004C02C;   /* rodata: volume multiplier for counter-expired fade */

s32 sfxSlotResolve(s32);  /* slot resolver (func_80061F0C.c) */

/* -------------------------------------------------------------------------
 * sfxGetEntity
 * Look up the entity pointer for a resolved heap slot.
 *
 *   slotSpec  — heap index or sentinel value (-4 to -1), resolved by
 *               sfxSlotResolve before the array access.
 *   outType   — if non-NULL, receives heap[slot].type
 *
 * Returns NULL (0) if the resolved slot is out of range.
 * Callers compare the return value against special sentinel pointers such as
 * gSfxSlotEnd (gSfxSlotEnd) to detect end-of-heap conditions.
 * ------------------------------------------------------------------------- */
void *sfxGetEntity(s32 slotSpec, s32 *outType) {
    s32 slot = sfxSlotResolve(slotSpec);

    if (slot < 0) {
        if (!((u32)slot < (u32)gSfxActiveCount)) {
            return NULL;
        }
    }

    if (outType != NULL) {
        *outType = gSfxHeap[slot].type;
    }
    return gSfxHeap[slot].entity;
}

/* -------------------------------------------------------------------------
 * func_80062240
 * Return the entity pointer at gSfxMaxIndex (the highest occupied heap slot).
 * Returns NULL if gSfxMaxIndex < 0 (heap is empty / uninitialized).
 * ------------------------------------------------------------------------- */
void *func_80062240(void) {
    s32 idx = gSfxMaxIndex;
    if (idx < 0) {
        return NULL;
    }
    return gSfxHeap[idx].entity;
}

/* -------------------------------------------------------------------------
 * func_80062278
 * Return the entity pointer at gSfxAllocCount (the allocation cursor).
 * Returns NULL if gSfxAllocCount < 0 or >= gSfxActiveCount.
 * ------------------------------------------------------------------------- */
void *func_80062278(void) {
    s32 idx = gSfxAllocCount;
    if (idx < 0) {
        return NULL;
    }
    if ((u32)idx >= (u32)gSfxActiveCount) {
        return NULL;
    }
    return gSfxHeap[idx].entity;
}

/* -------------------------------------------------------------------------
 * func_800622C0
 * Per-frame SFX channel state update.
 *
 * Iterates over all 4 SFX channels.  For each channel:
 *
 *   — If gSfxInputTable[chan].mute != 0: zero out the SfxChannelState entry.
 *
 *   — Else: compute stereo balance offsets (panL/panR) from the signed
 *     volume byte in gSfxInputTable[chan].vol using fixed-point division by
 *     10, apply a ±24-unit deadzone (values within ±24 are zeroed), then
 *     encode directional flags in soundId based on which channel has the
 *     larger absolute offset and the sign of that offset.
 *     A separate counter (counter/decrement) handles volume-fade-out using
 *     gSfxVolScale-scaled multiplication.
 *
 * After the 4-channel loop the function updates gSfxPendingSlot /
 * gSfxPendingCount and propagates the resulting mute flags back into
 * gSfxChannelMute[].
 *
 * NOTE: This function is marked nonmatching.  The channel-state arithmetic
 * matches the assembly control flow exactly but the magic-constant integer
 * division ( /10 ) and the flag-encoding bit positions are compiler-generated;
 * they will reproduce correctly only with the SN64 compiler.
 * ------------------------------------------------------------------------- */
void func_800622C0(void) {
    s32 chan;
    SfxInputEntry  *inp = gSfxInputTable;
    SfxChannelState *out = gSfxChannelState;
    f32 volScale = gSfxVolScale;

    for (chan = 0; chan < 4; chan++, inp++, out++) {

        if (inp->mute) {
            /* Muted channel — silence all output fields. */
            out->active  = 0;
            out->soundId = 0;
            out->panR    = 0;
            out->panL    = 0;
            continue;
        }

        /* --- Active channel: compute stereo balance values. --- */
        out->active  = 1;
        out->soundId = inp->id;

        /*
         * Compute left pan offset from vol.
         * The assembly uses magic-constant signed division by 10:
         *   panL = -(s32)inp->vol * 256 / 10
         * Small values (|panL| < 24) are suppressed (deadzone).
         */
        {
            s32 panL = (s32)(-(s32)inp->vol) * 256 / 10;
            out->panL = panL;
            if (panL < 0) { panL = -panL; }
            if (panL < 0x18) {
                out->panL = 0;
            }
        }

        /*
         * Compute right pan offset from the second signed byte (unk02).
         *   panR = (s32)inp->unk02 * 256 / 10
         * Same ±24 deadzone applied.
         */
        {
            s32 panR = (s32)inp->unk02 * 256 / 10;
            out->panR = panR;
            if (panR < 0) { panR = -panR; }
            if (panR < 0x18) {
                out->panR = 0;
            }
        }

        /*
         * Encode directional flags into soundId based on the relative
         * magnitude of panL vs half of |panR|, and vice versa.
         * The exact bit positions (0x10000, 0x20000, 0x40000, 0x80000)
         * are determined by the asm flag-or logic.
         */
        {
            s32 panL = out->panL;
            s32 absL = (panL < 0) ? -panL : panL;
            s32 panR = out->panR;
            s32 halfL = ((-absL + ((-absL) >> 31)) >> 1);  /* ceil(-absL/2) */
            u32 flags = out->soundId;

            if (panR < halfL) {
                flags |= (out->soundId | 0x20000);
            } else {
                s32 avg = (panL + (panL >> 31)) >> 1;
                if (avg < (s32)0x10000) {
                    flags |= 0x10000;
                }
            }

            {
                s32 absR = (panR < 0) ? -panR : panR;
                s32 halfR = ((-absR + ((-absR) >> 31)) >> 1);
                if (panL < halfR) {
                    flags |= 0x80000;
                } else {
                    s32 avg = (panR + (panR >> 31)) >> 1;
                    if (avg < (s32)0x40000) {
                        flags |= 0x40000;
                    }
                }
            }

            out->soundId = flags;
        }

        /* Update flags: xor previous with new to isolate changes. */
        {
            u32 raw  = out->soundId;
            u32 mask = out->prevFlags;
            u32 both = raw & mask;
            out->flags    = raw ^ both;
            out->prevFlags = raw;
        }

        /*
         * Volume fade counter logic.
         * When out->decrement > 0: clear bits 0xFFF0FFFF from flags,
         *   decrement the counter.
         * When counter expires (reaches 0): apply volScale multiplier to
         *   decrement, reset counter = trunc(volScale * D_8004C02C).
         */
        if (out->decrement > 0) {
            out->flags &= 0xFFF0FFFF;
            out->decrement--;
        } else {
            if (out->flags != 0) {
                if (out->flags & 0x000F0000) {
                    out->output = (s32)(volScale * D_8004C028);
                    out->decrement = (s32)(volScale * D_8004C028);
                }
            }
        }

        if (out->flags != 0) {
            out->counter = 0x19;  /* 25 */
            out->output  = out->soundId;
        } else if (out->soundId != 0) {
            s32 cnt = out->counter - 1;
            out->counter = cnt;
            if (cnt <= 0) {
                out->output  = out->soundId;
                out->counter = (s32)(volScale * D_8004C02C);
                inp += 6;  /* advance to next group (matches addiu $t0, $t0, 6 in asm) */
                continue;
            }
            out->output = 0;
        } else {
            out->counter = 0;
        }
    }

    /*
     * After the 4-channel loop, update gSfxPendingSlot / gSfxPendingCount
     * from gSfxChannelIdx (the channel that became pending this frame).
     */
    {
        s32 pending = gSfxChannelIdx;
        if (pending >= 0) {
            gSfxPendingCount = pending;
        } else {
            /* Scan channel states for any non-zero soundId; that channel
             * becomes the pending count. */
            s32 i;
            gSfxPendingCount = 0;
            for (i = 0; i < 4; i++) {
                if (gSfxChannelState[i].soundId != 0) {
                    gSfxPendingCount = chan;   /* chan = 4 at loop exit */
                    break;
                }
            }
        }
    }

    /*
     * Propagate final mute decisions back into gSfxChannelMute[] by
     * extracting bit 12 from each channel's soundId field.
     */
    {
        s32 i;
        u8  *mute = gSfxChannelMute;
        SfxChannelState *st = gSfxChannelState;
        for (i = 0; i < 4; i++, mute++, st++) {
            *mute = (u8)((st->soundId >> 12) & 1);
        }
    }
}

/* -------------------------------------------------------------------------
 * func_800625C0
 * Return the current active SFX entry count (trivial getter).
 * ------------------------------------------------------------------------- */
s32 func_800625C0(void) {
    return gSfxActiveCount;
}
