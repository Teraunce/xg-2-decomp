#include "ultra64.h"
s32 func_80061924();                                /* extern */
void osWritebackInvalDCache(u32, s32);                            /* extern */
void osWritebackDCache(u32, s32);                            /* extern */
s32 osRecvMesg(Unk*, s32*, s32);                         /* extern */
void osSetEventMesg(s32, s32, s32);                      /* extern */
s32 func_80087BC8(s32);                               /* extern */
void func_80087C4C(s32);                               /* extern */
s32 func_8008C898(void *);                             /* extern */
s32 func_8008CA00(void *);                             /* extern */
s32 contPakBuildMap(s32, Unk*, s32);                   /* extern */
extern s32 D_800925C8;
extern s32 D_80093EFC;
extern s32 D_80093F00;
extern s32 gInitStateFlags;
extern s32 D_80093F08;
extern s32 D_80173C28;
extern s32 D_8017C890;
extern s32 D_8017C940;
extern s32 D_80182EA8;
extern char *D_80188770;
extern s32 D_801887A0;
extern s32 D_801887D0;
extern s32 D_8018894C;
extern s32 D_80188E24;
extern s32 D_80188E28;
extern s32 D_8018AD28;
extern s32 D_80192860;

void func_80072E00(s32 arg0) {
    s32 sp14;
    s32 sp10;
    char *var_a0;
    Unk *var_s1;
    char *var_s5;
    Unk *var_s7;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 var_a3;
    s32 var_fp;
    s32 var_s0;
    s32 var_s4;
    s32 var_v1;
    s32 var_v1_2;
    u32 var_v0;

    var_fp = 0;
    osSetEventMesg(5, &D_801887A0, &D_8017C890);
    if (arg0 != 0) {
        gInitStateFlags = 1;
    }
    var_s4 = 0;
    var_s1 = &D_801887D0;
    var_s5 = &D_8018894C;
    var_s7 = &D_80192860;
    sp10 = 0;
    sp14 = 0;
    do {
        if (var_s1->unk31C == 5) {
            if ((gInitStateFlags != 0) || (D_800925C8 != 0)) {
                var_s0 = 0;
                if (D_80093F08 == 0) {
                    if (contPakBuildMap(&D_801887A0, var_s5, var_s4) != 0) {
                        var_s1->unk33C = 1;
                    } else {
                        var_s1->unk33C = 0;
                    }
                    var_s1->unk32C = 1;
                    var_s0 = 0;
                }
                do {
                    if (func_8008C898(sp14 + &D_8018894C) != 0) {
                        var_s1->unk33C = 1;
                    }
                    var_s0 += 1;
                } while (var_s0 < 3);
                var_s1 += 4;
            } else {
                temp_v1 = var_s1->unk35C;
                if (temp_v1 <= 0) {
                    var_v1 = 0;
                } else if (arg0 != 0) {
                    var_v1 = 0;
                } else if (D_8017C940 != 0) {
                    var_v1 = 0;
                } else {
                    if (var_s1->unk36C > 0) {
                        var_v0 = func_80061924();
                        var_v1_2 = var_s1->unk36C;
                        goto block_32;
                    }
                    if (temp_v1 >= var_s1->unk37C) {
                        var_v1 = 1;
                    } else {
                        var_v0 = func_80061924();
                        var_v1_2 = var_s1->unk37C - var_s1->unk35C;
block_32:
                        var_v1 = (var_v0 % (u32) var_v1_2) == 0;
                    }
                    var_s1->unk35C = (s32) (var_s1->unk35C - 1);
                }
                if (var_s1->unk33C != 0) {
                    if ((D_80093EFC >= 0xF) && (D_80093F00 == var_s4)) {
                        if (var_fp == 0) {
                            osWritebackDCache(&D_80192860, 0x10);
                            var_fp = 1;
                            func_80087BC8(&D_801887A0);
                            osRecvMesg(&D_801887A0, 0, 1);
                            osWritebackInvalDCache(&D_8018AD28, 0x40);
                            func_80087C4C(&D_80192860);
                        }
                        if ((void *)(((Unk*)((char*)&D_80192860 + sp10))->unk2 & 1) && (contPakBuildMap(&D_801887A0, var_s5, var_s4) == 0)) {
                            var_s1->unk33C = 0;
                            var_s1->unk32C = 1;
                            goto block_71;
                        }
                        if (var_s7->unk2 & 2) {
                            var_s1->unk34C = 1;
                            goto block_72;
                        }
                        var_s1 += 4;
                    } else {
                        goto block_72;
                    }
                } else {
                    if (var_v1 != 0) {
                        if (var_s1->unk32C == 0) {
                            if (func_8008CA00(var_s5) != 0) {
                                var_s1->unk33C = 1;
                            }
                            var_s1->unk32C = 1;
                        }
                    } else if (var_s1->unk32C != 0) {
                        if (func_8008C898(var_s5) != 0) {
                            var_s1->unk33C = 1;
                        } else {
                            var_s1->unk32C = 0;
                        }
                    }
                    goto block_72;
                }
            }
        } else {
            if ((D_80093EFC >= 0xF) && (D_80093F00 == var_s4)) {
                if (var_fp == 0) {
                    osWritebackDCache(&D_80192860, 0x10);
                    var_fp = 1;
                    func_80087BC8(&D_801887A0);
                    osRecvMesg(&D_801887A0, 0, 1);
                    osWritebackInvalDCache(&D_8018AD28, 0x40);
                    func_80087C4C(&D_80192860);
                }
                if (var_s7->unk2 & 2) {
                    var_s1->unk34C = 1;
                }
                if (var_s7->unk2 & 1) {
                    if (var_s1->unk34C == 0) {
                        temp_v0 = var_s1->unk31C;
                        var_a0 = &D_801887A0;
                        if (temp_v0 != 0) {
                            if (temp_v0 == 1) {
                                goto block_67;
                            }
                        } else {
                            goto block_68;
                        }
                    } else {
block_67:
                        var_a0 = &D_801887A0;
block_68:
                        if (contPakBuildMap(var_a0, var_s5, var_s4) == 0) {
                            var_s1->unk32C = 0;
                            var_s1->unk33C = 0;
                            var_s1->unk34C = 0;
                            var_s1->unk35C = 0;
                            var_s1->unk36C = 0;
                            var_s1->unk37C = 0;
                            var_s1->unk31C = 5;
                        } else {
                            var_s1->unk31C = 7;
block_71:
                            var_s1->unk34C = 0;
                        }
                    }
                }
            }
block_72:
            var_s1 += 4;
        }
        var_s5 += 0x68;
        var_s7 += 4;
        var_s4 += 1;
        sp10 += 4;
        sp14 += 0x68;
    } while (var_s4 < 4);
    temp_v0_2 = D_80093EFC + 1;
    D_80093EFC = temp_v0_2;
    var_a3 = 0;
    if (temp_v0_2 >= 0x10) {
        D_80093EFC = 0;
        temp_v0_3 = D_80093F00 + 1;
        D_80093F00 = temp_v0_3;
        if (temp_v0_3 >= 4) {
            D_80093F00 = 0;
        } else {
            var_a3 = 0;
        }
    }
    if ((gInitStateFlags != 0) || (D_800925C8 != 0)) {
        var_a3 = 1;
    }
    D_80093F08 = var_a3;
    osSetEventMesg(5, D_80188770, &D_8017C890);
}

