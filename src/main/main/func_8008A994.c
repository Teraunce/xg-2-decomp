#include "ultra64.h"
s32 func_80088C98(s32, s32, u16, s32, s32);         /* extern */
s32 func_80089A68(void *);                          /* extern */
s32 func_80089E84(Unk*);                          /* extern */
s32 func_80089EF8(s32, s32, u16, u8*);              /* extern */
s32 func_8008A898(void *, u8*, s32, void *);        /* extern */

s32 func_8008A994(Unk *arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4, char *arg5) {
    s32 sp154;
    u8 sp13C;
    s32 sp134;
    s32 sp34;
    u16 sp30;
    s32 sp2C;
    s32 sp28;
    char *sp24;
    s8 sp23;
    u16 sp20;
    s32 temp_t3;
    s32 var_v0;
    u16 temp_t3_2;

    s16 unksp31;
    s16 unksp13B;
    s32 sp13A;
    if ((arg1 >= arg0->unk50) || (arg1 < 0)) {
        return 5;
    }
    if ((arg4 <= 0) || (arg4 & 0x1F)) {
        return 5;
    }
    if ((arg3 < 0) || (arg3 & 0x1F)) {
        return 5;
    }
    if (!(arg0->unk0 & 1)) {
        return 5;
    }
    if (func_80089A68(arg0) == 2) {
        return 2;
    }
    if (arg0->unk65 != 0) {
        arg0->unk65 = 0U;
        sp154 = func_80089E84(arg0);
        if (sp154 != 0) {
            return sp154;
        }
    }
    sp154 = func_80089EF8(arg0->unk4, arg0->unk8, arg0->unk5C + arg1, &sp134);
    if (sp154 != 0) {
        return sp154;
    }
    if (((s32) sp13A < arg0->unk60) || ((s32) (u8) sp13A >= (s32) arg0->unk64) || ((s32) unksp13B <= 0) || ((s32) unksp13B >= 0x80)) {
        if (sp13A == 1) {
            return 5;
        }
        return 3;
    }
    if ((arg2 == 0) && !(sp13C & 2)) {
        return 6;
    }
    sp23 = 0xFF;
    sp2C = arg3 / 32;
    sp30 = sp13A;
    if (sp2C >= 8) {
loop_29:
        sp154 = func_8008A898(arg0, &sp23, &sp34, &sp30);
        if (sp154 != 0) {
            return sp154;
        }
        sp2C -= 8;
        if (sp2C < 8) {
            goto block_32;
        }
        goto loop_29;
    }
block_32:
    temp_t3 = arg4 / 32;
    sp28 = temp_t3;
    sp24 = arg5;
    if (temp_t3 > 0) {
loop_33:
        if (sp2C == 8) {
            sp154 = func_8008A898(arg0, &sp23, &sp34, &sp30);
            if (sp154 != 0) {
                return sp154;
            }
            sp2C = 0;
            goto block_37;
        }
block_37:
        if (arg0->unk65 != (u8) sp30) {
            arg0->unk65 = (u8) sp30;
            sp154 = func_80089E84(arg0);
            if (sp154 != 0) {
                return sp154;
            }
        }
        temp_t3_2 = (unksp31 * 8) + sp2C;
        sp20 = temp_t3_2;
        if (arg2 == 0) {
            var_v0 = func_80089EF8(arg0->unk4, arg0->unk8, temp_t3_2 & 0xFFFF, sp24);
        } else {
            var_v0 = func_80088C98(arg0->unk4, arg0->unk8, sp20, sp24, 0);
        }
        sp154 = var_v0;
        if (sp154 != 0) {
            return sp154;
        }
        sp28 -= 1;
        sp24 += 0x20;
        sp2C += 1;
        if (sp28 <= 0) {
            goto block_46;
        }
        goto loop_33;
    }
block_46:
    if ((arg2 == 1) && !(sp13C & 2)) {
        sp13C |= 2;
        arg0->unk65 = 0U;
        sp154 = func_80089E84(arg0);
        if (sp154 != 0) {
            return sp154;
        }
        sp154 = func_80088C98(arg0->unk4, arg0->unk8, arg0->unk5C + arg1, &sp134, 0);
        if (sp154 != 0) {
            return sp154;
        }
        goto block_52;
    }
block_52:
    return 0;
}
