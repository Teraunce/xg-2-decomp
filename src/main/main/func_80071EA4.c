#include "ultra64.h"
s32 func_80061AEC(void *, void *, s32);                  /* extern */
s32 func_80070F50(s32, s32, s32, s32, s32, s32, s32);     /* extern */
void func_800716E4(s32, s32);                       /* extern */
s32 func_8008AD98(void *, s32, void *);              /* extern */
s32 func_8008B5B8(void *, s32*);                  /* extern */
extern u16 gContPakNoteCode;
extern s32 gGameID;
extern s32 D_80093ECC;
extern Unk D_801887D0;
extern s32 D_80188940;

void func_80071EA4(s32 arg0, s32 arg1) {
    Unk *var_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_s2;
    s32 var_s6;
    s8 var_s2_2;
    Unk *temp_s0;
    Unk *temp_s0_2;
    char *temp_s3;
    Unk *temp_s7;
    Unk *var_v0;

    D_80188940 = 0;
loop_1:
loop_2:
    D_801887D0.unk168 = 1;
    var_s2 = 0xF;
    var_v0 = &D_801887D0 + 0x294;
    do {
        var_v0->unk38C = 0;
        var_s2 -= 1;
        var_v0 -= 0x2C;
    } while (var_s2 >= 0);
    temp_s0 = (arg1 * 4) + &D_801887D0;
    if ((temp_s0->unk31C != 2) || (temp_s0->unk34C != 0)) {
        func_800716E4(arg1, 2);
        if (temp_s0->unk31C != 2) {
            D_801887D0.unk168 = 0;
        }
    }
    if (D_801887D0.unk168 != 0) {
        temp_v0 = func_8008B5B8((arg1 * 0x68) + (&D_801887D0 + 0x17C), &D_801887D0 + 0x64C);
        if (temp_v0 != 0) {
            if (temp_v0 == 2) {
                temp_s0_2 = (arg1 * 4) + &D_801887D0;
                temp_s0_2->unk31C = 6;
                func_800716E4(arg1, 2);
                if (temp_s0_2->unk31C != temp_v0) {
                    D_801887D0.unk168 = 0;
                } else {
                    goto loop_2;
                }
            } else if (func_80070F50(0x3C, arg1, 0x52, 0x31, 0, 0, 0) != 0) {
                ((arg1 * 4) + &D_801887D0)->unk31C = 3;
                D_801887D0.unk168 = 0;
            } else {
                goto loop_1;
            }
        }
    }
    var_s2_2 = 0;
    temp_s7 = (arg1 * 4) + &D_801887D0;
    var_s1 = &D_801887D0;
    var_s6 = 0;
loop_17:
    if (D_801887D0.unk168 != 0) {
        temp_s3 = var_s6 + (&D_801887D0 + 0x398);
        temp_v0_2 = func_8008AD98((arg1 * 0x68) + (&D_801887D0 + 0x17C), var_s2_2, temp_s3);
        switch (temp_v0_2) {                        /* irregular */
        case 0:
            var_a0 = 0;
            if (var_s1->unk3A0 == gContPakNoteCode) {
                if ((var_s1->unk39C == gGameID) && (var_s1->unk3A2 == 0)) {
                    var_a0 = func_80061AEC(temp_s3 + 0xE, &D_80093ECC, 0x10) == 0;
                }
            }
            var_s1->unk394 = var_s2_2;
            var_s1->unk390 = var_a0;
            var_s1->unk38C = 1;
            var_s1 += 0x2C;
            var_s6 += 0x2C;
        case 5:
block_35:
            var_s2_2 += 1;
            if (var_s2_2 < 0x10) {
                goto loop_17;
            }
            break;
        case 2:
            temp_s7->unk31C = 6;
            func_800716E4(arg1, 2);
            if (temp_s7->unk31C != temp_v0_2) {
                D_801887D0.unk168 = 0;
                goto block_35;
            }
            goto loop_2;
        default:
            if (func_80070F50(0x3C, arg1, 0x52, 0x31, 0, 0, 0) != 0) {
                temp_s7->unk31C = 3;
                D_801887D0.unk168 = 0;
                goto block_35;
            }
            goto loop_2;
        }
    }
    D_801887D0.unk160 = (s32) (D_801887D0.unk160 - 1);
}
