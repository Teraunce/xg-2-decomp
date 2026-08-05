#include "ultra64.h"
#include "audio.h"

/*
 * sfxLookupName / sfxSlotResolve / sfxSlotResolve — SFX slot-index resolver
 *
 * sfxSlotResolve resolves four magic negative sentinel values into real heap
 * indices before any access to gSfxHeap (gSfxHeap):
 *
 *   slotSpec == -4  →  0               (first slot)
 *   slotSpec == -3  →  gSfxMaxIndex    (highest occupied slot; 0 if unset)
 *   slotSpec == -2  →  gSfxMaxIndex+1  if gSfxMaxIndex >= 0
 *                   →  gSfxActiveCount  if gSfxMaxIndex < 0
 *   slotSpec == -1  →  gSfxActiveCount
 *   slotSpec >= 0   →  slotSpec        (pass-through)
 *
 * sfxSlotResolve is the label name for the same function (4-byte-aligned
 * padding precedes the real entry at sfxSlotResolve).
 *
 * sfxLookupName is a thin wrapper around sfxFormatName that passes
 * a3=0, sp+0x10=0, sp+0x14=1 while forwarding a0–a2 unchanged.
 */

extern s32 gSfxActiveCount;  /* 0x80092CB8  s32 active-heap entry count */
extern s32 gSfxMaxIndex;     /* 0x80092CBC  s32 highest occupied heap index */

void sfxFormatName(s32 a0, s32 a1, s32 a2, s32 a3, s32 extra1, s32 extra2);

/* -------------------------------------------------------------------------
 * sfxSlotResolve / sfxSlotResolve
 * Resolve a symbolic slot index to a concrete index into gSfxHeap.
 * Called before every heap access that may use sentinel values.
 * ------------------------------------------------------------------------- */
s32 sfxSlotResolve(s32 slotSpec) {
    s32 idx;

    if (slotSpec == -4) {
        return 0;
    }

    if (slotSpec == -3) {
        idx = gSfxMaxIndex;
        if (idx < 0) {
            return 0;
        }
        return idx;
    }

    if (slotSpec == -2) {
        idx = gSfxMaxIndex;
        if (idx < 0) {
            return gSfxActiveCount;
        }
        return idx + 1;
    }

    if (slotSpec == -1) {
        return gSfxActiveCount;
    }

    return slotSpec;
}

/* -------------------------------------------------------------------------
 * sfxLookupName
 * Wrapper: call sfxFormatName with fixed last three args (0, 0, 1).
 * a0/a1/a2 are forwarded from the caller.
 * ------------------------------------------------------------------------- */
void sfxLookupName(s32 a0, s32 a1, s32 a2) {
    sfxFormatName(a0, a1, a2, 0, 0, 1);
}
