#include "ultra64.h"
s32 func_80070F50(s32, s32, s32, s32, s32, s32, s32);     /* extern */
s32 func_80071108(s32, s32);                          /* extern */
void func_800716E4(s32, s32);                       /* extern */
s32 func_80072340(s32, s32, s32);                     /* extern */
s32 func_8008AD98(void *, s32, void *);              /* extern */
s32 func_8008B088(void *, u16, s32, s32, s32, s32*); /* extern */
s32 func_8008B5B8(void *, s32*);                   /* extern */
s32 func_8008B708(void *, s32*, s32*);              /* extern */
extern u16 gContPakNoteCode;
extern s32 gGameID;
extern s32 D_80093EC8;
extern s32 D_80093ECC;
extern Unk D_801887D0;
extern s32 D_80188940;

void func_80072550(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 sp20;
    Unk *var_v0;
    Unk *var_v1;
    s32 var_a0;
    s32 temp_v0;
    s32 var_s1;
    Unk *temp_s0;
    char *temp_s0_2;
    char *temp_s0_3;

    D_80188940 = 0;
loop_1:
    var_v0 = &D_801887D0;
loop_2:
    var_v0->unk168 = 1;
    temp_s0 = (arg1 * 4) + var_v0;
    if ((temp_s0->unk31C != 2) || (temp_s0->unk34C != 0)) {
        func_800716E4(arg1, 2);
        if (temp_s0->unk31C != 2) {
            var_v0->unk168 = 0;
        }
    }
    sp40 = 0;
    if ((D_801887D0.unk168 != 0) && ((temp_s0_2 = (arg1 * 0x68) + (&D_801887D0 + 0x17C), var_v0 = &D_801887D0, (func_80072340(func_8008B5B8(temp_s0_2, &sp40), arg1, -1) != 0)) || ((D_801887D0.unk168 != 0) && (var_v0 = &D_801887D0, (func_80072340(func_8008B708(temp_s0_2, &sp44, &sp48), arg1, -1) != 0))))) {
        goto loop_2;
    }
    var_s1 = 0;
    if (D_801887D0.unk168 != 0) {
        temp_s0_3 = (arg1 * 0x68) + (&D_801887D0 + 0x17C);
        if ((func_8008B088(temp_s0_3, gContPakNoteCode, gGameID, &D_80093ECC, &D_80093EC8, &sp4C) == 0) && (func_8008AD98(temp_s0_3, sp4C, &sp20) == 0)) {
            var_s1 = sp20;
            sp48 -= 1;
        }
        if (D_801887D0.unk168 != 0) {
            if (((sp40 + var_s1) < arg2) || (var_v1 = &D_801887D0, ((sp48 < 0x10) == 0))) {
                var_a0 = 0x4E;
                if (sp48 >= 0x10) {
                    var_a0 = 0x4C;
                }
                temp_v0 = func_80070F50(var_a0, arg1, 0x37, 0x49, 0x36, 0, 0);
                if (temp_v0 != 1) {
                    if (temp_v0 < 2) {
                        if (temp_v0 != 0) {
                            var_v1 = &D_801887D0;
                        } else {
                            goto loop_1;
                        }
                    } else if (temp_v0 != 2) {
                        var_v1 = &D_801887D0;
                    } else {
                        ((arg1 * 4) + &D_801887D0)->unk31C = 4;
                        D_801887D0.unk168 = 0;
                        goto block_28;
                    }
                } else {
                    func_80071108(arg1, arg2);
                    var_v0 = (void *)0x80190000;
                    goto loop_2;
                }
            }
        } else {
            goto block_29;
        }
    } else {
block_28:
block_29:
        var_v1 = &D_801887D0;
    }
    var_v1->unk160 = (s32) (var_v1->unk160 - 1);
}
