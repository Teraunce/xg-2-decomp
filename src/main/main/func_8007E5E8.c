#include "ultra64.h"
/*
 * func_8007E5E8 — build a 16-byte AnimCmd on the stack (type=0xF), pass to osSetTimer
 * Compiled with IDO 7.1 -O2 -mips2
 */
void osSetTimer(char *, void *, int);

void func_8007E5E8(char *arg0) {
    struct { short type; char _pad[14]; } local;
    local.type = 0xF;
    osSetTimer(arg0 + 0x48, &local, 0);
}
