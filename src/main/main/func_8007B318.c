#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8007B368 (initial). */

void func_8007A758(char*, char*);                          /* extern */
void func_8007B178(void *, f32, f32, s32, f32);             /* extern */
extern f32 D_8004C888;

/*
 * func_8007B318 — nonmatching.
 *
 * arg1 ($fa0/$f12), arg2_fa1 ($fa1/$f14), and arg3_ft4 ($ft4/$f16) are
 * float arguments; arg3_ft4 uses non-standard register $f16 (SN64 quirk).
 * Typically called via getter func_8007B368 which scales $a1 by D_8004C888
 * and moves $a1/$a2/$a3 into $fa0/$fa1/$ft4 before falling through.
 */
void func_8007B318(f32 arg1, s32 arg0, f32 arg2_fa1, f32 arg3_ft4, f32 arg4) {
    s32 sp20;

    func_8007B178(&sp20, arg0, arg1, (s32) arg3_ft4, arg4);
    func_8007A758(&sp20, arg0);
}

/*
 * func_8007B368 — GETTER fallthrough preamble for func_8007B318.
 *
 * Loads D_8004C888 into $fv0, moves $a1/$a2/$a3 into $fa0/$fa1/$ft4,
 * then scales $fa0 by D_8004C888, then falls through to func_8007B318.
 * Cannot be expressed in standard C.
 */
void func_8007B368(s32 arg1, s32 arg2, s32 arg3) {
    (void)arg1; (void)arg2; (void)arg3;
}
