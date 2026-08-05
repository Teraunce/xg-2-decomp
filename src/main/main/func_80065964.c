#include "ultra64.h"
void func_80065618(u16*, u16*);                        /* extern */
void func_80065694(Unk*, s32);                        /* extern */
void func_80065764(Unk*, s32);                        /* extern */
void func_80065838(u16 *, u8, s32, s32);               /* extern */
extern s32 D_80182E88;
extern s32 D_80182EA4;

void func_80065964(u16 *arg0, Unk *arg1, s32 arg2) {
    Unk *var_s1;
    u16 *var_s0;
    Unk *temp_a0;
    Unk *temp_v0;
    u8 *var_v1;
    u8 temp_a1;
    u8 temp_v0_2;
    u8 temp_v1;

    var_s0 = arg0;
    var_s1 = &arg2;
    if (arg1->unk0 != 0) {
        do {
            temp_a0 = arg1;
            temp_a1 = temp_a0->unk0;
            if (temp_a1 == 0x25) {
                arg1 = temp_a0 + 1;
                temp_v1 = temp_a0->unk1;
                if (temp_v1 != 0x66) {
                    if ((s32) temp_v1 < 0x67) {
                        if (temp_v1 != 0x61) {
                            if ((s32) temp_v1 >= 0x62) {
                                if (temp_v1 == 0x64) {
                                    var_s1 += 4;
                                    func_80065694(var_s0, var_s1->unk0 /* FIXME: was ->unk-4 */);
                                    if (*var_s0 != 0) {
                                        do {
                                            var_s0 += 2;
                                        } while (*var_s0 != 0);
                                    }
                                }
                            } else if (temp_v1 == 0) {
                                arg1 = temp_a0;
                            } else if (temp_v1 == temp_a1) {
                                *var_s0 = (u16) temp_v1;
                                goto block_37;
                            }
                        } else {
                            var_s1 += 4;
                            var_v1 = var_s1->unk0 /* FIXME: was ->unk-4 */;
                            if (*var_v1 != 0) {
                                do {
                                    temp_v0_2 = *var_v1;
                                    var_v1 += 1;
                                    *var_s0 = (u16) temp_v0_2;
                                    var_s0 += 2;
                                } while (*var_v1 != 0);
                            }
                        }
                    } else if (temp_v1 != 0x69) {
                        if (temp_v1 == 0x73) {
                            var_s1 += 4;
                            func_80065618(var_s0, var_s1->unk0 /* FIXME: was ->unk-4 */);
                            if (*var_s0 != 0) {
                                do {
                                    var_s0 += 2;
                                } while (*var_s0 != 0);
                            }
                        }
                    } else {
                        var_s1 += 4;
                        func_80065764(var_s0, var_s1->unk0 /* FIXME: was ->unk-4 */);
                        if (*var_s0 != 0) {
                            do {
                                var_s0 += 2;
                            } while (*var_s0 != 0);
                        }
                    }
                } else {
                    var_s1 += 8;
                    func_80065838(var_s0, temp_a1, var_s1->unk0 /* FIXME: was ->unk-8 */, var_s1->unk0 /* FIXME: was ->unk-4 */);
                    if (*var_s0 != 0) {
                        do {
                            var_s0 += 2;
                        } while (*var_s0 != 0);
                    }
                }
            } else {
                *var_s0 = (u16) temp_a0->unk0;
block_37:
                var_s0 += 2;
            }
            temp_v0 = arg1;
            arg1 = temp_v0 + 1;
        } while (temp_v0->unk1 != 0);
    }
    *var_s0 = 0;
}

s32 func_80065B44(s32 arg0, s16 arg1, s16 arg2) {
    s16 var_a1;
    s32 var_a3;
    s32 var_v0;
    Unk *temp_v0;
    Unk *var_a0;

    var_a1 = arg1;
    var_a3 = 0;
    if (var_a1 < arg2) {
        var_a0 = (var_a1 * 0x10) + arg0;
        do {
            temp_v0 = var_a0->unk0;
            if (temp_v0 != NULL) {
                var_a3 += (u32) (temp_v0->unk0 * var_a0->unk8) >> 0x10;
            } else {
                var_v0 = D_80182EA4;
                if (var_v0 < 0) {
                    var_v0 += 3;
                }
                var_a3 = var_a3 + 6 + (var_v0 >> 2);
            }
            if (var_a1 < (arg2 - 1)) {
                var_a3 += D_80182E88;
            }
            var_a1 += 1;
            var_a0 += 0x10;
        } while (var_a1 < arg2);
    }
    return var_a3;
}
