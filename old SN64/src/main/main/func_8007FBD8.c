#include "ultra64.h"
void func_8007E8E4(Unk*, s32, s32);                  /* extern */
void func_800814EC(Unk*);                            /* extern */
void func_80086088(void *, void *);                       /* extern */
char *func_8007FD48(s32 arg0, s32 arg1, Unk *arg2, u8 arg3, s32 arg4); /* static */
extern s32 D_800952D0;
extern s32 func_8007F5C4;

void func_8007FBD8(Unk *arg0, Unk *arg1) {
    char *sp2C;
    char *temp_v0;
    char *var_v1;
    s32 var_a0;
    char *temp_a2;

    temp_a2 = arg1->unkC;
    arg0->unk20 = 0;
    arg0->unk18 = 0;
    arg0->unk30 = 0xFF;
    arg0->unk24 = 0x1E8;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk32 = 0x7FFF;
    arg0->unk5C = 0x3E80;
    arg0->unk1C = 0;
    arg0->unk14 = (s32) D_800952D0;
    arg0->unk70 = (s32) arg1->unk10;
    arg0->unk74 = (s32) arg1->unk14;
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
    arg0->unk8 = &func_8007F5C4;
    arg0->unk4 = arg0;
    func_80086088(D_800952D0, arg0);
}

char *func_8007FD48(s32 arg0, s32 arg1, Unk *arg2, u8 arg3, s32 arg4) {
    char *temp_a0;
    char *var_v1;
    s32 temp_t7;

    temp_a0 = arg2->unk4;
    var_v1 = NULL;
    temp_t7 = ((arg3 * arg4) + 0xF) & ~0xF;
    if ((u32) (arg2->unk0 + arg2->unk8) >= (u32) (temp_a0 + temp_t7)) {
        var_v1 = temp_a0;
        arg2->unk4 = (void *) (temp_a0 + temp_t7);
    }
    return var_v1;
}

void func_8007FDA8(Unk *arg0, Unk *arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = arg2 * 0x10;
    *(Unk**)(s32)(arg0->unk60 + temp_v0) = arg1;
    ((Unk *)(arg0->unk60 + temp_v0))->unk7 /* FIXME: type unknown */ = (u8) arg1->unk1;
    ((Unk *)(arg0->unk60 + temp_v0))->unk9 /* FIXME: type unknown */ = (u8) arg1->unk0;
    ((Unk *)(arg0->unk60 + temp_v0))->unk8 /* FIXME: type unknown */ = (u8) arg1->unk2;
    ((Unk *)(arg0->unk60 + temp_v0))->unk4 /* FIXME: type unknown */ = (s16) arg1->unkC;
}

void func_8007FDFC(Unk *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = arg1 * 0x10;
    ((Unk *)(arg0->unk60 + temp_v0))->unk6 /* FIXME: type unknown */ = 0;
    ((Unk *)(arg0->unk60 + temp_v0))->unkA /* FIXME: type unknown */ = 0;
    ((Unk *)(arg0->unk60 + temp_v0))->unk7 /* FIXME: type unknown */ = 0x40;
    ((Unk *)(arg0->unk60 + temp_v0))->unk9 /* FIXME: type unknown */ = 0x7F;
    ((Unk *)(arg0->unk60 + temp_v0))->unk8 /* FIXME: type unknown */ = 5;
    ((Unk *)(arg0->unk60 + temp_v0))->unkB /* FIXME: type unknown */ = 0;
    ((Unk *)(arg0->unk60 + temp_v0))->unk4 /* FIXME: type unknown */ = 0xC8;
    ((Unk *)(arg0->unk60 + temp_v0))->unkC /* FIXME: type unknown */ = 1.0f;
}
