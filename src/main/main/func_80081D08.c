#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ s32 unk8;
} UnkStruct_temp_s1;
typedef struct {
    /* 0x00 */ char *unk0;
    /* 0x04 */ u8 pad04[0x4];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 pad0C[0x4];
    /* 0x10 */ s32 unk10;
} UnkStruct_var_s0;

s32 func_8007C7A8(s32);                             /* extern */
void func_8007DA18(Unk*);                            /* extern */
void func_8007DA48(Unk*, void**);                    /* extern */

void func_80081D08(void) {
    Unk *saved_reg_s2 = M2C_ERROR(/* saved s2 */);
    s32 saved_reg_s3;
    s32 temp_s4;
    UnkStruct_temp_s1 *temp_s1;
    UnkStruct_var_s0 *var_s0;

    var_s0 = saved_reg_s2->unk8;
    temp_s4 = func_8007C7A8(1);
    if (var_s0 != NULL) {
        do {
            temp_s1 = var_s0->unk0;
            if (saved_reg_s3 == var_s0->unk10) {
                if (temp_s1 != NULL) {
                    temp_s1->unk8 = (s32) (temp_s1->unk8 + var_s0->unk8);
                }
                func_8007DA18(var_s0);
                func_8007DA48(var_s0, saved_reg_s2);
            }
            var_s0 = temp_s1;
        } while (temp_s1 != NULL);
    }
    func_8007C7A8(temp_s4);
}
