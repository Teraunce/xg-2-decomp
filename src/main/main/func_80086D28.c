#include "ultra64.h"
/*
 * func_80086D28 — wrapper: call osSpSetStatus(0x400)
 * Compiled with IDO 7.1 -O2 -mips2
 */

void osSpSetStatus(int);   /* osSpSetStatus — sets SP status register bits */

void func_80086D28(void) {
    osSpSetStatus(0x400);
}
