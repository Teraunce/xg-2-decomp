#include "ultra64.h"
s32 func_80074EA0();                                /* extern */
void func_80074ED8(s32);                               /* extern */
s32 sramStartDma(s32, s32, s32);                    /* extern */
static void func_80076000(void);                      /* static, forward decl */
void func_8007611C();                               /* static */
void func_80076138();                               /* static */
extern s32 D_80000000;
extern s32 D_80001FF0;
extern s32 D_80003FE0;
extern s32 D_80189180;

s32 func_80075F90(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;
    s32 temp_s0_2;

    temp_s0_2 = func_80074EA0();
    temp_s0 = sramStartDma(0x707, arg1, arg2);
    func_80074ED8(temp_s0_2);
    return temp_s0;
}

/* -------------------------------------------------------------------------
 * func_80076000 — exception vector stubs (0x70 bytes, static/handwritten).
 *
 * Contains two MIPS exception vector stubs copied to 0x80000180 and
 * 0x80000000 by func_80076070.  Each stub saves $k0 via mtc0 and jumps
 * to func_8007616C.  Uses CP0 registers and kernel regs ($k0) — cannot
 * be expressed in C.  The .L80076014 block (NOPs + redirect to 0x80000194)
 * caused m2c to fail (jump table false positive).
 * ------------------------------------------------------------------------- */
static void func_80076000(void) {
    /* handwritten: mtc0 $k0,$30; lui/addiu $k0, func_8007616C; jr $k0 */
}

void func_80076070(void) {
    char *var_t0;
    char *var_t0_2;
    s32 *var_t1;
    s32 *var_t1_2;
    s32 *var_t2;
    s32 *var_t2_2;
    s32 temp_t5;
    s32 temp_t5_2;

    var_t0 = (char*)func_80076000;
    var_t1 = (s32*)((char*)func_80076000 + 0x14);
    var_t2 = (s32 *)0x80000180;
    do {
        temp_t5 = *(s32*)var_t0;
        var_t0 += 4;
        *var_t1 = *var_t2;
        var_t1 += 4;
        *var_t2 = temp_t5;
        var_t2 += 4;
    } while (var_t0 != (char*)func_80076000 + 0x14);
    var_t0_2 = (char*)func_80076000 + 0x38;
    var_t1_2 = (s32*)((char*)func_80076000 + 0x4C);
    var_t2_2 = &D_80000000;
    do {
        temp_t5_2 = *(s32*)var_t0_2;
        var_t0_2 += 4;
        *var_t1_2 = *var_t2_2;
        var_t1_2 += 4;
        *var_t2_2 = temp_t5_2;
    } while (var_t0_2 != (char*)func_80076000 + 0x4C);
    func_8007611C();
    func_80076138();
    D_80189180 = -0x802;
}

void func_8007611C(void) {
    char *var_t0;

    var_t0 = &D_80001FF0;
    do {
        /* cache 0x1, ($t0) — D-cache invalidate index */
        var_t0 += 0x10;
    } while (var_t0 != (char*)&D_80001FF0);
}

void func_80076138(void) {
    char *var_t0;

    var_t0 = &D_80003FE0;
    do {
        /* cache 0x0, ($t0) — I-cache invalidate index */
        var_t0 += 0x20;
    } while (var_t0 != (char*)&D_80003FE0);
}

s32 func_80076154(void) {
    return 0; /* mfc0 $v0, $12 — read COP0 Status */
}

void func_80076160(void) {
    /* mtc0 $a0, $12 — write COP0 Status */
}

/* -------------------------------------------------------------------------
 * func_8007616C — interrupt/exception dispatcher (0x1D8 bytes, static).
 *
 * Full MIPS interrupt handler.  On entry ($k0 = handler base):
 *   - Saves $at/$v0 to D_80188E48 context block (+0x328/+0x330)
 *   - Reads CP0 Cause register (mfc0 $at, $13), checks IP bits
 *   - If external interrupt (IP5 = 0x800): handles PI DMA IRQ via
 *     cartridge-bus register D_B1FFFFD8, waits for PI idle, toggles
 *     write mask (0x3030303), delays, clears.
 *   - If other interrupt: reads EPC (mfc0 $v0, $14), checks for
 *     syscall-in-ROM (breakpoint address < 0x8004_0000), logs cause.
 *   - Returns via `bgez $zero, .L80076014` (unconditional backward
 *     branch to the NOP sled in func_80076000 that restores state).
 * Uses sd/ld (64-bit), mfc0/mtc0, kernel regs — not expressible in C.
 * m2c failed: "Cannot find branch target .L80076014" (cross-function).
 * ------------------------------------------------------------------------- */
static void func_8007616C(void) {
    /* handwritten exception handler: sd/ld/mfc0/mtc0/$k0 */
}
