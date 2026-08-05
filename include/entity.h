/**
 * entity.h — XG2 game entity (object/actor) struct
 *
 * Layout reverse-engineered from entity pool init code.
 * Pool stride confirmed as 0x228 bytes via GCC magic-divide pattern:
 *   mul 0x76B981DB → equivalent to ÷ 552 (0x228).
 *
 * ROM defaults observed in pool initializer:
 *   +0x00  radius_a  = 500.0f
 *   +0x08  radius_b  = 1000.0f
 *   +0x1C  unk_1C    = 1.0f  (first element only)
 *
 * Many interior fields are still unknown; they are named unk_XX where XX
 * is the hex offset.  Update as more code is decompiled.
 */

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "ultra64.h"   /* u8, u32, s32, f32 */

typedef struct Entity_s {
    /* +0x000 */ f32  radius_a;        /* collision/render radius A (default 500.0) */
    /* +0x004 */ f32  unk_04;
    /* +0x008 */ f32  radius_b;        /* collision/render radius B (default 1000.0) */

    /* World-space position */
    /* +0x00C */ f32  posX;
    /* +0x010 */ f32  posY;
    /* +0x014 */ f32  posZ;

    /* +0x018 */ u8   unk_18[4];
    /* +0x01C */ f32  unk_1C;          /* default 1.0f for pool[0]; scale? */
    /* +0x020 */ u8   unk_20[0xB0];    /* large unknown block */

    /* +0x0D0 */ void *subObj;         /* pointer to sub-object or component */
    /* +0x0D4 */ u8   unk_D4[0x108];   /* unknown block */

    /* +0x1DC */ s32  state;           /* entity state (compared to 4 = active?) */
    /* +0x1E0 */ u8   unk_1E0[0x48];  /* padding / unknown fields to end of struct */
    /* = 0x228 total */
} Entity;  /* size: 0x228 bytes */

/* Entity pool globals (main BSS) */
/* gEntityPool:  the flat array, address TBD (overlay-resident) */
/* gTrackNodeCount (0x80091968): s32 count of active overlay track/AI path nodes */

#endif /* _ENTITY_H_ */
