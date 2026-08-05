#include "ultra64.h"
s32 func_8008896C(void *, s32, s32, s32*, u8, s32*, s32*); /* extern */
s32 func_80088C98(s32, s32, u16, s32, s32);       /* extern */
s32 func_80089A68(void *);                          /* extern */
s32 func_80089B64(Unk*, Unk*, u8, u8);              /* extern */
s32 func_8008B088(void *, u16, s32, s32, s32, s32*); /* extern */
s32 func_8008B5B8(void *, s32*);                   /* extern */

s32 func_800884E8(Unk *arg0, u16 arg1, s32 arg2, u8 *arg3, u8 *arg4, s32 arg5, s32 *arg6) {
    Unk *sp = (Unk*)0;
    s32 sp274;
    s32 sp270;
    s32 sp26C;
    s32 sp268;
    s32 sp264;
    s32 sp260;
    s32 sp25C;
    s32 sp15C;
    s32 sp5C;
    s16 sp46;
    u16 sp42;
    u16 sp40;
    s32 sp3C;
    u8 sp3B;
    u8 sp3A;
    s32 sp34;
    s32 sp30;
    s8 sp2D;
    u8 sp2C;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_t3;
    s32 temp_t7;
    u8 temp_t9;

    sp268 = 0;
    sp260 = 0;
    sp3A = 0;
    sp34 = 0;
    if ((arg1 == 0) || (arg2 == 0)) {
        goto block_48;
    }
    sp25C = (s32) (arg5 + 0xFF) / 256;
    if (!(arg0->unk0 & 1)) {
        goto block_48;
    }
    if (func_80089A68(arg0) == 2) {
        return 2;
    }
    sp260 = func_8008B088(arg0, arg1, arg2, arg3, arg4, arg6);
    if ((sp260 != 0) && (sp260 != 5)) {
        return sp260;
    }
    if (*arg6 != -1) {
        return 9;
    }
    sp260 = func_8008B5B8(arg0, &sp30);
    if (sp30 < arg5) {
        return 7;
    }
    if (sp25C != 0) {
        sp260 = func_8008B088(arg0, 0U, 0, 0, 0, arg6);
        if ((sp260 != 0) && (sp260 != 5)) {
            return sp260;
        }
        if (*arg6 == -1) {
            return 8;
        }
        sp3B = 0;
        if ((s32) arg0->unk64 > 0) {
loop_21:
            sp260 = func_80089B64(arg0, &sp15C, 0, sp3B);
            if (sp260 != 0) {
                return sp260;
            }
            sp260 = func_8008896C(arg0, &sp15C, sp25C, &sp274, (s32) sp3B, &sp270, &sp26C);
            if (sp260 != 0) {
                return sp260;
            }
            if (sp274 != -1) {
                if (sp34 == 0) {
                    sp2D = (s8) sp274;
                    sp2C = sp3B;
                    goto block_30;
                }
                (sp + (sp268 * 2))->unk5C = sp3B;
                (sp + (sp268 * 2))->unk5D = (s8) sp274;
                sp260 = func_80089B64(arg0, &sp5C, 1, sp3A);
                if (sp260 != 0) {
                    return sp260;
                }
block_30:
                sp264 = 0;
                do {
                    temp_t7 = sp264 * 2;
                    ((Unk *)(sp + temp_t7))->unk5C = (u16) ((Unk *)(sp + temp_t7))->unk15C;
                    temp_t1 = sp264 + 1;
                    sp264 = temp_t1;
                } while (temp_t1 < 0x80);
                sp34 += 1;
                sp268 = sp26C;
                sp3A = sp3B;
                if (sp270 < sp25C) {
                    sp25C -= sp270;
                    goto block_35;
                }
                sp25C = 0;
                goto block_36;
            }
block_35:
            temp_t9 = sp3B + 1;
            sp3B = temp_t9;
            if ((temp_t9 & 0xFF) >= (s32) arg0->unk64) {
                goto block_36;
            }
            goto loop_21;
        }
block_36:
        if ((sp25C > 0) || (sp274 == -1)) {
            return 3;
        }
        (sp + (sp268 * 2))->unk5C = sp3B;
        (sp + (sp268 * 2))->unk5D = (s8) sp274;
        sp260 = func_80089B64(arg0, &sp5C, 1, sp3A);
        if (sp260 != 0) {
            return sp260;
        }
        sp46 = 0;
        sp264 = 0;
        sp42 = (u16) sp2C;
        sp40 = arg1;
        sp3C = arg2;
        do {
            ((Unk *)(sp + sp264))->unk4C = (u8) *arg3;
            temp_t3 = sp264 + 1;
            sp264 = temp_t3;
            arg3 += 1;
        } while (temp_t3 < 0x10);
        sp264 = 0;
        do {
            ((Unk *)(sp + sp264))->unk48 = (u8) *arg4;
            temp_t2 = sp264 + 1;
            sp264 = temp_t2;
            arg4 += 1;
        } while (temp_t2 < 4);
        sp260 = func_80088C98(arg0->unk4, arg0->unk8, *arg6 + arg0->unk5C, &sp3C, 0);
        if (sp260 != 0) {
            return sp260;
        }
        return sp260;
    }
block_48:
    return 5;
}
