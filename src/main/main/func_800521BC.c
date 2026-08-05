#include "ultra64.h"
char *gfxGetWritePtr();                              /* extern */
s32 *frameAlloc(s32, s32, void *, void *);         /* extern */
s32 func_800524B8(s32);                               /* extern */
extern s32 D_8004B9C8;
extern s32 D_80091FD8;
extern s32 D_80091FF8;
extern char *D_80173D0C;
extern char *D_80174BE8;
extern s32 *D_80174BF8;
extern char *D_80178698;
extern char *D_801786A8;
extern char *D_8017CCBC;

void func_800521BC(s32 arg0) {
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

    D_8017CCBC = gfxGetWritePtr();
    temp_v0 = gfxGetWritePtr();
    D_801786A8 = temp_v0;
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
    D_80174BE8 = temp_v0_15;
    temp_v0_16 = temp_v0_15 + 8;
    temp_v0_17 = temp_v0_16 + 8;
    sp20 = 0xFC117E04;
    temp_v0->unk0 = 0xFD100000;
    temp_v0->unk4 = &D_80091FF8;
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
    temp_v0_8->unk4 = &D_80091FD8;
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
    D_80173D0C = temp_v0_18;
    temp_v0_19 = temp_v0_18 + 8;
    temp_v0_20 = temp_v0_19 + 8;
    D_80178698 = temp_v0_20;
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
    D_80174BF8 = temp_v0_24;
    func_800524B8(arg0);
}

/* -------------------------------------------------------------------------
 * func_80052490 — async wait/alloc loop (0x9C bytes, nonmatching).
 *
 * Allocates a 0x88-byte block via frameAlloc, sets up a linked-list node,
 * then polls func_800503F8 in a tight loop until it returns 0.  On success,
 * resolves a symbol via D_80174BF8, calls func_80050260, then accounts for
 * elapsed time (D_8017CCBC delta) via gfxGetWritePtr.
 * Branch back to function start (bnez $s1, func_80052490) caused m2c to fail.
 * ------------------------------------------------------------------------- */
s32  func_800503F8(void);               /* extern */
void func_80050260(Unk*);               /* extern */
extern s32 D_8017CCB8;

void func_80052490(s32 arg0) {
    /* nonmatching: self-loop (do { alloc+poll } while (func_800503F8() != 0)) */
    (void)arg0;
}
