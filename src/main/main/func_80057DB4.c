#include "ultra64.h"
s32 vec3Normalize(f32 *, f32 *, f32 *);               /* extern */
void vec3Cross(Unk*, Unk*, Unk*);               /* extern */
extern f32 D_8004BDB0;
extern f32 D_8004BDB4;
extern f32 D_8004BDB8;
extern f32 D_8004BDBC;

void func_80057DB4(Unk *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 *var_a0;
    f32 temp_ft1;
    f32 temp_ft2;
    f32 temp_ft3;
    s32 temp_fa0;
    s32 temp_fa0_2;
    s32 temp_fa0_3;
    s32 temp_fa0_4;
    s32 temp_fa0_5;
    s32 temp_fa0_6;
    s32 temp_fa0_7;
    s32 temp_fa0_8;
    s32 temp_fa0_9;

    temp_ft1 = -arg1;
    sp60 = -arg4;
    sp70 = temp_ft1;
    sp64 = -arg5;
    sp68 = -arg6;
    temp_ft2 = -arg2;
    sp74 = temp_ft2;
    temp_ft3 = -arg3;
    sp78 = temp_ft3;
    if ((temp_ft1 == 0.0f) && (temp_ft2 == 0.0f) && (temp_ft3 == 0.0f)) {
        sp78 = D_8004BDB0;
    }
    if (sp60 == 0.0f) {
        var_a0 = &sp70;
        if (sp64 == 0.0f) {
            if (sp68 == 0.0f) {
                sp64 = D_8004BDB4;
                goto block_8;
            }
        }
    } else {
block_8:
        var_a0 = &sp70;
    }
    vec3Cross(var_a0, &sp60, &sp50);
    if ((sp50 == 0.0f) && (sp54 == 0.0f) && (sp58 == 0.0f)) {
        sp68 += D_8004BDB8;
        vec3Cross(&sp60, &sp50, &sp54);
    }
    vec3Cross(&sp50, &sp60, &sp64);
    vec3Normalize(&sp50, &sp54, &sp58);
    vec3Normalize(&sp60, &sp64, &sp68);
    vec3Normalize(&sp70, &sp74, &sp78);
    temp_fa0 = (s32) (sp50 * D_8004BDBC);
    temp_fa0_2 = (s32) (sp54 * D_8004BDBC);
    temp_fa0_3 = (s32) (sp58 * D_8004BDBC);
    arg0->unk0 = (s32) ((temp_fa0 & 0xFFFF0000) | ((u32) temp_fa0_2 >> 0x10));
    arg0->unk4 = (s32) (temp_fa0_3 & 0xFFFF0000);
    arg0->unk20 = (s32) ((temp_fa0 << 0x10) | (temp_fa0_2 & 0xFFFF));
    arg0->unk24 = (s32) (temp_fa0_3 << 0x10);
    temp_fa0_4 = (s32) (sp60 * D_8004BDBC);
    temp_fa0_5 = (s32) (sp64 * D_8004BDBC);
    temp_fa0_6 = (s32) (sp68 * D_8004BDBC);
    arg0->unk8 = (s32) ((temp_fa0_4 & 0xFFFF0000) | ((u32) temp_fa0_5 >> 0x10));
    arg0->unkC = (s32) (temp_fa0_6 & 0xFFFF0000);
    arg0->unk28 = (s32) ((temp_fa0_4 << 0x10) | (temp_fa0_5 & 0xFFFF));
    arg0->unk2C = (s32) (temp_fa0_6 << 0x10);
    arg0->unk18 = 0;
    arg0->unk1C = 1;
    arg0->unk38 = 0;
    arg0->unk3C = 0;
    temp_fa0_7 = (s32) (sp70 * D_8004BDBC);
    temp_fa0_8 = (s32) (sp74 * D_8004BDBC);
    temp_fa0_9 = (s32) (sp78 * D_8004BDBC);
    arg0->unk10 = (s32) ((temp_fa0_7 & 0xFFFF0000) | ((u32) temp_fa0_8 >> 0x10));
    arg0->unk30 = (s32) ((temp_fa0_7 << 0x10) | (temp_fa0_8 & 0xFFFF));
    arg0->unk14 = (s32) (temp_fa0_9 & 0xFFFF0000);
    arg0->unk34 = (s32) (temp_fa0_9 << 0x10);
}

void func_800580C0(Unk *arg0, Unk *arg1) {
    if (arg0 != arg1) {
        arg1->unk0 = (f32) arg0->unk0;
        arg1->unk10 = (f32) arg0->unk4;
        arg1->unk20 = (f32) arg0->unk8;
        arg1->unk4 = (f32) arg0->unk10;
        arg1->unk14 = (f32) arg0->unk14;
        arg1->unk24 = (f32) arg0->unk18;
        arg1->unk8 = (f32) arg0->unk20;
        arg1->unk18 = (f32) arg0->unk14;
        arg1->unk3C = 0.0f;
        arg1->unk38 = 0.0f;
        arg1->unk34 = 0.0f;
        arg1->unk30 = 0.0f;
        arg1->unk2C = 0.0f;
        arg1->unk1C = 0.0f;
        arg1->unkC = 0.0f;
        arg1->unk28 = (f32) arg0->unk8;
    }
}