void func_800732D8(Unk *arg0, s32 arg1, s32 arg2) {
    s32 temp_a3;
    s32 var_v0;
    u32 temp_a3_2;
    Unk *temp_a0;

    temp_a3 = arg0->unk560;
    if ((temp_a3 >= 0) && (temp_a3 < D_80173C28) && (arg0->unk450 == 0)) {
        temp_a3_2 = ((Unk*)(s32)((Unk*)((char*)&D_80182EA8 + (temp_a3 * 4)))->unk16F8)->unk4;
        if (temp_a3_2 < 4U) {
            temp_a0 = (Unk*)((char*)&D_801887D0 + (temp_a3_2 * 4));
            if (temp_a0->unk35C < arg1) {
                temp_a0->unk35C = arg1;
                var_v0 = arg1 * 3;
                temp_a0->unk36C = arg2;
                if (var_v0 < 0) {
                    var_v0 += 3;
                }
                temp_a0->unk37C = (s32) (var_v0 >> 2);
            }
        }
    }
}

/* D_80073364: rodata — defined in entry.s */

void func_800733A8(Unk *arg0) {
    Unk *temp_v0;
    Unk *temp_v0_2;

    temp_v0 = (Unk*)(s32)arg0->unk0;
    arg0->unk0 = (s32)(temp_v0 + 8);
    temp_v0->unk0 = 0xE7000000;
    temp_v0->unk4 = 0;
    temp_v0_2 = (Unk*)(s32)arg0->unk0;
    arg0->unk0 = (s32)(temp_v0_2 + 8);
    temp_v0_2->unk0 = 0xE3000C00;
    temp_v0_2->unk4 = 0x80000;
}

void func_800733EC(Unk *arg0, s32 arg1) {
    Unk *temp_v0;
    Unk *temp_v0_2;

    temp_v0 = (Unk*)(s32)arg0->unk0;
    arg0->unk0 = (s32)(temp_v0 + 8);
    temp_v0->unk0 = 0xE7000000;
    temp_v0->unk4 = 0;
    temp_v0_2 = (Unk*)(s32)arg0->unk0;
    arg0->unk0 = (s32)(temp_v0_2 + 8);
    temp_v0_2->unk0 = 0xE3000C00;
    temp_v0_2->unk4 = 0x80000;
    D_80188E24 = 1;
    D_80188E28 = arg1;
}

void func_80073444(s32 arg0, s32 arg1, u16 *arg2, u16 *arg3, u16 *arg4, u16 *arg5) {
    Unk *temp_a0;

    temp_a0 = arg0 + (arg1 * 0x18);
    *arg2 = temp_a0->unk0;
    *arg3 = temp_a0->unk2;
    *arg4 = temp_a0->unk4;
    *arg5 = temp_a0->unk6;
}
