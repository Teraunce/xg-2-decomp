#include "ultra64.h"
void func_8005C8B8();                                  /* extern */
void func_8005C8EC(s32, s32);                              /* extern */
void guLookAt(void *, s32, s32, s32, s32, s32, f32, f32, f32, f32); /* extern */
void func_8007A8E0(s32);                               /* extern */
void guMtxCat(s32, s32, s32);                     /* extern */
void func_8007AE7C(s32, s32, s32, s32, f32, f32, f32, f32);  /* extern */
void func_8007B118(void *, void *, s32, s32, f32, f32, f32);     /* extern */
extern f32 D_8004BF58;
extern f32 D_8004BF5C;
extern f32 D_8004BF60;
extern f32 D_8004BF64;
extern s32 D_8004BF68;
extern s32 D_8004BF6C;
extern f32 D_8004BF70;
extern s32 gSfxPendingSlot;
extern s32 gInitStateFlags;
extern s32 D_80181E48;
extern s32 D_80181E4C;
extern s32 D_80181E70;
extern s32 D_80181EB0;
extern s32 D_80182078;
extern s32 gSfxChannelState;
extern s32 D_801822D8;

void func_8005F6B8(void) {
    s32 sp68;
    s32 sp28;
    Unk *var_v1;
    f32 temp_fs0;
    s32 var_a0;

    func_8005C8EC(0x28, 0);
    func_8005C8B8();
    var_a0 = 0;
    var_v1 = &gSfxChannelState;
    do {
        var_v1->unk0 = 0;
        var_v1->unkC = 0;
        var_v1->unk10 = 0;
        var_v1->unk18 = 0;
        var_v1->unk14 = 0;
        var_v1->unk8 = 0;
        var_v1->unk4 = 0;
        var_v1->unk1C = 0;
        var_v1->unk20 = 0;
        var_a0 += 1;
        var_v1 += 0x24;
    } while (var_a0 < 4);
    func_8007A8E0(&D_80181EB0);
    temp_fs0 = D_8004BF60;
    func_8007AE7C(&D_80182078, 0, 0x43A00000, 0x43700000, 0.0f, D_8004BF58, D_8004BF5C, temp_fs0);
    func_8007B118(&sp28, &D_801822D8, 0x42040000, 0x3FAAAAAB, temp_fs0, D_8004BF64, temp_fs0);
    guLookAt(&sp68, D_8004BF68, D_8004BF6C, 0xC3CB0000, D_8004BF68, D_8004BF6C, 0.0f, 0.0f, D_8004BF70, 0.0f);
    guMtxCat(&sp68, &sp28, &D_80181E70);
    D_80181E48 = 0;
    D_80181E4C = 0;
    gSfxPendingSlot = -1;
    gInitStateFlags = 0;
}
