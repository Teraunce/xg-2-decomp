#include "ultra64.h"
#include "mtx.h"
/* Warning: missing "jr $ra" in last block of func_80056C2C (initial). */

s32 func_80056850(void *, s32);                            /* extern */
f32 mtxRotAxisFGetter(s32);                                    /* extern */
f32 mtxRotAxisFGetter2(s32);                                 /* extern */
void mtxCatFSafe(s32, s32, s32);                     /* extern */
extern f32 gMtxZeroF;
extern f32 gSfxPanScale;
extern f32 gSfxPitchScale;

void mtxRotAxisApply(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp10;

    mtxRotAxisFGetter2(arg3);
    mtxRotAxisFGetter(arg2);
    mtxCatFSafe(&sp10, arg0, arg0);
    func_80056850(&sp10, arg1);
    mtxCatFSafe(&sp10, arg0, arg0);
}

void mtxIdentInit(Matrix4x4 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk10 = 0;
    arg0->unk18 = 0;
    arg0->unk1C = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk30 = arg1;
    arg0->unk34 = arg2;
    arg0->unk38 = arg3;
    arg0->unk0 = (f32) gMtxZeroF;
    arg0->unk14 = (f32) gMtxZeroF;
    arg0->unk28 = (f32) gMtxZeroF;
    arg0->unk3C = (f32) gMtxZeroF;
}

void mtxCopyTranslate(Matrix4x4 *arg0, Matrix4x4 *arg1, f32 arg2, f32 arg3, f32 arg4) {
    if (arg0 != arg1) {
        arg1->unk0 = (f32) arg0->unk0;
        arg1->unk4 = (f32) arg0->unk4;
        arg1->unk8 = (f32) arg0->unk8;
        arg1->unkC = (f32) arg0->unkC;
        arg1->unk10 = (f32) arg0->unk10;
        arg1->unk14 = (f32) arg0->unk14;
        arg1->unk18 = (f32) arg0->unk18;
        arg1->unk1C = (f32) arg0->unk1C;
        arg1->unk20 = (f32) arg0->unk20;
        arg1->unk24 = (f32) arg0->unk24;
        arg1->unk28 = (f32) arg0->unk28;
        arg1->unk2C = (f32) arg0->unk2C;
    }
    arg1->unk30 = (f32) (arg0->unk30 + arg2);
    arg1->unk34 = (f32) (arg0->unk34 + arg3);
    arg1->unk38 = (f32) (arg0->unk38 + arg4);
    arg1->unk3C = (f32) arg0->unk3C;
}

void func_80056B80(Unk *arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 temp_ft1;
    s32 temp_ft1_2;
    s32 temp_ft1_3;

    arg0->unk0 = 0x10000;
    arg0->unk4 = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk8 = 1;
    arg0->unkC = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk10 = 0;
    arg0->unk14 = 0x10000;
    arg0->unk30 = 0;
    arg0->unk34 = 0;
    temp_ft1 = (s32) (arg1 * gSfxPanScale);
    temp_ft1_2 = (s32) (arg2 * gSfxPanScale);
    arg0->unk18 = (s32) ((temp_ft1 & 0xFFFF0000) | ((u32) temp_ft1_2 >> 0x10));
    arg0->unk38 = (s32) ((temp_ft1 << 0x10) | (temp_ft1_2 & 0xFFFF));
    temp_ft1_3 = (s32) (arg3 * gSfxPanScale);
    arg0->unk1C = (s32) ((temp_ft1_3 & 0xFFFF0000) | 1);
    arg0->unk3C = (s32) (temp_ft1_3 << 0x10);
}

void func_80056C2C(Unk *arg0, Unk *arg1, f32 arg2, f32 arg3) {
    s32 temp_fa0;
    s32 temp_fa0_10;
    s32 temp_fa0_11;
    s32 temp_fa0_12;
    s32 temp_fa0_2;
    s32 temp_fa0_3;
    s32 temp_fa0_4;
    s32 temp_fa0_5;
    s32 temp_fa0_6;
    s32 temp_fa0_7;
    s32 temp_fa0_8;
    s32 temp_fa0_9;

    temp_fa0 = (s32) (arg0->unk0 * gSfxPitchScale);
    temp_fa0_2 = (s32) (arg0->unk4 * gSfxPitchScale);
    temp_fa0_3 = (s32) (arg0->unk8 * gSfxPitchScale);
    temp_fa0_4 = (s32) (arg0->unkC * gSfxPitchScale);
    arg1->unk0 = (s32) ((temp_fa0 & 0xFFFF0000) | ((u32) temp_fa0_2 >> 0x10));
    arg1->unk4 = (s32) ((temp_fa0_3 & 0xFFFF0000) | ((u32) temp_fa0_4 >> 0x10));
    arg1->unk20 = (s32) ((temp_fa0 << 0x10) | (temp_fa0_2 & 0xFFFF));
    arg1->unk24 = (s32) ((temp_fa0_3 << 0x10) | (temp_fa0_4 & 0xFFFF));
    temp_fa0_5 = (s32) (arg0->unk10 * gSfxPitchScale);
    temp_fa0_6 = (s32) (arg0->unk14 * gSfxPitchScale);
    temp_fa0_7 = (s32) (arg0->unk18 * gSfxPitchScale);
    temp_fa0_8 = (s32) (arg0->unk1C * gSfxPitchScale);
    arg1->unk8 = (s32) ((temp_fa0_5 & 0xFFFF0000) | ((u32) temp_fa0_6 >> 0x10));
    arg1->unkC = (s32) ((temp_fa0_7 & 0xFFFF0000) | ((u32) temp_fa0_8 >> 0x10));
    arg1->unk28 = (s32) ((temp_fa0_5 << 0x10) | (temp_fa0_6 & 0xFFFF));
    arg1->unk2C = (s32) ((temp_fa0_7 << 0x10) | (temp_fa0_8 & 0xFFFF));
    temp_fa0_9 = (s32) (arg0->unk20 * gSfxPitchScale);
    temp_fa0_10 = (s32) (arg0->unk24 * gSfxPitchScale);
    temp_fa0_11 = (s32) (arg0->unk28 * gSfxPitchScale);
    temp_fa0_12 = (s32) (arg0->unk2C * gSfxPitchScale);
    arg1->unk10 = (s32) ((temp_fa0_9 & 0xFFFF0000) | ((u32) temp_fa0_10 >> 0x10));
    arg1->unk14 = (s32) ((temp_fa0_11 & 0xFFFF0000) | ((u32) temp_fa0_12 >> 0x10));
    arg1->unk30 = (s32) ((temp_fa0_9 << 0x10) | (temp_fa0_10 & 0xFFFF));
    arg1->unk34 = (s32) ((temp_fa0_11 << 0x10) | (temp_fa0_12 & 0xFFFF));
    rdpMtxPackRow(arg0, arg1, arg2);
}
