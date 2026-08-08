#include "ultra64.h"
void sfxFlushTimers(Unk*);                            /* extern */
extern f64 D_8004CEB0;
extern char *gPendingFlushFlag;

char *audioBuildFrame(char *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    Unk *spB4;
    s16 spAA;
    f64 temp_fs0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s3;
    s32 var_s5;
    s32 var_v1;
    Unk *temp_s1;
    Unk *temp_s2;
    Unk *var_s4;
    Unk *var_v0;
    Unk *var_v1_2;

    temp_s1 = gPendingFlushFlag;
    spAA = 0;
    var_s3 = arg3;
    var_s4 = arg0;
    var_s5 = arg2;
    if (temp_s1->unk0 == 0) {
        *arg1 = 0;
        return arg0;
    }
    spB4 = NULL;
    var_v0 = temp_s1->unk0;
    var_v1 = 0x7FFFFFFF;
    if (var_v0 != NULL) {
        do {
            if ((var_v0->unk10 - temp_s1->unk20) < var_v1) {
                spB4 = var_v0;
                var_v1 = var_v0->unk10 - temp_s1->unk20;
            }
            var_v0 = var_v0->unk0;
        } while (var_v0 != NULL);
    }
    temp_v0 = spB4->unk10;
    temp_s1->unk1C = temp_v0;
    if ((temp_v0 - temp_s1->unk20) < var_s3) {
        temp_fs0 = D_8004CEB0;
        do {
            var_s0 = 0x7FFFFFFF;
            temp_s1->unk1C = (s32) (temp_s1->unk1C & ~0xF);
            spB4->unk10 = (s32) (spB4->unk10 + (s32) (f32) (((f64) ((f32) ((s32(*)())(s32)spB4->unk8)(spB4) * (f32) temp_s1->unk44) / temp_fs0) + 0.5));
            spB4 = NULL;
            var_v1_2 = temp_s1->unk0;
            if (var_v1_2 != NULL) {
                do {
                    if ((var_v1_2->unk10 - temp_s1->unk20) < var_s0) {
                        spB4 = var_v1_2;
                        var_s0 = var_v1_2->unk10 - temp_s1->unk20;
                    }
                    var_v1_2 = var_v1_2->unk0;
                } while (var_v1_2 != NULL);
            }
            temp_v0_2 = spB4->unk10;
            temp_s1->unk1C = temp_v0_2;
        } while ((temp_v0_2 - temp_s1->unk20) < var_s3);
    }
    temp_s1->unk1C = (s32) (temp_s1->unk1C & ~0xF);
    if (var_s3 > 0) {
        do {
            temp_v0_3 = temp_s1->unk48;
            var_s0_2 = var_s3;
            if (temp_v0_3 < var_s3) {
                var_s0_2 = temp_v0_3;
            }
            var_s4->unk0 = 0x07000000;
            var_s4->unk4 = 0;
            temp_s2 = temp_s1->unk38;
            ((s32(*)())(s32)temp_s2->unk8)(temp_s2, 6, var_s5);
            var_s3 -= var_s0_2;
            var_s4 = ((s32(*)())(s32)temp_s2->unk4)(temp_s2, &spAA, var_s0_2, temp_s1->unk20, var_s4 + 8);
            var_s5 += var_s0_2 * 4;
            temp_s1->unk20 = (s32) (temp_s1->unk20 + var_s0_2);
        } while (var_s3 > 0);
    }
    *arg1 = (s32) (((char*)var_s4) - arg0) >> 3;
    sfxFlushTimers(temp_s1);
    return var_s4;
}
