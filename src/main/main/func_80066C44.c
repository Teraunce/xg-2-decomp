#include "ultra64.h"
void safeCopy(u32, u32, u32);                       /* extern */
void audioSetBeatPos(Unk*, s32, s32);                       /* extern */
extern s32 gSceneObjFuncTable;
extern s32 gScreenHeight;
extern Unk *gDLPtr;
extern s32 gScreenWidth;
extern Unk gRaceCtx;
extern s32 gSceneBuf;
extern s32 gSceneCtx;
extern s32 gAudioBeatPos;
extern s32 gRaceCtxBak;
extern Unk gRenderSentinel;

void gameStateSync(void) {
    char *var_s0;
    char *var_s0_2;
    Unk *var_s0_3;
    char *var_s2;
    char *var_s2_2;
    Unk *var_v1_3;
    s32 temp_a1;
    s32 var_a0;
    s32 var_a3;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s1_6;
    s32 var_t0;
    s32 var_t3;
    s32 var_t4;
    s32 var_t5;
    s32 var_v1;
    s8 temp_v0;
    u8 *var_a0_2;
    u8 *var_a2;
    u8 *var_v1_2;
    u8 var_v0;
    Unk *temp_v1;
    Unk *var_a0_3;
    char *var_a0_4;
    char *var_t1;
    char *var_t2;
    char *var_t6;

    var_s1 = 0;
    var_t6 = &gRaceCtx + 0x1C;
    var_t5 = 0;
    var_t4 = 0;
    gRaceCtx.unk0 = 0;
    do {
        var_a3 = 0;
        var_t3 = var_t4;
        var_t2 = var_t4 + &gSceneBuf;
        var_t1 = var_t6;
        var_t0 = var_t4;
loop_2:
        var_v1 = 0;
        if ((((var_s1 == 0) || (var_s1 == 8)) && (var_a3 == 0)) || (var_a0 = var_t5 + var_a3, ((var_s1 < 0xC) == 0))) {
            var_v1 = 1;
            var_a0 = var_t5 + var_a3;
        }
        var_a2 = var_t1 + 5;
        ((Unk*)((char*)&gRaceCtx + var_t0))->unk4 = var_v1;
        temp_a1 = var_a0 % 7;
        temp_v1 = var_t3 + &gRaceCtx;
        var_a0_2 = *((temp_a1 * 4) + &gSceneObjFuncTable);
        temp_v1->unk1C = 0xE10;
        temp_v0 = temp_a1 + 0xD;
        temp_v1->unk20 = temp_v0;
        temp_v1->unk7C = 0;
        temp_v1->unk80 = temp_v0;
        var_v0 = *var_a0_2;
        var_v1_2 = var_t2 + 5;
        if (var_v0 != 0) {
            do {
                var_a0_2 += 1;
                *var_v1_2 = var_v0;
                var_v1_2 += 1;
                *var_a2 = var_v0;
                var_v0 = *var_a0_2;
                var_a2 += 1;
            } while (var_v0 != 0);
        }
        var_t3 += 0x10;
        var_t2 += 0x10;
        var_t1 += 0x10;
        var_t0 += 4;
        var_a3 += 1;
        *var_a2 = 0;
        *var_v1_2 = 0;
        if (var_a3 < 6) {
            goto loop_2;
        }
        var_t6 += 0xD8;
        var_t5 += 6;
        var_s1 += 1;
        var_t4 += 0xD8;
    } while (var_s1 < 0xD);
    var_s1_2 = 0xC;
    var_a0_3 = &gRaceCtx + 0x30;
    gRaceCtx.unkAFC = 0xC000;
    gRaceCtx.unkB00 = 0xC000;
    gRaceCtx.unkB04 = 0xC000;
    gRaceCtx.unkB14 = 2;
    gRaceCtx.unkB08 = 0;
    gRaceCtx.unkB0C = 0;
    gRaceCtx.unkB10 = 0;
    gRaceCtx.unkB18 = 3;
    gRaceCtx.unkB1C = 0;
    gRaceCtx.unkB20 = 0;
    gRaceCtx.unkB24 = 0;
    gRaceCtx.unkB28 = 0;
    gRaceCtx.unkB2C = 0;
    gRaceCtx.unkB30 = 0;
    gRaceCtx.unkB34 = 0;
    do {
        var_a0_3->unkB38 = 0;
        var_s1_2 -= 1;
        var_a0_3 -= 4;
    } while (var_s1_2 >= 0);
    var_s1_3 = 0;
    var_s2 = &gRaceCtx + 0xCF8;
    var_s0 = &gRaceCtx + 0xB88;
    gRaceCtx.unkB78 = 6;
    gRaceCtx.unkB6C = 0;
    gRaceCtx.unkB70 = 1;
    gRaceCtx.unkB7C = 0;
    gRaceCtx.unkB80 = -1;
    gRaceCtx.unkB84 = 0;
    gRaceCtx.unk10F8 = 0;
    gRaceCtx.unk10FC = 1;
    gRaceCtx.unk10EC = (s32) gRaceCtx.unkB0C;
    gRaceCtx.unk10F0 = (s32) gRaceCtx.unkB14;
    gRaceCtx.unk10F4 = (s32) gRaceCtx.unkB18;
    do {
        audioSetBeatPos(var_s0, var_s1_3, 1);
        audioSetBeatPos(var_s2, var_s1_3, 1);
        var_s2 += 0x5C;
        var_s1_3 += 1;
        var_s0 += 0x5C;
    } while (var_s1_3 < 4);
    var_s1_4 = 0;
    var_s0_2 = &gSceneCtx;
    do {
        audioSetBeatPos(var_s0_2, var_s1_4, 0);
        var_s1_4 += 1;
        var_s0_2 += 0x5C;
    } while (var_s1_4 < 7);
    audioSetBeatPos(&gAudioBeatPos, 0, 0);
    var_s1_5 = 0;
    var_s0_3 = &gRaceCtx;
    var_s2_2 = &gRaceCtx + 0x1114;
    gRaceCtx.unk1104 = -1;
    gRaceCtx.unk1100 = 0;
    gRaceCtx.unk1108 = 0;
    gRaceCtx.unk1110 = 0;
    gRaceCtx.unk16D4 = 1;
    gRaceCtx.unk110C = (s32) gRaceCtx.unkB18;
    do {
        audioSetBeatPos(var_s2_2, var_s1_5, 1);
        var_s0_3->unk1118 = -1;
        var_s0_3 += 0x5C;
        var_s1_5 += 1;
        var_s2_2 += 0x5C;
    } while (var_s1_5 < 0x10);
    var_s1_6 = 0;
    var_a0_4 = &gRaceCtx + 0xE68;
    var_v1_3 = &gRaceCtx;
    gRaceCtx.unk16D8 = 6;
    gRaceCtx.unk16DC = 0;
    gRaceCtx.unk16E0 = 0;
    gRaceCtx.unk16E4 = 0;
    gRaceCtx.unk16E8 = 0;
    gRaceCtx.unk16EC = 0;
    gRaceCtx.unk16F0 = 0;
    do {
        var_v1_3->unk16F8 = var_a0_4;
        var_a0_4 += 0x5C;
        var_v1_3->unk1718 = var_s1_6;
        var_s1_6 += 1;
        var_v1_3 += 4;
    } while (var_s1_6 < 8);
    safeCopy(&gRaceCtxBak, &gRaceCtx, 0x1738);
    gRenderSentinel.unk0 = -1;
    gRenderSentinel.unk1 = -1;
}

