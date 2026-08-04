#include "ultra64.h"
u64 func_8008EB84(s32, s32, s32, s32);              /* extern */
u64 func_8008EBC0(s32, s32, s32, s32);              /* extern */
s32 func_8008EE98(s32, void *, s32);                  /* extern */
void func_8008FE98(void *, s32, u32, s32, u32);        /* extern */
extern s32 D_80096510;
extern s32 D_80096524;

void func_8008FBF8(Unk *arg0, s32 arg1) {
    s32 sp54;
    s32 sp5C;
    s8 sp78;
    s32 sp70;
    s32 sp64;
    s32 sp60;
    s32 sp50;
    s32 sp4C;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    char *var_s3;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s0;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 temp_t8_3;
    s32 temp_t9;
    s32 temp_t9_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_s0;
    s32 var_t0;
    s32 var_t1;
    u32 temp_v1;
    u64 temp_ret;
    u8 *temp_t7_2;
    u8 temp_t7;

    temp_v0 = arg1 & 0xFF;
    if (temp_v0 == 0x58) {
        var_s3 = &D_80096524;
    } else {
        var_s3 = &D_80096510;
    }
    var_s0 = 0x18;
    if (temp_v0 == 0x6F) {
        var_t1 = 8;
    } else {
        var_t0 = 0x10;
        if ((temp_v0 != 0x78) && (temp_v0 != 0x58)) {
            var_t0 = 0xA;
        }
        var_t1 = var_t0;
    }
    temp_t8 = arg0->unk0;
    temp_t9 = arg0->unk4;
    sp60 = temp_t8;
    sp40 = temp_t8;
    sp44 = temp_t9;
    sp64 = temp_t9;
    if (((temp_v0 == 0x64) || (temp_v0 == 0x69)) && (sp40 <= 0)) {
        if (sp40 >= 0) {

        } else {
            temp_t8_2 = ~sp60 + (sp64 == 0);
            sp64 = -sp64;
            sp60 = temp_t8_2;
        }
    }
    if ((sp60 != 0) || (sp64 != 0) || (arg0->unk24 != 0)) {
        var_s0 = 0x17;
        sp4C = 0x17;
        sp70 = var_t1;
        temp_t7 = *((u32) func_8008EB84(sp60, sp64, var_t1 >> 0x1F, var_t1) + var_s3);
        ((Unk*)&sp78)->unk17 = temp_t7;
    }
    sp70 = var_t1;
    temp_ret = func_8008EBC0(sp60, sp64, var_t1 >> 0x1F, var_t1);
    temp_v0_2 = temp_ret;
    temp_v1 = (u32) temp_ret;
    arg0->unk4 = (s32) temp_v1;
    arg0->unk0 = temp_v0_2;
    if ((temp_v0_2 >= 0) && ((temp_v0_2 > 0) || (temp_v1 != 0)) && (var_s0 > 0)) {
        sp3C = var_t1;
        sp38 = var_t1 >> 0x1F;
        sp40 = arg0->unk0;
        sp44 = arg0->unk4;
loop_24:
        func_8008FE98(&sp50, sp40, (u32)sp44, sp38, (u32)sp3C);
        temp_a0 = var_s0 - 1;
        arg0->unk0 = sp50;
        arg0->unk4 = sp54;
        temp_t7_2 = &sp78 + temp_a0;
        var_s0 = temp_a0;
        *temp_t7_2 = *(sp5C + var_s3);
        temp_t8_3 = arg0->unk0;
        temp_t9_2 = arg0->unk4;
        sp40 = temp_t8_3;
        sp44 = temp_t9_2;
        if ((temp_t8_3 >= 0) && ((temp_t8_3 > 0) || (temp_t9_2 != 0))) {
            if (var_s0 > 0) {
                goto loop_24;
            }
        }
    }
    temp_a2 = 0x18 - var_s0;
    arg0->unk14 = temp_a2;
    func_8008EE98(arg0->unk8, &sp78 + var_s0, temp_a2);
    temp_a1 = arg0->unk14;
    temp_a0_2 = arg0->unk24;
    if (temp_a1 < temp_a0_2) {
        arg0->unk10 = (s32) (temp_a0_2 - temp_a1);
    }
    if ((temp_a0_2 < 0) && ((arg0->unk30 & 0x14) == 0x10)) {
        temp_v0_3 = arg0->unk10;
        temp_s0 = ((arg0->unk28 - arg0->unkC) - temp_v0_3) - temp_a1;
        if (temp_s0 > 0) {
            arg0->unk10 = (s32) (temp_v0_3 + temp_s0);
        }
    }
}
