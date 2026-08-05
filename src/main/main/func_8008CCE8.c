#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8008CEB8 (initial). */

s32 func_80088C98(s32, s32, u16, s32, s32);           /* extern */
s32 func_80089EF8(s32, s32, u16, u8*);                /* extern */
void func_8008CB6C(s32, u16, u8*, void *);               /* extern */
extern s32 D_8018ADF8;
extern s32 D_8018AEF8;
extern s32 D_8018AFF8;
extern s32 D_8018B018;
extern s32 D_A4600010;

s32 func_8008CCE8(s32 arg0, Unk *arg1, s32 arg2) {
    Unk *sp = (Unk*)0;
    s32 sp44;
    s32 sp40;
    s8 sp20;
    s32 temp_t7;
    s32 temp_t9;

    arg1->unk4 = arg0;
    arg1->unk8 = arg2;
    arg1->unk0 = 0;
    arg1->unk65 = 0x80;
    sp44 = 0;
    do {
        ((Unk *)(sp + sp44))->unk20 = 0x80;
        temp_t7 = sp44 + 1;
        sp44 = temp_t7;
    } while (temp_t7 < 0x20);
    sp40 = func_80088C98(arg0, arg2, 0x400, &sp20, 0);
    if (sp40 == 2) {
        sp40 = func_80088C98(arg0, arg2, 0x400, &sp20, 0);
    }
    if (sp40 != 0) {
        return sp40;
    }
    sp40 = func_80089EF8(arg0, arg2, 0x400, &sp20);
    if (sp40 == 2) {
        sp40 = 4;
    }
    if (sp40 != 0) {
        return sp40;
    }
    if (((Unk*)&sp20)->unk1F != 0x80) {
        return 0xB;
    }
    sp44 = 0;
    do {
        *(&D_8018B018 + sp44) = 1;
        *(&D_8018AFF8 + sp44) = 0;
        temp_t9 = sp44 + 1;
        sp44 = temp_t9;
    } while (temp_t9 < 0x20);
    func_8008CB6C(arg2, 0x600, &D_8018B018, (arg2 << 6) + &D_8018AEF8);
    func_8008CB6C(arg2, 0x600, &D_8018AFF8, (arg2 << 6) + &D_8018ADF8);
    return 0;
}

void func_8008CEB8(void) {

}
