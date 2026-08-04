#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
void func_8007BB48(u32, s32);                              /* extern */
void func_8007BC28(u32, s32);                              /* extern */
s32 func_80087AF8(s32, s32 *);                        /* extern */
s32 func_80087B78(s32, s32);                          /* extern */
void func_8008CEB8(s32, u32 *);                          /* extern */
void func_8008EAB8(s32, s32);                            /* extern */
u32 func_8008EBC0(s32, u32, s32, s32);                  /* extern */
s32 func_8008ECC0(u32, s32, s32, s32);                  /* extern */
s32 func_8007CC78();                                /* static */
s32 func_8007CC88(s32);                               /* static */
void func_8007CC98(s32);                            /* static */
void func_8007CCA8();                               /* static */
extern s32 D_80000000;
extern s32 D_80000300;
extern s32 D_8000030C;
extern s32 D_8000031C;
extern u32 D_80095280;
extern s32 D_80095284;
extern s32 D_80095288;
extern s32 D_80189828;
extern Unk func_8007BE58;

void func_8007C9E8(void) {
    s32 sp34;
    u32 sp30;
    u32 sp24;
    s32 sp20;
    s32 temp_ret;
    u32 temp_ret_2;
    u32 temp_t9;

    sp30 = 0;
    D_80189828 = 1;
    func_8007CC98(func_8007CC78() | 0x20000000);
    func_8007CC88(0x01000800);
    if (func_80087AF8(0x1FC007FC, &sp34) != 0) {
        do {

        } while (func_80087AF8(0x1FC007FC, &sp34) != 0);
    }
    if (func_80087B78(0x1FC007FC, sp34 | 8) != 0) {
        do {

        } while (func_80087B78(0x1FC007FC, sp34 | 8) != 0);
    }
    D_80000000 = func_8007BE58.unk0;
    D_80000000 = func_8007BE58.unk4;
    D_80000000 = func_8007BE58.unk8;
    D_80000000 = func_8007BE58.unkC;
    (( Unk*)0x80000080)->unk0 = (s32) func_8007BE58.unk0;
    (( Unk*)0x80000080)->unk4 = (s32) func_8007BE58.unk4;
    (( Unk*)0x80000080)->unk8 = (s32) func_8007BE58.unk8;
    (( Unk*)0x80000080)->unkC = (s32) func_8007BE58.unkC;
    (( Unk*)0x80000100)->unk0 = (s32) func_8007BE58.unk0;
    (( Unk*)0x80000100)->unk4 = (s32) func_8007BE58.unk4;
    (( Unk*)0x80000100)->unk8 = (s32) func_8007BE58.unk8;
    (( Unk*)0x80000100)->unkC = (s32) func_8007BE58.unkC;
    (( Unk*)0x80000180)->unk0 = (s32) func_8007BE58.unk0;
    (( Unk*)0x80000180)->unk4 = (s32) func_8007BE58.unk4;
    (( Unk*)0x80000180)->unk8 = (s32) func_8007BE58.unk8;
    (( Unk*)0x80000180)->unkC = (s32) func_8007BE58.unkC;
    func_8007BC28(0x80000000, 0x190);
    func_8007BB48(0x80000000, 0x190);
    func_8007CCA8();
    func_8008CEB8(4, &sp30);
    temp_t9 = sp30 & ~0xF;
    sp30 = temp_t9;
    if (temp_t9 != 0) {
        D_80095280 = 0;
        D_80095280 = temp_t9;
    }
    temp_ret = func_8008ECC0(D_80095280, D_80095284, 0, 3);
    sp20 = temp_ret;
    sp24 = (u32) (u64) temp_ret;
    temp_ret_2 = func_8008EBC0(sp20, sp24, 0, 4);
    D_80095280 = temp_ret_2;
    D_80095280 = (u32) (u64) temp_ret_2;
    if (D_8000030C == 0) {
        func_8008EAB8(&D_8000031C, 0x40);
    }
    if (D_80000300 == 0) {
        D_80095288 = 0x02F5B2D2;
        return;
    }
    if (D_80000300 == 2) {
        D_80095288 = 0x02E6025C;
        return;
    }
    D_80095288 = 0x02E6D354;
}

s32 func_8007CC78(void) {
    return (s32)M2C_ERROR(/* mfc0 $12 */);
}

s32 func_8007CC88(s32 arg0) {
    return (s32)M2C_ERROR(/* cfc1 */);
}

void func_8007CC98(s32 arg0) {
    (s32)M2C_ERROR(/* mtc0 $a0, $12 */);
}

void func_8007CCA8(void) {
    (s32)M2C_ERROR(/* mtc0 $t1, $0 */);
    (s32)M2C_ERROR(/* mtc0 $zero, $5 */);
    (s32)M2C_ERROR(/* mtc0 $t1, $10 */);
    (s32)M2C_ERROR(/* mtc0 $t3, $2 */);
    (s32)M2C_ERROR(/* mtc0 $t1, $3 */);
    (s32)M2C_ERROR(/* unknown instruction: tlbwi */);
    (s32)M2C_ERROR(/* mtc0 $t0, $10 */);
}
