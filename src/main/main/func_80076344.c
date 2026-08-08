#include "ultra64.h"
/*
 * renderMainDispatch — handwritten 64-bit MIPS function (nonmatching).
 *
 * PERMANENTLY NONMATCHING — spimdisasm cannot decode this function at all.
 * Every instruction is emitted as a raw `.word` directive because the opcodes
 * are 64-bit MIPS LD/SD instructions (MIPS III load-doubleword / store-
 * doubleword) that the disassembler's 32-bit N64 mode does not recognize
 * ("handwritten instruction" in spimdisasm output).  m2c therefore sees "no
 * instructions" and cannot generate any C.
 *
 * This is the ONLY function in the project that is entirely in raw .word form.
 * It ends with a normal `jr $ra`, so it IS a callable function — the 64-bit
 * opcodes are likely hand-authored RSP microcode submission or a bulk
 * data-copy routine that requires 64-bit memory transfers on the R4300.
 *
 * Allocates a 0x6828-byte (26,664-byte) stack frame — the largest in the
 * project.  Address range: 0x80076344 – 0x80079F24 (0x3BE0 bytes / ~3983
 * disassembly lines).  Contains five jump tables in its rodata:
 *   jtbl_80076520, D_800769A8, D_800777C8, D_80077898, D_80078A28.
 */
void renderMainDispatch(void) { /* nonmatching — see asm stub */ }

/* jtbl_80076520: rodata/jtbl — defined in .s file */

/* D_800769A8: rodata/jtbl — defined in .s file */

/* D_800777C8: rodata/jtbl — defined in .s file */

/* D_80077898: rodata/jtbl — defined in .s file */

/* D_80078A28: rodata/jtbl — defined in .s file */
