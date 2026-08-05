/**
 * audio.h — XG2 audio / SFX subsystem types
 *
 * Three struct types are defined here:
 *
 *  1. AudioQueueEntry  — one slot in the 128-entry ring buffer at D_80180B38
 *     (overlay segment).  Stride confirmed as 0x14 bytes from func_8005C9BC:
 *       gAudioQueueWriteIdx wraps at 0x80 (128); entry = base + idx * 0x14
 *
 *  2. SfxSortEntry  — one node in the priority-insert heap at gSfxHeap
 *     (0x80182348, overlay segment).  Stride confirmed as 0x0C bytes (3 words).
 *     Fields confirmed from func_80061FB4 (insert) and func_800620CC (mark).
 *       +0x00  entity  void*  sound-source entity pointer (insertion key)
 *       +0x04  type    s32    type flags: 2=pending, |4=active, |8=done
 *       +0x08  state   s32    slot state: 0=pending, 3=active
 *
 *  3. SfxInputEntry  — per-channel input parameters fed into func_800622C0
 *     (gSfxInputTable at 0x8017CA08, overlay).  Stride: 0x06 bytes.
 *       +0x00  id    u16   sound/instrument ID
 *       +0x02  unk02 s8    unknown (pan? pitch?)
 *       +0x03  vol   s8    volume/balance (signed; 0=centre, ±= pan offset)
 *       +0x04  mute  u8    mute flag (0=play, nonzero=mute/silence)
 *       +0x05  pad   u8    padding
 *
 *  4. SfxChannelState — per-channel processed output state maintained by
 *     func_800622C0 (gSfxChannelState at 0x801820D8, overlay).
 *     Stride: 0x24 bytes.
 *
 * Ring-buffer / heap globals (main BSS):
 *   gAudioQueueWriteIdx  0x8009282C  u32  write index (wraps at 128)
 *   gAudioQueueReadIdx   0x80092828  u32  read index
 *   gSfxActiveCount      0x80092CB8  s32  number of active entries in heap
 *   gSfxMaxIndex         0x80092CBC  s32  highest occupied heap index (can be -1)
 *   gSfxAllocCount       0x80092CC0  s32  heap allocation cursor / search index
 */

#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "ultra64.h"   /* u8, u16, u32, s16, s32, f32 */

/* ---- AudioQueueEntry ---------------------------------------------------
 * Ring-buffer slot.  Written by func_8005C9BC; read by the audio driver.
 * Stride: 0x14 bytes.
 * ----------------------------------------------------------------------- */
typedef struct {
    /* +0x00 */ u32  soundId;    /* packed sound identifier */
    /* +0x04 */ s16  type;       /* sound category / bank selector */
    /* +0x06 */ s16  priority;   /* playback priority */
    /* +0x08 */ f32  volume;     /* linear volume 0.0–1.0 */
    /* +0x0C */ u32  extra;      /* auxiliary param (pitch? pan? TBD) */
    /* +0x10 */ u8   channel;    /* output channel index */
    /* +0x11 */ u8   flags;      /* misc flags */
    /* +0x12 */ u8   pad[2];
    /* = 0x14 total */
} AudioQueueEntry;  /* size: 0x14 bytes */

/* ---- SfxSortEntry ------------------------------------------------------
 * Node in the active-SFX priority heap (gSfxHeap, 0x80182348).
 * Sorted by insertion order; entries are shifted up to insert at a given
 * position (func_80061FB4).  Stride: 0x0C bytes.
 *
 * type flag bits:
 *   0x2  set on insert (pending)
 *   0x4  set by func_800620CC when the entity becomes active
 *   0x6  set by func_80062A6C when the slot is finalised
 *   0x8  set by func_80062A6C when state counter expires
 * ----------------------------------------------------------------------- */
typedef struct {
    /* +0x00 */ void *entity;   /* sound-source entity pointer (look-up key) */
    /* +0x04 */ s32   type;     /* type/status flags (see above) */
    /* +0x08 */ s32   state;    /* slot state counter (0=pending, 3=active) */
    /* = 0x0C total */
} SfxSortEntry;  /* size: 0x0C bytes */

/* ---- SfxInputEntry -----------------------------------------------------
 * Per-channel input record consumed by func_800622C0.
 * Four entries packed at gSfxInputTable (0x8017CA08).
 * Stride: 0x06 bytes.
 * ----------------------------------------------------------------------- */
typedef struct {
    /* +0x00 */ u16 id;    /* sound / instrument ID */
    /* +0x02 */ s8  unk02; /* unknown (pitch? effect index?) */
    /* +0x03 */ s8  vol;   /* signed balance/volume offset */
    /* +0x04 */ u8  mute;  /* 0 = play; nonzero = silence this channel */
    /* +0x05 */ u8  pad;
    /* = 0x06 total */
} SfxInputEntry;  /* size: 0x06 bytes */

/* ---- SfxChannelState ---------------------------------------------------
 * Per-channel processed output state maintained by func_800622C0.
 * Four entries at gSfxChannelState (0x801820D8).
 * Stride: 0x24 bytes.
 * ----------------------------------------------------------------------- */
typedef struct {
    /* +0x00 */ s32 active;     /* 0=muted, 1=playing */
    /* +0x04 */ s32 panL;       /* left-channel balance offset */
    /* +0x08 */ s32 panR;       /* right-channel balance offset */
    /* +0x0C */ u32 soundId;    /* sound ID copied from SfxInputEntry */
    /* +0x10 */ u32 flags;      /* filtered direction flags (xor of prev & raw) */
    /* +0x14 */ s32 output;     /* final output value / level */
    /* +0x18 */ u32 prevFlags;  /* previous raw flags (for delta detection) */
    /* +0x1C */ s32 counter;    /* countdown timer (starts at 25/0x19) */
    /* +0x20 */ s32 decrement;  /* per-frame decrement for counter */
    /* = 0x24 total */
} SfxChannelState;  /* size: 0x24 bytes */

/* Ring buffer capacity */
#define AUDIO_QUEUE_SIZE  128   /* 0x80 */

/* SfxSortEntry type flag constants */
#define SFX_TYPE_PENDING  0x2   /* inserted, not yet claimed */
#define SFX_TYPE_ACTIVE   0x4   /* entity has been activated */
#define SFX_TYPE_DONE     0x8   /* slot has expired */

#endif /* _AUDIO_H_ */
