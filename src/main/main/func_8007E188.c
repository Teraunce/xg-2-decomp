#include "ultra64.h"
void func_8007DD7C(Unk*, Unk*);                        /* extern */
void func_8007E074(Unk*, char*);                         /* extern */
extern f64 D_8004C9C8;
extern f64 D_8004C9D0;

void func_8007E188(Unk *arg0, Unk *arg1, u32 arg2) {
    s16 sp140;
    s32 sp58;
    s32 sp54;
    s32 sp4C;
    s32 sp48;
    Unk *var_a0;
    Unk *var_v1;
    s32 temp_t1;
    Unk *var_a1;
    Unk *var_v0;

    func_8007E074(&sp48, arg0->unk0);
loop_1:
    var_a0 = &sp48;
    var_v1 = var_a0;
    arg1->unk0 = sp4C;
    var_v0 = arg1;
    var_a1 = arg1;
    arg1->unk4 = sp54;
    arg1->unk8 = sp58;
    do {
        var_a0 += 4;
        var_v0 += 0x10;
        var_v0->unk0 /* FIXME: was ->unk-4 */ = (s32) var_v1->unk18;
        temp_t1 = var_v1->unk58;
        var_v1 += 0x10;
        var_a1 += 4;
        var_v0->unk3C = temp_t1;
        var_a1->unk88 = (u8) var_a0->unk94;
        var_a1->unk98 = (u8) var_a0->unkA4;
        var_v0->unk9C = (s32) var_v1->unkA8;
        var_v0->unk0 = (s32) var_v1->unkC;
        var_v0->unk40 = (s32) var_v1->unk4C;
        var_a1->unk89 = (u8) var_a0->unk95;
        var_a1->unk99 = (u8) var_a0->unkA5;
        var_v0->unkA0 = (s32) var_v1->unkAC;
        var_v0->unk4 = (s32) var_v1->unk10;
        var_v0->unk44 = (s32) var_v1->unk50;
        var_a1->unk8A = (u8) var_a0->unk96;
        var_a1->unk9A = (u8) var_a0->unkA6;
        var_v0->unkA4 = (s32) var_v1->unkB0;
        var_v0->unk8 = (s32) var_v1->unk14;
        var_v0->unk48 = (s32) var_v1->unk54;
        var_a1->unk8B = (u8) var_a0->unk97;
        var_a1->unk9B = (u8) var_a0->unkA7;
        var_v0->unkA8 = (s32) var_v1->unkB4;
    } while ((void*)var_a0 != (void*)&sp58);
    func_8007DD7C(&sp48, &sp140);
    if ((sp140 != 4) && (sp54 < arg2)) {
        goto loop_1;
    }
}

s32 func_8007E2F4(Unk *arg0) {
    return arg0->unkC;
}

s32 func_8007E2FC(Unk *arg0, f32 arg1, s32 arg2) {
    f64 temp_ft2;
    f64 var_ft3;
    f64 var_ft4;
    s32 temp_ft4;
    s32 temp_t7;

    temp_t7 = ((Unk*)(s32)arg0->unk0)->unk40;
    var_ft4 = (f64) temp_t7;
    if (temp_t7 < 0) {
        var_ft4 += 4294967296.0;
    }
    var_ft3 = (f64) arg2;
    if (arg2 < 0) {
        var_ft3 += 4294967296.0;
    }
    temp_ft2 = ((f64) arg1 * D_8004C9C8 * var_ft4) / var_ft3;
    temp_ft4 = (s32) temp_ft2;
    if (0 /* cfc1 $v0, $31: FCR31 FPU status */ & 0x78) {
        if (!(0 /* cfc1 $v0, $31: FCR31 FPU status */ & 0x78)) {
            return (s32) (temp_ft2 - 2147483648.0) | 0x80000000;
        }
        /* Duplicate return node #7. Try simplifying control flow for better match */
        return -1;
    }
    if (temp_ft4 >= 0) {
        return temp_ft4;
    }
    return -1;
}

f32 func_8007E3F8(Unk *arg0, s32 arg1, s32 arg2) {
    f32 var_ft3;
    f32 var_ft4;
    s32 temp_t7;

    var_ft3 = (f32) arg2;
    if (arg2 < 0) {
        var_ft3 += 4294967296.0f;
    }
    temp_t7 = ((Unk*)(s32)arg0->unk0)->unk40;
    var_ft4 = (f32) temp_t7;
    if (temp_t7 < 0) {
        var_ft4 += 4294967296.0f;
    }
    return (f32) ((f64) ((f32) arg1 * var_ft3) / ((f64) var_ft4 * D_8004C9D0));
}

s32 func_8007E464(Unk *arg0, Unk *arg1) {
    s32 temp_v0;
    s32 var_a2;
    u32 temp_a1;
    u32 temp_t0;
    u32 temp_t0_2;
    u32 temp_t0_3;
    u32 var_v1;
    Unk *temp_a3;
    Unk *temp_a3_2;
    Unk *temp_a3_3;
    Unk *temp_a3_4;

    var_v1 = -1U;
    temp_v0 = arg0->unk10;
    if (arg0->unk4 == 0) {
        return 0;
    }
    var_a2 = 0;
    do {
        if (((u32) arg0->unk4 >> var_a2) & 1) {
            temp_a3 = arg0 + (var_a2 * 4);
            if (arg0->unk14 != 0) {
                temp_a3->unkB8 = (u32) (temp_a3->unkB8 - temp_v0);
            }
            temp_t0 = temp_a3->unkB8;
            if (temp_t0 < var_v1) {
                var_v1 = temp_t0;
            }
        }
        if ((arg0->unk4 >> (var_a2 + 1)) & 1) {
            temp_a3_2 = arg0 + (var_a2 * 4);
            if (arg0->unk14 != 0) {
                temp_a3_2->unkBC = (u32) (temp_a3_2->unkBC - temp_v0);
            }
            temp_t0_2 = temp_a3_2->unkBC;
            if (temp_t0_2 < var_v1) {
                var_v1 = temp_t0_2;
            }
        }
        if ((arg0->unk4 >> (var_a2 + 2)) & 1) {
            temp_a3_3 = arg0 + (var_a2 * 4);
            if (arg0->unk14 != 0) {
                temp_a3_3->unkC0 = (u32) (temp_a3_3->unkC0 - temp_v0);
            }
            temp_t0_3 = temp_a3_3->unkC0;
            if (temp_t0_3 < var_v1) {
                var_v1 = temp_t0_3;
            }
        }
        if ((arg0->unk4 >> (var_a2 + 3)) & 1) {
            temp_a3_4 = arg0 + (var_a2 * 4);
            if (arg0->unk14 != 0) {
                temp_a3_4->unkC4 = (u32) (temp_a3_4->unkC4 - temp_v0);
            }
            temp_a1 = temp_a3_4->unkC4;
            if (temp_a1 < var_v1) {
                var_v1 = temp_a1;
            }
        }
        var_a2 += 4;
    } while (var_a2 != 0x10);
    arg0->unk14 = 0;
    arg1->unk0 = var_v1;
    return 1;
}

s32 func_8007E5D8(Unk *arg0) {
    return arg0->unk2C;
}
