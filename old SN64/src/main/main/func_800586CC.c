#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
/* Warning: missing "jr $ra" in last block of func_8005A2FC (initial). */

s32 func_80056788(f32 *, f32 *, f32 *);               /* extern */
void func_80057B74(Unk*, Unk*, Unk*);               /* extern */
void func_8007AC38(s32, s32, s32);                  /* extern */
void func_8007B820(s32, f32, f32, f32);                  /* extern */
void func_8005A214(Unk *arg0, Unk *arg1, s32 arg2); /* static */
s32 func_8005A33C();                                  /* static */
s32 func_8005A47C(s32);                               /* static */
extern f32 D_8004BDDC;
extern f32 D_8004BDE0;
extern f32 D_8004BDE4;
extern Unk D_80091F7C;

void func_800586CC(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    s32 saved_reg_f24;
    s32 saved_reg_f26;
    s32 saved_reg_f28;
    s32 saved_reg_f30;
    s32 saved_reg_s0;
    s32 saved_reg_s1;
    s32 saved_reg_s2;
    s32 saved_reg_s3;
    s32 spFC;
    s32 spF8;
    s32 spF4;
    s32 spF0;
    s32 spEC;
    s32 spE8;
    s32 spE4;
    s32 spE0;
    s32 spDC;
    s32 spD8;
    s32 spD4;
    s32 spD0;
    s32 spCC;
    s32 spC8;
    s32 spC4;
    s32 spC0;
    s32 sp80;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    s32 temp_a3;
    s32 temp_ft2;
    s32 temp_ft2_2;
    s32 temp_ft2_3;
    s32 temp_ft2_4;
    s32 temp_ft2_5;
    s32 temp_ft2_6;
    s32 temp_ft2_7;
    s32 temp_ft2_8;
    s32 temp_ft2_9;

    func_8007B820(&sp80, arg1, arg2, arg3);
    sp64 = arg8;
    sp60 = arg7;
    sp68 = arg9;
    sp70 = arg4 - arg1;
    sp74 = arg5 - arg2;
    sp78 = arg3 - arg6;
    func_80057B74(&sp70, &sp60, &sp50);
    func_80057B74(&sp50, &sp70, &sp60);
    func_80056788(&sp50, &sp54, &sp58);
    func_80056788(&sp60, &sp64, &sp68);
    func_80056788(&sp70, &sp74, &sp78);
    spD8 = 0;
    spDC = 1;
    spF8 = 0;
    spFC = 0;
    temp_ft2 = (s32) (sp50 * D_8004BDDC);
    temp_ft2_2 = (s32) (sp54 * D_8004BDDC);
    temp_ft2_3 = (s32) (sp58 * D_8004BDDC);
    spC0 = (temp_ft2 & 0xFFFF0000) | ((u32) temp_ft2_2 >> 0x10);
    spC4 = temp_ft2_3 & 0xFFFF0000;
    spE0 = (temp_ft2 << 0x10) | (temp_ft2_2 & 0xFFFF);
    spE4 = temp_ft2_3 << 0x10;
    temp_ft2_4 = (s32) (sp60 * D_8004BDDC);
    temp_ft2_5 = (s32) (sp64 * D_8004BDDC);
    spC8 = (temp_ft2_4 & 0xFFFF0000) | ((u32) temp_ft2_5 >> 0x10);
    spE8 = (temp_ft2_4 << 0x10) | (temp_ft2_5 & 0xFFFF);
    temp_ft2_6 = (s32) (sp68 * D_8004BDDC);
    temp_ft2_7 = (s32) (sp70 * D_8004BDDC);
    temp_ft2_8 = (s32) (sp74 * D_8004BDDC);
    spD0 = (temp_ft2_7 & 0xFFFF0000) | ((u32) temp_ft2_8 >> 0x10);
    spCC = temp_ft2_6 & 0xFFFF0000;
    spEC = temp_ft2_6 << 0x10;
    spF0 = (temp_ft2_7 << 0x10) | (temp_ft2_8 & 0xFFFF);
    temp_ft2_9 = (s32) (sp78 * D_8004BDDC);
    temp_a3 = temp_ft2_9 & 0xFFFF0000;
    spD4 = temp_a3;
    spF4 = temp_ft2_9 << 0x10;
    func_8007AC38(&spC0, &sp80, arg0);
}

