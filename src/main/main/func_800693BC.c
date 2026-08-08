#include "ultra64.h"
void mtxCopyTranslate(Unk*, Unk*, f32, f32, f32);           /* extern */
void mtxNodeInit(void *, f32, f32, f32);                /* extern */
void mtxCatFSafe(s32, s32, s32);                     /* extern */
void guMtxScaleF2L(Unk*, Unk*);                          /* extern */
void mtxLookAt(Unk*, f32, f32, f32, f32, f32, f32); /* extern */
f32 sinf(f32);                             /* extern */
extern f32 gNodeRenderParam0;
extern f32 gNodeRenderParam1;
extern f32 gNodeRenderParam2;
extern f32 gNodeRenderParam3;
extern f32 gNodeRenderParam4;
extern f32 gNodeRenderParam5;
extern f32 gNodeRenderParam6;
extern f32 gNodeRenderParam7;
extern f32 gNodeScale;
extern f32 gNodeRenderParam8;
extern f32 gNodeRenderParam9;
extern f32 gNodeAmpF;
extern f32 gNodeClamp;
extern s32 gPlayerList;
extern s32 gPlayerList2;
extern s32 gEntityDL2;
extern s32 gEntityDL;
extern Unk *gDLPtr;
extern s32 gRenderIdx;
extern s32 gRenderBase;

