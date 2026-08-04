#include "ultra64.h"
s32 func_80071794(void *);                               /* extern */
extern s32 D_801887D0;
extern s32 D_8018894C;

void func_800716E4(s32 arg1, s32 arg2) {
    Unk *temp_v1;

    temp_v1 = (arg1 * 4) + &D_801887D0;
    temp_v1->unk32C = 0;
    temp_v1->unk33C = 0;
    temp_v1->unk34C = 0;
    temp_v1->unk35C = 0;
    temp_v1->unk36C = 0;
    temp_v1->unk37C = 0;
    func_80071794(&D_801887D0);
}

/* -------------------------------------------------------------------------
 * func_80071778 — game-state machine loop (0x2B0 bytes, nonmatching).
 *
 * Shared stack frame with func_800716E4 (no prologue here).
 * On each iteration: zeroes D_80092CD0[v1..], dispatches on a 12-entry
 * jump table (jtbl_8004C730, index from func_8008B858 return value),
 * calls func_80070F50 for logging, optionally calls func_8008C528 /
 * func_8008CCE8 / func_80071408 / func_80071360.
 * Loop: `beqz s1, func_80071778` — repeats while s1==0.
 * m2c failed: "Cannot find branch target func_80071778" (branch-to-self).
 * ------------------------------------------------------------------------- */
void func_80071360(void *);
s32  func_80070F50(s32, void *, s32, s32, s32, s32, s32);
s32  func_80071408(void *);
s32  func_8008B858(void *, s32, void *);
s32  func_8008CCE8(void *, void *, void *);
s32  func_8008C528(void *);
extern u8    D_80092CD0[];
extern void *D_801887A0;

void func_80071778(void) {
    /* nonmatching state-machine loop — see asm/main/main/func_800716E4.s */
}
