#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8005D9BC (initial). */

s16 func_80082418(Unk*, Unk*);                        /* extern */
void func_800824B8(Unk*, s16);                          /* extern */
void func_80082508(Unk*, s16);                          /* extern */
void func_80082528(void *);                               /* extern */
void func_80082598(char*);                               /* extern */
s32 func_800825E8(char*);                             /* extern */
void func_80082608(void *, f32);                          /* extern */
void func_80082668(void *, s16, s32);                      /* extern */
void func_80082698(void *, s16);                          /* extern */
void func_800826F8(void *, s8);                           /* extern */
void func_80082758(void *, s8);                           /* extern */
extern f32 D_8004BE20;
extern f32 D_8004BE24;
extern f32 D_8004BE28;
extern f32 D_8004BE2C;
extern f64 D_8004BE30;
extern f64 D_8004BE38;
extern f64 D_8004BE40;
extern f32 D_8004BE48;
extern s32 D_800927F0;
extern s32 D_80092828;
extern s32 D_8009282C;
extern s32 D_80092830;
extern s32 D_80092834;
extern s32 D_80092838;
extern s32 D_8009283C;
extern s32 D_80092844;
extern s32 D_80092848;
extern s32 D_800928DC;
extern s32 D_80092A00;
extern s32 D_801808DC;
extern s32 D_80180908;
extern s32 D_80180B38;
extern s32 D_801839A4;

