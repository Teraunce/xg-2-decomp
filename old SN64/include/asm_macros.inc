/* asm_macros.inc — GNU as macro definitions for spimdisasm-style directives */

/* glabel: export a global function label */
.macro glabel name
    .globl \name
    .type \name, @function
    \name:
.endm

/* alabel: local branch target (no export) */
.macro alabel name
    \name:
.endm

/* endlabel: marks end of a nonmatching region — pure no-op for assembly */
.macro endlabel name
.endm

/* nonmatching: metadata marker — the C decompilation doesn't byte-match */
.macro nonmatching name, size
.endm