/*
 * trackSegmentOffset — palette-offset lookup + modulo-3 adjustment (nonmatching).
 *
 * PERMANENTLY NONMATCHING — two reasons:
 * 1. jr dispatch through jtbl_8004C2F8 (12 entries, index = arg0).
 * 2. alabel func_80067054: the epilogue (modulo-3 + return) is shared with
 *    another function that branches directly into it mid-body.
 *
 * Maps arg0 (palette index 0-11) to a base offset:
 *   0→0xAC, 1→0xAF, 2→0xBE, 3→0xC1, 4→0xC4, 5→0xC7,
 *   6→0xB2, 7→0xB5, 8→0xB8, 9→0xBB, 10→0xCA, 11→0xCD
 * Then returns base + (arg1 % 3).  Index >= 12 → base = 0.
 */
s32 trackSegmentOffset(s32 arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 base;
    (void)arg2; (void)arg3;
    if ((u32)arg0 >= 12U) {
        base = 0;
    } else {
        switch (arg0) {
        case 0:  base = 0xAC; break;
        case 1:  base = 0xAF; break;
        case 2:  base = 0xBE; break;
        case 3:  base = 0xC1; break;
        case 4:  base = 0xC4; break;
        case 5:  base = 0xC7; break;
        case 6:  base = 0xB2; break;
        case 7:  base = 0xB5; break;
        case 8:  base = 0xB8; break;
        case 9:  base = 0xBB; break;
        case 10: base = 0xCA; break;
        default: base = 0xCD; break;
        }
    }
    return base + (arg1 % 3);
}

