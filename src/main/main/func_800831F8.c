#include "ultra64.h"

/* -------------------------------------------------------------------------
 * func_800831F8 — 3D mesh initialiser (0x43C bytes, nonmatching).
 *
 * Initialises a mesh/vertex object (arg0 = dest Unk*) from a source
 * descriptor (arg1 = Unk*) and a render context (arg2 = void *).
 *
 * The selector byte at arg1->unk1C (1-6) picks a geometry data table:
 *   1 → D_800952E0   2 → D_80095348   3 → D_800953F8
 *   4 → D_80095420   5 → D_800953D0   6 → *(s32*)(arg1->unk20)
 *   default → D_80095448
 *
 * After selection, iterates over the table entries converting integer
 * geometry data to floats and building vertex/strip arrays via
 * func_8007FD48, func_80083158.  Uses double-precision FPU for scale.
 *
 * Jump table: jtbl_8004CEB8 (6 entries, selector-1 = 0-5).
 * -------------------------------------------------------------------------
 */

void func_80084EF8(void *arg0, void *arg1, void *arg2, s32 arg3);
char *func_8007FD48(s32 arg0, s32 arg1, Unk *arg2, u8 arg3, s32 arg4);
void func_80083158(Unk *arg0);
void osSendMesg(void *arg0, void *arg1, s32 arg2);  /* unused extern? */

extern s32 D_800952E0[];   /* geometry table: selector 1 */
extern s32 D_80095348[];   /* geometry table: selector 2 */
extern s32 D_800953F8[];   /* geometry table: selector 3 */
extern s32 D_80095420[];   /* geometry table: selector 4 */
extern s32 D_800953D0[];   /* geometry table: selector 5 */
extern s32 D_80095448[];   /* geometry table: default */
extern f64 D_8004CED0;     /* double constant (scale factor, ldc1 in asm) */

/* func_80085C5C — mesh element setter (nonmatching, in func_80085A04.c) */
s32 func_80085C5C(s32 *arg0, s32 arg1, s32 arg2);
/* func_80085C74, func_80085A00 — installed as callbacks into dest->unk4/unk28 */
extern void func_80085C74(void);
extern void func_80085A00(void);

void func_800831F8(Unk *arg0, Unk *arg1, void *arg2) {
    /* nonmatching: FPU vertex loop — see asm/main/main/func_800831F8.s */
    s32 *tbl;
    u8 sel;

    /* Install callbacks and init dest object */
    arg0->unk4  = (s32)func_80085C74;
    arg0->unk28 = (s32)func_80085A00;
    func_80084EF8(arg0, (void *)0, (void *)func_80085C5C, 5);

    /* Select geometry data table from arg1->unk1C (1-6) */
    sel = *(u8 *)((char *)arg1 + 0x1C);
    switch ((u32)(sel - 1)) {
    case 0:  tbl = D_800952E0;                               break;
    case 1:  tbl = D_80095348;                               break;
    case 2:  tbl = D_800953F8;                               break;
    case 3:  tbl = D_80095420;                               break;
    case 4:  tbl = D_800953D0;                               break;
    case 5:  tbl = *(s32 **)((char *)arg1 + 0x20);          break;
    default: tbl = D_80095448;                               break;
    }

    /* nonmatching: FPU vertex/strip loop over tbl[].
     * Reads count from tbl[0], converts geometry to floats,
     * calls func_8007FD48 / func_80083158 per strip.
     * See asm stub for full implementation. */
    (void)tbl;
    (void)arg2;
}
