#include "ultra64.h"
#include "audio.h"

/*
 * SFX heap core operations — insert, mark-active, find, contains, count.
 *
 * The SFX subsystem maintains a fixed-stride array of SfxSortEntry structs
 * at gSfxHeap (gSfxHeap, overlay segment, 0x0C bytes each).  Entries are
 * kept in insertion-priority order: func_80061FB4 shifts existing entries up
 * to open a slot at the requested position, then writes the new entry.
 *
 * Globals (main BSS):
 *   gSfxActiveCount  0x80092CB8  s32  occupied entry count in gSfxHeap
 *   gSfxMaxIndex     0x80092CBC  s32  highest heap index ever used (can be -1)
 *   gSfxAllocCount   0x80092CC0  s32  allocation-cursor / search index
 *   gSfxHeap         0x80182348  SfxSortEntry[]  priority heap (overlay)
 */

extern s32 gSfxActiveCount;     /* 0x80092CB8 */
extern s32 gSfxMaxIndex;        /* 0x80092CBC */
extern s32 gSfxAllocCount;      /* 0x80092CC0 */
extern SfxSortEntry gSfxHeap[]; /* 0x80182348 */

s32 func_80061F34(s32);  /* slot-index resolver (func_80061F0C.c) */

/* -------------------------------------------------------------------------
 * func_80061FB4
 * Priority-sorted insert of a new entity into gSfxHeap.
 *
 *   entity     — the sound-source entity pointer stored at heap[slot].entity
 *   slotSpec   — requested heap position (resolved via func_80061F34)
 *   flags      — bit 0: if set, update gSfxAllocCount = slot after insert
 *
 * The function shifts all entries from [slot .. gSfxActiveCount-1] up by one
 * to make room, writes the new entry, then increments gSfxActiveCount.
 * gSfxAllocCount and gSfxMaxIndex are also bumped if they would overlap.
 * ------------------------------------------------------------------------- */
void func_80061FB4(void *entity, s32 slotSpec, s32 flags) {
    s32 slot;
    s32 i;

    slot = func_80061F34(slotSpec);

    /* Keep gSfxAllocCount and gSfxMaxIndex above the insertion point. */
    if (gSfxAllocCount >= slot) {
        gSfxAllocCount++;
    }
    if (gSfxMaxIndex >= slot) {
        gSfxMaxIndex++;
    }

    /* Shift entries [slot .. gSfxActiveCount-1] up by one to open slot. */
    if ((u32)slot < (u32)gSfxActiveCount) {
        for (i = gSfxActiveCount; (u32)slot < (u32)i; i--) {
            gSfxHeap[i] = gSfxHeap[i - 1];
        }
    }

    /* Write the new entry at the chosen slot. */
    gSfxHeap[slot].entity = entity;
    gSfxHeap[slot].type   = SFX_TYPE_PENDING;   /* 2 */
    gSfxHeap[slot].state  = 0;

    gSfxActiveCount++;

    if (flags & 1) {
        gSfxAllocCount = slot;
    }
}

/* -------------------------------------------------------------------------
 * func_800620CC
 * Mark all heap entries that match 'entity' as active:
 *   type  |= SFX_TYPE_ACTIVE  (bit 2)
 *   state  = 3
 * Multiple entries can share the same entity pointer; all are marked.
 * ------------------------------------------------------------------------- */
void func_800620CC(void *entity) {
    s32 i;
    s32 count = gSfxActiveCount;

    if (count == 0) {
        return;
    }

    for (i = 0; i < count; i++) {
        if (gSfxHeap[i].entity == entity) {
            gSfxHeap[i].type  |= SFX_TYPE_ACTIVE;   /* |= 4 */
            gSfxHeap[i].state  = 3;
        }
    }
}

/* -------------------------------------------------------------------------
 * func_8006211C
 * Find the first heap entry matching 'entity' and record its index in
 * gSfxAllocCount.  Sets gSfxAllocCount = -5 if not found.
 * ------------------------------------------------------------------------- */
void func_8006211C(void *entity) {
    s32 i;
    s32 count = gSfxActiveCount;

    if (count == 0) {
        gSfxAllocCount = -5;
        return;
    }

    for (i = 0; i < count; i++) {
        if (gSfxHeap[i].entity == entity) {
            gSfxAllocCount = i;
            return;
        }
    }

    gSfxAllocCount = -5;
}

/* -------------------------------------------------------------------------
 * func_8006216C
 * Return 1 if any heap entry matches 'entity', 0 if not found.
 * ------------------------------------------------------------------------- */
s32 func_8006216C(void *entity) {
    s32 i;
    s32 count = gSfxActiveCount;

    if (count == 0) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (gSfxHeap[i].entity == entity) {
            return 1;
        }
    }

    return 0;
}

/* -------------------------------------------------------------------------
 * func_800621B0
 * Return the current active-heap entry count.
 * ------------------------------------------------------------------------- */
s32 func_800621B0(void) {
    return gSfxActiveCount;
}
