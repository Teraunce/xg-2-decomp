#include "ultra64.h"
s32 func_80071794(void *);                               /* extern */
extern s32 D_801887D0;
extern s32 D_8018894C;

void entityClearSlots(s32 arg1, s32 arg2) {
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
 * Shared stack frame with entityClearSlots (no prologue here).
 * On each iteration: zeroes gSfxChannelMute[v1..], dispatches on a 12-entry
 * jump table (jtbl_8004C730, index from func_8008B858 return value),
 * calls handlerPostCmd for logging, optionally calls contPakReadEntry /
 * contPakBuildMap / func_80071408 / func_80071360.
 * Loop: `beqz s1, func_80071778` — repeats while s1==0.
 * m2c failed: "Cannot find branch target func_80071778" (branch-to-self).
 * ------------------------------------------------------------------------- */
void func_80071360(void *);
s32  handlerPostCmd(s32, void *, s32, s32, s32, s32, s32);
s32  func_80071408(void *);
s32  func_8008B858(void *, s32, void *);
s32  contPakBuildMap(void *, void *, void *);
s32  contPakReadEntry(void *);
extern u8    gSfxChannelMute[];
extern void *D_801887A0;

void func_80071778(void) {
    /* nonmatching state-machine loop — see asm/main/main/entityClearSlots.s */
}
