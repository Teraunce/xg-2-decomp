#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of trackNodeFindNearestGetter (initial). */

extern s32 D_80091FD0;
extern s32 D_8017CC60;
extern Unk *D_8017CCB8;

void trackNodeSearchNearest(f32 *arg0, s32 *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 temp_ft0;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    s32 temp_s1;
    s32 var_s0;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_v1;
    u16 temp_v1_2;
    Unk *temp_a0;
    Unk *temp_a0_2;

    temp_s1 = ((Unk *)D_8017CCB8->unk8)->unk38;
    var_s0 = arg5;
    *(((s32) (((Unk *)((char *)(s32)temp_s1 + arg5 * 0x38))->unk16 & 0xF800) >> 0xB) + &D_8017CC60) = 1;
    var_v0 = var_s0 * 8;
loop_1:
    temp_a0 = ((var_v0 - var_s0) * 8) + temp_s1;
    temp_v1 = temp_a0->unk18;
    if (temp_v1 != var_s0) {
        var_v0_2 = var_s0 * 8;
        if (*(((s32) (((Unk *)((char *)(s32)temp_s1 + temp_v1 * 0x38))->unk16 & 0xF800) >> 0xB) + &D_8017CC60) == 0) {
            trackNodeSearchNearest(arg0, arg1, arg2, arg3, arg4, (s32) temp_a0->unk18);
            goto block_4;
        }
    } else {
block_4:
        var_v0_2 = var_s0 * 8;
    }
    temp_a0_2 = ((var_v0_2 - var_s0) * 8) + temp_s1;
    if (temp_a0_2->unk16 & (D_80091FD0 * 4)) {
        temp_fv1 = arg2 - (f32) temp_a0_2->unk0;
        temp_ft0 = arg3 - (f32) temp_a0_2->unk4;
        temp_fv0 = arg4 - (f32) temp_a0_2->unk8;
        temp_fv1_2 = (temp_fv1 * temp_fv1) + (temp_ft0 * temp_ft0) + (temp_fv0 * temp_fv0);
        if (temp_fv1_2 < *arg0) {
            *arg0 = temp_fv1_2;
            *arg1 = var_s0;
        }
    }
    var_s0 += 1;
    temp_v1_2 = ((Unk *)((char *)(s32)temp_s1 + var_s0 * 0x38))->unk18;
    if (temp_v1_2 != 0x8000) {
        if (temp_v1_2 & 0x8000) {
            var_s0 = temp_v1_2 & 0x7FFF;
        }
        var_v0 = var_s0 * 8;
        if (var_s0 != arg5) {
            goto loop_1;
        }
    }
}

char *trackNodeFindNearestGetter(void) {
    trackNodeFindNearest(0.0f, 0.0f, 0.0f);
    return D_8017CCB8;
}
