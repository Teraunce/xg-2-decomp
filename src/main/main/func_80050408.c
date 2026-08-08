#include "ultra64.h"
/*
 * gameMainLoop — main game-loop top-level dispatcher (nonmatching).
 *
 * PERMANENTLY NONMATCHING — three reasons:
 *
 * 1. Non-standard ABI: $v0 and $v1 are used as input arguments.  Immediately
 *    after the prologue register saves: `xori $v0, $v0, 0x1` (XOR on input $v0)
 *    and `or $v1, $v1, $a0` (OR of $v1 with $a0).  In standard MIPS ABI,
 *    $v0/$v1 are return-value registers, not argument registers.
 *    No C declaration can express this.
 *
 * 2. Seventeen alabel markers: other functions branch INTO this function's body
 *    at 17 mid-body addresses.  m2c cannot represent cross-function entry points.
 *
 * 3. Dispatches via jr through a jump table.  m2c marks any jr-from-table as
 *    nonmatching.
 *
 * Also reads 5th+ arguments from the incoming caller's stack (sp+0x... before
 * frame pointer adjusted).
 * Function size: 0x1DB4 bytes — second largest in the project.
 */
void gameMainLoop(void) { /* nonmatching — see asm stub */ }
