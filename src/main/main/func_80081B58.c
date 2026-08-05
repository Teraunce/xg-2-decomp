#include "ultra64.h"

/*
 * streamTryReadVarInt — guarded stream-delta call, writes result to *arg1.
 *
 * Jal delay-slot ABI fix (three registers):
 *   or  $a2, $a0, $zero   — saves arg0 into $a2 before branch/jal
 *   or  $t0, $a1, $zero   — delay slot of bnez: saves arg1 (ptr) into $t0
 *   or  $a3, $v0, $zero   — saves arg0->unk8 (temp_v0) into $a3
 *   jal streamReadVarInt
 *    or $a0, $a2, $zero   — delay slot restores arg0 into $a0
 *   sw  $v0, 0x0($t0)     — *arg1 = return value
 *   sw  $a3, 0x8($a2)     — arg0->unk8 = temp_v0 (restores stream position)
 * m2c saw $a2, $a3, $t0 as unset after the jal.
 * Fixed: $t0 → arg1 (s32 *), $a2 → arg0, $a3 → (s32)temp_v0.
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad04[0x4];
    /* 0x08 */ char *unk8;
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

u8 streamReadVarInt(Unk*);                            /* extern */

s32 streamTryReadVarInt(UnkStruct_arg0 *arg0, s32 *arg1) {
    u32 temp_v0;

    temp_v0 = arg0->unk8;
    if (temp_v0 >= (u32) (arg0->unk0 + arg0->unk10)) {
        return 0;
    }
    *arg1 = streamReadVarInt(arg0);
    arg0->unk8 = (char *)(s32) temp_v0;
    return 1;
}

s32 streamReadU32(UnkStruct_arg0 *arg0) {
    UnkStruct_temp_a1 *temp_a1;
    UnkStruct_temp_t6 *temp_t6;
    UnkStruct_temp_t7 *temp_t7;
    char *temp_t9;

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

s16 streamReadS16(UnkStruct_arg0 *arg0) {
    UnkStruct_temp_a1 *temp_a1;
    char *temp_t9;

    temp_a1 = arg0->unk8;
    temp_t9 = temp_a1 + 1;
    arg0->unk8 = temp_t9;
    arg0->unk8 = (void *) (temp_t9 + 1);
    return (s16) ((temp_a1->unk0 << 8) | temp_a1->unk1);
}