s16 func_80058940(s16 arg0) {
    s32 temp_v0;
    u16 temp_a1;
    u16 temp_a2;
    u16 temp_a3;
    u16 temp_t2;
    u32 temp_v1;

    temp_a1 = (D_80091F7C.unk0 ^ D_80091F7C.unk2) + 7;
    temp_t2 = temp_a1 * 2;
    temp_a3 = temp_t2 | ((u32) (temp_a1 & 0xFFFF) >> 0xF);
    temp_v0 = (s32) (temp_a3 & 0x7FFF) % arg0;
    temp_a2 = (D_80091F7C.unk2 - 0x5347) ^ 0x7C9F;
    temp_v1 = (u32) (temp_a2 & 0xFFFF) >> 1;
    D_80091F7C.unk2 = temp_a2;
    D_80091F7C.unk2 = (u16) temp_v1;
    D_80091F7C.unk0 = temp_a1;
    D_80091F7C.unk0 = temp_t2;
    D_80091F7C.unk0 = temp_a3;
    D_80091F7C.unk2 = (u16) (temp_v1 | (temp_a2 << 0xF));
    return (s16) temp_v0;
}

s32 func_800589DC(s32 arg0, s32 arg1, s32 arg2) {
    return (s32) ((arg2 * arg1) + (arg0 * (0x1000 - arg2))) >> 0xC;
}

f32 func_80058A00(f32 arg0, f32 arg1, f32 arg2) {
    return ((arg2 * arg1) + (arg0 * (D_8004BDE0 - arg2))) * D_8004BDE4;
}

/* D_80059234: rodata/jtbl — defined in .s file */

s32 func_80059774(f32 arg_fa0_unused, f32 arg_fa1_unused) {
    Unk *saved_reg_s0;
    Unk *saved_reg_s1;
    Unk *saved_reg_s2;
    f32 saved_reg_f24;
    f32 saved_reg_f26;
    f32 saved_reg_f28;
    f32 saved_reg_f30;
    f32 temp_ft4;
    f32 var_fa0;
    f32 var_ft0;
    f32 var_ft1;
    f32 var_ft2;
    f32 var_ft3;
    f32 var_fv1;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a3;

    temp_a0 = M2C_ERROR(/* Read from unset register $t5 */)->unk4;
    temp_a1 = M2C_ERROR(/* Read from unset register $t5 */)->unk8;
    temp_a3 = M2C_ERROR(/* Read from unset register $t5 */)->unkC;
    if (M2C_ERROR(/* Read from unset register $t4 */)->unk3 & 0x80) {
        var_fv1 = (f32) (saved_reg_s0->unk2 + temp_a1) - saved_reg_f28;
        var_ft0 = (f32) (saved_reg_s1->unk2 + temp_a1) - saved_reg_f28;
        var_ft1 = (f32) (saved_reg_s2->unk2 + temp_a1) - saved_reg_f28;
    } else {
        var_fv1 = (f32) (saved_reg_s0->unk0 + temp_a0) - saved_reg_f26;
        var_ft0 = (f32) (saved_reg_s1->unk0 + temp_a0) - saved_reg_f26;
        var_ft1 = (f32) (saved_reg_s2->unk0 + temp_a0) - saved_reg_f26;
    }
    if (M2C_ERROR(/* Read from unset register $t4 */)->unk3 & 0x40) {
        var_ft2 = (f32) (saved_reg_s0->unk2 + temp_a1) - saved_reg_f28;
        var_ft3 = (f32) (saved_reg_s1->unk2 + temp_a1) - saved_reg_f28;
        var_fa0 = (f32) (saved_reg_s2->unk2 + temp_a1) - saved_reg_f28;
    } else {
        var_ft2 = (f32) (saved_reg_s0->unk4 + temp_a3) - saved_reg_f30;
        var_ft3 = (f32) (saved_reg_s1->unk4 + temp_a3) - saved_reg_f30;
        var_fa0 = (f32) (saved_reg_s2->unk4 + temp_a3) - saved_reg_f30;
    }
    temp_ft4 = var_fa0 - var_ft3;
    if (((var_ft3 - var_ft2) * var_fv1) < ((var_ft0 - var_fv1) * var_ft2)) {
        if (((temp_ft4 * var_ft0) < ((var_ft1 - var_ft0) * var_ft3)) && (((var_ft2 - var_fa0) * var_ft1) < ((var_fv1 - var_ft1) * var_fa0))) {
            return 1;
        }
        /* Duplicate return node #13. Try simplifying control flow for better match */
        return 0;
    }
    if (!((temp_ft4 * var_ft0) <= ((var_ft1 - var_ft0) * var_ft3)) && !(((var_ft2 - var_fa0) * var_ft1) <= ((var_fv1 - var_ft1) * var_fa0))) {
        return 1;
    }
    return 0;
}

