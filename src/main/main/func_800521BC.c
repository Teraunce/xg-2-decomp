#include "ultra64.h"
char *gfxGetWritePtr();                              /* extern */
s32 *frameAlloc(s32, s32, void *, void *);         /* extern */
s32 func_800524B8(s32);                               /* extern */
extern s32 gGfxSetupTable;
extern s32 gTrackDL4;
extern s32 gTrackDL3;
extern char *gRdpTilePtr2;
extern char *gRdpTilePtr;
extern s32 *gTrackNodePtr;
extern char *gTrackRenderPtr;
extern char *gRenderWritePtr;
extern char *gGfxWriteTick;

void gfxFrameSetup(s32 arg0) {
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 *temp_v0_24;
    Unk *temp_v0;
    Unk *temp_v0_10;
    Unk *temp_v0_11;
    Unk *temp_v0_12;
    Unk *temp_v0_13;
    Unk *temp_v0_14;
    Unk *temp_v0_15;
    Unk *temp_v0_16;
    Unk *temp_v0_17;
    Unk *temp_v0_18;
    Unk *temp_v0_19;
    Unk *temp_v0_20;
    Unk *temp_v0_21;
    Unk *temp_v0_22;
    Unk *temp_v0_23;
    Unk *temp_v0_2;
    Unk *temp_v0_3;
    Unk *temp_v0_4;
    Unk *temp_v0_5;
    Unk *temp_v0_6;
    Unk *temp_v0_7;
    Unk *temp_v0_8;
    Unk *temp_v0_9;

    gGfxWriteTick = gfxGetWritePtr();
    temp_v0 = gfxGetWritePtr();
    gRenderWritePtr = temp_v0;
    temp_v0_2 = temp_v0 + 8;
    temp_v0_3 = temp_v0_2 + 8;
    sp10 = 0xF5100080;
    temp_v0_4 = temp_v0_3 + 8;
    temp_v0_5 = temp_v0_4 + 8;
    sp14 = 0x07014050;
    temp_v0_6 = temp_v0_5 + 8;
    temp_v0_7 = temp_v0_6 + 8;
    sp18 = 0x070FF400;
    temp_v0_8 = temp_v0_7 + 8;
    temp_v0_9 = temp_v0_8 + 8;
    temp_v0_10 = temp_v0_9 + 8;
    temp_v0_11 = temp_v0_10 + 8;
    temp_v0_12 = temp_v0_11 + 8;
    temp_v0_13 = temp_v0_12 + 8;
    temp_v0_14 = temp_v0_13 + 8;
    temp_v0_15 = temp_v0_14 + 8;
    sp1C = 0xF5000480;
    gRdpTilePtr = temp_v0_15;
    temp_v0_16 = temp_v0_15 + 8;
    temp_v0_17 = temp_v0_16 + 8;
    sp20 = 0xFC117E04;
    temp_v0->unk0 = 0xFD100000;
    temp_v0->unk4 = &gTrackDL3;
    temp_v0_18 = temp_v0_17 + 8;
    temp_v0->unk8 = 0xF5100080;
    temp_v0_2->unk4 = 0x07014050;
    temp_v0_2->unk8 = 0xE6000000;
    temp_v0_3->unk4 = 0;
    temp_v0_3->unk8 = 0xF3000000;
    temp_v0_4->unk4 = 0x070FF400;
    temp_v0_4->unk8 = 0xE7000000;
    temp_v0_5->unk4 = 0;
    temp_v0_5->unk8 = 0xF5000480;
    temp_v0_6->unk4 = 0x01114050;
    temp_v0_6->unk8 = 0xF2000000;
    temp_v0_7->unk4 = 0x0107C07C;
    temp_v0_8->unk4 = &gTrackDL4;
    temp_v0_7->unk8 = 0xFD100000;
    temp_v0_8->unk8 = 0xE8000000;
    temp_v0_9->unk4 = 0;
    temp_v0_9->unk8 = 0xF5000110;
    temp_v0_10->unk4 = 0x07000000;
    temp_v0_10->unk8 = 0xE6000000;
    temp_v0_11->unk4 = 0;
    temp_v0_11->unk8 = 0xF0000000;
    temp_v0_12->unk4 = 0x0703C000;
    temp_v0_12->unk8 = 0xE7000000;
    temp_v0_13->unk4 = 0;
    temp_v0_13->unk8 = 0xFC117E04;
    temp_v0_14->unk4 = -0xC08;
    temp_v0_14->unk8 = 0xF2000000;
    temp_v0_15->unk4 = 0;
    temp_v0_15->unk8 = 0xF2000000;
    temp_v0_16->unk4 = 0x01000000;
    gRdpTilePtr2 = temp_v0_18;
    temp_v0_19 = temp_v0_18 + 8;
    temp_v0_20 = temp_v0_19 + 8;
    gTrackRenderPtr = temp_v0_20;
    temp_v0_21 = temp_v0_20 + 8;
    temp_v0_22 = temp_v0_21 + 8;
    temp_v0_23 = temp_v0_22 + 8;
    temp_v0_16->unk8 = 0xDF000000;
    temp_v0_17->unk4 = 0;
    temp_v0_17->unk8 = 0xF2000000;
    temp_v0_18->unk4 = 0;
    temp_v0_18->unk8 = 0xDF000000;
    temp_v0_19->unk4 = 0;
    temp_v0_19->unk8 = 0xF2000000;
    temp_v0_20->unk4 = 0;
    temp_v0_20->unk8 = 0xFB000000;
    temp_v0_21->unk4 = 0;
    temp_v0_21->unk8 = 0xFC127E0C;
    temp_v0_22->unk4 = -0xC08;
    temp_v0_22->unk8 = 0xDF000000;
    temp_v0_23->unk4 = 0;
    frameAlloc((temp_v0_23 + 8) - temp_v0, 0xF2000000, temp_v0_23, temp_v0_20);
    temp_v0_24 = frameAlloc(0x88, 0, NULL, NULL);
    *temp_v0_24 = 0;
    gTrackNodePtr = temp_v0_24;
    func_800524B8(arg0);
}

/* -------------------------------------------------------------------------
 * func_80052490 — async wait/alloc loop (0x9C bytes, nonmatching).
 *
 * Allocates a 0x88-byte block via frameAlloc, sets up a linked-list node,
 * then polls sfxGetRunning in a tight loop until it returns 0.  On success,
 * resolves a symbol via gTrackNodePtr, calls trackEdgeProcess, then accounts for
 * elapsed time (gGfxWriteTick delta) via gfxGetWritePtr.
 * Branch back to function start (bnez $s1, func_80052490) caused m2c to fail.
 * ------------------------------------------------------------------------- */
s32  sfxGetRunning(void);               /* extern */
void trackEdgeProcess(Unk*);               /* extern */
extern s32 gCurRenderNode;

void func_80052490(s32 arg0) {
    /* nonmatching: self-loop (do { alloc+poll } while (sfxGetRunning() != 0)) */
    (void)arg0;
}
