#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_80085A00 (initial). */

s32 osVirtualToPhysical(u32);                             /* extern */
f32 func_80085368(Unk*, s32);                     /* extern */
char *func_80085650(f32, s32, void *, s32, s32, s32, s32); /* extern */

char *func_800857DC(Unk *arg0, Unk *arg1, s32 arg2, s32 arg3, s32 arg4) {
    char *sp5C;
    f32 sp44;
    s32 sp38;
    char *sp30;
    s32 sp2C;
    s32 sp28;
    f32 temp_fa0;
    f32 temp_fv1;
    s32 temp_ft4;
    s32 temp_t0;
    s32 temp_t3;
    s32 temp_t8;
    Unk *temp_t6;
    Unk *temp_v0;
    Unk *temp_v0_2;
    char *temp_v1;
    char *var_v1;

    if (arg1->unk24 != 0) {
        sp38 = arg1->unk4 - arg1->unk0;
        temp_fv1 = (f32) (1.0 - (f64) ((f32) (s32) ((func_80085368(arg1, arg3) / (f32) sp38) * 32768.0f) / 32768.0f));
        sp44 = temp_fv1;
        temp_v0 = arg1->unk24;
        temp_fa0 = temp_v0->unk20 + (temp_fv1 * (f32) arg3);
        temp_ft4 = (s32) temp_fa0;
        temp_v0->unk20 = (f32) (temp_fa0 - (f32) temp_ft4);
        sp2C = temp_ft4;
        temp_t0 = arg0->unk18 + ((arg1->unk4 - arg1->unk18) * -2);
        temp_t8 = (s32) (temp_t0 & 7) >> 1;
        temp_t3 = temp_t8 * 2;
        sp28 = temp_t3;
        temp_v0_2 = func_80085650(temp_fa0, 0x47000000, arg0, temp_t0 - temp_t3, 0x280, temp_ft4 + temp_t8, arg4);
        temp_t6 = temp_v0_2 + 8;
        temp_v0_2->unk0 = (s32) (((temp_t3 + 0x280) & 0xFFFF) | 0x08000000);
        temp_v0_2->unk4 = (s32) ((arg2 << 0x10) | ((arg3 * 2) & 0xFFFF));
        sp30 = temp_t6;
        temp_v1 = temp_v0_2 + 0x10;
        temp_v0_2->unk8 = (s32) (((((Unk *)arg1->unk24)->unk24 & 0xFF) << 0x10) | 0x05000000 | ((s32) (sp44 * 32768.0f) & 0xFFFF));
        sp5C = temp_v1;
        var_v1 = temp_v1;
        temp_t6->unk4 = osVirtualToPhysical(((Unk *)arg1->unk24)->unk14);
        ((Unk *)arg1->unk24)->unk24 = 0;
        arg1->unk18 = (s32) ((arg1->unk18 + temp_ft4) - arg3);
    } else {
        var_v1 = func_80085650((f32)(s32) arg0, arg0->unk18 + (arg1->unk4 * -2), (void *)(s32) arg2, arg3, arg4, 0, 0);
    }
    return var_v1;
}

s32 func_80085A04(void);  /* forward: GETTER_NOJR fallthrough */
void func_80085A00(s32 arg1) {
    return func_80085A04();
}
