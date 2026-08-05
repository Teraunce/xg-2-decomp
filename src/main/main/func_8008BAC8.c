#include "ultra64.h"
s32 osContPakWrite(s32, s32, u16, s32, s32);       /* extern */
s32 func_8008980C(void *);                          /* extern */
s32 contPakReadNoteDir(void *);                          /* extern */
s32 contPakReadWriteNote(void *, u16 (*)[], s32, u8);        /* extern */
s32 contPakRepairId(Unk*);                          /* extern */
s32 osContPakRead(s32, s32, u16, u8*);            /* extern */
s32 func_8008C18C(void *, void *);                     /* extern */
s32 func_8008C340(void *, u8, void *);                /* extern */

s32 func_8008BAC8(Unk *arg0) {
    Unk *sp = (Unk*)0;
    s32 sp484;
    s32 sp480;
    u16 sp47C;
    s16 sp266;
    s8 sp264;
    u16 sp262;
    u16 sp260;
    s32 sp25C;
    s32 sp38;
    s32 sp34;
    u8 sp33;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    u8 sp23;
    u16 sp20;
    s32 temp_t0;
    s32 temp_t0_2;
    s32 temp_t4;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t8;
    u16 *temp_t7;
    u16 *temp_t9;
    u8 temp_t1;
    u8 temp_t9_2;

    s16 unksp47D;
    u16 sp27C[256];
    u16 sp23C[256];
    u16 sp37C[256];
    s32 subroutine_arg1 = 0;
    sp34 = 0;
    sp480 = contPakReadNoteDir(arg0);
    if (sp480 == 2) {
        sp480 = func_8008980C(arg0);
    }
    if (sp480 != 0) {
        return sp480;
    }
    sp480 = func_8008C18C(arg0, &sp38);
    if (sp480 != 0) {
        return sp480;
    }
    sp484 = 0;
    if (arg0->unk50 > 0) {
loop_7:
        sp480 = osContPakRead(arg0->unk4, arg0->unk8, arg0->unk5C + sp484, &sp25C);
        if (sp480 != 0) {
            return sp480;
        }
        if ((sp260 != 0) && (sp25C != 0)) {
            sp47C = sp262;
            sp2C = 0;
            sp28 = 0;
            sp33 = 0xFF;
            if (((s32) sp47C >= arg0->unk60) && ((s32) (u8) sp47C < (s32) arg0->unk64) && ((s32) unksp47D > 0) && ((s32) unksp47D < 0x80)) {
loop_15:
                if (sp33 != (u8) sp47C) {
                    sp33 = (u8) sp47C;
                    sp480 = contPakReadWriteNote(arg0, (u16 (*)[]) &sp27C[0], 0, (u8) sp47C);
                    if ((sp480 != 0) && (sp480 != 3)) {
                        return sp480;
                    }
                }
                sp2C = func_8008C340(arg0, subroutine_arg1, &sp38) - sp28;
                if ((sp2C != 0) || (sp28 = 1, sp47C = (&sp27C[0])[unksp47D], (((s32) sp47C < arg0->unk60) != 0)) || ((s32) (u8) sp47C >= (s32) arg0->unk64) || ((s32) unksp47D <= 0) || ((s32) unksp47D >= 0x80)) {
                    goto block_24;
                }
                goto loop_15;
            }
block_24:
            if ((sp2C != 0) || (sp47C != 1)) {
                sp260 = 0;
                sp25C = 0;
                sp262 = 0;
                sp264 = 0;
                sp266 = 0;
                if (arg0->unk65 != 0) {
                    arg0->unk65 = 0U;
                    sp480 = contPakRepairId(arg0);
                    if (sp480 != 0) {
                        return sp480;
                    }
                }
                sp480 = osContPakWrite(arg0->unk4, arg0->unk8, arg0->unk5C + sp484, &sp25C, 0);
                if (sp480 != 0) {
                    return sp480;
                }
                sp34 += 1;
                goto block_40;
            }
            goto block_40;
        }
        if ((sp260 != 0) || (sp25C != 0)) {
            sp260 = 0;
            sp25C = 0;
            sp262 = 0;
            sp264 = 0;
            sp266 = 0;
            if (arg0->unk65 != 0) {
                arg0->unk65 = 0U;
                sp480 = contPakRepairId(arg0);
                if (sp480 != 0) {
                    return sp480;
                }
            }
            sp480 = osContPakWrite(arg0->unk4, arg0->unk8, arg0->unk5C + sp484, &sp25C, 0);
            if (sp480 != 0) {
                return sp480;
            }
            sp34 += 1;
            goto block_40;
        }
block_40:
        temp_t0 = sp484 + 1;
        sp484 = temp_t0;
        if (temp_t0 >= arg0->unk50) {
            goto block_41;
        }
        goto loop_7;
    }
block_41:
    sp484 = 0;
    if (arg0->unk50 > 0) {
loop_42:
        sp480 = osContPakRead(arg0->unk4, arg0->unk8, arg0->unk5C + sp484, &sp25C);
        if (sp480 != 0) {
            return sp480;
        }
        if ((sp260 != 0) && (sp25C != 0) && ((s32) sp262 >= (s32) arg0->unk62)) {
            (sp + (sp484 * 2))->unk23C = sp262;
        } else {
            (sp + (sp484 * 2))->unk23C = 0;
        }
        temp_t4 = sp484 + 1;
        sp484 = temp_t4;
        if (temp_t4 >= arg0->unk50) {
            goto block_50;
        }
        goto loop_42;
    }
block_50:
    sp33 = 0;
    if ((s32) arg0->unk64 > 0) {
loop_51:
        sp480 = contPakReadWriteNote(arg0, (u16 (*)[]) &sp27C[0], 0, sp33);
        if ((sp480 != 0) && (sp480 != 3)) {
            return sp480;
        }
        if ((s32) sp33 > 0) {
            sp24 = 1;
        } else {
            sp24 = arg0->unk60;
        }
        sp484 = 0;
        if (sp24 > 0) {
            do {
                temp_t5 = sp484 * 2;
                ((Unk *)(sp + temp_t5))->unk37C = (u16) ((Unk *)(sp + temp_t5))->unk27C;
                temp_t8 = sp484 + 1;
                sp484 = temp_t8;
            } while (temp_t8 < sp24);
        }
        if (sp484 < 0x80) {
            do {
                (sp + (sp484 * 2))->unk37C = 3;
                temp_t6 = sp484 + 1;
                sp484 = temp_t6;
            } while (temp_t6 < 0x80);
        }
        sp484 = 0;
        if (arg0->unk50 > 0) {
            do {
                temp_t7 = &(&sp23C[0])[sp484];
                if ((*temp_t7 == sp33) && ((s32) *temp_t7 >= (s32) arg0->unk62)) {
loop_64:
                    temp_t1 = (sp + (sp484 * 2))->unk23D;
                    sp23 = temp_t1;
                    sp20 = (&sp27C[0])[temp_t1];
                    (&sp37C[0])[sp23] = sp20;
                    (&sp23C[0])[sp484] = sp20;
                    temp_t9 = &(&sp23C[0])[sp484];
                    if (*temp_t9 == sp33) {
                        if ((s32) *temp_t9 >= (s32) arg0->unk62) {
                            goto loop_64;
                        }
                    }
                }
                temp_t0_2 = sp484 + 1;
                sp484 = temp_t0_2;
            } while (temp_t0_2 < arg0->unk50);
        }
        sp480 = contPakReadWriteNote(arg0, (u16 (*)[]) &sp37C[0], 1, sp33);
        if (sp480 != 0) {
            return sp480;
        }
        temp_t9_2 = sp33 + 1;
        sp33 = temp_t9_2;
        if ((temp_t9_2 & 0xFF) >= (s32) arg0->unk64) {
            goto block_70;
        }
        goto loop_51;
    }
block_70:
    if (sp34 != 0) {
        arg0->unk0 = (s32) (arg0->unk0 | 2);
    } else {
        arg0->unk0 = (s32) (arg0->unk0 & ~2);
    }
    return 0;
}
