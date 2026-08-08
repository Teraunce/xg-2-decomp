#include "ultra64.h"
/*
 * __piLockGetter — preload stub: loads gFontInitDone into $t6 and falls through
 * to __piLock, which uses $t6 as a condition.  This cannot be expressed
 * as a normal C function; it is kept as a matched asm stub.
 */
extern s32 gFontInitDone;
