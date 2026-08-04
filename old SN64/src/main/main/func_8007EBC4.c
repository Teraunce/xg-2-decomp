#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ s32 unk8;
    /* 0x09 */ s32 unk9;
} UnkStruct_arg1;
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ s32 unk8;
} UnkStruct_temp_a0;
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ s32 unk8;
} UnkStruct_temp_s2;
typedef struct {
    /* 0x00 */ u8 pad00[0x7];
    /* 0x07 */ s32 unk7;
    /* 0x08 */ s32 unk8;
    /* 0x09 */ s32 unk9;
} UnkStruct_temp_v0;
typedef struct {
    /* 0x00 */ char *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
} UnkStruct_var_s1;
typedef struct {
    /* 0x00 */ char *unk0;
    /* 0x04 */ u8 pad04[0x4];
    /* 0x08 */ s32 unk8;
} UnkStruct_var_s1_2;

s32 func_8007C7A8(s32);                             /* extern */
void func_8007DA18(Unk*);                               /* extern */
void func_8007DA48(Unk*, void**);                        /* extern */
void func_8007EB88(void*);                           /* extern */

void func_8007EBC4(UnkStruct_arg1 *arg1) {
    Unk *saved_reg_s7 = M2C_ERROR(/* saved s7 */);
    UnkStruct_temp_a0 *temp_a0;
    UnkStruct_temp_s2 *temp_s2;
    char *temp_s2_2;
    char *var_s0_2;
    UnkStruct_var_s1 *var_s1;
    UnkStruct_var_s1_2 *var_s1_2;
    char *var_s3;
    s32 temp_fp;
    s32 temp_s3;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_s0;
    char *temp_s4;
    UnkStruct_temp_v0 *temp_v0;

    var_s0 = 0;
    var_s3 = NULL;
    if (arg1->unk8 == 0xFF) {
        temp_v0 = arg1 + 4;
        if (arg1->unk9 == 0x51) {
            temp_fp = saved_reg_s7->unk24;
            func_8007EB88(saved_reg_s7);
            var_s1 = saved_reg_s7->unk50;
            if (var_s1 != NULL) {
                do {
                    temp_s2 = var_s1->unk0;
                    var_s0 += var_s1->unk8;
                    if (var_s1->unkC == 0x15) {
                        func_8007DA18(var_s1);
                        if (var_s3 != NULL) {
                            func_8007DA48(var_s1, var_s3);
                        } else {
                            var_s1->unk0 = NULL;
                            var_s1->unk4 = 0;
                            var_s3 = var_s1;
                        }
                        temp_v1 = var_s0;
                        if (temp_s2 != NULL) {
                            temp_v0_2 = var_s1->unk8;
                            var_s0 -= temp_v0_2;
                            temp_s2->unk8 = (s32) (temp_s2->unk8 + temp_v0_2);
                        }
                        var_s1->unk8 = temp_v1;
                    }
                    var_s1 = temp_s2;
                } while (temp_s2 != NULL);
            }
            var_s1_2 = var_s3;
            if (var_s3 != NULL) {
                temp_s4 = saved_reg_s7 + 0x48;
                do {
                    temp_s2_2 = var_s1_2->unk0;
                    var_s0_2 = temp_s4 + 8;
                    var_s1_2->unk8 = (s32) (saved_reg_s7->unk24 * ((s32) var_s1_2->unk8 / temp_fp));
                    temp_s3 = func_8007C7A8(1);
                    if (temp_s4 != (void *)-8) {
loop_15:
                        temp_a0 = *var_s0_2;
                        if (temp_a0 == NULL) {
                            func_8007DA48(var_s1_2, var_s0_2);
                        } else {
                            temp_v0_3 = var_s1_2->unk8;
                            temp_v1_2 = temp_a0->unk8;
                            if (temp_v0_3 < temp_v1_2) {
                                temp_a0->unk8 = (s32) (temp_v1_2 - temp_v0_3);
                                func_8007DA48(var_s1_2, var_s0_2);
                            } else {
                                var_s1_2->unk8 = (s32) (temp_v0_3 - temp_v1_2);
                                var_s0_2 = *var_s0_2;
                                if (var_s0_2 != NULL) {
                                    goto loop_15;
                                }
                            }
                        }
                    }
                    func_8007C7A8(temp_s3);
                    var_s1_2 = temp_s2_2;
                } while (temp_s2_2 != NULL);
            }
        }
    }
}
