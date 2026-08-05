#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
void func_8007A918(Unk *arg0, s32 *arg1) {
    s32 sp4;
    s32 sp0;
    s32 *var_v0;
    s32 temp_a3;
    s32 var_a0;
    s32 var_a2;
    u32 *var_v1;
    char *var_t0;
    Unk *var_t1;

    var_v0 = arg1;
    var_v1 = arg1 + 0x20;
    var_a2 = 0;
    var_t0 = arg0;
    do {
        var_a0 = 0;
        var_t1 = var_t0;
loop_2:
        var_a0 += 1;
        sp4 = (((u32) *var_v1 >> 0x10) & 0xFFFF) | (*var_v0 & 0xFFFF0000);
        temp_a3 = (*var_v1 & 0xFFFF) | ((*var_v0 << 0x10) & 0xFFFF0000);
        sp0 = temp_a3;
        var_v0 += 4;
        var_v1 += 4;
        var_t1 += 8;
        var_t1->unk0 /* FIXME: was ->unk-8 */ = (f32) ((f32) sp4 / (s32)M2C_ERROR(/* Read from unset register $f0 */));
        var_t1->unk0 /* FIXME: was ->unk-4 */ = (f32) ((f32) temp_a3 / (s32)M2C_ERROR(/* Read from unset register $f0 */));
        if (var_a0 != 2) {
            goto loop_2;
        }
        var_a2 += 1;
        var_t0 += 0x10;
    } while (var_a2 != 4);
}

void func_8007A9C8(Unk *arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    *arg4 = arg0->unk30 + ((arg0->unk0 * arg1) + (arg0->unk10 * arg2) + (arg0->unk20 * arg3));
    *arg5 = arg0->unk34 + ((arg0->unk4 * arg1) + (arg0->unk14 * arg2) + (arg0->unk24 * arg3));
    *arg6 = arg0->unk38 + ((arg0->unk8 * arg1) + (arg0->unk18 * arg2) + (arg0->unk28 * arg3));
}
