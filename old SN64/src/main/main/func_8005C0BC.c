#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8005C538 (initial). */

s32 *func_8004D4A8(s32);                            /* extern */
void func_8005C8D4(s32);                               /* extern */
void func_8005C8EC(s32, s32);                              /* extern */
void func_8005CF84(s32);                               /* extern */
void func_8005CF9C(s32);                               /* extern */
void func_8007BA98(u32, s32);                        /* extern */
void func_8007BCA8();                                  /* extern */
void func_8007BCD8(Unk*, s32, s32);                       /* extern */
s32 func_8007CD08(Unk*, s32*, s32);                         /* extern */
void func_8007D8CC(Unk*, s32);                        /* extern */
void func_8007DAA4(void *, void *, s32 *, void *);              /* extern */
void func_8007DAD8(void *, s32, s32);                     /* extern */
void func_8007E9D8(s32, s32);                          /* extern */
void func_8007EA18(s32, s8, s8);                     /* extern */
void func_8007FBD8(Unk*, Unk*);                          /* extern */
void func_800822DC(Unk*, Unk*);                          /* extern */
s32 func_800866E8(s32);                               /* extern */
s32 func_8008E518(Unk*, s32, s32, s32, s32, s32, s32);   /* extern */
extern s32 D_8004B660;
extern s32 D_8004B664;
extern s32 D_8004B668;
extern s32 D_8004B670;
extern s32 D_8004B674;
extern s32 D_8004B678;
extern s32 D_8004B680;
extern f32 D_8004BDE8;
extern s32 D_800927E4;
extern s32 D_800927EC;
extern s32 D_800927F0;
extern char *D_800927F4;
extern s32 D_800927F8;
extern s32 D_80092AB0;
extern s32 D_8017EFC8;
extern s32 D_8017EFE8;
extern s32 D_8017F008;
extern s32 D_8017F328;
extern s32 D_8017F338;
extern Unk D_8017F370;
extern s32 D_8017F378;
extern s32 D_8017F388;
extern Unk D_8017F3D8;
extern Unk D_8017F408;
extern Unk D_8017F428;
extern s32 *D_8017F434;
extern Unk D_8017F438;
extern s32 D_801808DC;
extern s32 D_801808E0;
extern s32 D_801808E4;
extern s32 *D_801808EC;
extern Unk *D_801808F0;
extern Unk *D_801808F4;
extern s32 *D_801808F8;
extern s32 D_80180908;
extern Unk D_80182EA8;
extern s32 D_801839A8;
extern s32 func_8005BF64;

