#include "ultra64.h"
extern f32 D_8004BDAC;

/*
 * func_80057AC4 — compute cross product of two edge vectors (nonmatching).
 *
 * Caller pre-computes arg1->unk0 - arg0->unk0 and passes it in $fv0/$f0.
 * sp0 captures that value from the stack save at function entry.
 * Written to be self-contained (computes unk0 delta here for readability).
 */
void func_80057AC4(Unk *arg0, Unk *arg1, Unk *arg2, Unk *arg3) {
    /* B = arg1 - arg0 */
    f32 sp0 = arg1->unk0 - arg0->unk0;   /* caller passed this in $fv0 */
    f32 sp4 = arg1->unk4 - arg0->unk4;
    f32 sp8 = arg1->unk8 - arg0->unk8;
    /* C = arg2 - arg0 */
    f32 sp10 = arg2->unk0 - arg0->unk0;
    f32 sp14 = arg2->unk4 - arg0->unk4;
    f32 sp18 = arg2->unk8 - arg0->unk8;
    /* cross product B × C */
    arg3->unk0 = (f32) ((sp4 * sp18) - (sp8 * sp14));
    arg3->unk4 = (f32) ((sp8 * sp10) - (sp0 * sp18));
    arg3->unk8 = (f32) ((sp0 * sp14) - (sp4 * sp10));
}

void func_80057B74(Unk *arg0, Unk *arg1, Unk *arg2) {
    f32 temp_ft0;

    arg2->unk0 = (f32) ((arg0->unk4 * arg1->unk8) - (arg0->unk8 * arg1->unk4));
    arg2->unk4 = (f32) ((arg0->unk8 * arg1->unk0) - (arg0->unk0 * arg1->unk8));
    temp_ft0 = (arg0->unk0 * arg1->unk4) - (arg0->unk4 * arg1->unk0);
    arg2->unk8 = temp_ft0;
    if ((arg2->unk0 == 0.0f) && (arg2->unk4 == 0.0f) && (temp_ft0 == 0.0f)) {
        arg2->unk0 = (f32) D_8004BDAC;
    }
}

s32 func_80057C20(Unk *arg0, Unk *arg1, Unk *arg2, Unk *arg3) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft2;
    f32 temp_ft2_2;
    f32 temp_ft3;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    s16 temp_a0;
    s16 temp_a3;
    s16 temp_t0;

    temp_t0 = arg0->unk0;
    temp_a3 = arg0->unk2;
    temp_a0 = arg0->unk4;
    temp_ft2 = (f32) (arg1->unk0 - temp_t0);
    temp_fv1 = (f32) (arg1->unk4 - temp_a0);
    temp_ft3 = (f32) (arg1->unk2 - temp_a3);
    temp_fa1 = (f32) (arg2->unk0 - temp_t0);
    temp_fa0 = (f32) (arg2->unk2 - temp_a3);
    temp_ft1 = (f32) (arg2->unk4 - temp_a0);
    if ((temp_ft2 == 0.0f) && (temp_ft3 == 0.0f) && (temp_fv1 == 0.0f)) {
        /* Duplicate return node #3. Try simplifying control flow for better match */
        return 0;
    }
    if (((temp_fa1 != 0.0f) || (temp_fa0 != 0.0f) || (temp_ft1 != 0.0f)) && ((temp_ft2 != temp_fa1) || (temp_ft3 != temp_fa0) || (temp_fv1 != temp_ft1))) {
        temp_fv0 = (temp_ft3 * temp_ft1) - (temp_fv1 * temp_fa0);
        temp_fv1_2 = (temp_fv1 * temp_fa1) - (temp_ft2 * temp_ft1);
        arg3->unk0 = temp_fv0;
        arg3->unk4 = temp_fv1_2;
        temp_ft2_2 = (temp_ft2 * temp_fa0) - (temp_ft3 * temp_fa1);
        arg3->unk8 = temp_ft2_2;
        temp_ft0 = sqrtf((temp_fv0 * temp_fv0) + (temp_fv1_2 * temp_fv1_2) + (temp_ft2_2 * temp_ft2_2));
        arg3->unk0 = (f32) (temp_fv0 / temp_ft0);
        arg3->unk4 = (f32) (arg3->unk4 / temp_ft0);
        arg3->unk8 = (f32) (temp_ft2_2 / temp_ft0);
        return 1;
    }
    return 0;
}
