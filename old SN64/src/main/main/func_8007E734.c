#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ s32 unk8;
} UnkStruct_temp_t0;
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ s32 unk8;
} UnkStruct_temp_v0_2;

s32 func_8007C7A8(s32, s32);                        /* extern */
void func_8007DA18(Unk*);                           /* extern */
void func_8007DA48(Unk*, void**);                        /* extern */
void func_8007E958(Unk*, char*, s32);                    /* extern */

void func_8007E734(void **arg0, s32 arg1, s32 arg2) {
    char *sp2C;
    s32 sp20;
    s32 sp1C;
    UnkStruct_temp_v0_2 *temp_v0_2;
    char *var_a1;
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a3;
    UnkStruct_temp_t0 *temp_t0;

    sp20 = 0;
    temp_v0 = func_8007C7A8(1, 0);
    temp_a1 = temp_v0;
    temp_t0 = *arg0;
    if (temp_t0 == NULL) {
        func_8007C7A8(temp_v0, temp_a1);
        return;
    }
    sp1C = temp_a1;
    sp2C = temp_t0;
    func_8007DA18(temp_t0);
    func_8007E958(arg1, temp_t0 + 0xC, 0x10);
    var_a3 = arg2;
    if (var_a3 == 0x7FFFFFFF) {
        sp20 = -1;
    }
    var_a1 = arg0 + 8;
    if (arg0 != (void **)-8) {
loop_5:
        temp_v0_2 = *var_a1;
        if (temp_v0_2 == NULL) {
            if (sp20 != 0) {
                temp_t0->unk8 = 0;
            } else {
                temp_t0->unk8 = var_a3;
            }
            func_8007DA48(temp_t0, var_a1);
        } else {
            temp_v1 = temp_v0_2->unk8;
            if (var_a3 < temp_v1) {
                temp_t0->unk8 = var_a3;
                temp_v0_2->unk8 = (s32) (temp_v0_2->unk8 - var_a3);
                func_8007DA48(temp_t0, var_a1);
            } else {
                var_a1 = temp_v0_2;
                var_a3 -= temp_v1;
                if (temp_v0_2 != NULL) {
                    goto loop_5;
                }
            }
        }
    }
    func_8007C7A8(sp1C, 0);
}