void func_80067080(void) {
    s32 temp_v0;
    Unk *temp_a1;

    temp_a1 = gDLPtr + 8;
    gDLPtr->unk0 = 0xE7000000;
    gDLPtr->unk4 = 0;
    gDLPtr = temp_a1;
    gDLPtr = temp_a1 + 8;
    temp_a1->unk4 = 0x300000;
    gDLPtr = temp_a1 + 0x10;
    gDLPtr = temp_a1 + 0x18;
    gDLPtr = temp_a1 + 0x20;
    temp_a1->unk18 = 0xF7000000;
    gDLPtr->unk8 = 0xE3000A01;
    gDLPtr = temp_a1 + 0x28;
    temp_a1->unk10 = 0xE7000000;
    temp_a1->unk8 = 0xE200001C;
    temp_a1->unkC = 0x0F0A4000;
    temp_a1->unk14 = 0;
    temp_a1->unk1C = 0x10001;
    temp_v0 = (s32) gScreenHeight / 2;
    temp_a1->unk20 = (s32) (((gScreenWidth & 0x3FF) << 0xE) | (((temp_v0 & 0x3FF) * 4) | 0xF6000000));
    temp_a1->unk24 = (s32) (((temp_v0 - 1) & 0x3FF) * 4);
}

void func_80067160(void) {
    s32 temp_v1;
    Unk *temp_a1;

    temp_a1 = gDLPtr + 8;
    gDLPtr->unk0 = 0xE7000000;
    gDLPtr->unk4 = 0;
    gDLPtr = temp_a1;
    gDLPtr = temp_a1 + 8;
    temp_a1->unk4 = 0x300000;
    gDLPtr = temp_a1 + 0x10;
    gDLPtr = temp_a1 + 0x18;
    gDLPtr = temp_a1 + 0x20;
    temp_a1->unk18 = 0xF7000000;
    temp_a1->unk10 = 0xE7000000;
    gDLPtr = temp_a1 + 0x28;
    gDLPtr->unk8 = 0xE3000A01;
    temp_a1->unk8 = 0xE200001C;
    temp_a1->unkC = 0x0F0A4000;
    temp_a1->unk14 = 0;
    temp_a1->unk1C = 0x10001;
    temp_v1 = (s32) gScreenWidth / 2;
    temp_a1->unk24 = (s32) (((temp_v1 - 1) & 0x3FF) << 0xE);
    temp_a1->unk20 = (s32) (((temp_v1 & 0x3FF) << 0xE) | (((gScreenHeight & 0x3FF) * 4) | 0xF6000000));
}

void func_80067240(void) {
    s32 temp_a1;
    s32 temp_v0;
    Unk *temp_a0;

    temp_a0 = gDLPtr + 8;
    gDLPtr->unk0 = 0xE7000000;
    gDLPtr->unk4 = 0;
    gDLPtr = temp_a0;
    gDLPtr = temp_a0 + 8;
    temp_a0->unk4 = 0x300000;
    gDLPtr = temp_a0 + 0x10;
    gDLPtr = temp_a0 + 0x18;
    gDLPtr = temp_a0 + 0x20;
    temp_a0->unk18 = 0xF7000000;
    gDLPtr->unk8 = 0xE3000A01;
    gDLPtr = temp_a0 + 0x28;
    temp_a0->unkC = 0x0F0A4000;
    temp_a0->unk1C = 0x10001;
    temp_a0->unk8 = 0xE200001C;
    temp_a0->unk10 = 0xE7000000;
    temp_a0->unk14 = 0;
    temp_v0 = (s32) gScreenHeight / 2;
    temp_a0->unk24 = (s32) (((temp_v0 - 1) & 0x3FF) * 4);
    gDLPtr = temp_a0 + 0x30;
    temp_a1 = (s32) gScreenWidth / 2;
    temp_a0->unk20 = (s32) (((gScreenWidth & 0x3FF) << 0xE) | (((temp_v0 & 0x3FF) * 4) | 0xF6000000));
    temp_a0->unk28 = (s32) (((temp_a1 & 0x3FF) << 0xE) | (((gScreenHeight & 0x3FF) * 4) | 0xF6000000));
    temp_a0->unk2C = (s32) (((temp_a1 - 1) & 0x3FF) << 0xE);
}

