#include "ultra64.h"
/*
 * renderSceneDispatch — rendering/scene-graph sub-dispatcher (nonmatching).
 *
 * PERMANENTLY NONMATCHING — two reasons:
 *
 * 1. Ten alabel markers: other functions branch INTO this function's body at
 *    ten mid-body addresses.  m2c cannot represent cross-function entry points.
 *
 * 2. Dispatches via jr through a jump table.  The jump register is loaded
 *    through a chain of $t4-based pointer dereferences, then `jr` fires.
 *    m2c marks any jr-from-table as nonmatching.
 *
 * Function size: 0xC64 bytes.
 */
void renderSceneDispatch(void) { /* nonmatching — see asm stub */ }
