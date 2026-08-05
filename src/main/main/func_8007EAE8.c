#include "ultra64.h"
/*
 * func_8007EAE8 — build a 16-byte AnimCmd on the stack (type=0x11), pass to func_8007E734
 * Compiled with IDO 7.1 -O2 -mips2
 */
void func_8007E734(char *, void *, int);

void func_8007EAE8(char *arg0) {
    struct { short type; char _pad[14]; } local;
    local.type = 0x11;
    func_8007E734(arg0 + 0x48, &local, 0);
}
