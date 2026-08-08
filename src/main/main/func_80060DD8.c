#include "ultra64.h"
void renderLineStrip(void **);                   /* extern */
extern s32 gLineVtxBuf;
extern Unk gLineVtxIdx;
extern u32 gLineTexPtr;
extern s32 D_80178690;
extern Unk *D_801821E8;

void renderLineRectEx(s32 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, u32 arg10, u32 arg11, u32 arg12, u32 arg13, s32 arg14) {
    s16 temp_a1;
    s16 temp_a1_2;
    s16 temp_a1_3;
    s16 temp_a1_4;
    u32 temp_a0;
    u32 temp_v1_9;
    Unk *temp_v1;
    Unk *temp_v1_2;
    Unk *temp_v1_3;
    Unk *temp_v1_4;
    Unk *temp_v1_5;
    Unk *temp_v1_6;
    Unk *temp_v1_7;
    Unk *temp_v1_8;

    if (gLineVtxBuf == 0) {
        gLineVtxIdx.unk0 = 0U;
        gLineVtxBuf = D_80178690;
    }
    if (arg14 != 0) {
        temp_v1 = gLineVtxBuf + (gLineVtxIdx.unk0 * 0x10);
        temp_v1->unk3D = (s8) (arg10 >> 8);
        temp_v1->unk3E = (s8) (arg10 >> 0x10);
        temp_v1->unk3C = (s8) arg10;
        temp_v1->unk3F = (s8) (arg10 >> 0x18);
        temp_v1->unk30 = arg1;
        temp_v1->unk32 = arg2;
        temp_v1->unk34 = (s16) arg5;
        temp_v1->unk36 = 0;
        temp_v1->unk38 = (s16) arg6;
        temp_v1->unk3A = (s16) arg7;
        temp_v1_2 = gLineVtxBuf + (gLineVtxIdx.unk0 * 0x10);
        temp_v1_2->unkD = (s8) (arg11 >> 8);
        temp_v1_2->unkE = (s8) (arg11 >> 0x10);
        temp_v1_2->unkC = (s8) arg11;
        temp_v1_2->unkF = (s8) (arg11 >> 0x18);
        temp_a1 = arg1 + arg3;
        temp_v1_2->unk0 = temp_a1;
        temp_v1_2->unk2 = arg2;
        temp_v1_2->unk4 = (s16) arg5;
        temp_v1_2->unk6 = 0;
        temp_v1_2->unk8 = (s16) arg8;
        temp_v1_2->unkA = (s16) arg7;
        temp_v1_3 = gLineVtxBuf + (gLineVtxIdx.unk0 * 0x10);
        temp_v1_3->unk10 = temp_a1;
        temp_a1_2 = arg2 + arg4;
        temp_v1_3->unk12 = temp_a1_2;
        temp_v1_3->unk14 = (s16) arg5;
        temp_v1_3->unk16 = 0;
        temp_v1_3->unk18 = (s16) arg8;
        temp_v1_3->unk1A = (s16) arg9;
        temp_v1_3->unk1C = (s8) arg12;
        temp_v1_3->unk1D = (s8) (arg12 >> 8);
        temp_v1_3->unk1E = (s8) (arg12 >> 0x10);
        temp_v1_3->unk1F = (s8) (arg12 >> 0x18);
        temp_v1_4 = gLineVtxBuf + (gLineVtxIdx.unk0 * 0x10);
        temp_v1_4->unk2D = (s8) (arg13 >> 8);
        temp_v1_4->unk2E = (s8) (arg13 >> 0x10);
        temp_v1_4->unk20 = arg1;
        temp_v1_4->unk22 = temp_a1_2;
        temp_v1_4->unk24 = (s16) arg5;
        temp_v1_4->unk26 = 0;
        temp_v1_4->unk28 = (s16) arg6;
        temp_v1_4->unk2A = (s16) arg9;
        temp_v1_4->unk2C = (s8) arg13;
        temp_v1_4->unk2F = (s8) (arg13 >> 0x18);
    } else {
        temp_v1_5 = gLineVtxBuf + (gLineVtxIdx.unk0 * 0x10);
        temp_v1_5->unkD = (s8) (arg10 >> 8);
        temp_v1_5->unkE = (s8) (arg10 >> 0x10);
        temp_v1_5->unkC = (s8) arg10;
        temp_v1_5->unkF = (s8) (arg10 >> 0x18);
        temp_v1_5->unk0 = arg1;
        temp_v1_5->unk2 = arg2;
        temp_v1_5->unk4 = (s16) arg5;
        temp_v1_5->unk6 = 0;
        temp_v1_5->unk8 = (s16) arg6;
        temp_v1_5->unkA = (s16) arg7;
        temp_v1_6 = gLineVtxBuf + (gLineVtxIdx.unk0 * 0x10);
        temp_v1_6->unk1D = (s8) (arg11 >> 8);
        temp_v1_6->unk1E = (s8) (arg11 >> 0x10);
        temp_v1_6->unk1C = (s8) arg11;
        temp_v1_6->unk1F = (s8) (arg11 >> 0x18);
        temp_a1_3 = arg1 + arg3;
        temp_v1_6->unk10 = temp_a1_3;
        temp_v1_6->unk12 = arg2;
        temp_v1_6->unk14 = (s16) arg5;
        temp_v1_6->unk16 = 0;
        temp_v1_6->unk18 = (s16) arg8;
        temp_v1_6->unk1A = (s16) arg7;
        temp_v1_7 = gLineVtxBuf + (gLineVtxIdx.unk0 * 0x10);
        temp_v1_7->unk20 = temp_a1_3;
        temp_a1_4 = arg2 + arg4;
        temp_v1_7->unk22 = temp_a1_4;
        temp_v1_7->unk24 = (s16) arg5;
        temp_v1_7->unk26 = 0;
        temp_v1_7->unk28 = (s16) arg8;
        temp_v1_7->unk2A = (s16) arg9;
        temp_v1_7->unk2C = (s8) arg12;
        temp_v1_7->unk2D = (s8) (arg12 >> 8);
        temp_v1_7->unk2E = (s8) (arg12 >> 0x10);
        temp_v1_7->unk2F = (s8) (arg12 >> 0x18);
        temp_v1_8 = gLineVtxBuf + (gLineVtxIdx.unk0 * 0x10);
        temp_v1_8->unk3D = (s8) (arg13 >> 8);
        temp_v1_8->unk3E = (s8) (arg13 >> 0x10);
        temp_v1_8->unk30 = arg1;
        temp_v1_8->unk32 = temp_a1_4;
        temp_v1_8->unk34 = (s16) arg5;
        temp_v1_8->unk36 = 0;
        temp_v1_8->unk38 = (s16) arg6;
        temp_v1_8->unk3A = (s16) arg9;
        temp_v1_8->unk3C = (s8) arg13;
        temp_v1_8->unk3F = (s8) (arg13 >> 0x18);
    }
    ((Unk*)((char*)D_801821E8 + gLineTexPtr * 0x10))->unkC = (s8) (gLineVtxIdx.unk3 + 3);
    ((Unk*)((char*)D_801821E8 + gLineTexPtr * 0x10))->unkD = (s8) (gLineVtxIdx.unk3 + 2);
    ((Unk*)((char*)D_801821E8 + gLineTexPtr * 0x10))->unkE = (s8) (gLineVtxIdx.unk3 + 1);
    ((Unk*)((char*)D_801821E8 + gLineTexPtr * 0x10))->unkF = (u8) gLineVtxIdx.unk3;
    temp_v1_9 = gLineTexPtr + 1;
    temp_a0 = gLineVtxIdx.unk0 + 4;
    gLineTexPtr = temp_v1_9;
    gLineVtxIdx.unk0 = temp_a0;
    D_80178690 += 0x40;
    if ((temp_v1_9 >= 0x20U) || (temp_a0 >= 0x1DU)) {
        renderLineStrip((void **)arg0);
    }
}