f32 func_80059948(Unk *arg0, Unk *arg2) {
    Unk *saved_reg_s0;
    return ((arg0->unk0 - (f32) ((Unk *)(s32)(saved_reg_s0->unk0 + (s32)M2C_ERROR(/* Read from unset register $t5 */)))->unk4) * arg2->unk0) + ((arg0->unk4 - (f32) ((Unk *)(s32)(saved_reg_s0->unk2 + (s32)M2C_ERROR(/* Read from unset register $t5 */)))->unk8) * arg2->unk4) + ((arg0->unk8 - (f32) ((Unk *)(s32)(saved_reg_s0->unk4 + (s32)M2C_ERROR(/* Read from unset register $t5 */)))->unkC) * arg2->unk8);
}

/* nonmatching func_800599C0: Unable to determine jump table for jr instruction at func_80 */
void func_800599C0(void) { /* nonmatching — see asm stub */ }

s32 func_80059CFC(Unk *arg0, Unk *arg1) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 temp_ft1;
    f32 temp_ft2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    s16 *var_t0;
    s16 temp_t4;
    s32 var_s3;
    Unk *temp_v0;
    Unk *temp_v0_2;
    Unk *temp_v0_3;
    Unk *temp_v1;

    var_s3 = 0;
    var_t0 = arg1->unk1C;
    if (arg1->unk18 != 0) {
        do {
            temp_t4 = *var_t0;
            if (temp_t4 >= 0) {
                if (*(s32*)((char*)(s32)M2C_ERROR(/* Read from unset register $t3 */) + ((Unk*)((char*)(s32)M2C_ERROR(/* Read from unset register $t2 */) + temp_t4 * 0xC))->unk4 * 0x10) <= 0) {

                }
                temp_fv0 = func_80059948(arg0->unk0, NULL);
                if (temp_fv0 < 0.0f) {
                    temp_fv0_2 = func_80059948(arg0->unk4, NULL);
                    temp_v0 = arg0->unk0;
                    if (!(temp_fv0_2 < 0.0f)) {
                        temp_v1 = arg0->unk4;
                        temp_ft1 = temp_fv0 / (temp_fv0 - temp_fv0_2);
                        temp_fv1 = temp_v0->unk0;
                        temp_ft2 = temp_v0->unk4;
                        temp_fa0 = temp_v0->unk8;
                        temp_fs3 = temp_fv1 - ((temp_fv1 - temp_v1->unk0) * temp_ft1);
                        temp_fs4 = temp_ft2 - ((temp_ft2 - temp_v1->unk4) * temp_ft1);
                        temp_fa1 = (temp_fa0 - temp_v1->unk8) * temp_ft1;
                        temp_v0_2 = arg0->unk0;
                        if (func_80059774(temp_fa0, temp_fa1) != 0) {
                            temp_v0_2->unk0 = temp_fs3;
                            temp_v0_2->unk4 = temp_fs4;
                            temp_v0_2->unk8 = (f32) (temp_fa0 - temp_fa1);
                            temp_v0_3 = arg0->unkC;
                            temp_v0_3->unk0 = (f32) (temp_v0_3->unk0 + (s32)M2C_ERROR(/* Read from unset register $a2 */));
                            temp_v0_3->unk4 = (f32) ((Unk *)(s32)(temp_v0_3->unk4 + (s32)M2C_ERROR(/* Read from unset register $a2 */)))->unk4;
                            temp_v0_3->unk8 = (f32) ((Unk *)(s32)(temp_v0_3->unk8 + (s32)M2C_ERROR(/* Read from unset register $a2 */)))->unk8;
                            var_s3 |= 1;
                        }
                    }
                }
            }
            var_t0 = (s32)M2C_ERROR(/* Read from unset register $t0 */) + 2;
        } while (((s32)M2C_ERROR(/* Read from unset register $t1 */) - 1) != 0);
    }
    return var_s3;
}