void func_8005C0BC(void) {
    Unk *var_v1;
    f32 temp_fv1;
    s32 *temp_v0_2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_ft0;
    s32 temp_s1;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_v0;
    s32 var_s4;
    s32 var_s4_2;
    Unk *temp_v1;

    func_8007BCD8(&D_8017EFC8, &D_8017F008, 0xC8);
    func_8007BCD8(&D_8017EFE8, &D_8017F328, 1);
    func_8007DAD8(&D_8017F378, func_8004D4A8(0xB400), 0xB400);
    D_8017F434 = func_8004D4A8(0x4E20);
    D_8017F370.unk0 = func_8004D4A8(0x40);
    D_8017F370.unk4 = func_8004D4A8(0x40);
    D_8017F438.unk0 = func_8004D4A8(0x800);
    D_8017F438.unk4 = func_8004D4A8(0x800);
    temp_s3 = D_8004B674;
    D_8017F438.unk8 = func_8004D4A8(0x800);
    D_801808F0 = func_8004D4A8(temp_s3);
    func_8007BCA8();
    func_8008E518(&D_8017F338, 0, 0, D_8004B670, D_801808F0, temp_s3, &D_8017EFC8);
    func_8007CD08(&D_8017EFC8, 0, 1);
    temp_s3_2 = D_8004B664;
    D_801808F4 = func_8004D4A8(temp_s3_2);
    func_8007BCA8();
    func_8008E518(&D_8017F338, 0, 0, D_8004B660, D_801808F4, temp_s3_2, &D_8017EFC8);
    func_8007CD08(&D_8017EFC8, 0, 1);
    temp_v0 = func_800866E8(0x5622);
    temp_fv1 = (f32) temp_v0 * D_8004BDE8;
    D_8017F3D8.unk18 = temp_v0;
    temp_ft0 = (s32) temp_fv1;
    D_801808E0 = temp_ft0;
    if ((f32) temp_ft0 < temp_fv1) {
        D_801808E0 = temp_ft0 + 1;
    }
    if (D_801808E0 & 0xF) {
        D_801808E0 = (D_801808E0 & ~0xF) + 0x10;
    }
    D_8017F3D8.unk0 = 0x2C;
    D_8017F3D8.unk4 = 0x24;
    D_8017F3D8.unk10 = &func_8005BF64;
    D_8017F3D8.unk1C = 6;
    D_8017F3D8.unk20 = &D_80092AB0;
    D_8017F3D8.unk8 = 0x100;
    D_8017F3D8.unk14 = &D_8017F378;
    D_801808E4 = D_801808E0 - 0x10;
    func_8007DAA4(&D_8017F388, &D_8017F3D8, &D_801808E0, &D_8017F3D8);
    D_8017F408.unk0 = 0x10;
    D_8017F408.unk4 = 0x100;
    D_8017F408.unk8 = 0x10;
    D_8017F408.unkC = &D_8017F378;
    D_8017F408.unk10 = 0;
    D_8017F408.unk14 = 0;
    D_8017F408.unk18 = 0;
    func_8007FBD8(D_800927E4, &D_8017F408);
    var_s4 = 0;
    func_8007D8CC(D_801808F0, D_8004B678);
    temp_a1 = D_801808F0->unk4;
    D_800927EC = temp_a1;
    func_8007E9D8(D_800927E4, temp_a1);
    do {
        temp_a1_2 = var_s4 & 0xFF;
        temp_a2 = (0x10 - var_s4) & 0xFF;
        var_s4 += 1;
        func_8007EA18(D_800927E4, temp_a1_2, temp_a2);
    } while (var_s4 < 0x10);
    D_8017F428.unk0 = 0x1C;
    D_8017F428.unk4 = 0x100;
    D_8017F428.unk8 = &D_8017F378;
    func_800822DC(D_800927F0, &D_8017F428);
    func_8007D8CC(D_801808F4, D_8004B668);
    temp_v1 = D_801808F4->unk4;
    D_800927F4 = temp_v1;
    D_801808DC = temp_v1->unkC;
    D_801808EC = func_8004D4A8(0x3800);
    func_8007BCA8();
    func_8008E518(&D_8017F338, 0, 0, D_8004B680, D_801808EC, 4, &D_8017EFC8);
    func_8007CD08(&D_8017EFC8, 0, 1);
    func_8007BA98(D_801808EC, 4);
    temp_s1 = *D_801808EC * 0x10;
    temp_v0_2 = func_8004D4A8(temp_s1);
    D_801808F8 = temp_v0_2;
    func_8008E518(&D_8017F338, 0, 0, D_8004B680 + 8, temp_v0_2, temp_s1, &D_8017EFC8);
    func_8007CD08(&D_8017EFC8, 0, 1);
    func_8007BA98(D_801808F8, temp_s1);
    var_s4_2 = 0;
    func_8005C8D4(D_801839A8);
    func_8005C8EC(0x78, 0);
    var_v1 = &D_80180908;
    do {
        var_v1->unk0 = 0;
        var_v1->unk4 = 0;
        var_s4_2 += 1;
        var_v1 += 0x14;
    } while (var_s4_2 < 0x1C);
    func_8005CF84(D_80182EA8.unkAFC);
    func_8005CF9C(D_80182EA8.unkB04);
}

s32 func_8005C538(void) {
    return D_800927F8;
}
