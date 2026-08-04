#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ s32 unk8;
    /* 0x09 */ s32 unk9;
    /* 0x0D */ u8 pad0D[0xB];
    /* 0x18 */ char *unk18;
    /* 0x1C */ u8 pad1C[0x4];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8 pad28[0x4];
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ u8 pad30[0x1];
    /* 0x31 */ s32 unk31;
    /* 0x35 */ u8 pad35[0x2B];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ char *unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ char *unk6C;
    /* 0x70 */ u8 pad70[0xC];
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ u8 pad00[0x18];
    /* 0x18 */ char *unk18;
    /* 0x1C */ u8 pad1C[0x8];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8 pad28[0x38];
    /* 0x60 */ s32 unk60;
} UnkStruct_arg1;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x01 */ s32 unk1;
    /* 0x02 */ s32 unk2;
    /* 0x03 */ s32 unk3;
    /* 0x07 */ u8 pad07[0xD];
    /* 0x14 */ s32 unk14;
} UnkStruct_temp_a2;
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ char *unk4;
} UnkStruct_temp_a3;
typedef struct {
    /* 0x00 */ u8 pad00[0x7];
    /* 0x07 */ s32 unk7;
    /* 0x08 */ s32 unk8;
    /* 0x09 */ s32 unk9;
    /* 0x0D */ u8 pad0D[0x1];
    /* 0x0E */ s32 unkE;
} UnkStruct_temp_v0;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad04[0x10];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 pad18[0x19];
    /* 0x31 */ s8 unk31;
    /* 0x32 */ s8 unk32;
    /* 0x33 */ s8 unk33;
} UnkStruct_temp_v1;
typedef struct {
    /* 0x00 */ char *unk0;
    /* 0x04 */ u8 pad04[0x2D];
    /* 0x31 */ s32 unk31;
    /* 0x32 */ s32 unk32;
    /* 0x35 */ s32 unk35;
} UnkStruct_var_v1;

void func_8007E734(void **, s32, s32);           /* extern */
void func_80081704(Unk*, Unk*);                   /* extern */
s32 func_80081720(Unk*);                           /* extern */
s32 func_80081B58(UnkStruct_arg0*, s32*);                    /* extern */

void func_80080228(UnkStruct_arg0 *arg0) {
    s16 sp28;
    s32 sp24;
    s32 sp20;
    s32 temp_a2;
    s32 temp_v0;

    temp_a2 = arg0->unk18;
    if ((arg0->unk2C == 1) && (temp_a2 != 0)) {
        sp20 = temp_a2;
        if (func_80081B58(temp_a2, &sp24) != 0) {
            if ((arg0->unk84 != 0) && ((func_80081720(sp20) + sp24) >= ((Unk *)arg0->unk80)->unk8)) {
                func_80081704(sp20, arg0->unk7C);
                temp_v0 = arg0->unk84;
                if (temp_v0 != -1) {
                    arg0->unk84 = (s32) (temp_v0 - 1);
                }
            }
            sp28 = 0;
            func_8007E734((void **)(arg0 + 0x48), &sp28, arg0->unk24 * sp24);
        }
    }
}

void func_80080304(UnkStruct_arg0 *arg0, UnkStruct_arg1 *arg1) {
    UnkStruct_temp_a2 *temp_a2;
    UnkStruct_temp_v0 *temp_v0;

    if ((arg0->unk8 == 0xFF) && (temp_v0 = arg0 + 4, (arg0->unk9 == 0x51))) {
        temp_a2 = arg1->unk18;
        if (temp_a2 != NULL) {
            arg1->unk24 = (s32) ((f32) ((temp_v0->unk7 << 0x10) | (temp_v0->unk8 << 8) | temp_v0->unk9) * temp_a2->unk14);
            return;
        }
        arg1->unk24 = 0x1E8;
    }
}

s32 func_8008037C(UnkStruct_arg0 *arg0, UnkStruct_arg1 *arg1) {
    s32 var_v1;

    var_v1 = (((Unk*)(s32)(arg1->unk60 + (arg0->unk31 * 0x10)))->unk7 + ((Unk *)arg0->unk20)->unkC) - 0x40;
    if (var_v1 <= 0) {
        var_v1 = 0;
    }
    if (var_v1 >= 0x7F) {
        var_v1 = 0x7F;
    }
    return var_v1 & 0xFF;
}

char *func_800803C4(UnkStruct_arg0 *arg0, s32 arg1, s32 arg2) {
    u8 temp_a0;
    UnkStruct_var_v1 *var_v1;

    var_v1 = arg0->unk64;
    if (var_v1 != NULL) {
loop_2:
        if (((arg1 & 0xFF) == var_v1->unk32) && ((arg2 & 0xFF) == var_v1->unk31)) {
            temp_a0 = var_v1->unk35;
            if ((temp_a0 != 3) && (temp_a0 != 4)) {
                return var_v1;
            }
        }
        var_v1 = var_v1->unk0;
        if (var_v1 == NULL) {
            /* Duplicate return node #8. Try simplifying control flow for better match */
            return NULL;
        }
        goto loop_2;
    }
    return NULL;
}

char *func_80080438(UnkStruct_arg0 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    UnkStruct_temp_v1 *temp_v1;

    temp_v1 = arg0->unk6C;
    if (temp_v1 != NULL) {
        arg0->unk6C = (void *) temp_v1->unk0;
        temp_v1->unk0 = 0;
        if (arg0->unk64 == 0) {
            arg0->unk64 = temp_v1;
        } else {
            *(Unk**)(s32)arg0->unk68 = temp_v1;
        }
        arg0->unk68 = temp_v1;
        temp_v1->unk31 = (s8) (arg3 & 0xFF);
        temp_v1->unk32 = (s8) (arg1 & 0xFF);
        temp_v1->unk33 = (s8) (arg2 & 0xFF);
        temp_v1->unk14 = temp_v1;
    }
    return temp_v1;
}

char *func_800804A8(UnkStruct_arg0 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 var_t0;
    s32 temp_t3;
    s32 temp_t5;
    s32 temp_t6;
    s32 var_v1;
    u8 temp_t2;
    UnkStruct_temp_a2 *temp_a2;
    UnkStruct_temp_a3 *temp_a3;
    UnkStruct_temp_v0 *temp_v0;

    temp_v0 = *(UnkStruct_temp_v0**)(s32)(arg0->unk60 + ((arg3 & 0xFF) * 0x10));
    temp_t6 = arg1 & 0xFF;
    temp_t3 = arg2 & 0xFF;
    var_t0 = temp_v0->unkE;
    var_v1 = 1;
    if (var_t0 > 0) {
loop_1:
        temp_t5 = (s32) (var_v1 + var_t0) / 2;
        temp_a3 = ((Unk*)((char*)temp_v0 + (temp_t5 * 4)))->unkC;
        temp_a2 = temp_a3->unk4;
        temp_t2 = temp_a2->unk2;
        if ((temp_t6 >= (s32) temp_t2) && ((s32) temp_a2->unk3 >= temp_t6) && (temp_t3 >= (s32) temp_a2->unk0) && ((s32) temp_a2->unk1 >= temp_t3)) {
            return temp_a3;
        }
        if ((temp_t6 < (s32) temp_t2) || ((temp_t3 < (s32) temp_a2->unk0) && ((s32) temp_a2->unk3 >= temp_t6))) {
            var_t0 = temp_t5 - 1;
        } else {
            var_v1 = temp_t5 + 1;
        }
        if (var_t0 < var_v1) {
            /* Duplicate return node #12. Try simplifying control flow for better match */
            return NULL;
        }
        goto loop_1;
    }
    return NULL;
}
