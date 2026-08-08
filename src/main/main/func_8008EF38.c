#include "ultra64.h"

/*
 * gbiCmdDispatch — GBI command dispatcher variant (nonmatching).
 *
 * PERMANENTLY NONMATCHING — two reasons:
 *
 * 1. Non-standard ABI: $s0 is used as an implicit context pointer that the
 *    caller provides directly in the $s0 register.  The prologue saves $ra
 *    and $a1 but does NOT save $s0, then immediately writes through it:
 *      sw $zero, 0xC($s0)
 *      sw $zero, 0x10($s0)
 *      sw $zero, 0x14($s0)
 *      sw $zero, 0x18($s0)
 *      sw $zero, 0x1C($s0)
 *      sw $zero, 0x20($s0)
 *    This zeroing-of-six-words pattern happens before any load into $s0,
 *    proving it is an input, not a local.  No standard C calling convention
 *    passes arguments in $s0.
 *
 * 2. Dispatches via jr through jtbl_8004CFFC (52 entries, index = a1 - 0x45
 *    with a secondary range check for a1 < 0x26). m2c marks any function
 *    containing jr-from-table as nonmatching.
 *
 * Likely signature (non-C-expressible): (Unk *s0_ctx, u8 a1_cmd)
 * where s0_ctx arrives in $s0 from the caller's register state.
 */
void gbiCmdDispatch(void) { /* nonmatching — see asm stub */ }
