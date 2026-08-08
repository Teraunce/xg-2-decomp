#include "ultra64.h"
/*
 * gameStateInit — game-state initializer / main-loop sub-dispatcher (nonmatching).
 *
 * PERMANENTLY NONMATCHING — two reasons:
 *
 * 1. Fourteen alabel markers: other functions branch INTO this function's body.
 *    m2c cannot represent cross-function entry points and rejects the file.
 *
 * 2. Dispatches via jr through a jump table.  m2c marks any jr-from-table as
 *    nonmatching.
 *
 * The function begins with immediate stores to several global variables
 * (D_8017C938, D_8017C888, etc.) before any frame setup, consistent with
 * a cold-start initialization path.
 * Function size: 0xFA4 bytes.
 */
void gameStateInit(void) { /* nonmatching — see asm stub */ }
