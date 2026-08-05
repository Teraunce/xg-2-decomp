#include "ultra64.h"
/*
 * func_8008EE18 — call func_8008EE98(a0,a1,a2) and add a2 to the return value
 * Compiled with IDO 7.1 -O2 -mips2
 */

s32 func_8008EE98(s32, s32, s32);

s32 func_8008EE18(s32 arg0, s32 arg1, s32 arg2) {
    return func_8008EE98(arg0, arg1, arg2) + arg2;
}
