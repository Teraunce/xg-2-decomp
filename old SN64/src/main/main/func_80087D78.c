#include "ultra64.h"
/*
 * func_80087D78 — preload stub: loads D_80096370 into $t6 and falls through
 * to func_80087D80, which uses $t6 as a condition.  This cannot be expressed
 * as a normal C function; it is kept as a matched asm stub.
 */
extern s32 D_80096370;
