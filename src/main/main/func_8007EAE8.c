#include "ultra64.h"
/*
 * audioTimerCmd11 — build a 16-byte AnimCmd on the stack (type=0x11), pass to osSetTimer
 * Compiled with IDO 7.1 -O2 -mips2
 */
void osSetTimer(char *, void *, int);

void audioTimerCmd11(char *arg0) {
    struct { short type; char _pad[14]; } local;
    local.type = 0x11;
    osSetTimer(arg0 + 0x48, &local, 0);
}
