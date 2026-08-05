#include "ultra64.h"

/*
 * func_8007C0F4 — massive-stack helper function (nonmatching).
 *
 * PERMANENTLY NONMATCHING — cross-function backward branch:
 *
 *   b .L8007C068
 *
 * The target label 0x8007C068 lies 0x8C bytes BEFORE the function entry
 * point 0x8007C0F4 — i.e. inside the prior function's code.  m2c cannot
 * parse a branch to a label that doesn't exist within the current function,
 * so it rejects the file entirely and the build falls back to the .s stub.
 *
 * spimdisasm marks this file "Handwritten function", suggesting the branch
 * was deliberately authored this way (likely a shared epilogue or a
 * deliberately overlapping code sequence in the original source).
 *
 * Additional note: the prologue allocates a 0x3CF8-byte (15,608-byte)
 * stack frame, which is the largest in the project and points to this
 * function doing very heavyweight local work (possibly a large scratchpad
 * or a matrix/geometry buffer on the stack).
 *
 * Function size: 0x754 bytes.
 */
void func_8007C0F4(void) { /* nonmatching — see asm stub */ }
