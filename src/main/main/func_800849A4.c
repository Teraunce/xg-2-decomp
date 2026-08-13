#include "ultra64.h"
#include "audio.h"
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

void audioNodeInit(AudioNodeBase *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->state    = 0;
    arg0->cmdFn    = arg1;
    arg0->propFn   = arg2;
    arg0->unk0C    = 0;
    arg0->unk0E    = 0;
    arg0->nodeType = arg3;
}

s32 audioNoteWrite(AudioNoteWriteNode *arg0, s32 arg1, s32 arg2) {
    if (arg1 == 2) {
        *(s32*)(s32)(arg0->bufPtr + (arg0->writeIdx * 4)) = arg2;
        arg0->writeIdx = (s32) (arg0->writeIdx + 1);
    }
    return 0;
}
