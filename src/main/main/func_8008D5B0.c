#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8008DC4C (initial). */

s32 osEPiStartDma(Unk*, s32, s32, s32, s32);               /* extern */
void func_8008DD34();                                  /* extern */
void func_8008DC4C();                               /* static */
extern s32 osIntMask;
extern s32 D_8018C2FC;
extern s32 D_A4600010;
extern s32 D_A5000508;
extern s32 D_A5000510;

s32 func_8008D5B0(void) {
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    Unk *sp30;
    Unk *sp2C;
    u32 sp28;
    s32 *sp24;
    u32 temp_t9;
    Unk *temp_t0;
    Unk *temp_t3;
    char *temp_t7;

    temp_t7 = (s32)0 /* implicit $t6 from caller */ + 0x14;
    sp3C = 0;
    sp30 = temp_t7;
    temp_t0 = temp_t7 + (((Unk*)0 /* implicit $t6 */)->unk1A * 0x24);
    sp2C = temp_t0 + 0x18;
    sp38 = D_A4600010;
    if (sp38 & 1) {
        osIntMask &= ~0x800;
        temp_t0->unk18 = 0x1D;
        func_8008DD34();
        goto block_59;
    }
    sp38 = D_A4600010;
    if (sp38 & 3) {
        do {
            sp38 = D_A4600010;
        } while (sp38 & 3);
    }
    sp3C = D_A5000508;
    if (sp3C & 0x02000000) {
        sp38 = D_A4600010;
        if (sp38 & 3) {
            do {
                sp38 = D_A4600010;
            } while (sp38 & 3);
        }
        D_A5000510 = sp30->unk10 | 0x01000000;
        sp2C->unk0 = 0;
        return 0;
    }
    if (sp30->unk0 == 2) {
        goto block_59;
    }
    if (sp3C & 0x08000000) {
        sp38 = D_A4600010;
        if (sp38 & 3) {
            do {
                sp38 = D_A4600010;
            } while (sp38 & 3);
        }
        sp3C = D_A5000508;
        sp2C->unk0 = 0x16;
        func_8008DD34();
        D_A4600010 = 2;
        osIntMask |= 0x100401;
        goto block_59;
    }
    if (sp30->unk0 == 1) {
        if (!(sp3C & 0x40000000)) {
            if ((sp30->unk8 + 1) != (sp30->unk4 * 0x55)) {
                sp2C->unk0 = 0x18;
                func_8008DC4C();
            } else {
                D_A4600010 = 2;
                osIntMask |= 0x100401;
                sp2C->unk0 = 0;
                func_8008DD34();
            }
        } else {
            sp2C->unk4 = (s32) (sp2C->unk4 + sp2C->unkC);
            sp30->unk8 = (s32) (sp30->unk8 + 1);
            osEPiStartDma(D_8018C2FC, 1, 0x05000400, sp2C->unk4, sp2C->unkC);
        }
        goto block_59;
    }
    if (sp30->unk0 == 0) {
        if (sp30->unk4 == 3) {
            if ((sp2C->unk10 + 0x11) < sp30->unk8) {
                sp2C->unk0 = 0;
                func_8008DC4C();
                goto block_59;
            }
            if (!(sp3C & 0x40000000)) {
                sp2C->unk0 = 0x17;
                func_8008DC4C();
                goto block_59;
            }
            goto block_27;
        }
        sp2C->unk4 = (s32) (sp2C->unk4 + sp2C->unkC);
block_27:
        sp34 = D_A5000510;
        if (((sp34 & 0x200000) && (sp34 & 0x400000)) || (sp34 & 0x02000000)) {
            if ((u32) sp2C->unk10 >= 4U) {
                if ((sp30->unk4 != 3) || (sp30->unk8 >= 0x53)) {
                    sp2C->unk0 = 0x17;
                    func_8008DC4C();
                    goto block_59;
                }
                goto block_35;
            }
            temp_t9 = sp2C->unk10;
            sp28 = temp_t9;
            (sp2C + (temp_t9 * 4))->unk14 = (s32) (sp30->unk8 + 1);
block_35:
            sp2C->unk10 = (u32) (sp2C->unk10 + 1);
            goto block_36;
        }
block_36:
        if (sp3C & 0x10000000) {
            if (sp30->unk8 != 0x57) {
                sp2C->unk0 = 0x18;
                func_8008DC4C();
            }
            if ((sp30->unk4 == 2) && (sp30->unk6 == 0)) {
                sp30->unk6 = 1U;
                sp30->unk8 = -1;
                sp30->unk40 = (s32) (sp30->unk40 - sp30->unk48);
                sp2C->unk0 = 0x16;
            } else {
                D_A4600010 = 2;
                osIntMask |= 0x100401;
                sp30->unk0 = 2;
                sp2C->unk0 = 0;
            }
            osEPiStartDma(D_8018C2FC, 0, 0x05000000, sp2C->unk8, sp2C->unkC * 4);
            goto block_59;
        }
        if ((sp30->unk8 == -1) && (sp30->unk4 == 2) && (sp30->unk6 == 1)) {
            sp24 = sp30 + 0x18;
            if (sp30->unk28 == 0) {
                temp_t3 = sp30->unk20;
                if ((temp_t3->unkC | (temp_t3->unk0 | temp_t3->unk4 | temp_t3->unk8)) != 0) {
                    sp30->unk18 = 0x18;
                    func_8008DC4C();
                    goto block_59;
                }
            }
            *sp24 = 0;
            func_8008DD34();
            goto block_51;
        }
block_51:
        sp30->unk8 = (s32) (sp30->unk8 + 1);
        if (sp3C & 0x40000000) {
            if (sp30->unk8 >= 0x55) {
                sp2C->unk0 = 0x18;
                func_8008DC4C();
                goto block_59;
            }
            osEPiStartDma(D_8018C2FC, 0, 0x05000400, sp2C->unk4, sp2C->unkC);
            sp2C->unk0 = 0;
            return 1;
        }
        if (sp30->unk8 < 0x55) {
            sp2C->unk0 = 0x18;
            func_8008DC4C();
        }
        goto block_59;
    }
    sp2C->unk0 = 4;
    func_8008DC4C();
block_59:
    return 1;
}

void func_8008DC4C(void) {

}
