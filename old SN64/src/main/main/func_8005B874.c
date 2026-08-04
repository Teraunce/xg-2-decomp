#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
void func_8005AA98(Unk*);                            /* extern */
void func_8005AFC4();                                  /* extern */
extern s32 D_800925D0;
extern s32 D_800926D0;
extern Unk D_8017CE08;
extern s32 D_8017D2F8;
extern Unk D_8017DA58;
extern char *D_8017DF44;
extern u32 D_8017DF48;
extern s32 D_8017DF4C;
extern s16 D_8017DF50;
extern s16 D_8017DF52;
extern s16 D_8017DF54;
extern u16 D_8017DF56;
extern s32 D_8017DF58;
extern s32 D_80190000;

s16 func_8005B874(s32 arg0) {
    s32 subroutine_arg5 = 0;
    s16 *temp_a0_2;
    s16 temp_s0_2;
    s16 temp_v0;
    s16 temp_v1_3;
    s16 var_a1;
    s16 var_s5;
    s32 temp_a0;
    s32 temp_a0_3;
    s32 temp_a3;
    s32 temp_s1;
    s32 temp_s4;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 var_a0;
    s8 *temp_v0_8;
    u16 *temp_a1;
    u16 *temp_v0_2;
    u16 *temp_v0_5;
    u16 temp_a3_2;
    u16 temp_t0;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v1_2;
    u16 var_a1_2;
    u16 var_a2;
    u16 var_s2;
    u16 var_s2_3;
    u32 var_s2_2;
    u32 var_s3;
    Unk *temp_s0;
    Unk *temp_s0_3;
    Unk *temp_s0_4;

    var_s5 = 0;
    if (arg0 == (s32)M2C_ERROR(/* Read from unset register $v0 */)) {
        var_s2 = D_8017DA58.unk4E4;
        if (var_s2 < 0x273U) {
            do {
                if (D_8017DF4C == 0) {
                    temp_s0 = D_8017DF44;
                    if ((u32) temp_s0->unkC >= (u32) temp_s0->unk10) {
                        func_8005AA98(temp_s0);
                    }
                    temp_v1 = temp_s0->unkC;
                    temp_s0->unkC = (s32) (temp_v1 + 4);
                    D_8017DF4C = 0x20;
                    D_8017DF48 = *((temp_s0->unk8 << 0xA) + temp_v1 + &D_80190000);
                }
                var_s2 = *(u16*)((char*)&D_8017DA58 + (((var_s2 + ((u32)D_8017DF48 >> 0x1F)) & 0xFFFF) * 2));
                D_8017DF48 *= 2;
                D_8017DF4C -= 1;
            } while (var_s2 < 0x273U);
        }
        temp_s0_2 = var_s2 - 0x273;
        if (D_8017CE08.unk4E4 == 0x8000) {
            func_8005AFC4();
        }
        var_a2 = ((Unk*)((char*)&D_8017D2F8 + ((s32)(temp_s0_2 << 0x10) >> 0xF)))->unk4E6;
        do {
            temp_v0_2 = (u16*)((char*)&D_8017CE08 + ((s32)(var_a2 << 0x10) >> 0xF));
            temp_v1_2 = *temp_v0_2 + 1;
            *temp_v0_2 = temp_v1_2;
            var_a1 = (s16) temp_v1_2;
            temp_v0_3 = var_a2 + 2;
            if ((s32) *(u16*)((char*)&D_8017CE08 + ((s32)((var_a2 + 1) << 0x10) >> 0xF)) < var_a1) {
                var_a0 = temp_v0_3;
                if ((s32) *(u16*)((char*)&D_8017CE08 + ((s32)(temp_v0_3 << 0x10) >> 0xF)) < var_a1) {
                    do {
                        temp_v0_4 = var_a0 + 1;
                        var_a0 = temp_v0_4;
                    } while ((s32) *(u16*)((char*)&D_8017CE08 + ((s32)(temp_v0_4 << 0x10) >> 0xF)) < var_a1);
                }
                temp_t0 = var_a0 - 1;
                temp_a0 = (s32) (var_a2 << 0x10) >> 0xF;
                temp_a3 = (s32) (temp_t0 << 0x10) >> 0xF;
                temp_a1 = (u16*)((char*)&D_8017CE08 + temp_a3);
                temp_a0_2 = (s16*)((char*)&D_8017DA58 + temp_a0);
                *(u16*)((char*)&D_8017CE08 + temp_a0) = *temp_a1;
                *temp_a1 = temp_v1_2;
                temp_v1_3 = *temp_a0_2;
                var_a1 = (s16) (u16) *temp_a0_2;
                *((temp_v1_3 * 2) + &D_8017D2F8) = temp_t0;
                if (temp_v1_3 < 0x273) {
                    *(((temp_v1_3 + 1) * 2) + &D_8017D2F8) = temp_t0;
                }
                temp_v0_5 = (u16*)((char*)&D_8017DA58 + temp_a3);
                temp_a3_2 = *temp_v0_5;
                *temp_v0_5 = (u16) var_a1;
                *(((s16) temp_a3_2 * 2) + &D_8017D2F8) = var_a2;
                if ((s16) temp_a3_2 < 0x273) {
                    *((((s16) temp_a3_2 + 1) * 2) + &D_8017D2F8) = var_a2;
                }
                *temp_a0_2 = (s16) temp_a3_2;
                var_a2 = temp_t0;
            }
            temp_v0 = *(((s32) (var_a2 << 0x10) >> 0xF) + &D_8017D2F8);
            var_a2 = (u16) temp_v0;
        } while (temp_v0 != 0);
        var_s5 = temp_s0_2;
        if (temp_s0_2 < 0x100) {
            temp_v0_6 = D_8017DF56;
            D_8017DF56 = temp_v0_6 + 1;
            *((s16) temp_v0_6 + &D_8017DF58) = (s8) var_s5;
            D_8017DF56 &= 0xFFF;
        } else {
            var_s2_2 = (u32) D_8017DF48 >> 0x18;
            if (D_8017DF4C < 8) {
                temp_s1 = 8 - D_8017DF4C;
                temp_s0_3 = D_8017DF44;
                temp_s4 = ~(-1U >> temp_s1);
                if ((u32) temp_s0_3->unkC >= (u32) temp_s0_3->unk10) {
                    func_8005AA98(temp_s0_3);
                }
                temp_v1_4 = temp_s0_3->unkC;
                temp_a0_3 = *((temp_s0_3->unk8 << 0xA) + temp_v1_4 + &D_80190000);
                temp_s0_3->unkC = (s32) (temp_v1_4 + 4);
                temp_v1_5 = 0x20 - temp_s1;
                D_8017DF4C = temp_v1_5;
                var_s2_2 |= (u32) (temp_a0_3 & temp_s4) >> temp_v1_5;
                D_8017DF48 = temp_a0_3 << temp_s1;
            } else {
                D_8017DF4C -= 8;
                D_8017DF48 <<= 8;
            }
            var_s3 = var_s2_2;
            temp_v0_7 = *((var_s3 & 0xFFFF) + &D_800926D0) - 3;
            var_s2_3 = temp_v0_7;
            if ((temp_v0_7 & 0xFFFF) != 0xFFFF) {
                do {
                    var_a1_2 = var_s2_3 - 1;
                    if (D_8017DF4C == 0) {
                        temp_s0_4 = D_8017DF44;
                        if ((u32) temp_s0_4->unkC >= (u32) temp_s0_4->unk10) {
                            func_8005AA98(temp_s0_4);
                        }
                        temp_v1_6 = temp_s0_4->unkC;
                        temp_s0_4->unkC = (s32) (temp_v1_6 + 4);
                        D_8017DF4C = 0x20;
                        D_8017DF48 = *((temp_s0_4->unk8 << 0xA) + temp_v1_6 + &D_80190000);
                        var_a1_2 = var_s2_3 - 1;
                    }
                    var_s2_3 = var_a1_2;
                    var_s3 = ((u32) D_8017DF48 >> 0x1F) | (var_s3 * 2);
                    D_8017DF48 *= 2;
                    D_8017DF4C -= 1;
                } while ((var_a1_2 & 0xFFFF) != 0xFFFF);
            }
            D_8017DF52 = var_s5 - 0xFD;
            D_8017DF54 = 0;
            D_8017DF50 = (~((var_s3 & 0x3F) | subroutine_arg5) + D_8017DF56) & 0xFFF;
        }
    }
    if (D_8017DF54 < D_8017DF52) {
        var_s5 = (s16) *(((D_8017DF50 + D_8017DF54) & 0xFFF) + &D_8017DF58);
        temp_v0_8 = (s16) D_8017DF56 + &D_8017DF58;
        D_8017DF56 += 1;
        *temp_v0_8 = (s8) var_s5;
        D_8017DF56 &= 0xFFF;
        D_8017DF54 = (u16) D_8017DF54 + 1;
    }
    return var_s5;
}
