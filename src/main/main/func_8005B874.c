#include "ultra64.h"
void viSwapBuffers(Unk*);                            /* extern */
void audioInitFreqTable();                                  /* extern */
extern s32 gAudioSampleTable;
extern s32 gSfxDecodeTable;
extern Unk gTrackEdgeData;
extern s32 gTrackEdgeTable;
extern Unk gAudioStreamBuf;
extern char *gSfxDecodeDst;
extern u32 gSfxDecodeBuf;
extern s32 gSfxCooldown;
extern s16 gSfxDecodeReadOff;
extern s16 gSfxDecodedCount;
extern s16 gSfxDecodeIdx;
extern u16 gSfxDecodeSize;
extern s32 gSfxDecodeBufData;
extern s32 gAudioDmaBuf;

s16 fmvDecodeFrame(s32 arg0) {
    s32 subroutine_arg5 = 0;
    s16 *temp_a0_2;
    s16 temp_s0_2;
    s16 temp_v0;
    s16 temp_v1_3;
    s16 var_a1;
    s16 var_s5;
    s32 temp_a0;
    s32 temp_a0_3;
    s32 temp_a3;
    s32 temp_s1;
    s32 temp_s4;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 var_a0;
    s8 *temp_v0_8;
    u16 *temp_a1;
    u16 *temp_v0_2;
    u16 *temp_v0_5;
    u16 temp_a3_2;
    u16 temp_t0;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v1_2;
    u16 var_a1_2;
    u16 var_a2;
    u16 var_s2;
    u16 var_s2_3;
    u32 var_s2_2;
    u32 var_s3;
    Unk *temp_s0;
    Unk *temp_s0_3;
    Unk *temp_s0_4;

    var_s5 = 0;
    if (arg0 == (s32)0 /* implicit $v0 from caller */) {
        var_s2 = gAudioStreamBuf.unk4E4;
        if (var_s2 < 0x273U) {
            do {
                if (gSfxCooldown == 0) {
                    temp_s0 = gSfxDecodeDst;
                    if ((u32) temp_s0->unkC >= (u32) temp_s0->unk10) {
                        viSwapBuffers(temp_s0);
                    }
                    temp_v1 = temp_s0->unkC;
                    temp_s0->unkC = (s32) (temp_v1 + 4);
                    gSfxCooldown = 0x20;
                    gSfxDecodeBuf = *((temp_s0->unk8 << 0xA) + temp_v1 + &gAudioDmaBuf);
                }
                var_s2 = *(u16*)((char*)&gAudioStreamBuf + (((var_s2 + ((u32)gSfxDecodeBuf >> 0x1F)) & 0xFFFF) * 2));
                gSfxDecodeBuf *= 2;
                gSfxCooldown -= 1;
            } while (var_s2 < 0x273U);
        }
        temp_s0_2 = var_s2 - 0x273;
        if (gTrackEdgeData.unk4E4 == 0x8000) {
            audioInitFreqTable();
        }
        var_a2 = ((Unk*)((char*)&gTrackEdgeTable + ((s32)(temp_s0_2 << 0x10) >> 0xF)))->unk4E6;
        do {
            temp_v0_2 = (u16*)((char*)&gTrackEdgeData + ((s32)(var_a2 << 0x10) >> 0xF));
            temp_v1_2 = *temp_v0_2 + 1;
            *temp_v0_2 = temp_v1_2;
            var_a1 = (s16) temp_v1_2;
            temp_v0_3 = var_a2 + 2;
            if ((s32) *(u16*)((char*)&gTrackEdgeData + ((s32)((var_a2 + 1) << 0x10) >> 0xF)) < var_a1) {
                var_a0 = temp_v0_3;
                if ((s32) *(u16*)((char*)&gTrackEdgeData + ((s32)(temp_v0_3 << 0x10) >> 0xF)) < var_a1) {
                    do {
                        temp_v0_4 = var_a0 + 1;
                        var_a0 = temp_v0_4;
                    } while ((s32) *(u16*)((char*)&gTrackEdgeData + ((s32)(temp_v0_4 << 0x10) >> 0xF)) < var_a1);
                }
                temp_t0 = var_a0 - 1;
                temp_a0 = (s32) (var_a2 << 0x10) >> 0xF;
                temp_a3 = (s32) (temp_t0 << 0x10) >> 0xF;
                temp_a1 = (u16*)((char*)&gTrackEdgeData + temp_a3);
                temp_a0_2 = (s16*)((char*)&gAudioStreamBuf + temp_a0);
                *(u16*)((char*)&gTrackEdgeData + temp_a0) = *temp_a1;
                *temp_a1 = temp_v1_2;
                temp_v1_3 = *temp_a0_2;
                var_a1 = (s16) (u16) *temp_a0_2;
                *((temp_v1_3 * 2) + &gTrackEdgeTable) = temp_t0;
                if (temp_v1_3 < 0x273) {
                    *(((temp_v1_3 + 1) * 2) + &gTrackEdgeTable) = temp_t0;
                }
                temp_v0_5 = (u16*)((char*)&gAudioStreamBuf + temp_a3);
                temp_a3_2 = *temp_v0_5;
                *temp_v0_5 = (u16) var_a1;
                *(((s16) temp_a3_2 * 2) + &gTrackEdgeTable) = var_a2;
                if ((s16) temp_a3_2 < 0x273) {
                    *((((s16) temp_a3_2 + 1) * 2) + &gTrackEdgeTable) = var_a2;
                }
                *temp_a0_2 = (s16) temp_a3_2;
                var_a2 = temp_t0;
            }
            temp_v0 = *(((s32) (var_a2 << 0x10) >> 0xF) + &gTrackEdgeTable);
            var_a2 = (u16) temp_v0;
        } while (temp_v0 != 0);
        var_s5 = temp_s0_2;
        if (temp_s0_2 < 0x100) {
            temp_v0_6 = gSfxDecodeSize;
            gSfxDecodeSize = temp_v0_6 + 1;
            *((s16) temp_v0_6 + &gSfxDecodeBufData) = (s8) var_s5;
            gSfxDecodeSize &= 0xFFF;
        } else {
            var_s2_2 = (u32) gSfxDecodeBuf >> 0x18;
            if (gSfxCooldown < 8) {
                temp_s1 = 8 - gSfxCooldown;
                temp_s0_3 = gSfxDecodeDst;
                temp_s4 = ~(-1U >> temp_s1);
                if ((u32) temp_s0_3->unkC >= (u32) temp_s0_3->unk10) {
                    viSwapBuffers(temp_s0_3);
                }
                temp_v1_4 = temp_s0_3->unkC;
                temp_a0_3 = *((temp_s0_3->unk8 << 0xA) + temp_v1_4 + &gAudioDmaBuf);
                temp_s0_3->unkC = (s32) (temp_v1_4 + 4);
                temp_v1_5 = 0x20 - temp_s1;
                gSfxCooldown = temp_v1_5;
                var_s2_2 |= (u32) (temp_a0_3 & temp_s4) >> temp_v1_5;
                gSfxDecodeBuf = temp_a0_3 << temp_s1;
            } else {
                gSfxCooldown -= 8;
                gSfxDecodeBuf <<= 8;
            }
            var_s3 = var_s2_2;
            temp_v0_7 = *((var_s3 & 0xFFFF) + &gSfxDecodeTable) - 3;
            var_s2_3 = temp_v0_7;
            if ((temp_v0_7 & 0xFFFF) != 0xFFFF) {
                do {
                    var_a1_2 = var_s2_3 - 1;
                    if (gSfxCooldown == 0) {
                        temp_s0_4 = gSfxDecodeDst;
                        if ((u32) temp_s0_4->unkC >= (u32) temp_s0_4->unk10) {
                            viSwapBuffers(temp_s0_4);
                        }
                        temp_v1_6 = temp_s0_4->unkC;
                        temp_s0_4->unkC = (s32) (temp_v1_6 + 4);
                        gSfxCooldown = 0x20;
                        gSfxDecodeBuf = *((temp_s0_4->unk8 << 0xA) + temp_v1_6 + &gAudioDmaBuf);
                        var_a1_2 = var_s2_3 - 1;
                    }
                    var_s2_3 = var_a1_2;
                    var_s3 = ((u32) gSfxDecodeBuf >> 0x1F) | (var_s3 * 2);
                    gSfxDecodeBuf *= 2;
                    gSfxCooldown -= 1;
                } while ((var_a1_2 & 0xFFFF) != 0xFFFF);
            }
            gSfxDecodedCount = var_s5 - 0xFD;
            gSfxDecodeIdx = 0;
            gSfxDecodeReadOff = (~((var_s3 & 0x3F) | subroutine_arg5) + gSfxDecodeSize) & 0xFFF;
        }
    }
    if (gSfxDecodeIdx < gSfxDecodedCount) {
        var_s5 = (s16) *(((gSfxDecodeReadOff + gSfxDecodeIdx) & 0xFFF) + &gSfxDecodeBufData);
        temp_v0_8 = (s16) gSfxDecodeSize + &gSfxDecodeBufData;
        gSfxDecodeSize += 1;
        *temp_v0_8 = (s8) var_s5;
        gSfxDecodeSize &= 0xFFF;
        gSfxDecodeIdx = (u16) gSfxDecodeIdx + 1;
    }
    return var_s5;
}
