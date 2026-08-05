#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x50];
    /* 0x50 */ char *unk50;
    /* 0x54 */ u8 pad54[0x10];
    /* 0x64 */ char *unk64;
    /* 0x68 */ char *unk68;
    /* 0x6C */ char *unk6C;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ char *unk0;
    /* 0x04 */ u8 pad04[0x4];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_var_a3;
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ s32 unk8;
} UnkStruct_temp_v0;

void func_8007DA18(Unk*);                           /* extern */
void func_8007DA48(Unk*, void**);                        /* extern */

u8 func_80080110(UnkStruct_arg0 *arg0, s32 arg1, s32 arg2) {
    char *sp2C;
    u8 sp1F;
    s32 temp_v1;
    s32 var_t0;
    u8 var_t1;
    UnkStruct_temp_v0 *temp_v0;
    UnkStruct_var_a3 *var_a3;

    var_a3 = arg0->unk50;
    var_t0 = 0;
    var_t1 = 1;
    if (var_a3 != NULL) {
loop_2:
        temp_v1 = var_a3->unk8;
        temp_v0 = var_a3->unk0;
        var_t0 += temp_v1;
        if ((var_a3->unkC == 5) && (arg1 == var_a3->unk10)) {
            if (arg2 < var_t0) {
                if (temp_v0 != NULL) {
                    temp_v0->unk8 = (s32) (temp_v0->unk8 + temp_v1);
                }
                sp2C = var_a3;
                sp1F = 1;
                func_8007DA18(var_a3);
                func_8007DA48(sp2C, (char *)arg0 + 0x48);
                var_t1 = 1;
            } else {
                var_t1 = 0;
            }
        } else {
            var_a3 = temp_v0;
            if (temp_v0 != NULL) {
                goto loop_2;
            }
        }
    }
    return var_t1;
}

void func_800801B8(UnkStruct_arg0 *arg0, s32 arg1) {
    void **var_v0;
    void **var_v1;

    var_v1 = arg0->unk64;
    var_v0 = NULL;
    if (var_v1 != NULL) {
loop_1:
        if (var_v1 == (void **)(arg1 - 4)) {
            if (var_v0 != NULL) {
                *var_v0 = *var_v1;
            } else {
                arg0->unk64 = *var_v1;
            }
            if ((void *)var_v1 == (void *)arg0->unk68) {
                arg0->unk68 = (char *)var_v0;
            }
            *var_v1 = arg0->unk6C;
            arg0->unk6C = (char *)var_v1;
            return;
        }
        var_v0 = var_v1;
        var_v1 = *var_v1;
        if (var_v1 == NULL) {

        } else {
            goto loop_1;
        }
    }
}
