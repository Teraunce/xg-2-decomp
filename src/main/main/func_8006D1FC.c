#include "ultra64.h"

/*
 * func_8006D1FC — main game-loop dispatcher / renderer (nonmatching).
 *
 * PERMANENTLY NONMATCHING — two reasons:
 *
 * 1. Non-standard ABI: $v0 and $v1 are used as input arguments.
 *    The prologue saves s0-s4 and the FP pair fs0/fs1 normally, but then
 *    immediately uses $v1 and $v0 as caller-supplied values:
 *      addiu $v1, $v1, 0x1           <- $v1 is an input counter
 *      sw    $v1, -0x375C($v0)       <- $v0 is an input base pointer
 *    In standard MIPS ABI, $v0/$v1 are return-value registers and are not
 *    used to pass arguments.  No C declaration can express this.
 *
 * 2. Dispatches via jr through jtbl_8004C488 (7 entries, 0x8006D30C) based
 *    on a0 value loaded from gGameState.  m2c marks any function containing
 *    jr-from-table as nonmatching.
 *
 * This is the largest function in the project: 0x2FCC bytes (12,236 bytes,
 * ~1500 asm lines, addr range 0x8006D1FC–0x800701C0).  It contains nested
 * loops iterating over game-object tables, RSP microcode submission, scene
 * traversal, and the full RCP display-list build for each frame.  Even
 * ignoring the ABI issue, it would be extremely difficult to match.
 */
void func_8006D1FC(void) { /* nonmatching — see asm stub */ }
