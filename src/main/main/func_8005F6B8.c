#include "ultra64.h"
void audioResetCallback();                                  /* extern */
void audioSetRates(s32, s32);                              /* extern */
void guLookAt(void *, s32, s32, s32, s32, s32, f32, f32, f32, f32); /* extern */
void guMtxIdentL(s32);                               /* extern */
void guMtxCat(s32, s32, s32);                     /* extern */
void guOrtho(s32, s32, s32, s32, f32, f32, f32, f32);  /* extern */
void guPerspective(void *, void *, s32, s32, f32, f32, f32);     /* extern */
extern f32 gCamNearClip;
extern f32 gCamFarClip;
extern f32 gCamPerspDist;
extern f32 gCamPerspFar;
extern s32 gLookAtEyeX;
extern s32 gLookAtEyeY;
extern f32 gCamUpVecY;
extern s32 gSfxPendingSlot;
extern s32 gInitStateFlags;
extern s32 gSfxRaceReady;
extern s32 gSfxRaceTimer;
extern s32 gLookMtxOut;
extern s32 gLookMtxL;
extern s32 gOrthoMtx;
extern s32 gSfxChannelState;
extern s32 gPerspMtx;

void gameModeReset(void) {
    s32 sp68;
    s32 sp28;
    Unk *var_v1;
    f32 temp_fs0;
    s32 var_a0;

    audioSetRates(0x28, 0);
    audioResetCallback();
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
    guMtxIdentL(&gLookMtxL);
    temp_fs0 = gCamPerspDist;
    guOrtho(&gOrthoMtx, 0, 0x43A00000, 0x43700000, 0.0f, gCamNearClip, gCamFarClip, temp_fs0);
    guPerspective(&sp28, &gPerspMtx, 0x42040000, 0x3FAAAAAB, temp_fs0, gCamPerspFar, temp_fs0);
    guLookAt(&sp68, gLookAtEyeX, gLookAtEyeY, 0xC3CB0000, gLookAtEyeX, gLookAtEyeY, 0.0f, 0.0f, gCamUpVecY, 0.0f);
    guMtxCat(&sp68, &sp28, &gLookMtxOut);
    gSfxRaceReady = 0;
    gSfxRaceTimer = 0;
    gSfxPendingSlot = -1;
    gInitStateFlags = 0;
}
