#include "ultra64.h"
/*
 * __siLock — preload stub: loads gSiAcquired into $t6 and falls through
 * to __siAcquire, which uses $t6 as a condition.  This cannot be expressed
 * as a normal C function; it is kept as a matched asm stub.
 */
extern s32 gSiAcquired;
