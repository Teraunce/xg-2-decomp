#include "ultra64.h"
void func_8007A758(char*, char*);                          /* extern */
void func_8007B878(f32, s32, s32);                       /* extern */
extern s32 D_800952A0;

void func_8007BA28(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    s32 sp28;

    func_8007B878(arg1, arg2, arg3);
    func_8007A758(&sp28, arg0);
}

void func_8007BA98(u32 arg0, s32 arg1) {
    s32 temp_t2;
    s32 temp_t2_2;
    u32 temp_t0;
    u32 temp_t1;
    u32 var_t0;
    u32 var_t0_2;
    u32 var_t1;

    if (arg1 > 0) {
        if ((u32) arg1 < 0x2000U) {
            var_t0 = arg0;
            temp_t1 = arg0 + arg1;
            if (var_t0 < temp_t1) {
                temp_t2 = var_t0 & 0xF;
                var_t1 = temp_t1 - 0x10;
                if (temp_t2 != 0) {
                    temp_t0 = var_t0 - temp_t2;
                    /* cache 0x15, ($t0) — D-cache writeback-invalidate hit */
                    if (temp_t0 < var_t1) {
                        var_t0 = temp_t0 + 0x10;
                        goto block_6;
                    }
                } else {
block_6:
                    temp_t2_2 = var_t1 & 0xF;
                    /* cache 0x15, 0x10($t1) — D-cache writeback-invalidate hit (tail align) */
                    if ((temp_t2_2 == 0) || (var_t1 -= temp_t2_2, ((var_t1 < var_t0) == 0))) {
                        do {
                            /* cache 0x11, ($t0) — D-cache writeback hit */
                            var_t0 += 0x10;
                        } while (var_t0 < var_t1);
                    }
                }
            }
        } else {
            var_t0_2 = 0x80000000;
            do {
                /* cache 0x1, ($t0) — D-cache invalidate index */
                var_t0_2 += 0x10;
            } while (var_t0_2 < 0x80001FF0U);
        }
    }
}

void func_8007BB48(u32 arg0, s32 arg1) {
    u32 temp_t1;
    u32 var_t0;
    u32 var_t0_2;

    if (arg1 > 0) {
        if ((u32) arg1 < 0x4000U) {
            temp_t1 = arg0 + arg1;
            if (arg0 < temp_t1) {
                var_t0 = arg0 - (arg0 & 0x1F);
                do {
                    /* cache 0x10, ($t0) — I-cache hit invalidate */
                    var_t0 += 0x20;
                } while (var_t0 < (u32) (temp_t1 - 0x20));
            }
        } else {
            var_t0_2 = 0x80000000;
            do {
                /* cache 0x0, ($t0) — I-cache invalidate index */
                var_t0_2 += 0x20;
            } while (var_t0_2 < 0x80003FE0U);
        }
    }
}

void func_8007BC28(u32 arg0, s32 arg1) {
    u32 temp_t1;
    u32 var_t0;
    u32 var_t0_2;

    if (arg1 > 0) {
        if ((u32) arg1 < 0x2000U) {
            temp_t1 = arg0 + arg1;
            if (arg0 < temp_t1) {
                var_t0 = arg0 - (arg0 & 0xF);
                do {
                    /* cache 0x19, ($t0) — D-cache writeback index */
                    var_t0 += 0x10;
                } while (var_t0 < (u32) (temp_t1 - 0x10));
            }
        } else {
            var_t0_2 = 0x80000000;
            do {
                /* cache 0x1, ($t0) — D-cache invalidate index */
                var_t0_2 += 0x10;
            } while (var_t0_2 < 0x80001FF0U);
        }
    }
}

void func_8007BCA8(void) {
    u32 var_t0;

    var_t0 = 0x80000000;
    do {
        /* cache 0x1, ($t0) — D-cache invalidate index */
        var_t0 += 0x10;
    } while (var_t0 < 0x80001FF0U);
}

void func_8007BCD8(Unk *arg0, s32 arg1, s32 arg2) {
    arg0->unk0 = &D_800952A0;
    arg0->unk4 = &D_800952A0;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk10 = arg2;
    arg0->unk14 = arg1;
}
