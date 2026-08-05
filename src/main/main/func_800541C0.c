#include "ultra64.h"
/*
 * func_800541C0 — large game-state / object-pool sub-dispatcher (nonmatching).
 *
 * PERMANENTLY NONMATCHING — two reasons:
 *
 * 1. Twenty-two alabel markers: other functions branch INTO this function's
 *    body at 22 mid-body addresses — the most alabel entries in the project.
 *    m2c cannot represent cross-function entry points.
 *
 * 2. Dispatches via jr through a jump table.  m2c marks any jr-from-table as
 *    nonmatching.
 *
 * Entry begins with a zeroing loop, suggesting pool or table initialization.
 * Function size: 0x1418 bytes.
 */
void func_800541C0(void) { /* nonmatching — see asm stub */ }