void cameraMatrixBuild(Unk *arg0, Unk *arg1) {
    s32 spA0;
    s32 sp60;
    s32 sp20;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft1_2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 var_ft1;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s2;
    s32 temp_v1_3;
    s32 var_a1;
    s32 var_s1;
    s32 var_t0;
    s32 var_v1;
    Unk *temp_a0;
    Unk *temp_a0_2;
    Unk *temp_a3;
    Unk *temp_a3_2;
    Unk *temp_v0;
    Unk *temp_v1;
    Unk *temp_v1_2;

    if (arg0->unk648 != 0.0f) {
        var_s1 = 0;
        temp_fs0 = gNodeRenderParam0;
        temp_fs2 = gNodeRenderParam1;
        temp_fs1 = gNodeRenderParam2;
        temp_v0 = gDLPtr + 8;
        gDLPtr->unk0 = 0xE7000000;
        gDLPtr->unk4 = 0;
        gDLPtr = temp_v0;
        gDLPtr = temp_v0 + 8;
        gDLPtr = temp_v0 + 0x10;
        gDLPtr = temp_v0 + 0x18;
        gDLPtr->unk8 = 0xD9FEF9FF;
        temp_v0->unk4 = 0;
        temp_v0->unk8 = 0xE7000000;
        temp_v0->unkC = 0;
        temp_v0->unk10 = 0xE200001C;
        temp_v0->unk14 = 0x0C184DD8;
        gDLPtr = temp_v0 + 0x20;
        temp_v0->unk18 = 0xFCFFFFFF;
        temp_v0->unk1C = 0xFFFDF638;
        do {
            temp_ft1 = (f32) ((gPlayerList2 + (var_s1 << 6)) & 0x7F) * gNodeRenderParam3;
            temp_ft0 = temp_ft1 - temp_fs0;
            temp_s2 = (s32) ((temp_fs0 - fabsf(temp_ft0)) * (f32) (0xFF - arg0->unk558) * gNodeRenderParam4);
            if (!(temp_ft1 < temp_fs0)) {
                var_ft1 = (temp_fs0 - (sqrtf(gNodeRenderParam5 - (2.0f * temp_ft0)) * temp_fs2)) + (temp_ft1 * temp_fs0);
            } else {
                var_ft1 = (temp_ft1 * temp_fs0) + (sqrtf(2.0f * temp_ft1) * temp_fs2);
            }
            temp_ft1_2 = var_ft1 * gNodeRenderParam6;
            temp_fv0 = arg0->unk648;
            temp_fv1 = 2.0f * temp_fv0 * temp_ft1_2;
            mtxNodeInit(&sp20, temp_fv1, temp_fv1, temp_fv0 * (temp_ft1_2 * gNodeRenderParam7));
            mtxLookAt(&sp60, arg1->unkC - arg1->unk0, arg1->unk10 - arg1->unk4, arg1->unk14 - arg1->unk8, arg1->unk18, arg1->unk1C, arg1->unk20);
            mtxCatFSafe(&sp20, &sp60, &spA0);
            mtxCopyTranslate(&spA0, &sp20, arg0->unk0 - arg1->unk0, arg0->unk4 - arg1->unk4, arg0->unk8 - arg1->unk8);
            guMtxScaleF2L(&sp20, gRenderBase + (gRenderIdx << 7) + (gPlayerList << 6));
            temp_a0 = gDLPtr + 8;
            gDLPtr->unk0 = 0xDA380003;
            gDLPtr->unk4 = (void *) (gRenderBase + (gRenderIdx << 7) + (gPlayerList << 6));
            gDLPtr->unk8 = 0xFA000000;
            temp_fv0_2 = arg0->unk648 * (f32) temp_s2;
            gDLPtr = temp_a0;
            gRenderIdx += 1;
            gDLPtr = temp_a0 + 8;
            if (!(temp_fs1 <= temp_fv0_2)) {
                var_a1 = (s32) temp_fv0_2;
            } else {
                var_a1 = (s32) (temp_fv0_2 - temp_fs1) | 0x80000000;
            }
            var_s1 += 1;
            temp_a0->unk4 = (s32) ((var_a1 & 0xFF) | 0xA0C0E000);
            temp_v1 = gDLPtr + 8;
            gDLPtr->unk0 = 0xDE000000;
            gDLPtr->unk4 = &gEntityDL2;
            gDLPtr = temp_v1;
            gDLPtr = temp_v1 + 8;
            gDLPtr->unk8 = 0xE7000000;
            temp_v1->unk4 = 0;
        } while (var_s1 < 2);
        temp_v1_2 = gDLPtr + 8;
        gDLPtr->unk0 = 0xE7000000;
        gDLPtr->unk4 = 0;
        gDLPtr = temp_v1_2;
        gDLPtr = temp_v1_2 + 8;
        gDLPtr->unk8 = 0xE200001C;
        temp_v1_2->unk4 = 0x0C1849D8;
        gDLPtr = temp_v1_2 + 0x10;
        temp_v1_2->unk8 = 0xFCFFB9FF;
        temp_v1_2->unkC = 0xFFFDFE38;
        mtxNodeInit(&sp20, gNodeScale, gNodeScale, 2.0f);
        mtxLookAt(&sp60, arg0->unk340, arg0->unk344, arg0->unk348, arg1->unk18, arg1->unk1C, arg1->unk20);
        mtxCatFSafe(&sp20, &sp60, &spA0);
        mtxCopyTranslate(&spA0, &sp20, arg0->unk0 - arg1->unk0, arg0->unk4 - arg1->unk4, arg0->unk8 - arg1->unk8);
        guMtxScaleF2L(&sp20, gRenderBase + (gRenderIdx << 7) + (gPlayerList << 6));
        temp_a3 = gDLPtr;
        temp_a0_2 = gDLPtr + 8;
        temp_a2 = gRenderIdx << 7;
        temp_a1 = gRenderIdx + 1;
        temp_a3->unk0 = 0xDA380003;
        temp_v1_3 = gRenderBase + temp_a2;
        gRenderIdx = temp_a1;
        gDLPtr = temp_a0_2;
        temp_a3->unk4 = (s32) (temp_v1_3 + (gPlayerList << 6));
        gDLPtr = temp_a0_2 + 8;
        gDLPtr->unk8 = 0xFA000000;
        temp_fv0_3 = arg0->unk648 * (((sinf((f32) gPlayerList2 * gNodeRenderParam8) + gNodeRenderParam9) * gNodeAmpF) + gNodeAmpF);
        if (gNodeClamp <= temp_fv0_3) {
            var_t0 = (s32) (temp_fv0_3 - gNodeClamp) | 0x80000000;
        } else {
            var_t0 = (s32) temp_fv0_3;
        }
        temp_a0_2->unk4 = (s32) ((var_t0 & 0xFF) | 0xA0C0E000);
        temp_a3_2 = gDLPtr + 8;
        gDLPtr->unk0 = 0xDE000000;
        gDLPtr->unk4 = &gEntityDL;
        gDLPtr = temp_a3_2;
        gDLPtr = temp_a3_2 + 8;
        gDLPtr->unk8 = 0xE7000000;
        gDLPtr = temp_a3_2 + 0x10;
        temp_a3_2->unk4 = 0;
        temp_a3_2->unk8 = 0xE200001C;
        temp_a3_2->unkC = 0xC8103078;
        temp_a3_2->unk10 = 0xFC127FFF;
        temp_a3_2->unk14 = -0xDC8;
        gDLPtr = temp_a3_2 + 0x18;
        if (arg1->unk1E4 != 0) {
            var_v1 = 0x10200;
        } else {
            var_v1 = 0x10400;
        }
        gDLPtr = temp_a3_2 + 0x20;
        temp_a3_2->unk18 = 0xD9FFFFFF;
        temp_a3_2->unk1C = var_v1;
    }
}
