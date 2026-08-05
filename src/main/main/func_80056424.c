#include "ultra64.h"
extern f32 D_8004BD70;
extern f32 D_80091E74;
extern s32 D_80091968;

/* -------------------------------------------------------------------------
 * func_80056424 — particle/animation update loop (0x360 bytes, nonmatching).
 *
 * Reads count from D_80091968, float scale from D_80091E74, iterates over
 * D_80182EA8 array performing per-entry updates.  No arguments — all state
 * via globals.  m2c failed: "Failed to parse instruction" in func_80056784
 * (bltz to OS address at line 257 of func_80056424.s).
 * ------------------------------------------------------------------------- */
void func_80056424(void) {
    /* nonmatching: complex loop — see asm/main/main/func_80056424.s */
}

/* -------------------------------------------------------------------------
 * func_80056784 — 3D vector normalize (0xD8 bytes, nonmatching).
 *
 * Normalizes vector (*arg0, *arg1, *arg2) in-place:
 *   scale = D_8004BD70 / sqrtf(x²+y²+z²); then *arg0 *= scale, etc.
 * First instruction `bltz $t4, <OS_addr>` is a handwritten debug trap;
 * cannot be expressed in C.  m2c failed: "Failed to parse instruction".
 * ------------------------------------------------------------------------- */
void func_80056784(f32 *arg0, f32 *arg1, f32 *arg2) {
    /* nonmatching: starts with bltz-to-OS debug trap — see asm stub */
    (void)arg0; (void)arg1; (void)arg2;
}
