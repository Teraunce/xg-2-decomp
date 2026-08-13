#ifndef TRACK_H
#define TRACK_H

#include "ultra64.h"

/*
 * TrackNode — one entry in the track mesh node array, exactly 0x38 bytes.
 *
 * Nodes are stored in a flat array; sizeof(TrackNode) == stride == 0x38.
 * Cross-element edge vectors are computed by subtracting adjacent nodes:
 *   edgeX = node[i+1].posX - node[i].posX   (same as (ptr+1)->posX - ptr->posX)
 *
 * nextNode encoding:
 *   0x8000          — section end (last node in the section)
 *   bit15 set, !end — redirect: jump to node index (bits 14-0)
 *   otherwise       — index of the logically connected next node
 *
 * flags encoding:
 *   bits 11-15  — entity active-slot index  (extracted as (flags >> 11))
 *   bits  2- 4  — render/color mode bits
 */
typedef struct TrackNode {
    /* 0x00 */ s32  posX;       /* world X position (fixed-point) */
    /* 0x04 */ s32  posY;       /* world Y position */
    /* 0x08 */ s32  posZ;       /* world Z position */
    /* 0x0C */ s16  normalX;    /* surface normal X (fixed-point) */
    /* 0x0E */ s16  normalY;    /* surface normal Y */
    /* 0x10 */ s16  normalZ;    /* surface normal Z */
    /* 0x12 */ u16  colorIdx;   /* current display-color index (written per frame) */
    /* 0x14 */ u16  unk14;      /* unknown u16 */
    /* 0x16 */ u16  flags;      /* bitfield — see encoding above */
    /* 0x18 */ u16  nextNode;   /* next-node index — see encoding above */
    /* 0x1A */ u8   pad1A[0x12]; /* unused gap */
    /* 0x2C */ u16  raceColor0; /* color for race slot 0 */
    /* 0x2E */ u16  raceColor1; /* color for race slot 1 */
    /* 0x30 */ u16  raceColor2; /* color for race slot 2 */
    /* 0x32 */ s16  friction;   /* contact/friction result (written during render) */
    /* 0x34 */ s32  renderNode; /* associated render-node pointer (0 = none) */
    /* 0x38 */
} TrackNode;

#endif /* TRACK_H */
