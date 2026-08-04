#include "ultra64.h"

/*
 * func_8007ED94 — GBI audio command dispatcher variant (nonmatching).
 *
 * PERMANENTLY NONMATCHING — two reasons:
 *
 * 1. Non-standard ABI: the command buffer pointer arrives in $t0, not $a0.
 *    Prologue reads:
 *      lbu $s6, 0x8($t0)   <- cmd[8]  (expected: 0x8($a0))
 *      lbu $s4, 0x9($t0)   <- cmd[9]
 *      lbu $s1, 0xA($t0)   <- cmd[0xA]
 *    The node pointer is in $s2 (caller-provided, not saved in prologue).
 *    No C compiler will produce this calling convention from a normal
 *    function declaration.
 *
 * 2. Dispatches via jr through jtbl_8004C9D8 (same outer-dispatch structure
 *    as func_800805A4 / func_800805A4). m2c marks any function containing
 *    jr-from-table as nonmatching.
 *
 * Structurally this function mirrors func_800805A4 exactly — same GBI
 * command dispatch logic on (cmd[8] & 0xF0) — but the compiler placed the
 * cmd pointer in $t0 and the node pointer in $s2 instead of $a0/$s1.
 * This likely indicates it is called from a specific site that already has
 * $t0 set up (e.g. from inside another dispatcher via jalr or a tail call
 * with non-standard register passing).
 */
void func_8007ED94(void) { /* nonmatching — see asm stub */ }
