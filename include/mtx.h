#ifndef MTX_H
#define MTX_H
#include "ultra64.h"

/* 4×4 row-major float matrix, 0x40 bytes.
 *
 * Memory layout:
 *   row 0:  unk0   unk4   unk8   unkC
 *   row 1:  unk10  unk14  unk18  unk1C
 *   row 2:  unk20  unk24  unk28  unk2C
 *   row 3:  unk30  unk34  unk38  unk3C
 *
 * Row 3 carries the translation (unk30=X, unk34=Y, unk38=Z, unk3C=W).
 */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */
} Matrix4x4;

#endif /* MTX_H */
