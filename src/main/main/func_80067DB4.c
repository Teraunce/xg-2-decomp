#include "ultra64.h"
s16 randRange(s16);                                 /* extern */
void guLookAt(void *, s32, s32, s32, f32, f32, f32, s32, s32, s32); /* extern */
void guMtxXfm(s32, s32, s32, s32, s32, s32, s32); /* extern */
void guMtxCat(s32, s32, s32);               /* extern */
void guPerspective(void *, u16 *, f32, f32, f32, f32, f32); /* extern */
void guRotateInt(void *, f32, f32);                    /* extern */
void guScaleGetter(void *, f32, f32);                    /* extern */
s32 func_800AAEFC(u8, u8, void *, void *, f32, s32, s32, s32, s32, s32); /* extern */
s32 func_800AAFD0(u8, u8, void *, f32, s32, s32, s32, s32, s32); /* extern */
s32 func_8013AB6C(s32, s32, void *, void *, s32);     /* extern */
extern f32 gTrackRenderParam0;
extern f32 gTrackRenderParam1;
extern f32 gTrackRenderParam2;
extern f32 gCamClampF;
extern f32 gTrackRenderParam3;
extern f32 gTrackScale;
extern f32 gTrackRenderParam4;
extern f32 gTrackRenderParam5;
extern f32 gTrackRenderParam6;
extern f32 gTrackRenderParam7;
extern f32 gTrackClampA;
extern f32 gTrackRenderParam8;
extern f32 gTrackClampB;
extern f32 gTrackClampC;
extern s32 gEntityPool;
extern s32 gPlayerList;
extern s32 gPlayerList2;
extern s32 gGameFlags;
extern s32 gCamDLData;
extern s32 gCamTrackData;
extern char *gCamDLPtr;
extern s32 gTrackRenderDL;
extern s32 gTrackRenderDL2;
extern s32 gTrackTexBuf;
extern Unk *gDLPtr;
extern Unk *gRdpTilePtr2;
extern Unk *gRdpTilePtr;
extern char *gTrackNodePtr;
extern char *gTrackRenderPtr;
extern s32 gRenderIdx;
extern s32 gRenderBase;
extern s32 gVideoMode;
extern s32 gTrackRotMtx;
extern s32 gRaceColorMode;

