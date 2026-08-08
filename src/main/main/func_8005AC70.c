#include "ultra64.h"
void audioSetupCopySample(Unk*, s32, s32);                       /* extern */
void viSwapBuffers(Unk*);                               /* extern */
s32 audioGetRspCount();                                  /* extern */
extern s32 gTrackEdgeData;
extern s16 gSfxStreamEnd;
extern s32 gTrackEdgeTable;
extern s16 gSfxStreamPos;
extern s32 gAudioStreamBuf;
extern s32 gAudioDmaBuf;

void audioDecodeLZSS(s32 arg0, u8 *arg1, s32 arg2, s32 arg3) {
    u32 sp1038;
    s32 sp1030;
    u32 sp1034;
    s32 sp1028;
    s8 spFFD;
    s32 sp10;
    s32 temp_a0_2;
    s32 temp_s1;
    s32 var_a1;
    s32 var_s0;
    s32 var_s3;
    s32 var_s4;
    s32 var_v0_2;
    s32 var_v1;
    s8 *var_v0;
    u32 temp_v1;
    u8 *temp_v0_4;
    u8 *var_a0;
    u8 *var_s2;
    u8 temp_a0;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v1_2;

    var_s2 = arg1;
    audioSetupCopySample(&sp1028, arg0, arg3);
    var_v1 = 0xFED;
    var_v0 = &spFFD;
    do {
        *var_v0 = 0;
        var_v1 -= 1;
        var_v0 -= 1;
    } while (var_v1 >= 0);
    var_s0 = 0xFEE;
    var_s3 = 0;
    if (arg2 > 0) {
        var_s4 = 0 >> 1;
        do {
            var_v0_2 = var_s4 & 1;
            if (!(var_s4 & 0x100)) {
                if (sp1034 >= sp1038) {
                    viSwapBuffers(&sp1028);
                }
                temp_v0 = *(sp1034 + (sp1030 << 0xA) + &gAudioDmaBuf);
                sp1034 += 1;
                var_s4 = temp_v0 | 0xFF00;
                var_v0_2 = var_s4 & 1;
            }
            if (var_v0_2 != 0) {
                var_a0 = &sp10 + var_s0;
                if (sp1034 >= sp1038) {
                    viSwapBuffers(&sp1028);
                    var_a0 = &sp10 + var_s0;
                }
                var_s0 = (var_s0 + 1) & 0xFFF;
                var_s3 += 1;
                temp_v0_2 = *(sp1034 + (sp1030 << 0xA) + &gAudioDmaBuf);
                sp1034 += 1;
                *var_a0 = temp_v0_2;
                *var_s2 = temp_v0_2;
                var_s2 += 1;
            } else {
                if (sp1034 >= sp1038) {
                    viSwapBuffers(&sp1028);
                }
                temp_a0 = *(sp1034 + (sp1030 << 0xA) + &gAudioDmaBuf);
                temp_v1 = sp1034 + 1;
                sp1034 = temp_v1;
                if (temp_v1 >= sp1038) {
                    viSwapBuffers(&sp1028);
                }
                var_a1 = 0;
                temp_v0_3 = *(sp1034 + (sp1030 << 0xA) + &gAudioDmaBuf);
                temp_s1 = temp_a0 | ((temp_v0_3 & 0xF0) * 0x10);
                temp_a0_2 = (temp_v0_3 & 0xF) + 2;
                sp1034 += 1;
                if (temp_a0_2 >= 0) {
                    do {
                        temp_v0_4 = &sp10 + var_s0;
                        var_s0 = (var_s0 + 1) & 0xFFF;
                        var_s3 += 1;
                        temp_v1_2 = *(&sp10 + ((temp_s1 + var_a1) & 0xFFF));
                        var_a1 += 1;
                        *temp_v0_4 = temp_v1_2;
                        *var_s2 = temp_v1_2;
                        var_s2 += 1;
                    } while (temp_a0_2 >= var_a1);
                }
            }
            var_s4 = var_s4 >> 1;
        } while (var_s3 < arg2);
    }
    audioGetRspCount();
}

void audioInitDecodeTable(void) {
    s16 temp_v0;
    s16 temp_v0_3;
    s16 var_t0;
    s16 var_t0_2;
    s16 var_t1;
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_v0_2;
    s32 temp_v0_4;
    s32 var_v0;

    var_t0 = 0;
    var_v0 = 0 << 0x10;
    do {
        temp_v0_2 = var_v0 >> 0x10;
        temp_a0 = temp_v0_2 * 2;
        *(temp_a0 + &gTrackEdgeData) = 1;
        *(temp_a0 + &gAudioStreamBuf) = var_t0 + 0x273;
        *(((temp_v0_2 + 0x273) * 2) + &gTrackEdgeTable) = var_t0;
        temp_v0 = var_t0 + 1;
        var_t0 = temp_v0;
        var_v0 = var_t0 << 0x10;
    } while (temp_v0 < 0x13A);
    var_t0_2 = 0;
    var_t1 = 0x13A;
    do {
        temp_a2 = (s32) (var_t1 << 0x10) >> 0xF;
        temp_a3 = var_t0_2 * 2;
        temp_v0_4 = (var_t0_2 + 1) * 2;
        *(temp_a2 + &gTrackEdgeData) = *(temp_a3 + &gTrackEdgeData) + *(temp_v0_4 + &gTrackEdgeData);
        *(temp_a2 + &gAudioStreamBuf) = var_t0_2;
        *(temp_v0_4 + &gTrackEdgeTable) = var_t1;
        temp_v0_3 = var_t1 + 1;
        *(temp_a3 + &gTrackEdgeTable) = var_t1;
        var_t1 = temp_v0_3;
        var_t0_2 += 2;
    } while (temp_v0_3 < 0x273);
    gSfxStreamEnd = 0xFFFF;
    gSfxStreamPos = 0;
}
