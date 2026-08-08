#include "ultra64.h"
/*
 * audioNodeDispatch — audio playback sub-dispatcher (nonmatching).
 *
 * PERMANENTLY NONMATCHING — dispatches via jr through jtbl_8004CEE8.
 * m2c marks any function containing jr-from-table as nonmatching.
 *
 * Normal ABI (a0–a3 used as expected), but also reads a fifth argument from
 * the caller's stack frame: `lw $t6, 0xB8($sp)` in the prologue, before the
 * frame pointer is set up, indicating sp+0xB8 is caller-provided (5th+ arg).
 * Function size: 0x548 bytes.
 */
void audioNodeDispatch(void) { /* nonmatching — see asm stub */ }

void audioNodeInit(Unk *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk0 = 0;
    arg0->unk4 = arg1;
    arg0->unk8 = arg2;
    arg0->unkC = 0;
    arg0->unkE = 0;
    arg0->unk10 = arg3;
}

s32 audioNoteWrite(Unk *arg0, s32 arg1, s32 arg2) {
    if (arg1 == 2) {
        *(s32*)(s32)(arg0->unk1C + (arg0->unk14 * 4)) = arg2;
        arg0->unk14 = (s32) (arg0->unk14 + 1);
    }
    return 0;
}
