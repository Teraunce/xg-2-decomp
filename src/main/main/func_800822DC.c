#include "ultra64.h"
void func_8007E734(void**, s32, s32);                /* extern */
s32 func_8007E858(Unk*, s16*);                  /* extern */
void func_8007E8E4(Unk*, s32, s32);               /* extern */
char *func_8007FD48(s32, s32, s32, s32, s32);             /* extern */
void func_80086088(void *, void *);                       /* extern */
extern s32 gPendingFlushFlag;
extern s32 func_80081D94;

void func_800822DC(Unk *arg0, Unk *arg1) {
    s16 sp34;
    char *sp28;
    u32 var_v1;
    Unk *temp_a0;
    char *temp_a1;
    char *temp_v0;
    Unk *var_a0;

    arg0->unk3C = -1;
    arg0->unk48 = 0x3E80;
    arg0->unk44 = (u32) arg1->unk0;
    temp_v0 = func_8007FD48(0, 0, arg1->unk8, 1, arg1->unk0 * 0x30);
    arg0->unk40 = temp_v0;
    var_v1 = 0;
    var_a0 = temp_v0;
    if (arg1->unk0 != 0) {
        do {
            var_a0->unk1C = 0;
            var_v1 += 1;
            var_a0 += 0x30;
        } while (var_v1 < (u32) arg1->unk0);
    }
    temp_a0 = arg0 + 0x14;
    temp_a1 = func_8007FD48(0, 0, arg1->unk8, 1, arg1->unk4 * 0x1C);
    sp28 = temp_a0;
    func_8007E8E4(temp_a0, temp_a1, arg1->unk4);
    arg0->unk0 = 0;
    arg0->unk8 = &func_80081D94;
    arg0->unk4 = arg0;
    arg0->unk38 = (s32) gPendingFlushFlag;
    func_80086088(gPendingFlushFlag, arg0);
    sp34 = 5;
    func_8007E734(temp_a0, &sp34, arg0->unk48);
    arg0->unk4C = func_8007E858(sp28, arg0 + 0x28);
}

s16 func_80082418(Unk *arg0, Unk *arg1) {
    s16 var_v1;
    s32 temp_a2;
    Unk *temp_a0;

    temp_a2 = arg0->unk44;
    var_v1 = 0;
    if (temp_a2 > 0) {
loop_1:
        temp_a0 = arg0->unk40 + (var_v1 * 0x30);
        if (temp_a0->unk1C == 0) {
            temp_a0->unk1C = arg1;
            temp_a0->unk20 = 5;
            temp_a0->unk28 = 0;
            temp_a0->unk2E = 0x40;
            temp_a0->unk2F = 0;
            temp_a0->unk24 = 1.0f;
            temp_a0->unk2C = (s16) ((s32) (arg1->unkD * 0x7FFF) / 127);
            return var_v1;
        }
        var_v1 += 1;
        if (var_v1 >= temp_a2) {
            /* Duplicate return node #4. Try simplifying control flow for better match */
            return -1;
        }
        goto loop_1;
    }
    return -1;
}

void func_800824B8(Unk *arg0, s16 arg1) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = arg0->unk40;
    temp_v1 = arg1 * 0x30;
    if (((Unk *)(temp_v1 + temp_v0))->unk28 == 0) {
        ((Unk *)(temp_v0 + temp_v1))->unk1C = 0;
        if (arg1 == arg0->unk3C) {
            arg0->unk3C = -1;
        }
    }
}

void func_80082508(Unk *arg0, s16 arg1) {
    arg0->unk3C = (s32) arg1;
}
