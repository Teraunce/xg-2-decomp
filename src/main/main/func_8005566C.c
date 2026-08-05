#include "ultra64.h"
s32 func_80055900();                                  /* extern */

/*
 * func_8005566C — game-loop / entity-update sub-dispatcher (nonmatching).
 *
 * PERMANENTLY NONMATCHING — two reasons:
 *
 * 1. Seventeen alabel markers: other functions branch INTO this function's body
 *    at 17 mid-body addresses.  m2c cannot represent cross-function entry points
 *    and rejects the file.  The m2c error "Label ._m2c_.L800558F8before refers
 *    to a delay slot" is a secondary symptom of this alabel problem.
 *
 * 2. Dispatches via jr through a jump table.  m2c marks any jr-from-table as
 *    nonmatching.
 *
 * Function size: 0xDA8 bytes.
 */
void func_8005566C(void) { /* nonmatching — see asm stub */ }

void func_80056414(void) {
    func_80055900();
}

void func_8005641C(void) {
    func_80055900();
}