s32 func_80059F34(Unk *arg0, Unk *arg1) {
    f32 temp_fa0;
    f32 temp_fs1;
    f32 temp_fv0;
    s16 *var_t0;
    s16 temp_t4;
    s32 var_s3;
    Unk *temp_v0;

    var_s3 = 0;
    var_t0 = arg1->unk1C;
    if (arg1->unk18 != 0) {
        do {
            temp_t4 = *var_t0;
            if (temp_t4 >= 0) {
                if (*(s32*)((char*)(s32)M2C_ERROR(/* Read from unset register $t3 */) + ((Unk*)((char*)(s32)M2C_ERROR(/* Read from unset register $t2 */) + temp_t4 * 0xC))->unk4 * 0x10) <= 0) {

                }
                temp_fs1 = func_80059948(arg0->unk0, NULL);
                temp_fv0 = func_80059948(arg0->unk4, NULL);
                if (temp_fv0 < 0.0f) {
                    if (!(temp_fs1 < 0.0f)) {
                        goto block_9;
                    }
                } else if (temp_fs1 < 0.0f) {
block_9:
                    temp_fa0 = ((Unk *)arg0->unk0)->unk8;
                    temp_v0 = arg0->unkC;
                    if (func_80059774(temp_fa0, (temp_fa0 - ((Unk *)arg0->unk4)->unk8) * (temp_fs1 / (temp_fs1 - temp_fv0))) != 0) {
                        temp_v0->unk0 = (f32) (temp_v0->unk0 + (s32)M2C_ERROR(/* Read from unset register $a2 */));
                        temp_v0->unk4 = (f32) ((Unk *)(s32)(temp_v0->unk4 + (s32)M2C_ERROR(/* Read from unset register $a2 */)))->unk4;
                        temp_v0->unk8 = (f32) ((Unk *)(s32)(temp_v0->unk8 + (s32)M2C_ERROR(/* Read from unset register $a2 */)))->unk8;
                        var_s3 |= 1;
                    }
                }
            }
            var_t0 = (s32)M2C_ERROR(/* Read from unset register $t0 */) + 2;
        } while (((s32)M2C_ERROR(/* Read from unset register $t1 */) - 1) != 0);
    }
    return var_s3;
}

s32 func_8005A170(Unk *arg0) {
    func_8005A214(NULL, NULL, 0);
    return (s32)M2C_ERROR(/* Read from unset register $a3 */);
}

void func_8005A214(Unk *arg0, Unk *arg1, s32 arg2) {
    f32 saved_reg_f24;
    f32 saved_reg_f26;
    f32 saved_reg_f28;
    f32 saved_reg_f30;
    s32 var_s0;

    var_s0 = (s32)M2C_ERROR(/* Read from unset register $t0 */) - 0xFE00;
    if (var_s0 >= 0) {
        if (var_s0 != 0) {
            do {
                var_s0 -= 1;
                func_8005A33C();
            } while (var_s0 != 0);
        }
        return;
    }
    func_8005A47C(arg0->unk44 + ((s32)M2C_ERROR(/* Read from unset register $t0 */) * 2));
    if ((saved_reg_f24 < saved_reg_f28) || (saved_reg_f24 < saved_reg_f30)) {
        func_8005A214(NULL, NULL, 0);
    }
    if (!(saved_reg_f26 < saved_reg_f28) || !(saved_reg_f26 < saved_reg_f30)) {
        func_8005A214(NULL, NULL, 0);
    }
}

void func_8005A2FC(void) {

}

/* nonmatching func_8005A33C: Cannot find branch target .L8005A700 */
s32 func_8005A33C(void) { /* nonmatching — see asm stub */ return 0; }