void func_8005D178(void) {
    u8 sp10;
    Unk *var_s0;
    Unk *var_s0_2;
    Unk *var_s0_3;
    Unk *var_v1;
    Unk *var_v1_2;
    Unk *var_v1_3;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv1;
    f64 temp_fs0;
    f64 temp_fs1;
    f64 temp_fs2;
    f64 var_ft0;
    f64 var_ft0_2;
    f64 var_fv1_2;
    f64 var_fv1_3;
    f64 var_fv1_4;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1;
    s16 var_a1;
    s32 temp_a0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s2_3;
    s32 var_s3;
    s32 var_s3_2;
    s32 var_s3_3;
    s32 var_s3_4;
    s32 var_s3_5;
    s32 sp;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_7;
    s32 var_v0_8;
    u16 temp_v1_5;
    u8 *temp_s1_2;
    u8 *temp_s1_3;
    u8 *var_a2;
    u8 *var_v0;
    u8 temp_s2;
    u8 var_a1_2;
    u8 var_a1_3;
    Unk *temp_s1;
    Unk *var_v0_6;

    var_s3 = 0;
    var_v0 = &sp10;
    do {
        var_s3 += 1;
        *var_v0 = (D_80092838 != 0) * 4;
        var_v0 = &(&sp10)[var_s3];
    } while (var_s3 < 0x1C);
    D_80092838 = 0;
    var_s3_2 = 0;
    var_s0 = &D_80180908;
    do {
        temp_v0 = var_s0->unk4;
        if (temp_v0 != 1) {
            if (temp_v0 != 3) {
                var_s3_2 += 1;
            } else {
                goto block_7;
            }
        } else {
block_7:
            func_80082508(D_800927F0, var_s0->unk12);
            var_s3_2 += 1;
            if (func_800825E8(D_800927F0) == 0) {
                func_800824B8(D_800927F0, var_s0->unk12);
                var_s0->unk4 = 0;
                var_s0->unk0 = 0;
                D_80092844 -= 1;
            }
        }
        var_s0 += 0x14;
    } while (var_s3_2 < 0x1C);
    var_s3_3 = D_80092828;
    if (var_s3_3 != D_8009282C) {
        var_v0_2 = var_s3_3 * 4;
        do {
            temp_s1 = ((var_v0_2 + var_s3_3) * 4) + &D_80180B38;
            temp_v1 = temp_s1->unk4;
            if (temp_v1 != 1) {
                if (temp_v1 >= 2) {
                    if (temp_v1 != 2) {
                        if (temp_v1 == 3) {
                            var_s2 = 0;
                            var_v1 = &D_80180908;
loop_59:
                            if (var_v1->unk0 != temp_s1->unk0) {
                                var_s2 += 1;
                                var_v1 += 0x14;
                                if (var_s2 < 0x1C) {
                                    goto loop_59;
                                }
                            } else if (var_v1->unk4 == 1) {
                                temp_s1_2 = &(&sp10)[var_s2];
                                if (!(*temp_s1_2 & 1)) {
                                    func_80082508(D_800927F0, var_v1->unk12);
                                    func_80082598(D_800927F0);
                                }
                                *temp_s1_2 = 0;
                                var_v1->unk4 = 3;
                            }
                            goto block_67;
                        }
                        var_s3_3 += 1;
                    } else {
                        var_s2_2 = 0;
                        var_a2 = &sp10;
                        var_v1_2 = &D_80180908;
loop_28:
                        if (var_v1_2->unk0 != temp_s1->unk0) {
                            var_a2 += 1;
                            var_s2_2 += 1;
                            var_v1_2 += 0x14;
                            if (var_s2_2 >= 0x1C) {
                                var_s3_3 += 1;
                            } else {
                                goto loop_28;
                            }
                        } else {
                            if (var_v1_2->unk4 == 1) {
                                if (D_8004BE20 < fabsf(var_v1_2->unk8 - temp_s1->unk8)) {
                                    *var_a2 |= 2;
                                    temp_fv1 = var_v1_2->unk8;
                                    temp_fv0 = temp_s1->unk8;
                                    if (!(temp_fv0 < temp_fv1)) {
                                        temp_fv0_2 = temp_fv0 - temp_fv1;
                                        if (D_8004BE24 <= temp_fv0_2) {
                                            var_fv0 = temp_fv1 + D_8004BE24;
                                        } else {
                                            var_fv0 = temp_fv1 + temp_fv0_2;
                                        }
                                    } else {
                                        temp_fv0_3 = temp_fv1 - temp_fv0;
                                        if (D_8004BE24 <= temp_fv0_3) {
                                            var_fv0 = temp_fv1 - D_8004BE24;
                                        } else {
                                            var_fv0 = temp_fv1 - temp_fv0_3;
                                        }
                                    }
                                    *(f32*)((char*)var_v1_2 + 8) = var_fv0;
                                }
                                if (var_v1_2->unkC != temp_s1->unkC) {
                                    *var_a2 |= 4;
                                    temp_a0 = var_v1_2->unkC;
                                    temp_v1_2 = temp_s1->unkC;
                                    if (temp_v1_2 >= temp_a0) {
                                        temp_v1_3 = temp_v1_2 - temp_a0;
                                        var_v0_3 = temp_a0 + temp_v1_3;
                                        if (temp_v1_3 >= 0x2000) {
                                            var_v0_3 = temp_a0 + 0x2000;
                                        }
                                    } else {
                                        temp_v1_4 = temp_a0 - temp_v1_2;
                                        var_v0_3 = temp_a0 - temp_v1_4;
                                        if (temp_v1_4 >= 0x2000) {
                                            var_v0_3 = temp_a0 - 0x2000;
                                        }
                                    }
                                    var_v1_2->unkC = var_v0_3;
                                }
                                if (var_v1_2->unk10 != temp_s1->unk10) {
                                    *var_a2 |= 8;
                                    var_v1_2->unk10 = (u8) temp_s1->unk10;
                                }
                                if (var_v1_2->unk11 != temp_s1->unk11) {
                                    *var_a2 |= 0x10;
                                    var_v1_2->unk11 = (u8) temp_s1->unk11;
                                }
                            }
                            goto block_67;
                        }
                    }
                } else {
                    goto block_67;
                }
            } else {
                var_s2_3 = 0;
                var_v1_3 = &D_80180908;
loop_20:
                if (var_v1_3->unk4 != 0) {
                    var_s2_3 += 1;
                    var_v1_3 += 0x14;
                    if (var_s2_3 >= 0x1C) {
                        var_s3_3 += 1;
                    } else {
                        goto loop_20;
                    }
                } else {
                    temp_v0_2 = func_80082418(D_800927F0, ((Unk*)(s32)(D_801808DC + (temp_s1->unk6 * 4)))->unk10);
                    if (temp_v0_2 >= 0) {
                        var_v1_3->unk0 = (s32) temp_s1->unk0;
                        var_v1_3->unk4 = (s32) temp_s1->unk4;
                        var_v1_3->unk8 = (f32) temp_s1->unk8;
                        var_v1_3->unkC = (s32) temp_s1->unkC;
                        var_v1_3->unk10 = (s32) temp_s1->unk10;
                        var_v1_3->unk12 = temp_v0_2;
                        (&sp10)[var_s2_3] = 1;
                        D_80092844 += 1;
                    }
block_67:
                    var_s3_3 += 1;
                }
            }
            if (var_s3_3 >= 0x80) {
                var_s3_3 = 0;
            }
            var_v0_2 = var_s3_3 * 4;
        } while (var_s3_3 != D_8009282C);
    }
    D_80092828 = var_s3_3;
    if (D_8009283C != 0) {
        var_s3_4 = 0;
        var_s0_2 = &D_80180908;
        do {
            if (var_s0_2->unk4 == 1) {
                temp_s1_3 = &(&sp10)[var_s3_4];
                if (!(*temp_s1_3 & 1)) {
                    func_80082508(D_800927F0, var_s0_2->unk12);
                    func_80082598(D_800927F0);
                }
                *temp_s1_3 = 0;
                var_s0_2->unk4 = 3;
            }
            var_s3_4 += 1;
            var_s0_2 += 0x14;
        } while (var_s3_4 < 0x1C);
        D_8009283C = 0;
    }
    sp = 0;
    var_s3_5 = 0;
    var_s0_3 = &D_80180908;
    temp_fs4 = D_8004BE28;
    temp_fs3 = D_8004BE2C;
    temp_fs2 = D_8004BE30;
    temp_fs1 = D_8004BE38;
    temp_fs0 = D_8004BE40;
    do {
        temp_s2 = ((Unk*)(s32)(sp + var_s3_5))->unk10;
        if (var_s0_3->unk4 != 1) {
            var_s3_5 += 1;
        } else if (temp_s2 == 0) {
            var_s3_5 += 1;
        } else {
            func_80082508(D_800927F0, var_s0_3->unk12);
            var_v0_4 = temp_s2 & 5;
            if (temp_s2 & 3) {
                temp_fv1_2 = var_s0_3->unk8 * (f32) *(((var_s0_3->unk6 + 1) * 2) + &D_800928DC);
                var_fv0_2 = temp_fv1_2 * temp_fs4;
                if (!(var_fv0_2 <= temp_fs3)) {
                    var_fv0_2 = temp_fs3;
                }
                if (var_fv0_2 <= D_8004BE48) {
                    var_fv1 = D_8004BE48;
                } else {
                    var_fv1 = temp_fv1_2 * temp_fs4;
                    if (!(var_fv1 <= temp_fs3)) {
                        var_fv1 = temp_fs3;
                    }
                }
                func_80082608(D_800927F0, var_fv1);
                var_v0_4 = temp_s2 & 5;
            }
            var_v0_5 = temp_s2 & 9;
            if (var_v0_4 != 0) {
                temp_v1_5 = (u16) var_s0_3->unk6;
                if ((u32) (temp_v1_5 - 0x6A) < 0x22U) {
                    var_fv1_2 = (f64) D_80092834 * ((f64) var_s0_3->unkC * temp_fs2);
                    var_v0_6 = (s16) temp_v1_5 + &D_80092A00;
                    goto block_97;
                }
                if (((u32) ((temp_v1_5 - 0x18) & 0xFFFF) < 2U) || ((u32) ((temp_v1_5 - 0xE) & 0xFFFF) < 2U) || ((s16) temp_v1_5 == 0x10)) {
                    var_fv1_2 = (f64) D_801839A4 * ((f64) var_s0_3->unkC * temp_fs2);
                    var_v0_6 = var_s0_3->unk6 + &D_80092A00;
block_97:
                    var_fv1_3 = var_fv1_2 * (f64) var_v0_6->unk1;
                    var_ft0 = var_fv1_3 * temp_fs1;
                    if (!(var_ft0 <= temp_fs0)) {
                        var_ft0 = temp_fs0;
                    }
                    var_a1 = 0;
                    if (!(var_ft0 <= 0.0)) {
                        goto block_108;
                    }
                } else {
                    var_fv1_3 = (f64) D_80092830 * ((f64) var_s0_3->unkC * temp_fs2) * (f64) ((Unk*)((char*)&D_80092A00 + (s16)temp_v1_5))->unk1;
                    var_ft0_2 = var_fv1_3 * temp_fs1;
                    if (!(var_ft0_2 <= temp_fs0)) {
                        var_ft0_2 = temp_fs0;
                    }
                    var_a1 = 0;
                    if (!(var_ft0_2 <= 0.0)) {
block_108:
                        var_fv1_4 = var_fv1_3 * temp_fs1;
                        if (!(var_fv1_4 <= temp_fs0)) {
                            var_fv1_4 = temp_fs0;
                        }
                        var_a1 = (s16) (s32) var_fv1_4;
                    }
                }
                func_80082698(D_800927F0, var_a1);
                var_v0_5 = temp_s2 & 9;
            }
            var_v0_7 = temp_s2 & 0x11;
            if (var_v0_5 != 0) {
                var_a1_2 = 0x7F;
                if (var_s0_3->unk10 >= 0) {
                    var_a1_2 = (u8) var_s0_3->unk10;
                    if ((s32) var_a1_2 > 0) {
                        if (var_a1_2 & 0x80) {
                            var_a1_2 = 0x7F;
                        }
                    } else {
                        var_a1_2 = 0;
                    }
                }
                func_800826F8(D_800927F0, var_a1_2);
                var_v0_7 = temp_s2 & 0x11;
            }
            var_v0_8 = temp_s2 & 1;
            if (var_v0_7 != 0) {
                var_a1_3 = 0x7F;
                if (var_s0_3->unk11 >= 0) {
                    var_a1_3 = (u8) var_s0_3->unk11;
                    if ((s32) var_a1_3 > 0) {
                        if (var_a1_3 & 0x80) {
                            var_a1_3 = 0x7F;
                        }
                    } else {
                        var_a1_3 = 0;
                    }
                }
                func_80082758(D_800927F0, var_a1_3);
                var_v0_8 = temp_s2 & 1;
            }
            var_s3_5 += 1;
            if (var_v0_8 != 0) {
                func_80082668(D_800927F0, var_s0_3->unk12, *(var_s0_3->unk6 + &D_80092848));
                func_80082528(D_800927F0);
            }
        }
        var_s0_3 += 0x14;
    } while (var_s3_5 < 0x1C);
}

void func_8005D9BC(s32 arg2) {

}