void func_80067360(void) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_t0;
    s32 temp_v1;
    s32 temp_v1_2;
    Unk *temp_a0;

    temp_a0 = gDLPtr + 8;
    gDLPtr->unk0 = 0xE7000000;
    gDLPtr->unk4 = 0;
    gDLPtr = temp_a0;
    gDLPtr = temp_a0 + 8;
    temp_a0->unk4 = 0x300000;
    gDLPtr = temp_a0 + 0x10;
    gDLPtr = temp_a0 + 0x18;
    gDLPtr = temp_a0 + 0x20;
    temp_a0->unk18 = 0xF7000000;
    temp_a0->unk8 = 0xE200001C;
    gDLPtr = temp_a0 + 0x28;
    temp_a0->unkC = 0x0F0A4000;
    gDLPtr->unk8 = 0xE3000A01;
    temp_a0->unk10 = 0xE7000000;
    temp_a0->unk14 = 0;
    temp_a0->unk1C = 0x10001;
    temp_v1 = (s32) gScreenWidth / 2;
    temp_a1 = (s32) gScreenHeight / 2;
    temp_t0 = ((temp_v1 & 0x3FF) << 0xE) | (((temp_a1 & 0x3FF) * 4) | 0xF6000000);
    temp_a1_2 = ((temp_a1 - 1) & 0x3FF) * 4;
    temp_v1_2 = ((temp_v1 - 1) & 0x3FF) << 0xE;
    gDLPtr = temp_a0 + 0x30;
    temp_a0->unk2C = temp_v1_2;
    temp_a0->unk20 = temp_t0;
    temp_a0->unk24 = temp_a1_2;
    temp_a0->unk28 = temp_t0;
    gDLPtr = temp_a0 + 0x38;
    temp_a0->unk30 = (s32) (((gScreenWidth & 0x3FF) << 0xE) | (((gScreenHeight & 0x3FF) * 4) | 0xF6000000));
    temp_a0->unk34 = (s32) (temp_v1_2 | temp_a1_2);
}

void func_80067494(void) {
    s32 temp_a1;
    s32 temp_a3;
    s32 temp_v1;
    Unk *temp_a0;

    temp_a0 = gDLPtr + 8;
    gDLPtr->unk0 = 0xE7000000;
    gDLPtr->unk4 = 0;
    gDLPtr = temp_a0;
    gDLPtr = temp_a0 + 8;
    temp_a0->unk4 = 0x300000;
    gDLPtr = temp_a0 + 0x10;
    gDLPtr = temp_a0 + 0x18;
    gDLPtr = temp_a0 + 0x20;
    temp_a0->unk18 = 0xF7000000;
    gDLPtr->unk8 = 0xE3000A01;
    gDLPtr = temp_a0 + 0x28;
    temp_a0->unkC = 0x0F0A4000;
    temp_a0->unk1C = 0x10001;
    temp_a0->unk8 = 0xE200001C;
    temp_a0->unk10 = 0xE7000000;
    temp_a0->unk14 = 0;
    temp_v1 = (s32) gScreenHeight / 2;
    temp_a1 = (s32) gScreenWidth / 2;
    temp_a0->unk20 = (s32) (((gScreenWidth & 0x3FF) << 0xE) | (((temp_v1 & 0x3FF) * 4) | 0xF6000000));
    temp_a3 = (temp_a1 & 0x3FF) << 0xE;
    temp_a0->unk24 = (s32) (temp_a3 | (((temp_v1 - 1) & 0x3FF) * 4));
    gDLPtr = temp_a0 + 0x30;
    temp_a0->unk28 = (s32) (temp_a3 | (((gScreenHeight & 0x3FF) * 4) | 0xF6000000));
    temp_a0->unk2C = (s32) (((temp_a1 - 1) & 0x3FF) << 0xE);
}

void func_800675B8(void) {
    s32 temp_a0;
    s32 temp_t1;
    s32 temp_v0;
    Unk *temp_a1;

    temp_a1 = gDLPtr + 8;
    gDLPtr->unk0 = 0xE7000000;
    gDLPtr->unk4 = 0;
    gDLPtr = temp_a1;
    gDLPtr = temp_a1 + 8;
    temp_a1->unk4 = 0x300000;
    gDLPtr = temp_a1 + 0x10;
    gDLPtr = temp_a1 + 0x18;
    gDLPtr = temp_a1 + 0x20;
    temp_a1->unk18 = 0xF7000000;
    gDLPtr->unk8 = 0xE3000A01;
    gDLPtr = temp_a1 + 0x28;
    temp_a1->unkC = 0x0F0A4000;
    temp_a1->unk8 = 0xE200001C;
    temp_a1->unk10 = 0xE7000000;
    temp_a1->unk14 = 0;
    temp_a1->unk1C = 0x10001;
    temp_v0 = (s32) gScreenHeight / 2;
    temp_t1 = (temp_v0 & 0x3FF) * 4;
    temp_a1->unk24 = (s32) (((temp_v0 - 1) & 0x3FF) * 4);
    gDLPtr = temp_a1 + 0x30;
    temp_a0 = (s32) gScreenWidth / 2;
    temp_a1->unk20 = (s32) (((gScreenWidth & 0x3FF) << 0xE) | (temp_t1 | 0xF6000000));
    temp_a1->unk28 = (s32) (((temp_a0 & 0x3FF) << 0xE) | (((gScreenHeight & 0x3FF) * 4) | 0xF6000000));
    temp_a1->unk2C = (s32) ((((temp_a0 - 1) & 0x3FF) << 0xE) | temp_t1);
}
