#include "ultra64.h"
s32 func_80071794(void *);                               /* extern */
extern s32 gHandlerCtx;
extern s32 gContPakSlots;

void entityClearSlots(s32 arg1, s32 arg2) {
    Unk *temp_v1;

    temp_v1 = (arg1 * 4) + &gHandlerCtx;
    temp_v1->unk32C = 0;
    temp_v1->unk33C = 0;
    temp_v1->unk34C = 0;
    temp_v1->unk35C = 0;
    temp_v1->unk36C = 0;
    temp_v1->unk37C = 0;
    func_80071794(&gHandlerCtx);
}

/* -------------------------------------------------------------------------
 * gameStateMachineLoop — game-state machine loop (0x2B0 bytes, nonmatching).
 *
 * Shared stack frame with entityClearSlots (no prologue here).
 * On each iteration: zeroes gSfxChannelMute[v1..], dispatches on a 12-entry
 * jump table (jtbl_8004C730, index from contPakVerifyRead return value),
 * calls handlerPostCmd for logging, optionally calls contPakReadEntry /
 * contPakBuildMap / contPakFormatNote / contPakHandlerStatus.
 * Loop: `beqz s1, gameStateMachineLoop` — repeats while s1==0.
 * m2c failed: "Cannot find branch target gameStateMachineLoop" (branch-to-self).
 * ------------------------------------------------------------------------- */
void contPakHandlerStatus(void *);
s32  handlerPostCmd(s32, void *, s32, s32, s32, s32, s32);
s32  contPakFormatNote(void *);
s32  contPakVerifyRead(void *, s32, void *);
s32  contPakBuildMap(void *, void *, void *);
s32  contPakReadEntry(void *);
extern u8    gSfxChannelMute[];
extern void *gHandlerMsgQueue;

void gameStateMachineLoop(void) {
    /* nonmatching state-machine loop — see asm/main/main/entityClearSlots.s */
}