/* nonmatching func_8005A47C: Unable to determine jump table for jr instruction */
s32 func_8005A47C(s32 arg0) { /* nonmatching — see asm stub */ (void)arg0; return 0; }

void func_8005A70C(void) {
    Unk *saved_reg_s1;
    Unk *saved_reg_s3;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_ft2;
    f32 var_ft3;
    f32 var_ft4;
    f32 var_ft5;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_t1_4;
    u8 temp_t0;

    temp_t0 = saved_reg_s1->unk3;
    if (temp_t0 & 0x80) {
        temp_t1 = saved_reg_s3->unk8;
        var_ft2 = (f32) (M2C_ERROR(/* Read from unset register $t7 */)->unk2 + temp_t1) - (s32)M2C_ERROR(/* Read from unset register $f4 */);
        var_ft3 = (f32) (M2C_ERROR(/* Read from unset register $t8 */)->unk2 + temp_t1) - (s32)M2C_ERROR(/* Read from unset register $f4 */);
        var_fa0 = (f32) (M2C_ERROR(/* Read from unset register $t9 */)->unk2 + temp_t1) - (s32)M2C_ERROR(/* Read from unset register $f4 */);
    } else {
        temp_t1_2 = saved_reg_s3->unk4;
        var_ft2 = (f32) ((s32)M2C_ERROR(/* Read from unset register $t7 */) + temp_t1_2) - (s32)M2C_ERROR(/* Read from unset register $f2 */);
        var_ft3 = (f32) ((s32)M2C_ERROR(/* Read from unset register $t8 */) + temp_t1_2) - (s32)M2C_ERROR(/* Read from unset register $f2 */);
        var_fa0 = (f32) ((s32)M2C_ERROR(/* Read from unset register $t9 */) + temp_t1_2) - (s32)M2C_ERROR(/* Read from unset register $f2 */);
    }
    if (temp_t0 & 0x40) {
        temp_t1_3 = saved_reg_s3->unk8;
        var_fa1 = (f32) (M2C_ERROR(/* Read from unset register $t7 */)->unk2 + temp_t1_3) - (s32)M2C_ERROR(/* Read from unset register $f4 */);
        var_ft4 = (f32) (M2C_ERROR(/* Read from unset register $t8 */)->unk2 + temp_t1_3) - (s32)M2C_ERROR(/* Read from unset register $f4 */);
        var_ft5 = (f32) (M2C_ERROR(/* Read from unset register $t9 */)->unk2 + temp_t1_3) - (s32)M2C_ERROR(/* Read from unset register $f4 */);
    } else {
        temp_t1_4 = saved_reg_s3->unkC;
        var_fa1 = (f32) (M2C_ERROR(/* Read from unset register $t7 */)->unk4 + temp_t1_4) - (s32)M2C_ERROR(/* Read from unset register $f6 */);
        var_ft4 = (f32) (M2C_ERROR(/* Read from unset register $t8 */)->unk4 + temp_t1_4) - (s32)M2C_ERROR(/* Read from unset register $f6 */);
        var_ft5 = (f32) (M2C_ERROR(/* Read from unset register $t9 */)->unk4 + temp_t1_4) - (s32)M2C_ERROR(/* Read from unset register $f6 */);
    }
    if (!(temp_t0 & 0x20)) {
        if (!(((var_ft4 - var_fa1) * var_ft2) < ((var_ft3 - var_ft2) * var_fa1)) && !(((var_ft5 - var_ft4) * var_ft3) < ((var_fa0 - var_ft3) * var_ft4)) && !(((var_fa1 - var_ft5) * var_fa0) < ((var_ft2 - var_fa0) * var_ft5))) {

        }
    } else if (!(((var_ft4 - var_fa1) * var_ft2) < ((var_ft3 - var_ft2) * var_fa1)) || !(((var_ft5 - var_ft4) * var_ft3) < ((var_fa0 - var_ft3) * var_ft4)) || !(((var_fa1 - var_ft5) * var_fa0) < ((var_ft2 - var_fa0) * var_ft5))) {

    }
}

void func_8005A900(void) {

}
