#include "ultra64.h"
void gfxSpTaskWait(s32, s32, s32);                     /* extern */
void overlayRelocate(Unk*, Unk*, s32);                /* extern */
void __osInvalICache_full();                                  /* extern */
extern f32 gResScaleX;
extern f32 gResScaleY;
extern f32 gTexUVScale;
extern f32 gTileScaleU;
extern f32 gTileScaleV;
extern s32 gDLWritePtr;
extern s32 gVideoModeTable;
extern Unk gTexTileCmd;
extern s32 gScreenHeight;
extern f32 gTexScaleX;
extern f32 gTexScaleY;
extern s32 gScreenWidth;
extern s32 gDLBufEnd;

s32 *overlayLoadDL(Unk *arg0) {
    s32 *temp_s0;
    s32 temp_a2;

    temp_a2 = arg0->unk4;
    if ((s32) &gDLBufEnd >= (gDLWritePtr + temp_a2)) {
        gfxSpTaskWait(arg0->unk0, gDLWritePtr, temp_a2);
        temp_s0 = gDLWritePtr + (arg0->unk8 & 0xFFFFFF);
        overlayRelocate(temp_s0, arg0, gDLWritePtr);
        *temp_s0 = gDLWritePtr + (*temp_s0 & 0xFFFFFF);
        gDLWritePtr += arg0->unk4;
        __osInvalICache_full();
        return temp_s0;
    }
    M2C_BREAK(0);
    return NULL;
}

void viSetResolution(s32 arg0, s32 arg1) {
    Unk *var_a2;
    f32 temp_ft0;
    f32 temp_fv0;
    s32 var_t0;
    Unk *temp_a0;
    Unk *temp_a1;
    Unk *temp_a3;
    Unk *temp_v1;

    var_t0 = 0;
    var_a2 = &gVideoModeTable;
    temp_ft0 = (f32) arg0 * gResScaleX;
    gScreenWidth = arg0;
    temp_fv0 = (f32) arg1 * gResScaleY;
    gScreenHeight = arg1;
    gTexScaleX = temp_ft0;
    gTexScaleY = temp_fv0;
    do {
        temp_v1 = var_a2->unk0;
        temp_a1 = var_a2->unk4;
        temp_a0 = var_a2->unk10;
        temp_a3 = var_a2->unk14;
        if (temp_v1 != NULL) {
            temp_v1->unk0 = (s16) (s32) ((f32) var_a2->unk8 * temp_ft0);
            temp_v1->unk4 = 0x1FF;
            temp_v1->unk6 = 0;
            temp_v1->unk2 = (s16) (s32) ((f32) var_a2->unkA * temp_fv0);
            temp_v1->unk8 = (s16) (s32) ((f32) var_a2->unkC * temp_ft0);
            temp_v1->unkC = 0x1FF;
            temp_v1->unkE = 0;
            temp_v1->unkA = (s16) (s32) ((f32) var_a2->unkE * temp_fv0);
        }
        if (temp_a1 != NULL) {
            temp_a1->unk0 = (s16) (s32) ((f32) -var_a2->unk8 * temp_ft0);
            temp_a1->unk4 = 0x1FF;
            temp_a1->unk6 = 0;
            temp_a1->unk2 = (s16) (s32) ((f32) var_a2->unkA * temp_fv0);
            temp_a1->unk8 = (s16) (s32) ((f32) var_a2->unkC * temp_ft0);
            temp_a1->unkC = 0x1FF;
            temp_a1->unkE = 0;
            temp_a1->unkA = (s16) (s32) ((f32) var_a2->unkE * temp_fv0);
        }
        if (temp_a0 != NULL) {
            temp_a0->unk0 = (s32) ((((s32) ((f32) var_a2->unk18 * temp_ft0 * gTexUVScale) & 0xFFF) << 0xC) | (((s32) ((f32) var_a2->unk1A * temp_fv0 * gTexUVScale) & 0xFFF) | 0xED000000));
            temp_a0->unk4 = (s32) ((((s32) ((f32) var_a2->unk1C * temp_ft0 * gTexUVScale) & 0xFFF) << 0xC) | ((s32) ((f32) var_a2->unk1E * temp_fv0 * gTexUVScale) & 0xFFF));
        }
        var_t0 += 1;
        if (temp_a3 != NULL) {
            temp_a3->unk0 = (s32) ((((s32) ((f32) var_a2->unk18 * temp_ft0 * gTexUVScale) & 0xFFF) << 0xC) | (((s32) ((f32) var_a2->unk1A * temp_fv0 * gTexUVScale) & 0xFFF) | 0xED000000));
            temp_a3->unk4 = (s32) ((((s32) ((f32) var_a2->unk1C * temp_ft0 * gTexUVScale) & 0xFFF) << 0xC) | ((s32) ((f32) var_a2->unk1E * temp_fv0 * gTexUVScale) & 0xFFF));
        }
        var_a2 += 0x20;
    } while (var_t0 < 0xC);
    gTexTileCmd.unk0 = 0xED000000;
    gTexTileCmd.unk4 = (s32) ((((s32) (gTexScaleX * gTileScaleU) & 0xFFF) << 0xC) | ((s32) (gTexScaleY * gTileScaleV) & 0xFFF));
}
