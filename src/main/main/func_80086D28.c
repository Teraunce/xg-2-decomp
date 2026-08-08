#include "ultra64.h"
/*
 * rspHalt — wrapper: call osSpSetStatus(0x400)
 * Compiled with IDO 7.1 -O2 -mips2
 */

void osSpSetStatus(int);   /* osSpSetStatus — sets SP status register bits */

void rspHalt(void) {
    osSpSetStatus(0x400);
}
