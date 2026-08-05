#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} UnkStruct_arg1;
typedef struct {
    /* 0x00 */ u8 pad00[0x18];
    /* 0x18 */ char *unk18;
    /* 0x1C */ u8 pad1C[0x3C];
    /* 0x58 */ s32 unk58;
} UnkStruct_temp_a2;
typedef struct {
    /* 0x00 */ u8 pad00[0x58];
    /* 0x58 */ s32 unk58;
} UnkStruct_temp_a2_2;
typedef struct {
    /* 0x00 */ char *unk0;
    /* 0x01 */ s32 unk1;
} UnkStruct_temp_a3_2;
typedef struct {
    /* 0x00 */ u8 pad00[0x1];
    /* 0x01 */ s32 unk1;
} UnkStruct_temp_t8;
typedef struct {
    /* 0x00 */ u8 pad00[0x1];
    /* 0x01 */ s32 unk1;
} UnkStruct_temp_t9;
typedef struct {
    /* 0x00 */ u8 pad00[0x98];
    /* 0x98 */ u8 unk98;
} UnkStruct_temp_v0;
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 pad10[0x4];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 pad1C[0x2C];
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ u8 pad50[0x4];
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0x48];
    /* 0xA4 */ s32 unkA4;
    /* 0xA8 */ s32 unkA8;
    /* 0xAC */ u8 padAC[0x4];
    /* 0xB0 */ s32 unkB0;
    /* 0xB4 */ s32 unkB4;
} UnkStruct_var_a2;
typedef struct {
    /* 0x00 */ u8 pad00[0x8A];
    /* 0x8A */ s32 unk8A;
    /* 0x8B */ u8 unk8B;
    /* 0x8C */ u8 pad8C[0xA];
    /* 0x96 */ s32 unk96;
    /* 0x97 */ u8 unk97;
    /* 0x98 */ u8 pad98[0x2];
    /* 0x9A */ u8 unk9A;
    /* 0x9B */ u8 unk9B;
    /* 0x9C */ u8 pad9C[0xA];
    /* 0xA6 */ u8 unkA6;
    /* 0xA7 */ u8 unkA7;
} UnkStruct_var_a3;
typedef struct {
    /* 0x00 */ u8 pad00[0x8B];
    /* 0x8B */ s32 unk8B;
    /* 0x8C */ s32 unk8C;
    /* 0x90 */ u8 pad90[0x7];
    /* 0x97 */ s32 unk97;
    /* 0x98 */ s32 unk98;
    /* 0x9A */ s32 unk9A;
    /* 0x9B */ s32 unk9B;
    /* 0x9F */ u8 pad9F[0x7];
    /* 0xA6 */ s32 unkA6;
    /* 0xA7 */ s32 unkA7;
} UnkStruct_var_t0;
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 pad0C[0x4];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 pad18[0x2C];
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ u8 pad4C[0x4];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ u8 pad58[0x4C];
    /* 0xA4 */ s32 unkA4;
    /* 0xA8 */ s32 unkA8;
    /* 0xAC */ u8 padAC[0x4];
    /* 0xB0 */ s32 unkB0;
    /* 0xB4 */ s32 unkB4;
} UnkStruct_var_v1;

void func_80082B98();                                  /* extern */

void func_8007DAB0(s32 arg0) {
    if ((s32)M2C_ERROR(/* Read from unset register $t6 */) == 0) {
        *(s32*)(s32)M2C_ERROR(/* Read from unset register $v0 */) = arg0;
        func_80082B98();
    }
}

void func_8007DAD8(UnkStruct_arg0 *arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = 0x10 - (arg1 & 0xF);
    if (temp_v0 != 0x10) {
        arg0->unk0 = (s32) (arg1 + temp_v0);
    } else {
        arg0->unk0 = arg1;
    }
    arg0->unk8 = arg2;
    arg0->unkC = 0;
    arg0->unk4 = (s32) arg0->unk0;
}

