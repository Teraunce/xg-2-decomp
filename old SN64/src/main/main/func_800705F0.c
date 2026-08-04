#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_800707A8 (initial). */

void func_80061FB4(void *, s32, s32);                         /* extern */
void func_800620CC(void*);                               /* extern */
void func_8006211C(void *);                               /* extern */
s32 func_8006216C(void *);                             /* extern */
s32 func_80062240();                                /* extern */
s32 func_80062278();                                /* extern */
s32 func_8007CE48(Unk*, s32, s32);                       /* extern */
extern s32 D_80093EDC;
extern s32 D_80093EE0;
extern s32 D_80093EE4;
extern s32 D_80093EF8;
extern s32 D_800E412C;
extern s32 D_800E4220;
extern s32 D_8017C948;
extern s32 D_801887B8;
extern Unk D_801887D0;

void func_800705F0(s32 arg0) {
    char *var_a0;
    char *var_s0;
    s32 temp_v0;
    s32 temp_v1;

    if ((D_801887D0.unk160 < 0) || (D_801887D0.unk16C != 0)) {
        func_800620CC(func_80062240());
        if (D_801887D0.unk178 != 0) {
            func_8006211C((void*)(s32)D_801887D0.unk178);
        }
        if (D_801887D0.unk174 != 0) {
            ((void(*)(s32, s32))(s32)D_801887D0.unk174)(arg0, D_801887D0.unk168);
        }
        D_801887D0.unk16C = 1;
        return;
    }
    if ((u32) (*(s32*)((char*)&D_801887D0 + (D_801887D0.unk160 * 0x2C)) - 1) < 7U) {
        if ((D_80093EDC != 0) && (D_80093EE0 != 0)) {
            func_8007CE48(&D_801887B8, &D_8017C948, 0);
        }
    } else {
        temp_v0 = func_80062278();
        if ((temp_v0 == (s32)&D_80093EE4) || (temp_v0 == (s32)&D_800E412C) || (temp_v0 == (s32)&D_800E4220)) {
            temp_v1 = *(s32*)((char*)&D_801887D0 + (D_801887D0.unk160 * 0x2C));
            switch (temp_v1) {                      /* irregular */
            case 10:
                var_s0 = &D_800E412C;
                var_a0 = &D_800E412C;
                if (func_8006216C(&D_800E412C) != 0) {
block_21:
                    func_8006211C(var_s0);
                } else {
block_20:
                    func_80061FB4(var_a0, -3, 1);
                    return;
                }
                break;
            case 11:
                var_s0 = &D_800E4220;
                var_a0 = &D_800E4220;
                if (func_8006216C(&D_800E4220) == 0) {
                    goto block_20;
                }
                goto block_21;
            }
        }
    }
}

void func_800707A0(void) {

}

s32 func_800707A8(void) {
    return D_80093EF8;
}
