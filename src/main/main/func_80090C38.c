#include "ultra64.h"
void __osTimerUnlink(Unk*);                            /* extern */
void __osTimerInsert(Unk*, void**);                    /* extern */

s32 audioTimerAcquire(Unk *arg0, void **arg1, s16 arg2) {
    s16 var_a2;
    s32 var_s2;
    s32 var_v0;
    char *var_s0;
    Unk *var_s0_2;

    var_a2 = arg2;
    var_s0 = arg0->unk14;
    var_s2 = 0;
    if ((var_s0 != NULL) || (var_s0 = arg0->unk4, (var_s0 != NULL))) {
        *arg1 = var_s0;
        __osTimerUnlink(var_s0);
        __osTimerInsert(var_s0, arg0 + 0xC);
        return 0;
    }
    var_s0_2 = arg0->unkC;
    var_v0 = 0;
    if (var_s0_2 != NULL) {
        do {
            if ((var_a2 >= ((Unk *)var_s0_2->unk8)->unk16) && (var_s0_2->unkD8 == 0)) {
                *arg1 = var_s0_2;
                var_s2 = 1;
                var_a2 = (s16) (u16) ((Unk *)var_s0_2->unk8)->unk16;
            }
            var_s0_2 = var_s0_2->unk0;
            var_v0 = var_s2;
        } while (var_s0_2 != NULL);
    }
    return var_v0;
}

/* -------------------------------------------------------------------------
 * func_80090CF4 — 4-byte missing-delay-slot fragment.
 * Single instruction: beqz $a0, .L800726F4; delay slot in next function.
 * ------------------------------------------------------------------------- */
void func_80090CF4(s32 arg0) {
    if (arg0 == 0) {
        return;
    }
}