void func_8007DB18(UnkStruct_arg0 *arg0, UnkStruct_arg1 *arg1) {
    s32 temp_t1;
    s32 var_v0;
    u8 temp_t2;
    UnkStruct_var_a2 *var_a2;
    UnkStruct_var_a3 *var_a3;
    UnkStruct_var_t0 *var_t0;
    UnkStruct_var_v1 *var_v1;

    var_a2 = arg0;
    var_t0 = arg0;
    arg1->unk0 = (s32) arg0->unk4;
    var_v0 = 0;
    var_v1 = arg1;
    arg1->unk4 = (s32) arg0->unkC;
    var_a3 = arg1;
    arg1->unk8 = (s32) arg0->unk10;
    do {
        var_v0 += 2;
        var_v1 += 8;
        var_v1->unk4 = (s32) var_a2->unk18;
        temp_t1 = var_a2->unk58;
        var_a2 += 8;
        var_a3 += 2;
        var_v1->unk44 = temp_t1;
        temp_t2 = var_t0->unk98;
        var_t0 += 2;
        var_a3->unk8A = temp_t2;
        var_a3->unk9A = (u8) var_t0->unkA6;
        var_v1->unkA4 = (s32) var_a2->unkB0;
        var_v1->unk8 = (s32) var_a2->unk14;
        var_v1->unk48 = (s32) var_a2->unk54;
        var_a3->unk8B = (u8) var_t0->unk97;
        var_a3->unk9B = (u8) var_t0->unkA7;
        var_v1->unkA8 = (s32) var_a2->unkB4;
    } while (var_v0 != 0x10);
}

void func_8007DBB8(UnkStruct_arg0 *arg0, UnkStruct_arg1 *arg1) {
    s32 temp_t1;
    s32 var_v0;
    u8 temp_t2;
    UnkStruct_var_a2 *var_a2;
    UnkStruct_var_a3 *var_a3;
    UnkStruct_var_t0 *var_t0;
    UnkStruct_var_v1 *var_v1;

    var_v1 = arg0;
    var_a3 = arg0;
    arg0->unk4 = (s32) arg1->unk0;
    var_v0 = 0;
    var_a2 = arg1;
    arg0->unkC = (s32) arg1->unk4;
    var_t0 = arg1;
    arg0->unk10 = (s32) arg1->unk8;
    do {
        var_v0 += 2;
        var_v1 += 8;
        var_v1->unk10 = (s32) var_a2->unkC;
        temp_t1 = var_a2->unk4C;
        var_a2 += 8;
        var_a3 += 2;
        var_v1->unk50 = temp_t1;
        temp_t2 = var_t0->unk8C;
        var_t0 += 2;
        var_a3->unk96 = temp_t2;
        var_a3->unkA6 = (u8) var_t0->unk9A;
        var_v1->unkB0 = (s32) var_a2->unkA4;
        var_v1->unk14 = (s32) var_a2->unk8;
        var_v1->unk54 = (s32) var_a2->unk48;
        var_a3->unk97 = (u8) var_t0->unk8B;
        var_a3->unkA7 = (u8) var_t0->unk9B;
        var_v1->unkB4 = (s32) var_a2->unkA8;
    } while (var_v0 != 0x10);
}

u8 func_8007DC58(s32 arg0, s32 arg1) {
    u8 *temp_a3;
    u8 *temp_a3_3;
    u8 temp_a0;
    u8 var_v1;
    UnkStruct_temp_a2 *temp_a2;
    UnkStruct_temp_a2_2 *temp_a2_2;
    UnkStruct_temp_a3_2 *temp_a3_2;
    char *temp_t6;
    char *temp_t7;
    UnkStruct_temp_t8 *temp_t8;
    UnkStruct_temp_t9 *temp_t9;
    UnkStruct_temp_v0 *temp_v0;

    temp_v0 = arg0 + arg1;
    temp_a2 = arg0 + (arg1 * 4);
    if (temp_v0->unk98 != 0) {
        temp_a2_2 = arg0 + (arg1 * 4);
        temp_a3 = temp_a2_2->unk58;
        temp_a2_2->unk58 = (u8 *) (temp_a3 + 1);
        temp_v0->unk98 = (u8) (temp_v0->unk98 - 1);
        return *temp_a3;
    }
    temp_a3_2 = temp_a2->unk18;
    var_v1 = temp_a3_2->unk0;
    temp_t8 = temp_a3_2 + 1;
    temp_a2->unk18 = temp_t8;
    if (var_v1 == 0xFE) {
        temp_a0 = temp_a3_2->unk1;
        temp_t9 = temp_t8 + 1;
        temp_a2->unk18 = temp_t9;
        temp_t6 = temp_t9 + 1;
        if (temp_a0 != 0xFE) {
            temp_a2->unk18 = temp_t6;
            temp_t7 = temp_t6 + 1;
            temp_a2->unk18 = temp_t7;
            temp_a2->unk58 = (u8 *) ((temp_t7 - ((temp_a0 << 8) + temp_t8->unk1)) - 4);
            temp_v0->unk98 = (u8) temp_t9->unk1;
            temp_a3_3 = temp_a2->unk58;
            var_v1 = *temp_a3_3;
            temp_a2->unk58 = (u8 *) (temp_a3_3 + 1);
            temp_v0->unk98 = (u8) (temp_v0->unk98 - 1);
        }
    }
    return var_v1;
}
