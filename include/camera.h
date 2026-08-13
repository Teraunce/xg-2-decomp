#ifndef CAMERA_H
#define CAMERA_H
#include "ultra64.h"

/*
 * CameraView — camera descriptor passed to camera render functions.
 *
 * Contains the eye position, look-at target, up vector, and clip parameters
 * needed to build the view matrix.  This struct is an embedded sub-region
 * within an entity entry in gEntityPool.
 *
 * Confirmed minimum size: 0x1E8 bytes.
 * Unknown regions are left as u8 padding.
 *
 * Memory layout:
 *   0x000–0x008  eye position   (world-space camera origin)
 *   0x00C–0x014  at position    (world-space look-at target)
 *   0x018–0x020  up vector      (camera up direction)
 *   0x024–0x0CB  unknown
 *   0x0CC        nearClip       (near-clip / depth reference; negated for fog)
 *   0x0D0–0x1E3  unknown
 *   0x1E4        hiliteFlag     (0 = normal DL, nonzero = alternate hilite DL)
 */
typedef struct {
    /* 0x000 */ f32 eyeX;
    /* 0x004 */ f32 eyeY;
    /* 0x008 */ f32 eyeZ;
    /* 0x00C */ f32 atX;
    /* 0x010 */ f32 atY;
    /* 0x014 */ f32 atZ;
    /* 0x018 */ f32 upX;
    /* 0x01C */ f32 upY;
    /* 0x020 */ f32 upZ;
    /* 0x024 */ u8  unk024[0xA8];
    /* 0x0CC */ f32 nearClip;
    /* 0x0D0 */ u8  unk0D0[0x114];
    /* 0x1E4 */ s32 hiliteFlag;
    /* 0x1E8 */
} CameraView;

#endif /* CAMERA_H */