void gameCameraSetup(s32 arg0, f32 arg1, f32 arg3) {
    char *sp148;
    s32 *sp144;
    s32 *sp140;
    s32 sp138;
    s32 sp134;
    u16 sp130;
    s32 sp128;
    s32 sp124;
    s32 sp120;
    s32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    s32 sp68;
    s32 sp28;
    void **var_v1;
    char *var_t2;
    char *var_v0;
    s32 var_a3_2;
    f32 temp_fs0;
    f32 temp_ft0;
    f32 temp_ft0_2;
    f32 temp_ft0_3;
    f32 temp_ft1;
    f32 temp_ft1_2;
    f32 temp_ft2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv0_5;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 var_a3;
    f32 var_fs0;
    f32 var_ft0;
    f32 var_ft0_2;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv1;
    Unk *var_t0;
    Unk *var_t1;
    s32 *var_v0_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s0_5;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_s7;
    s32 temp_t0;
    s32 temp_v0_3;
    s32 temp_v1_4;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 temp_v1_9;
    s32 var_a0_2;
    s32 var_s2;
    s32 var_s4;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_7;
    s32 var_v1_2;
    s32 var_v1_4;
    char *temp_a0;
    Unk *temp_a0_2;
    Unk *temp_a0_3;
    Unk *temp_a1_2;
    Unk *temp_a1_3;
    Unk *temp_a1_4;
    Unk *temp_a2_2;
    Unk *temp_a3;
    Unk *temp_a3_2;
    Unk *temp_s0;
    char *temp_s0_2;
    char *temp_s0_3;
    Unk *temp_s0_4;
    Unk *temp_s1;
    Unk *temp_s1_2;
    Unk *temp_s1_3;
    Unk *temp_s2_3;
    Unk *temp_s5_2;
    Unk *temp_t0_2;
    Unk *temp_t1;
    Unk *temp_t1_2;
    Unk *temp_v0;
    Unk *temp_v0_2;
    Unk *temp_v0_4;
    Unk *temp_v0_5;
    Unk *temp_v1;
    Unk *temp_v1_2;
    Unk *temp_v1_3;
    char *temp_v1_5;
    char *temp_v1_8;
    Unk *var_a0;
    Unk *var_a1;
    Unk *var_s0;
    Unk *var_s6;
    Unk *var_v0_3;
    Unk *var_v0_6;
    char *var_v1_3;

    var_fs0 = arg3;
    temp_v1 = (arg0 * 0x228) + &gEntityPool;
    temp_v1->unk220 = arg1;
    if (temp_v1->unk1E4 != 0) {
        var_v1 = (void **)0x80090000;
        var_v0 = &gCamTrackData;
    } else {
        var_v1 = &gCamDLPtr;
        var_v0 = &gCamDLData;
    }
    *var_v1 = var_v0;
    gRaceColorMode = 0;
    temp_t1 = (arg0 * 0x228) + &gEntityPool;
    temp_t0 = temp_t1->unk134;
    temp_a2 = 0xFF - temp_t0;
    temp_s6 = ((temp_t1->unkBC * temp_a2) / 255) + temp_t0;
    temp_s5 = ((temp_t1->unkBD * temp_a2) / 255) + temp_t0;
    temp_s4 = ((temp_t1->unkBE * temp_a2) / 255) + temp_t0;
    if (temp_t1->unk1E0 == 0) {
        var_v0_2 = (s32 *)0x80090000;
        if (temp_t1->unk1DC == 4) {
            var_ft0 = temp_t1->unk144;
        } else {
            temp_v0 = temp_t1->unkD0;
            temp_fv1 = temp_v0->unk398;
            temp_ft0 = temp_v0->unk39C;
            temp_fv0 = temp_v0->unk3A0;
            var_ft0 = temp_t1->unk144 * (sqrtf((temp_fv1 * temp_fv1) + (temp_ft0 * temp_ft0) + (temp_fv0 * temp_fv0)) * gTrackRenderParam0);
            if (temp_v0 != NULL) {
                var_ft0 += temp_v0->unk648 * gTrackRenderParam1;
            }
            var_v0_2 = &gGameFlags;
        }
        if (!(*var_v0_2 & 0x20)) {
            var_fs0 += var_ft0;
        } else {
            var_fs0 += var_ft0 * gTrackRenderParam2;
        }
    }
    var_fv1 = var_fs0;
    if (!(var_fs0 <= gCamClampF)) {
        var_fv1 = gCamClampF;
    }
    var_fv0 = gTrackRenderParam3;
    if (!(var_fv1 <= var_fv0)) {
        var_fv0 = var_fs0;
        if (!(var_fv0 <= gCamClampF)) {
            var_fv0 = gCamClampF;
        }
    }
    temp_s1 = (arg0 << 5) + &gVideoMode;
    temp_s0 = (arg0 * 0x228) + &gEntityPool;
    temp_s0->unk148 = var_fv0;
    func_800AAEFC(temp_s0->unk1D8, temp_s0->unk1D9, temp_s1, temp_s0, var_fv0, temp_s6, temp_s5, temp_s4, temp_s0->unk134, 1);
    temp_v1_2 = gDLPtr + 8;
    gDLPtr->unk0 = 0xE3000A01;
    gDLPtr->unk4 = 0;
    gDLPtr = temp_v1_2;
    gDLPtr = temp_v1_2 + 8;
    gDLPtr->unk8 = 0xDE000000;
    temp_v1_2->unk4 = &gTrackRenderDL2;
    guScaleGetter(&sp68, gTrackScale, gTrackScale);
    sp134 = (s32) ((f32) temp_s0->unkB0 * arg1);
    if (gGameFlags & 1) {
        sp134 = sp134 / 2;
    }
    if (temp_s0->unk1E0 != 0) {
        var_a3 = 2.1111112f;
        var_fv0_2 = gTrackRenderParam4;
        var_ft0_2 = gTrackRenderParam5;
    } else {
        var_a3 = (f32) temp_s1->unk8 / (f32) temp_s1->unkC;
        var_fv0_2 = gTrackRenderParam6;
        var_ft0_2 = gTrackRenderParam7;
    }
    guPerspective(&sp28, &sp130, var_fv0, var_a3, var_fv0_2, (f32)sp134, var_ft0_2);
    temp_v1_3 = gDLPtr;
    gDLPtr += 8;
    temp_v1_3->unk0 = 0xDB0E0000;
    temp_v1_3->unk4 = (s32) sp130;
    temp_s2 = arg0 * 0x228;
    temp_s1_2 = temp_s2 + &gEntityPool;
    temp_s1_2->unk224 = sp130;
    guRotateInt(&gTrackRotMtx, 0.0f, 0.0f);
    sp120 = temp_s1_2->unk18;
    sp124 = temp_s1_2->unk1C;
    sp128 = temp_s1_2->unk20;
    if (gGameFlags & 0x10) {
        guRotateInt(&spE0, (f32) -gPlayerList2, temp_s1_2->unkC - temp_s1_2->unk0);
        guMtxXfm(&spE0, sp120, sp124, sp128, &sp120, &sp124, &sp128);
    }
    temp_s0_2 = temp_s2 + (&gEntityPool + 0x30);
    guLookAt(temp_s0_2 + (gPlayerList << 6), 0, 0, 0, temp_s1_2->unkC - temp_s1_2->unk0, temp_s1_2->unk10 - temp_s1_2->unk4, temp_s1_2->unk14 - temp_s1_2->unk8, sp120, sp124, sp128);
    temp_a0 = temp_s0_2 + (gPlayerList << 6);
    guMtxCat(temp_a0, &sp68, temp_a0);
    temp_s0_3 = temp_s0_2 + (gPlayerList << 6);
    guMtxCat(temp_s0_3, &sp28, temp_s0_3);
    temp_v1_4 = gPlayerList << 6;
    var_a0 = temp_v1_4 + ((gRenderIdx << 7) + gRenderBase);
    temp_v1_5 = temp_v1_4 + temp_s2 + &gEntityPool;
    var_v0_3 = temp_v1_5 + 0x30;
    do {
        var_a0->unk0 = (s32) var_v0_3->unk0;
        var_a0->unk4 = (s32) var_v0_3->unk4;
        var_a0->unk8 = (s32) var_v0_3->unk8;
        var_a0->unkC = (s32) var_v0_3->unkC;
        var_v0_3 += 0x10;
        var_a0 += 0x10;
    } while ((char*)var_v0_3 != (temp_v1_5 + 0x70));
    temp_t0_2 = gDLPtr;
    temp_t0_2->unk0 = 0xDA380007;
    temp_a1 = gRenderIdx << 7;
    gDLPtr += 8;
    gRenderIdx += 1;
    temp_t0_2->unk4 = (s32) (gRenderBase + temp_a1 + (gPlayerList << 6));
    temp_s0_4 = (arg0 * 0x228) + &gEntityPool;
    func_800AAFD0(temp_s0_4->unk1DA, temp_s0_4->unk1DB, temp_s0_4, var_fv0, temp_s6, temp_s5, temp_s4, temp_s0_4->unk134, 1);
    temp_v1_6 = temp_s0_4->unkB4;
    if (temp_v1_6 >= 0x3DF) {
        var_a3_2 = 0xE200001C;
        temp_a0_2 = gDLPtr;
        temp_v0_2 = gDLPtr + 8;
        temp_a0_2->unk0 = 0xDB080000;
        gDLPtr = temp_v0_2;
        gDLPtr = temp_v0_2 + 8;
        temp_a0_2->unk4 = 0x3200CF00;
        gDLPtr->unk8 = 0xE7000000;
        temp_v0_2->unk4 = 0;
        gDLPtr = temp_v0_2 + 0x10;
        temp_v0_2->unk8 = 0xE200001C;
        temp_v0_2->unkC = 0x0C183078;
    } else {
        temp_s2_2 = 0x3E3 - ((s32) (0x3E3 - temp_v1_6) / 16);
        temp_v0_3 = 0x3E8 - temp_s2_2;
        var_a3_2 = 0xC8103078;
        temp_a2_2 = gDLPtr;
        temp_a0_3 = gDLPtr + 8;
        temp_a2_2->unk0 = 0xDB080000;
        gDLPtr = temp_a0_3;
        gDLPtr = temp_a0_3 + 8;
        temp_a2_2->unk4 = (s32) (((0x1F400 / temp_v0_3) << 0x10) | (((s32) ((0x1F4 - temp_s2_2) << 8) / temp_v0_3) & 0xFFFF));
        gDLPtr->unk8 = 0xE200001C;
        temp_a0_3->unk4 = 0xC8103078;
    }
    temp_fv0_2 = (f32) gPlayerList2;
    temp_a1_2 = gDLPtr;
    gDLPtr += 8;
    temp_a1_2->unk0 = 0xF8000000;
    temp_a1_2->unk4 = (s32) ((temp_s6 << 0x18) | ((temp_s5 & 0xFF) << 0x10) | ((temp_s4 & 0xFF) << 8) | 0xFF);
    if (!(gTrackClampA <= temp_fv0_2)) {
        var_v0_4 = (s32) temp_fv0_2 & 0xFFF;
    } else {
        var_v0_4 = ((s32) (temp_fv0_2 - gTrackClampA) | 0x80000000) & 0xFFF;
    }
    temp_fv0_3 = (f32) gPlayerList2 * gTrackRenderParam8;
    gRdpTilePtr->unk0 = (s32) (var_v0_4 | 0xF2000000);
    gRdpTilePtr->unk4 = 0;
    if (!(gTrackClampB <= temp_fv0_3)) {
        var_v0_5 = (s32) temp_fv0_3 & 0xFFF;
    } else {
        var_v0_5 = ((s32) (temp_fv0_3 - gTrackClampB) | 0x80000000) & 0xFFF;
    }
    gRdpTilePtr->unk8 = (s32) ((var_v0_5 << 0xC) | 0xF2000000);
    ((Unk *)(gRdpTilePtr + 8))->unk4 = 0x01000000;
    temp_fv0_4 = 2.0f * (f32) gPlayerList2;
    if (gTrackClampC <= temp_fv0_4) {
        var_v1_2 = (s32) (temp_fv0_4 - gTrackClampC) | 0x80000000;
    } else {
        var_v1_2 = (s32) temp_fv0_4;
    }
    temp_s2_3 = gTrackRenderPtr;
    gRdpTilePtr2->unk0 = (s32) (((var_v1_2 & 0xFFF) << 0xC) | 0xF2000000);
    gRdpTilePtr2->unk4 = 0;
    temp_s0_5 = randRange(0x100);
    temp_s2_3->unk0 = (s32) (((temp_s0_5 & 0xFFF) << 0xC) | ((randRange(0x100) & 0xFFF) | 0xF2000000));
    temp_s2_3->unk4 = 0;
    temp_s2_3->unk8 = 0xFB000000;
    ((Unk *)(temp_s2_3 + 8))->unk4 = (s32) (randRange(0x100) & 0xFF);
    temp_v1_7 = gPlayerList << 6;
    var_a1 = temp_v1_7 + ((gRenderIdx << 7) + gRenderBase);
    temp_v1_8 = temp_v1_7 + (arg0 * 0x228) + &gEntityPool;
    var_v0_6 = temp_v1_8 + 0x30;
    do {
        var_a1->unk0 = (s32) var_v0_6->unk0;
        var_a1->unk4 = (s32) var_v0_6->unk4;
        var_a1->unk8 = (s32) var_v0_6->unk8;
        var_a1->unkC = (s32) var_v0_6->unkC;
        var_v0_6 += 0x10;
        var_a1 += 0x10;
    } while ((char*)var_v0_6 != (temp_v1_8 + 0x70));
    temp_a3 = gDLPtr;
    temp_t1_2 = gDLPtr + 8;
    temp_a3->unk0 = 0xDA380007;
    temp_v1_9 = gRenderBase + (gRenderIdx << 7);
    gDLPtr = temp_t1_2;
    gRenderIdx += 1;
    gDLPtr = temp_t1_2 + 8;
    temp_a3->unk4 = (s32) (temp_v1_9 + (gPlayerList << 6));
    temp_t1_2->unk4 = &gTrackRotMtx;
    temp_t1_2->unk8 = 0xDE000000;
    gDLPtr->unk8 = 0xDA380003;
    temp_t1_2->unkC = &gTrackRenderDL;
    gDLPtr = temp_t1_2 + 0x10;
    if (((Unk*)((char*)&gEntityPool + (arg0 * 0x228)))->unk1E4 != 0) {
        var_v1_3 = temp_t1_2 + 0x18;
        temp_t1_2->unk10 = 0xD9FFFFFF;
        var_v0_7 = 0x200;
    } else {
        var_v1_3 = temp_t1_2 + 0x18;
        temp_t1_2->unk10 = 0xD9FFFFFF;
        var_v0_7 = 0x400;
    }
    gDLPtr = var_v1_3;
    temp_t1_2->unk14 = var_v0_7;
    if (gGameFlags & 1) {
        temp_a1_3 = gDLPtr;
        temp_v0_4 = gDLPtr + 8;
        temp_a1_3->unk0 = 0xE7000000;
        gDLPtr = temp_v0_4;
        gDLPtr = temp_v0_4 + 8;
        gDLPtr = temp_v0_4 + 0x10;
        gDLPtr = temp_v0_4 + 0x18;
        temp_a1_3->unk4 = 0;
        temp_v0_4->unk10 = 0xF9000000;
        gDLPtr = temp_v0_4 + 0x20;
        gDLPtr->unk8 = 0xE3001201;
        temp_v0_4->unk4 = 0;
        temp_v0_4->unk8 = 0xE200001C;
        temp_v0_4->unkC = 0x0C193078;
        temp_v0_4->unk14 = 0x10101010;
        temp_v0_4->unk18 = 0xE2001E01;
        temp_v0_4->unk1C = 1;
    }
    temp_v0_5 = (arg0 * 0x228) + &gEntityPool;
    spA8 = temp_v0_5->unkC - temp_v0_5->unk0;
    spAC = temp_v0_5->unk10 - temp_v0_5->unk4;
    spB0 = temp_v0_5->unk14 - temp_v0_5->unk8;
    if (gGameFlags & 1) {
        sp134 = sp134 / 2;
    }
    var_s6 = gTrackNodePtr;
    if (var_s6 != NULL) {
        var_t2 = &gEntityPool;
        sp138 = arg0 * 0x44;
        do {
            temp_s5_2 = var_s6->unk84;
            var_s4 = temp_s5_2->unk18;
            var_s2 = 0;
            if (temp_s5_2->unk20 > 0) {
                temp_s7 = (sp138 + arg0) * 8;
                temp_s1_3 = temp_s7 + var_t2;
                temp_fs0 = (f32) sp134;
                var_t1 = &gRenderBase;
                var_t0 = &gPlayerList;
                var_s0 = var_s4 + 0x24;
                do {
                    temp_fv1_2 = temp_s1_3->unk0;
                    temp_ft2 = (f32) *(f32*)((char*)var_s0 - 18)- temp_fv1_2;
                    if ((temp_ft2 < temp_fs0) && (temp_ft1 = temp_s1_3->unk4, (((f32) *(f32*)((char*)var_s0 - 14)- temp_ft1) < temp_fs0)) && (temp_ft0_2 = temp_s1_3->unk8, (((f32) *(f32*)((char*)var_s0 - 10)- temp_ft0_2) < temp_fs0)) && (temp_fv1_3 = (f32) -sp134, (temp_fv1_3 < ((f32) *(s32*)((char*)var_s0 - 12) - temp_fv1_2))) && (temp_fv1_3 < ((f32) *(f32*)((char*)var_s0 - 8)- temp_ft1)) && (temp_fv1_3 < ((f32) *(f32*)((char*)var_s0 - 4)- temp_ft0_2))) {
                        spC8 = temp_ft2;
                        spCC = (f32) *(s32*)((char*)var_s0 - 12) - temp_s1_3->unk0;
                        spD0 = (f32) *(f32*)((char*)var_s0 - 14)- temp_s1_3->unk4;
                        spD4 = (f32) *(f32*)((char*)var_s0 - 8)- temp_s1_3->unk4;
                        spD8 = (f32) *(f32*)((char*)var_s0 - 10)- temp_s1_3->unk8;
                        var_a0_2 = 0;
                        spDC = (f32) *(f32*)((char*)var_s0 - 4)- temp_s1_3->unk8;
                        var_v1_4 = 0 & 1;
loop_61:
                        temp_ft0_3 = (&spC8)[var_v1_4];
                        spB8 = temp_ft0_3;
                        temp_fv0_5 = *(&spD0 + ((var_a0_2 * 2) & 4));
                        spBC = temp_fv0_5;
                        temp_ft1_2 = *(&spD8 + (var_a0_2 & 4));
                        spC0 = temp_ft1_2;
                        if (((spA8 * temp_ft0_3) + (spAC * temp_fv0_5) + (spB0 * temp_ft1_2)) >= 0.0f) {
                            sp140 = var_t0;
                            sp144 = var_t1;
                            sp148 = var_t2;
                            func_8013AB6C(var_t1->unk0 + (gRenderIdx << 7) + (var_t0->unk0 << 6), var_s4, temp_s7 + var_t2, temp_s5_2, gTrackTexBuf);
                            temp_a3_2 = gDLPtr;
                            temp_a1_4 = gDLPtr + 8;
                            temp_a3_2->unk0 = 0xDA380003;
                            gDLPtr = temp_a1_4;
                            gDLPtr = temp_a1_4 + 8;
                            temp_a3_2->unk4 = (s32) (*(s32*)((char*)var_t1 - 3810)+ (gRenderIdx << 7) + (var_t0->unk1E70 << 6));
                            gDLPtr->unk8 = 0xDE000000;
                            gRenderIdx += 1;
                            temp_a1_4->unk4 = (s32) var_s0->unk0;
                            var_s0 += 0x28;
                        } else {
                            var_a0_2 += 1;
                            var_v1_4 = var_a0_2 & 1;
                            if (var_a0_2 >= 8) {
                                goto block_64;
                            }
                            goto loop_61;
                        }
                    } else {
block_64:
                        var_s0 += 0x28;
                    }
                    var_s2 += 1;
                    var_s4 += 0x28;
                } while (var_s2 < temp_s5_2->unk20);
            }
            var_s6 = var_s6->unk0;
        } while (var_s6 != NULL);
    }
    gCamDLPtr = &gCamDLData;
    gDLPtr->unk0 = 0xE7000000;
    gDLPtr->unk4 = 0;
    gDLPtr += 8;
}
