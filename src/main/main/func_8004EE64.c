#include "ultra64.h"
void trackNodeSearchNearest(f32 *, s32 *, f32, f32, f32, s32);  /* extern */
extern f32 D_8004BBB4;
extern s32 D_8017CC60;

s32 trackNodeFindNearest(f32 arg0, f32 arg1, f32 arg2) {
    s32 sp1C;
    f32 sp18;
    s32 temp_v0;
    s32 var_v1;
    s8 *var_v0;
    Unk *temp_a0;

    /* implicit $v0 (ptr from caller): $v0->unk8->unk38 */
    temp_a0 = (Unk *)((Unk *)((Unk*)0 /* implicit $v0 */)->unk8)->unk38;
    var_v1 = 0x1F;
    if (temp_a0 == NULL) {
        return -1;
    }
    var_v0 = &D_8017CC60 + 0x1F;
    do {
        *var_v0 = 0;
        var_v1 -= 1;
        var_v0 -= 1;
    } while (var_v1 >= 0);
    sp1C = 1;
    if (!(temp_a0->unk50 & 0x8000)) {
loop_5:
        temp_v0 = sp1C + 1;
        if (((sp1C * 0x38) + temp_a0)->unk12 != 0) {
            sp1C = temp_v0;
            if (!(((temp_v0 * 0x38) + temp_a0)->unk18 & 0x8000)) {
                goto loop_5;
            }
        }
        if (((sp1C * 0x38) + temp_a0)->unk18 & 0x8000) {
            goto block_8;
        }
    } else {
block_8:
        sp1C = 0;
    }
    sp18 = D_8004BBB4;
    trackNodeSearchNearest(&sp18, &sp1C, arg0, arg1, arg2, sp1C);
    return sp1C;
}
