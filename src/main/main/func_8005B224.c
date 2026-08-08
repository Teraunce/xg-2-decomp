#include "ultra64.h"
void audioSetupCopySample(Unk*, s32, s32);                       /* extern */
void viSwapBuffers(Unk*);                            /* extern */
s32 audioGetRspCount();                                  /* extern */
void audioInitDecodeTable();                                  /* extern */
void audioInitFreqTable();                                  /* extern */
extern s32 gAudioSampleTable;
extern s32 gSfxDecodeTable;
extern Unk gTrackEdgeData;
extern s32 gTrackEdgeTable;
extern Unk gAudioStreamBuf;
extern s16 gSfxDecodeState;
extern s8 gSfxDecodePending;
extern char *gSfxDecodeDst;
extern u32 gSfxDecodeBuf;
extern s32 gSfxCooldown;
extern s32 gAudioDmaBuf;

void audioDecodeHufh(s32 arg0, u8 *arg1, u32 arg2) {
    u32 *sp1070;
    s32 sp106C;
    s32 sp1068;
    s32 sp1050;
    s32 sp10;
    Unk *temp_s0;
    Unk *temp_s0_3;
    Unk *temp_s0_4;
    s16 *var_a1_2;
    s16 temp_s0_2;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_7;
    s16 temp_v0_8;
    s16 temp_v1_5;
    s32 var_a1;
    s16 var_a1_3;
    s16 var_v1;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a1;
    s32 temp_a3;
    s32 temp_a3_3;
    s32 temp_s1;
    s32 temp_s4;
    s32 temp_s4_2;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 temp_v1_10;
    s32 temp_v1_7;
    s32 temp_v1_8;
    s32 temp_v1_9;
    s32 var_a0;
    s32 var_a2_2;
    s32 var_a3;
    s32 var_s1_2;
    s32 var_s5;
    s32 var_v0;
    u16 *temp_v0_3;
    u16 *temp_v0_6;
    u16 *temp_v1_4;
    u16 temp_a3_2;
    u16 temp_t0;
    u16 temp_v1_3;
    u16 var_a2;
    u16 var_s1;
    u32 *var_t4;
    u32 temp_a0;
    u32 temp_v1_11;
    u32 temp_v1_2;
    u32 var_s2;
    u32 var_s6;
    u8 *temp_v1_12;
    u8 *var_fp;
    u8 temp_s3;
    Unk *temp_v1_6;

    Unk *sp = 0;
    var_fp = arg1;
    gSfxDecodeDst = &sp1050;
    audioSetupCopySample(&sp1050, arg0, -1);
    audioInitDecodeTable();
    var_v1 = 0;
    gSfxDecodeState = 0;
    gSfxDecodePending = 0;
    gSfxCooldown = 0;
    var_v0 = 0 << 0x10;
    do {
        *(&sp10 + (var_v0 >> 0x10)) = 0;
        temp_v0 = var_v1 + 1;
        var_v1 = temp_v0;
        var_v0 = var_v1 << 0x10;
    } while (temp_v0 < 0xFC4);
    var_s5 = 0xFC4;
    var_s6 = 0;
    if (arg2 != 0) {
        var_t4 = &gSfxDecodeBuf;
loop_4:
        var_s1 = gAudioStreamBuf.unk4E4;
        if (var_s1 < 0x273U) {
            do {
                if (gSfxCooldown == 0) {
                    temp_s0 = gSfxDecodeDst;
                    if ((u32) temp_s0->unkC >= (u32) temp_s0->unk10) {
                        sp1070 = var_t4;
                        viSwapBuffers(temp_s0);
                    }
                    temp_v1 = temp_s0->unkC;
                    temp_s0->unkC = (s32) (temp_v1 + 4);
                    gSfxCooldown = 0x20;
                    *var_t4 = *((temp_s0->unk8 << 0xA) + temp_v1 + &gAudioDmaBuf);
                }
                temp_v1_2 = *var_t4;
                var_s1 = *(u16*)((char*)&gAudioStreamBuf + (((var_s1 + (temp_v1_2 >> 0x1F)) & 0xFFFF) * 2));
                *var_t4 = temp_v1_2 * 2;
                gSfxCooldown -= 1;
            } while (var_s1 < 0x273U);
        }
        temp_s0_2 = var_s1 - 0x273;
        if (gTrackEdgeData.unk4E4 == 0x8000) {
            sp1070 = var_t4;
            audioInitFreqTable();
        }
        var_a2 = ((Unk*)((char*)&gTrackEdgeTable + ((s32)(temp_s0_2 << 0x10) >> 0xF)))->unk4E6;
        do {
            temp_v0_3 = (u16*)((char*)&gTrackEdgeData + ((s32)(var_a2 << 0x10) >> 0xF));
            temp_v1_3 = *temp_v0_3 + 1;
            *temp_v0_3 = temp_v1_3;
            var_a1 = (s16) temp_v1_3;
            temp_v0_4 = var_a2 + 2;
            if ((s32) *(u16*)((char*)&gTrackEdgeData + ((s32)((var_a2 + 1) << 0x10) >> 0xF)) < var_a1) {
                var_a0 = temp_v0_4;
                if ((s32) *(u16*)((char*)&gTrackEdgeData + ((s32)(temp_v0_4 << 0x10) >> 0xF)) < var_a1) {
                    do {
                        temp_v0_5 = var_a0 + 1;
                        var_a0 = temp_v0_5;
                    } while ((s32) *(u16*)((char*)&gTrackEdgeData + ((s32)(temp_v0_5 << 0x10) >> 0xF)) < var_a1);
                }
                temp_t0 = var_a0 - 1;
                temp_a1 = (s32) (var_a2 << 0x10) >> 0xF;
                temp_a3 = (s32) (temp_t0 << 0x10) >> 0xF;
                temp_v1_4 = (u16*)((char*)&gTrackEdgeData + temp_a3);
                var_a1 = (s32)((char*)&gAudioStreamBuf + temp_a1);
                *(u16*)((char*)&gTrackEdgeData + temp_a1) = *temp_v1_4;
                *temp_v1_4 = temp_v1_3;
                temp_v1_5 = *(u16*)(s32)var_a1;
                *((temp_v1_5 * 2) + &gTrackEdgeTable) = temp_t0;
                if (temp_v1_5 < 0x273) {
                    *(((temp_v1_5 + 1) * 2) + &gTrackEdgeTable) = temp_t0;
                }
                temp_v0_6 = (u16*)((char*)&gAudioStreamBuf + temp_a3);
                temp_a3_2 = *temp_v0_6;
                *temp_v0_6 = (u16) *(u16*)(s32)var_a1;
                *(((s16) temp_a3_2 * 2) + &gTrackEdgeTable) = var_a2;
                if ((s16) temp_a3_2 < 0x273) {
                    *((((s16) temp_a3_2 + 1) * 2) + &gTrackEdgeTable) = var_a2;
                }
                *(u16*)(s32)var_a1 = (u16) temp_a3_2;
                var_a2 = temp_t0;
            }
            temp_v0_2 = *(((s32) (var_a2 << 0x10) >> 0xF) + &gTrackEdgeTable);
            var_a2 = (u16) temp_v0_2;
        } while (temp_v0_2 != 0);
        if (temp_s0_2 < 0x100) {
            *var_fp = (u8) temp_s0_2;
            var_fp += 1;
            temp_v1_6 = var_s5 + sp;
            var_s5 = (var_s5 + 1) & 0xFFF;
            var_s6 += 1;
            temp_v1_6->unk10 = (s8) temp_s0_2;
            goto block_41;
        }
        temp_a0 = *var_t4;
        var_s2 = temp_a0 >> 0x18;
        if (gSfxCooldown < 8) {
            temp_s1 = 8 - gSfxCooldown;
            temp_s0_3 = gSfxDecodeDst;
            temp_s4 = ~(-1U >> temp_s1);
            if ((u32) temp_s0_3->unkC >= (u32) temp_s0_3->unk10) {
                sp1070 = var_t4;
                viSwapBuffers(temp_s0_3);
            }
            temp_v1_7 = temp_s0_3->unkC;
            temp_a0_2 = *((temp_s0_3->unk8 << 0xA) + temp_v1_7 + &gAudioDmaBuf);
            temp_s0_3->unkC = (s32) (temp_v1_7 + 4);
            temp_v1_8 = 0x20 - temp_s1;
            gSfxCooldown = temp_v1_8;
            var_s2 |= (u32) (temp_a0_2 & temp_s4) >> temp_v1_8;
            *var_t4 = temp_a0_2 << temp_s1;
        } else {
            gSfxCooldown -= 8;
            *var_t4 = temp_a0 << 8;
        }
        temp_a0_3 = var_s2 & 0xFFFF;
        temp_s4_2 = *(temp_a0_3 + &gAudioSampleTable) << 6;
        temp_v1_9 = *(temp_a0_3 + &gSfxDecodeTable) - 3;
        var_s1_2 = temp_v1_9;
        if ((temp_v1_9 & 0xFFFF) != 0xFFFF) {
            var_a3 = 0x20;
            var_a2_2 = 0xFFFF;
            do {
                var_a1_2 = var_s1_2 - 1;
                if (gSfxCooldown == 0) {
                    temp_s0_4 = gSfxDecodeDst;
                    if ((u32) temp_s0_4->unkC >= (u32) temp_s0_4->unk10) {
                        sp1068 = var_a2_2;
                        sp106C = var_a3;
                        sp1070 = var_t4;
                        viSwapBuffers(temp_s0_4);
                    }
                    temp_v1_10 = temp_s0_4->unkC;
                    temp_s0_4->unkC = (s32) (temp_v1_10 + 4);
                    gSfxCooldown = var_a3;
                    *var_t4 = *((temp_s0_4->unk8 << 0xA) + temp_v1_10 + &gAudioDmaBuf);
                    var_a1_2 = var_s1_2 - 1;
                }
                var_s1_2 = (s32) var_a1_2;
                temp_v1_11 = *var_t4;
                var_s2 = (temp_v1_11 >> 0x1F) | (var_s2 * 2);
                *var_t4 = temp_v1_11 * 2;
                gSfxCooldown -= 1;
            } while (((s32) var_a1_2 & 0xFFFF) != var_a2_2);
        }
        temp_v0_7 = temp_s0_2 - 0xFD;
        var_a1_3 = 0;
        if (temp_v0_7 > 0) {
            temp_a3_3 = (~((var_s2 & 0x3F) | temp_s4_2) + var_s5) & 0xFFF;
loop_39:
            if (var_s6 < arg2) {
                temp_v1_12 = var_s5 + &sp10;
                var_s5 = (var_s5 + 1) & 0xFFF;
                var_s6 += 1;
                temp_s3 = *(&sp10 + ((temp_a3_3 + var_a1_3) & 0xFFF));
                temp_v0_8 = var_a1_3 + 1;
                var_a1_3 = temp_v0_8;
                *var_fp = temp_s3;
                var_fp += 1;
                *temp_v1_12 = temp_s3;
                if (temp_v0_8 >= temp_v0_7) {
                    goto block_41;
                }
                goto loop_39;
            }
        } else {
block_41:
            if (var_s6 < arg2) {
                goto loop_4;
            }
        }
    }
    audioGetRspCount();
}
