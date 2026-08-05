#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8005F528 (initial). */

extern s32 D_80181648;

/*
 * func_8005E8B4 — collision/geometry sub-dispatcher (nonmatching).
 *
 * PERMANENTLY NONMATCHING — three reasons:
 *
 * 1. Non-standard ABI: $v0 is used as an input argument.  The very first
 *    instruction after the prologue register saves is `blez $v0, .L8005EFF0`,
 *    branching on $v0 before it is ever loaded.  In standard MIPS ABI, $v0
 *    is a return-value register, not an argument.  No C declaration can
 *    express this.
 *
 * 2. Thirteen alabel markers: other functions branch INTO this function's
 *    code body at 13 mid-body addresses.  m2c cannot represent cross-function
 *    entry points and rejects the file.
 *
 * 3. Dispatches via jr through a jump table (index derived from $v0).
 *    m2c marks any jr-from-table as nonmatching.
 *    The m2c error "Label ._m2c_func_8005EFC0before refers to a delay slot"
 *    is a secondary symptom of the alabel problem.
 *
 * Six FP register pairs (fs0–fs5) are saved, indicating heavy floating-point
 * work.  Function size: 0xC74 bytes.
 */
void func_8005E8B4(void) { /* nonmatching — see asm stub */ }

s32 func_8005F528(void) {
    func_8005F530();
    return D_80181648;
}
