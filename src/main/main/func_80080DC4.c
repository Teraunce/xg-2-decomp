#include "ultra64.h"

/*
 * func_80080DC4 — per-frame audio node update dispatcher (nonmatching).
 *
 * PERMANENTLY NONMATCHING — dispatches via jr through jtbl_8004CDF0 (24 entries,
 * index = (u16)obj->0x38, range check < 0x18). m2c marks any function containing
 * jr-from-table as nonmatching.
 *
 * This is the direct sibling of func_8007F5C4: same prologue layout, same loop
 * structure, same s5 = a0+0x48 sub-struct, same loop-epilogue via osStopTimer.
 * Where func_8007F5C4 handles one class of audio objects, this handles another.
 *
 * Normal ABI: a0 = Unk *obj. All s-registers and fs0 saved; $sp reduced 0xD0.
 * sp+0x50 = obj+0x38 (pointer to current node's type-field block, cached early).
 * s2 = obj; s5 = obj+0x48 (audio context sub-struct passed to emit calls).
 *
 * Loop (.L80080E04):
 *   type = (u16)s2->0x38;
 *   if (type >= 0x18) goto default_next;
 *   jr jtbl_8004CDF0[type]       <- PERMANENT NM BLOCKER
 *   [epilogue calls osStopTimer(s5, sp+0x50); loops if result==0,
 *    else stores result to s2->0x28/0x1C and returns]
 *
 * Active cases (14 of 24 entries; rest → default advance):
 *
 * case 0:
 *   Decode audio command from s2->0x18 via midiDecodeEvent(s5, sp+0x88).
 *   Sub-dispatch on (s16)sp+0x88:
 *     == 1: func_800805A4(sp+0x50); audioStreamTick(s2)
 *     == 3: midiProcessTempo(sp+0x88); audioStreamTick(s2)
 *     == 4: s2->0x2C=2; osSetTimer(s5, cmd=0x10, a2=0x7FFFFFFF)
 *     else: (no action, advance)
 *
 * case 5:
 *   s0 = s2->0x3C; s1 = s0->0x10;
 *   sfxPlayNoteAtEntity(s2->0x14, s0);
 *   sfxStopAtEntity(s2->0x14, s0);
 *   if (s1->0x37) audioNoteRelease(s2, s1);
 *   audioNoteUnlink(s2, s0);
 *
 * case 6:
 *   s0 = s2->0x3C; s1 = s0->0x10;
 *   if (!s1->0x34) s1->0x34 = 1;
 *   s1->0x30 = s2->0x44; s3 = s2->0x40;
 *   s1->0x24 = s2->0x1C + s3;
 *   v0 = sfxComputeVolume(s1, s2);
 *   sfxPlayAtEntity(s2->0x14, s0, (s16)v0, s3);
 *
 * case 7:
 *   midiProcessTempo(sp+0x50, s2);   [sp+0x50 = stored obj+0x38 ptr]
 *
 * case 9:
 *   osSetTimer(s5, cmd=0x9, a2=s2->0x5C);
 *
 * case 0xA:
 *   sh s2->0x3C→s2->0x32; walk linked-list from s2->0x64;
 *   for each node: sfxComputeVolume(node, s2); progress=clamp(node->0x24-s2->0x1C, 0x3E8);
 *   sfxPlayAtEntity(s2->0x14, node+4, (s16)v0, progress);
 *   advance via node->0x0.
 *
 * case 0xB:
 *   s2->0x7C = s2->0x3C;
 *   s2->0x80 = s2->0x40;
 *   s2->0x84 = s2->0x44;
 *
 * case 0xC:
 *   idx = s2->0x3C (u8); base = s2->0x60;
 *   base[idx*16 + 8] = s2->0x3D (u8);
 *
 * case 0xD:
 *   s2->0x18 = s2->0x3C;
 *   if (s2->0x3C != NULL):
 *     s2->0x24 = trunc(D_8004CE50 * s2->0x3C->0x14);
 *   else:
 *     s2->0x24 = 0x1E8;
 *   if (s2->0x20 != NULL) audioLoadNotes(s2);
 *
 * case 0xE:
 *   audioLoadNotes(s2, a1=s2->0x3C, saved s2->0x3C→s2->0x20);
 *
 * case 0xF:
 *   if (s2->0x2C == 1) → loop (no advance);
 *   s2->0x2C = 1;
 *   audioStreamTick(s2);
 *
 * case 0x10:
 *   if (s2->0x2C != 2) → next;
 *   timerRelinkByType(s5, 0); timerRelinkByType(s5, 2);
 *   walk linked-list from s2->0x64;
 *     audioNoteActivate(s2, node+4, 0xC350);
 *     if result: sfxNoteRetrigger(s2, node+4, 0xC350);
 *     advance via node->0x0.
 *   s2->0x2C = 2;
 *   osSetTimer(s5, cmd=0x10, a2=0x7FFFFFFF);
 *
 * case 0x11:
 *   if (s2->0x2C != 1) → next;
 *   walk linked-list from s2->0x64;
 *     v0 = sfxComputeVolume(node, s2);
 *     progress = clamp(node->0x24 - s2->0x1C, 0x3E8);
 *     sfxPlayAtEntity(s2->0x14, node+4, (s16)v0, progress);
 *     advance via node->0x0.
 *   s2->0x1C = 0; s2->0x2C = 0;
 *
 * case 0x16:
 *   fn = s2->0x74; s4 = s2->0x40; s1 = s2->0x3C;
 *   s3 = fn(s4, sp+0xA8);              [sp+0xA8 = float result]
 *   [IDO saturating f32→s32 of sp+0xA8 → s1->0x36]
 *   v0 = sfxComputeVolume(s1, s2);
 *   progress = clamp(s1->0x24 - s2->0x1C, 0x3E8);
 *   sfxPlayAtEntity(s2->0x14, s1+4, (s16)v0, progress);
 *   osSetTimer(s5, cmd=0x16/s1/s4, a2=s3);
 *
 * case 0x17:
 *   fn = s2->0x74; s4 = s2->0x40; s1 = s2->0x3C; s0 = s2->0x44;
 *   s3 = fn(s4, sp+0xA8);
 *   s1->0x2C = sp+0xA8;                [store float result]
 *   vol = s2->0x60[(s0<<4) + 0xC] * (s1->0x28 * s1->0x2C);
 *   sfxPlayLoopAtEntity(s2->0x14, s1+4, (s32)vol);
 *   osSetTimer(s5, cmd=0x17/s1/s4/s0, a2=s3);
 */
void func_80080DC4(void) { /* nonmatching — see asm stub */ }
