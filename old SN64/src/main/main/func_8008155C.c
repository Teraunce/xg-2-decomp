#include "ultra64.h"
void func_8007E8E4(Unk*, s32, s32);                  /* extern */
char *func_8007FD48(s32, s32, s32, u8, s32);               /* extern */
void func_800814EC(Unk*);                            /* extern */
void func_80086088(void *, void *);                       /* extern */
extern s32 D_800952D0;
extern s32 func_80080DC4;

void func_8008155C(Unk *arg0, Unk *arg1) {
    s32 sp2C;
    char *temp_v0;
    char *var_v1;
    s32 temp_a2;
    s32 var_a0;

    temp_a2 = arg1->unkC;
    arg0->unk20 = 0;
    arg0->unk18 = 0;
    arg0->unk30 = 0xFF;
    arg0->unk24 = 0x1E8;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk32 = 0x7FFF;
    arg0->unk14 = (s32) D_800952D0;
    arg0->unk5C = 0x3E80;
    arg0->unk1C = 0;
    arg0->unk35 = (u8) arg1->unk9;
    arg0->unk70 = (s32) arg1->unk10;
    arg0->unk74 = (s32) arg1->unk14;
    arg0->unk7C = 0;
    arg0->unk80 = 0;
    arg0->unk84 = 0;
    arg0->unk38 = 9;
    arg0->unk78 = (s32) arg1->unk18;
    arg0->unk34 = (u8) arg1->unk8;
    sp2C = temp_a2;
    arg0->unk60 = func_8007FD48(0, 0, temp_a2, arg1->unk8, 0x10);
    func_800814EC(arg0);
    temp_v0 = func_8007FD48(0, 0, temp_a2, (u8) arg1->unk0, 0x38);
    arg0->unk6C = 0;
    var_a0 = 0;
    if (arg1->unk0 > 0) {
        var_v1 = temp_v0;
        do {
            var_a0 += 1;
            *var_v1 = arg0->unk6C;
            arg0->unk6C = var_v1;
            var_v1 += 0x38;
        } while (var_a0 < arg1->unk0);
    }
    arg0->unk64 = 0;
    arg0->unk68 = 0;
    func_8007E8E4(arg0 + 0x48, func_8007FD48(0, 0, sp2C, (u8) arg1->unk4, 0x1C), arg1->unk4);
    arg0->unk0 = 0;
    arg0->unk8 = &func_80080DC4;
    arg0->unk4 = arg0;
    func_80086088(D_800952D0, arg0);
}

void func_800816E8(Unk *arg0, Unk *arg1) {
    arg1->unk0 = (s32) arg0->unk8;
    arg1->unkC = (s16) arg0->unk1A;
    arg1->unk4 = (s32) arg0->unkC;
}

void func_80081704(Unk *arg0, Unk *arg1) {
    arg0->unk8 = (s32) arg1->unk0;
    arg0->unk1A = (s16) arg1->unkC;
    arg0->unkC = (s32) arg1->unk4;
}

s32 func_80081720(Unk *arg0) {
    return arg0->unkC;
}

void func_80081728(void) {

}

u8 func_80081730(Unk *arg0) {
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 var_a1;

    temp_v1 = arg0->unk8;
    temp_v0 = *temp_v1;
    arg0->unk8 = (u8 *) (temp_v1 + 1);
    var_a1 = temp_v0;
    if (temp_v0 & 0x80) {
        var_a1 = temp_v0 & 0x7F;
        do {
            temp_v1_2 = arg0->unk8;
            temp_v0_2 = *temp_v1_2;
            arg0->unk8 = (u8 *) (temp_v1_2 + 1);
            var_a1 = (var_a1 << 7) + (temp_v0_2 & 0x7F);
        } while (temp_v0_2 & 0x80);
    }
    return var_a1;
}
