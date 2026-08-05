#include "ultra64.h"
/*
 * byteCopyEnd — call byteCopy(a0,a1,a2) and add a2 to the return value
 * Compiled with IDO 7.1 -O2 -mips2
 */

s32 byteCopy(s32, s32, s32);

s32 byteCopyEnd(s32 arg0, s32 arg1, s32 arg2) {
    return byteCopy(arg0, arg1, arg2) + arg2;
}
