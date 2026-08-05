#include "ultra64.h"
void func_8004D8C0(s32, s32);                          /* extern */
void func_8007BCA8(void);                             /* extern */
extern s32 D_80000300;
extern s32 D_80090E94;
extern s32 D_80095650;

void func_8004DC24(Unk *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 sp30;
    s32 sp2C;
    u32 sp28;
    s16 sp22;
    s16 sp20;
    s32 sp1C;
    s32 sp18;
    s16 unksp12;
    s16 unksp16;
    s16 unksp1A;
    s16 unksp1E;
    s32 sp14;                                       /* compiler-managed */
    s32 sp10;                                       /* compiler-managed */
    s16 temp_a0_3;
    s16 temp_a0_4;
    s16 temp_a0_5;
    s16 temp_a0_6;
    s16 temp_a2_2;
    s16 temp_a2_3;
    s16 temp_a2_4;
    s16 temp_a2_5;
    s16 temp_a3_2;
    s16 temp_t3;
    s16 var_t6;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a3;
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_t4;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_v1_2;
    s32 var_a1;
    u32 temp_a2;
    char *temp_v1;
    Unk *var_a2;
    Unk *var_v0;

    func_8004D8C0(arg1, arg2);
    var_a1 = (arg2 >= 0x101) * 2;
    if (arg1 >= 0x141) {
        var_a1 |= 1;
    }
    if (D_80000300 != 1) {
        if (D_80000300 < 2) {
            if (D_80000300 == 0) {
                var_a1 += 4;
                goto block_12;
            }
            var_a2 = arg0;
        } else {
            if (D_80000300 == 2) {
                var_a1 += 8;
                goto block_12;
            }
            var_a2 = arg0;
        }
    } else {
block_12:
        var_a2 = arg0;
    }
    var_v0 = (*(var_a1 + &D_80090E94) * 0x50) + &D_80095650;
    temp_v1 = var_v0 + 0x50;
    do {
        var_a2->unk0 = (s32) var_v0->unk0;
        var_a2->unk4 = (s32) var_v0->unk4;
        var_a2->unk8 = (s32) var_v0->unk8;
        var_a2->unkC = (s32) var_v0->unkC;
        var_v0 += 0x10;
        var_a2 += 0x10;
    } while ((char *)var_v0 != temp_v1);
    if (*(var_a1 + &D_80090E94) == 0x10) {
        arg0->unk2C = 0x355;
        arg0->unk30 = 0x2C0268;
    }
    temp_t6 = arg0->unk1C;
    temp_t5 = temp_t6 >> 0x10;
    temp_a1 = (s16) temp_t6 - temp_t5;
    sp30 = (s32) (s16) temp_t6;
    temp_a0 = arg0->unk30;
    sp10 = temp_a0;
    temp_a2 = unksp12 - (s16) sp10;
    sp18 = temp_a0;
    temp_a0_2 = arg0->unk44;
    sp14 = temp_a0_2;
    temp_a3 = unksp16 - (s16) sp14;
    temp_t2 = arg6 / 2;
    temp_t4 = arg6 * 2;
    sp1C = temp_a0_2;
    sp28 = temp_a2;
    sp2C = temp_a3;
    temp_a0_3 = (u16) sp10 + ((s32) (temp_a2 + (temp_a2 >> 0x1F)) >> 1);
    sp20 = temp_a0_3;
    temp_a0_4 = temp_a0_3 - arg4;
    temp_a2_2 = (u16) sp14 + (temp_a3 / 2);
    sp22 = temp_a2_2;
    temp_a2_3 = temp_a2_2 - arg4;
    sp20 = temp_a0_4;
    sp22 = temp_a2_3;
    temp_v1_2 = (s32) ((s32) (arg2 * temp_a2) / arg2) / 2;
    temp_t3 = (temp_a0_4 - temp_v1_2) + temp_t2;
    temp_a0_5 = (temp_a0_4 + temp_v1_2) - temp_t4;
    temp_a1_2 = ((temp_a1 / 2) + temp_t5) - arg3;
    temp_t1 = (s32) ((s32) (arg1 * temp_a1) / arg1) / 2;
    var_t6 = (((temp_a1_2 - temp_t1) + (arg5 / 2)) << 0x10) | (((temp_a1_2 + temp_t1) - (arg5 * 2)) & 0xFFFF);
    unksp12 = temp_a0_5;
    temp_a0_6 = temp_a0_5 - 3;
    unksp12 = temp_a0_6;
    sp10 = temp_t3;
    temp_t0 = (s32) ((s32) (arg2 * temp_a3) / arg2) / 2;
    temp_a2_4 = (temp_a2_3 + temp_t0) - temp_t4;
    unksp16 = temp_a2_4;
    temp_a2_5 = temp_a2_4 - 3;
    sp14 = (temp_a2_3 - temp_t0) + temp_t2;
    unksp16 = temp_a2_5;
    temp_t7 = (arg0->unk2C & 0xFFFF0000) | (((s32) ((arg2 - 3) << 0xB) / (s32) (temp_a0_5 - temp_t3)) & 0xFFFF);
    temp_a3_2 = var_t6;
    temp_a1_3 = (s32) (arg1 << 0xA) / (s32) (temp_a3_2 - (var_t6 >> 0x10));
    if (unksp1A < temp_a0_6) {
        unksp12 = unksp1A;
    }
    if (unksp1E < temp_a2_5) {
        unksp16 = unksp1E;
    }
    if (sp30 < temp_a3_2) {
        var_t6 = (var_t6 & 0xFFFF0000) | (temp_t6 & 0xFFFF);
    }
    arg0->unk2C = temp_t7;
    arg0->unk40 = temp_t7;
    arg0->unk30 = (s32) sp10;
    arg0->unk28 = 0;
    arg0->unk3C = (s32) (arg1 * 2);
    arg0->unk8 = arg1;
    arg0->unk20 = temp_a1_3;
    arg0->unk1C = (s32) var_t6;
    arg0->unk44 = (s32) sp14;
    func_8007BCA8();
}
