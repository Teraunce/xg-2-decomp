#include "ultra64.h"
void entityListPrune(void);                              /* extern */
s32 vec3Normalize(f32 *, f32 *, f32 *);               /* extern */
void vec3Cross(Unk*, Unk*, Unk*);               /* extern */
s32 func_800FDD50(f32 *, f32 *, f32 *, f32 *, s32, f32 *); /* extern */
extern f32 D_8004BBFC;
extern f32 D_8004BC00;
extern f32 D_8004BC04;
extern f32 D_8004BC08;
extern f32 D_8004BC0C;
extern s32 gColorSwapMode;
extern s32 D_80091FD0;
extern s32 D_800B332C;
extern s32 D_8017CC80;
extern Unk *D_8017CCB8;
extern Unk D_80182EA8;

void trackNodeRender(s32 arg0, s32 arg1, u16 arg2, s32 arg3) {
    f32 spA8;
    f32 sp70;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp20;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft2;
    f32 temp_fv0;
    s32 var_condition_bit;
    s32 var_s6;
    s32 var_v0;
    u16 temp_a2;
    u16 temp_v1_2;
    u16 var_a0;
    u16 var_s3;
    Unk *temp_s0;
    Unk *temp_s2;
    Unk *temp_v1;
    Unk *var_v1;
    Unk *var_v1_2;
    Unk *spA4;

    var_s6 = 0;
    var_s3 = arg2;
    temp_fs3 = D_8004BC00;
    spA8 = D_8004BBFC;
    temp_fs2 = D_8004BC04;
    *(((s32) (((Unk *)((char *)(s32)arg0 + arg2 * 0x38))->unk16 << 0x10) >> 0x1B) + &D_8017CC80) = 1;
    var_v0 = var_s3 * 8;
loop_1:
    temp_a2 = ((Unk *)((char *)(s32)arg0 + (var_v0 - var_s3) * 8))->unk18;
    if ((temp_a2 != var_s3) && (temp_v1 = (Unk *)((char *)(s32)arg0 + temp_a2 * 0x38), (*(((s32) (temp_v1->unk16 << 0x10) >> 0x1B) + &D_8017CC80) == 0))) {
        if (*(s32*)((char*)temp_v1 - 20)== 0x8000) {
            trackNodeRender(arg0, arg1, temp_a2, arg3);
        }
    }
    temp_s2 = (Unk *)((char *)(s32)arg0 + var_s3 * 0x38);
    temp_s2->unk12 = (u16) ((Unk *)((char *)temp_s2 + (D_80182EA8.unk16E0 % 3) * 2))->unk2C;
    if (gColorSwapMode != 0) {
        temp_s2->unk0 = (s32) -temp_s2->unk0;
        temp_s2->unkC = (u16) -(s32) temp_s2->unkC;
    }
    if (D_800B332C == 0) {
        if (temp_s2->unk16 & (D_80091FD0 * 4)) {
            sp30 = (f32) (temp_s2->unk38 - temp_s2->unk0);
            sp34 = (f32) (temp_s2->unk3C - temp_s2->unk4);
            sp38 = (f32) (temp_s2->unk40 - temp_s2->unk8);
            sp10 = (f32) (s16) temp_s2->unkC;
            sp14 = (f32) temp_s2->unkE;
            sp18 = (f32) temp_s2->unk10;
            vec3Cross(&sp30, &sp10, &sp20);
            vec3Cross(&sp30, &sp20, &sp10);
            vec3Normalize(&sp10, &sp14, &sp18);
            sp40 = (f32) temp_s2->unk0;
            sp44 = (f32) temp_s2->unk4;
            sp48 = (f32) temp_s2->unk8;
            do {
                sp50 = sp40 + (sp10 * temp_fs3);
                sp54 = sp44 + (sp14 * temp_fs3);
                sp58 = sp48 + (sp18 * temp_fs3);
                func_800FDD50(&sp40, &sp50, (f32 *)0x14, NULL, 0, &sp70);
                temp_ft1 = sp50 - sp40;
                temp_ft0 = sp54 - sp44;
                temp_fv0 = sp58 - sp48;
                sp60 = temp_ft1;
                temp_ft2 = (sp10 * temp_ft1) + (sp14 * temp_ft0) + (sp18 * temp_fv0);
                sp64 = temp_ft0;
                var_condition_bit = temp_ft2 <= 0.0f;
                sp68 = temp_fv0;
                if (temp_ft2 <= 0.0f) {
                    sp40 += sp10 * temp_fs2;
                    sp44 += sp14 * temp_fs2;
                    sp48 += sp18 * temp_fs2;
                    var_condition_bit = temp_ft2 <= 0.0f;
                }
            } while (var_condition_bit);
            if (temp_ft2 < spA8) {
                spA8 = temp_ft2;
            }
            temp_s0 = (Unk *)((char *)(s32)arg0 + var_s3 * 0x38);
            temp_s0->unk32 = (s16) (s32) (temp_ft2 + D_8004BC08);
            sp40 -= sp10 * D_8004BC0C;
            sp48 -= sp18 * D_8004BC0C;
            sp44 -= sp14 * D_8004BC0C;
            func_800FDD50(&sp18, &sp14, &sp50, &sp40, 0x14, &sp70);
            if ((s32)spA4 == D_8017CCB8->unk8) {
                temp_s0->unk34 = 0;
            } else {
                temp_s0->unk34 = spA4;
            }
            if ((var_s6 == 0) && ((u32) (D_80182EA8.unk16D8 - 1) < 2U) && (spA4 != NULL) && (spA4->unk5C == 0x63)) {
                var_v1 = (Unk *)((char *)(s32)arg0 + var_s3 * 0x38);
                var_a0 = var_s3;
                if (*(s32*)((char*)var_v1 - 20)!= 0x8000) {
                    do {
                        var_v1 -= 0x38;
                        var_a0 -= 1;
                    } while (*(s32*)((char*)var_v1 - 20)!= 0x8000);
                }
                var_v1_2 = (Unk *)((char *)(s32)arg0 + var_a0 * 0x38);
                if (var_v1_2->unk18 != 0x8000) {
                    var_a0 = 0x8000;
                    do {
                        var_v1_2->unk32 = 0x206;
                        var_v1_2->unk34 = 0;
                        var_v1_2->unk16 = (u16) (var_v1_2->unk16 & ~0x1C);
                        var_v1_2 += 0x38;
                    } while (var_v1_2->unk18 != 0x8000);
                }
                var_s6 = 1;
                entityListPrune();
                var_s3 += 1;
            } else {
                goto block_32;
            }
        } else {
            temp_s2->unk32 = 0x206;
            temp_s2->unk34 = 0;
            goto block_32;
        }
    } else {
block_32:
        var_s3 += 1;
    }
    temp_v1_2 = ((Unk *)((char *)(s32)arg0 + var_s3 * 0x38))->unk18;
    if (temp_v1_2 != 0x8000) {
        if (temp_v1_2 & 0x8000) {
            var_s3 = temp_v1_2 & 0x7FFF;
        }
        var_v0 = var_s3 * 8;
        if (var_s3 != arg2) {
            goto loop_1;
        }
    }
}
