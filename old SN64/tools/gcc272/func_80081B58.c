#include "ultra64.h"
#define M2C_ERROR(x) 0
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad04[0x4];
    /* 0x08 */ void *unk8;
    /* 0x0C */ u8 pad0C[0x4];
    /* 0x10 */ s32 unk10;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x01 */ s32 unk1;
} UnkStruct_temp_a1;
typedef struct {
    /* 0x00 */ u8 pad00[0x1];
    /* 0x01 */ s32 unk1;
} UnkStruct_temp_t6;
typedef struct {
    /* 0x00 */ u8 pad00[0x1];
    /* 0x01 */ s32 unk1;
} UnkStruct_temp_t7;

s32 func_80081730(void *, void *, u32);             /* extern */

s32 func_80081B58(UnkStruct_arg0 *arg0, s32 arg1) {
    u32 temp_v0;

    temp_v0 = arg0->unk8;
    if (temp_v0 >= (u32) (arg0->unk0 + arg0->unk10)) {
        return 0;
    }
    *M2C_ERROR(/* Read from unset register $t0 */) = func_80081730(arg0, arg0, temp_v0);
    M2C_ERROR(/* Read from unset register $a2 */)->unk8 = (s32) M2C_ERROR(/* Read from unset register $a3 */);
    return 1;
}

s32 func_80081BB0(UnkStruct_arg0 *arg0) {
    UnkStruct_temp_a1 *temp_a1;
    UnkStruct_temp_t6 *temp_t6;
    UnkStruct_temp_t7 *temp_t7;
    void *temp_t9;

    temp_a1 = arg0->unk8;
    temp_t7 = temp_a1 + 1;
    arg0->unk8 = temp_t7;
    temp_t6 = temp_t7 + 1;
    arg0->unk8 = temp_t6;
    temp_t9 = temp_t6 + 1;
    arg0->unk8 = temp_t9;
    arg0->unk8 = (void *) (temp_t9 + 1);
    return (temp_a1->unk0 << 0x18) | (temp_a1->unk1 << 0x10) | (temp_t7->unk1 << 8) | temp_t6->unk1;
}

s16 func_80081C00(UnkStruct_arg0 *arg0) {
    UnkStruct_temp_a1 *temp_a1;
    void *temp_t9;

    temp_a1 = arg0->unk8;
    temp_t9 = temp_a1 + 1;
    arg0->unk8 = temp_t9;
    arg0->unk8 = (void *) (temp_t9 + 1);
    return (s16) ((temp_a1->unk0 << 8) | temp_a1->unk1);
}
