#include "ultra64.h"
char *func_80085410(s32, s16, s32, void *);         /* extern */
char *func_800854C8(void *, u32, s16, s32, void *); /* extern */
char *func_80085650(void *, u32, s16, s32, void *); /* extern */
char *func_800857DC(void *, void *, s16, s32, void *); /* extern */

char *func_80085C74(Unk *arg0, s32 arg2, s32 arg4) {
    s32 sp80;
    s32 sp50;
    s32 sp48;
    s16 temp_a0_2;
    s16 temp_t2;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 var_s2;
    s16 var_s5;
    s16 var_s7;
    s32 temp_a0_3;
    s32 temp_s1;
    s32 temp_t1;
    s32 temp_t2_2;
    s32 var_v1;
    u32 temp_fp;
    u32 temp_s4;
    u32 temp_t8;
    Unk *temp_a0;
    Unk *temp_s1_2;
    Unk *temp_v0;
    Unk *temp_v0_2;
    Unk *temp_v0_3;
    Unk *var_s0;

    temp_a0 = arg0->unk0;
    sp80 = 0;
    temp_v0 = ((s32(*)())(s32)temp_a0->unk4)(temp_a0, arg4);
    temp_s1 = arg2 * 2;
    temp_t1 = temp_s1 & 0xFFFF;
    temp_v0->unk0 = 0x08000000;
    temp_v0->unk4 = temp_t1;
    temp_v0->unk8 = 0x0C00DA83;
    temp_v0->unkC = 0x06C006C0;
    temp_v0->unk10 = 0x0C005A82;
    temp_v0->unk14 = 0x080006C0;
    var_s5 = 0;
    var_s2 = 0x140;
    sp48 = temp_t1;
    sp50 = temp_s1;
    temp_v0_2 = func_800854C8(arg0, arg0->unk18, 0x6C0, arg2, temp_v0 + 0x18);
    var_v1 = sp80;
    temp_v0_2->unk0 = 0x02000800;
    temp_v0_2->unk4 = temp_s1;
    var_s0 = temp_v0_2 + 8;
    var_s7 = 0;
    if ((s32) arg0->unk24 > 0) {
        do {
            temp_s1_2 = arg0->unk20 + (var_s7 * 0x28);
            temp_s4 = arg0->unk18 + (temp_s1_2->unk0 * -2);
            temp_fp = arg0->unk18 + (temp_s1_2->unk4 * -2);
            if (temp_s4 == var_v1) {
                temp_t2 = var_s2;
                var_s2 = var_s5;
                var_s5 = temp_t2;
            } else {
                var_s0 = func_80085650(arg0, temp_s4, var_s5, arg2, var_s0);
            }
            temp_v0_3 = func_800857DC(arg0, temp_s1_2, var_s2, arg2, var_s0);
            temp_a0_2 = temp_s1_2->unk8;
            var_s0 = temp_v0_3;
            if (temp_a0_2 != 0) {
                temp_v0_3->unk0 = (s32) ((temp_a0_2 & 0xFFFF) | 0x0C000000);
                temp_v0_3->unk4 = (s32) ((var_s5 << 0x10) | (var_s2 & 0xFFFF));
                var_s0 = temp_v0_3 + 8;
                if ((temp_s1_2->unk24 == 0) && (temp_s1_2->unk20 == 0)) {
                    var_s0 = func_800854C8(arg0, temp_fp, var_s2, arg2, var_s0);
                }
            }
            temp_v1 = temp_s1_2->unkA;
            if (temp_v1 != 0) {
                var_s0->unk0 = (s32) ((temp_v1 & 0xFFFF) | 0x0C000000);
                var_s0->unk4 = (s32) ((var_s2 << 0x10) | (var_s5 & 0xFFFF));
                var_s0 = func_800854C8(arg0, temp_s4, var_s5, arg2, var_s0 + 8);
            }
            temp_a0_3 = temp_s1_2->unk20;
            if (temp_a0_3 != 0) {
                var_s0 = func_80085410(temp_a0_3, var_s2, arg2, var_s0);
            }
            if (temp_s1_2->unk24 == 0) {
                var_s0 = func_800854C8(arg0, temp_fp, var_s2, arg2, var_s0);
            }
            temp_v1_2 = temp_s1_2->unkC;
            var_s7 += 1;
            if (temp_v1_2 != 0) {
                var_s0->unk0 = (s32) ((temp_v1_2 & 0xFFFF) | 0x0C000000);
                var_s0->unk4 = (s32) ((var_s2 << 0x10) | 0x800);
                var_s0 += 8;
            }
            var_v1 = arg0->unk18 + (temp_s1_2->unk4 * 2);
        } while (var_s7 < (s32) arg0->unk24);
    }
    temp_t2_2 = arg0->unk1C * 2;
    temp_t8 = arg0->unk18 + sp50;
    arg0->unk18 = temp_t8;
    if ((u32) (arg0->unk14 + temp_t2_2) < temp_t8) {
        arg0->unk18 = (u32) (temp_t8 - temp_t2_2);
    }
    var_s0->unk0 = 0x0A000800;
    var_s0->unk4 = (s32) (sp48 | 0x06C00000);
    return var_s0 + 8;
}

s32 func_80085FB8(Unk *arg0, s32 arg1, s32 arg2) {
    if (arg1 != 1) {
        if (arg1 != 6) {
            return 0;
        }
        arg0->unk14 = arg2;
        return 0;
    }
    arg0->unk0 = arg2;
    return 0;
}
