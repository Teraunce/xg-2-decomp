#include "ultra64.h"
void func_80061AC8(s32, s32, u32);                       /* extern */
u16 func_80063730(s32);                             /* extern */
void func_80063878(u16);                               /* extern */
s32 func_800639B0(s32);                             /* extern */
s32 func_80070560(u8*, s32);                        /* extern */
s32 func_800705D0(s32);                               /* extern */
s32 func_80070F50(s32, s32, s32, s32, s32, s32, s32);       /* extern */
void func_800716E4(s32, s32);                       /* extern */
s32 func_80072340(s32, s32, s32);                   /* extern */
s32 func_800884E8(Unk*, u16, s32, u8*, u8*, s32, s32*); /* extern */
s32 func_8008A288(Unk*, u16, s32, s32, s32);      /* extern */
s32 func_8008A994(Unk*, s32, u8, s32, s32, char*);     /* extern */
s32 func_8008AD98(void *, s32, void *);              /* extern */
s32 func_8008B088(void *, u16, s32, s32, s32, s32*); /* extern */
extern u16 D_80093EC0;
extern s32 D_80093EC4;
extern s32 D_80093EC8;
extern s32 D_80093ECC;
extern Unk D_801887D0;
extern s32 D_80188938;
extern s32 D_80188940;

void func_80072AD4(s32 arg0, s32 arg1, s32 arg2, s32 (*arg3)(s32)) {
    u16 sp44;
    s32 sp40;
    s32 sp20;
    s32 temp_s0_2;
    s32 temp_v0_3;
    u16 temp_s0;
    u16 temp_v0_2;
    u32 temp_v0;
    Unk *temp_s0_3;
    char *temp_s0_4;
    Unk *temp_s1;

    temp_v0 = func_800705D0(arg2);
    temp_v0_2 = func_80063730(temp_v0);
    sp44 = temp_v0_2;
    temp_s0 = temp_v0_2 & 0xFFFF;
    func_80061AC8(func_800639B0(temp_s0), 0xDEADBEEF, temp_v0 >> 2);
    temp_s0_2 = func_800639B0(temp_s0);
    temp_s1 = func_800639B0(temp_s0) + temp_v0;
    arg3(temp_s0_2);
    *(s32*)((char*)temp_s1 - 4)= func_80070560(temp_s0_2, temp_v0 - 4);
    D_80188940 = 0;
loop_1:
    D_801887D0.unk168 = 1;
    temp_s0_3 = (arg1 * 4) + &D_801887D0;
    if ((temp_s0_3->unk31C != 2) || (temp_s0_3->unk34C != 0)) {
        func_800716E4(arg1, 2);
        if (temp_s0_3->unk31C != 2) {
            D_801887D0.unk168 = 0;
        }
    }
    if (D_801887D0.unk168 != 0) {
        temp_s0_4 = (arg1 * 0x68) + (&D_801887D0 + 0x17C);
        temp_v0_3 = func_8008B088(temp_s0_4, D_80093EC0, D_80093EC4, &D_80093ECC, &D_80093EC8, &sp40);
        switch (temp_v0_3) {                        /* irregular */
        case 0:
            if (func_80072340(func_8008AD98(temp_s0_4, sp40, &sp20), arg1, temp_v0) == 0) {
                if (D_801887D0.unk168 != 0) {
                    if (sp20 != temp_v0) {
                        if (func_80072340(func_8008A288(temp_s0_4, D_80093EC0, D_80093EC4, &D_80093ECC, &D_80093EC8), arg1, temp_v0) == 0) {
                            if (D_801887D0.unk168 != 0) {
                            case 5:
                                if (func_80072340(func_800884E8(temp_s0_4, D_80093EC0, D_80093EC4, &D_80093ECC, &D_80093EC8, temp_v0, &sp40), arg1, temp_v0) == 0) {
                                    goto block_20;
                                }
                                goto loop_1;
                            }
                            goto block_24;
                        }
                        goto loop_1;
                    }
block_19:
block_20:
                    if (D_801887D0.unk168 != 0) {
                        if (func_80072340(func_8008A994((arg1 * 0x68) + (&D_801887D0 + 0x17C), sp40, 1, 0, temp_v0, func_800639B0(sp44)), arg1, temp_v0) == 0) {
                            if (D_801887D0.unk168 == 0) {
                                goto block_23;
                            }
                        } else {
                            goto loop_1;
                        }
                    } else {
                        goto block_24;
                    }
                } else {
                    goto block_24;
                }
            } else {
                goto loop_1;
            }
            break;
        default:
            if (func_80072340(temp_v0_3, arg1, temp_v0) == 0) {
                D_80188938 = 0;
                goto block_19;
            }
            goto loop_1;
        }
    } else {
block_23:
block_24:
        func_80070F50(0x56, arg1, 0, 0, 0, 0, 0);
    }
    func_80063878(sp44);
    D_801887D0.unk160 = (s32) (D_801887D0.unk160 - 1);
}
