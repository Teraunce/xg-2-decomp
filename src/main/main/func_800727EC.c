#include "ultra64.h"
void func_80061A9C(s8*, s8, s32);                       /* extern */
u16 func_80063730(s32);                             /* extern */
void sfxPlay(u16);                               /* extern */
s32 sfxGetEntry(s32);                             /* extern */
s32 func_80070560(u8*, s32);                        /* extern */
s32 func_80070F50(s32, s32, s32, s32, s32, s32, s32);     /* extern */
void func_800716E4(s32, s32);                       /* extern */
s32 func_80072340(s32, s32, s32);                     /* extern */
s32 contPakWriteNote(Unk*, s32, u8, s32, s32, char*);     /* extern */
s32 func_8008AD98(void *, s32, void *);              /* extern */
s32 contPakReadNote(void *, u16, s32, s32, s32, s32*); /* extern */
extern u16 gContPakNoteCode;
extern s32 gGameID;
extern s32 D_80093EC8;
extern s32 D_80093ECC;
extern Unk D_801887D0;
extern s32 D_80188940;

void func_800727EC(s32 arg0, s32 arg1, s32 (*arg2)(s32, s32)) {
    s32 sp40;
    s32 sp20;
    Unk *var_v0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    Unk *temp_s0;
    char *temp_s0_2;

    D_80188940 = 0;
    var_v0 = &D_801887D0;
loop_1:
    var_v0->unk168 = 1;
    sp40 = -1;
    temp_s0 = (arg1 * 4) + var_v0;
    if ((temp_s0->unk31C != 2) || (temp_s0->unk34C != 0)) {
        func_800716E4(arg1, 2);
        if (temp_s0->unk31C != 2) {
            var_v0->unk168 = 0;
        }
    }
    if (D_801887D0.unk168 != 0) {
        temp_v0 = contPakReadNote((arg1 * 0x68) + (&D_801887D0 + 0x17C), gContPakNoteCode, gGameID, &D_80093ECC, &D_80093EC8, &sp40);
        if (temp_v0 != 0) {
            if (temp_v0 == 5) {
                sp40 = -1;
                goto block_12;
            }
            var_v0 = &D_801887D0;
            if (func_80072340(temp_v0, arg1, -1) == 0) {
                D_801887D0.unk168 = 0;
                goto block_12;
            }
            goto loop_1;
        }
block_12:
        if ((D_801887D0.unk168 != 0) && (sp40 >= 0)) {
            temp_s0_2 = (arg1 * 0x68) + (&D_801887D0 + 0x17C);
            var_v0 = &D_801887D0;
            if (func_80072340(func_8008AD98(temp_s0_2, sp40, &sp20), arg1, -1) == 0) {
                if (D_801887D0.unk168 != 0) {
                    if (sp20 <= 0) {
                        var_v0 = &D_801887D0;
                        if (func_80070F50(0x35, arg1, 0x52, 0x65, 0, 0, 0) != 0) {
                            D_801887D0.unk168 = 0;
                        } else {
                            goto loop_1;
                        }
                    } else {
                        temp_v0_2 = func_80063730(arg1);
                        temp_s2 = temp_v0_2 & 0xFFFF;
                        func_80061A9C(sfxGetEntry(temp_s2), 0, sp20);
                        temp_v0_3 = sfxGetEntry(temp_s2);
                        if (func_80072340(contPakWriteNote(temp_s0_2, sp40, 0, 0, sp20, temp_v0_3), arg1, -1) == 0) {
                            if ((D_801887D0.unk168 != 0) && ((void *)((temp_s1 = sp20 - 4, *(f32*)((char*)((s32)(temp_v0_3 + sp20)) - 4)!= func_80070560(temp_v0_3, temp_s1))) || (arg2(temp_v0_3, temp_s1) == 0))) {
                                if (func_80070F50(0x35, arg1, 0x52, 0x65, 0, 0, 0) != 0) {
                                    D_801887D0.unk168 = 0;
                                    goto block_27;
                                }
                                goto block_26;
                            }
block_27:
                            sfxPlay(temp_v0_2 & 0xFFFF);
                        } else {
block_26:
                            sfxPlay(temp_s2);
                            var_v0 = (void *)0x80190000;
                            goto loop_1;
                        }
                    }
                }
            } else {
                goto loop_1;
            }
        }
    }
    D_801887D0.unk160 = (s32) (D_801887D0.unk160 - 1);
}
