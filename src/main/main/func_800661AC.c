#include "ultra64.h"
s32 trackComputeLen(s32, s16, s16);                     /* extern */
void rdpTextLayout(s32, u8**, s32);                       /* extern */
extern s16 gTrackSegLen;
extern u16 gTextCurX;
extern s16 gTextCurY;
extern Unk gGlyphSize;
extern s16 gTextLayoutW;
extern u16 gTextLayoutX;

void rdpTrackLayout(s32 arg0, s32 arg1) {
    s16 var_s0;
    s16 var_s0_2;
    s16 var_v0;
    s32 *var_v1;
    u16 var_s1;
    Unk *temp_v0;
    Unk *var_a0;

    if ((s32)0 /* implicit $v0 from caller */ & 1) {
loop_2:
        if (gTextLayoutW < trackComputeLen(arg1, 0, gTrackSegLen)) {
            var_s0 = (u16) gTrackSegLen - 1;
            if (var_s0 >= 0) {
                var_v1 = (var_s0 * 0x10) + arg1;
loop_5:
                if (*var_v1 != 0) {
                    var_s0 -= 1;
                    var_v1 -= 0x10;
                    if (var_s0 >= 0) {
                        goto loop_5;
                    }
                }
                if (var_s0 >= 0) {
                    if (trackComputeLen(arg1, 0, var_s0) < ((s16) (u16) gTextLayoutW / 2)) {
                        var_s0_2 = (u16) gTrackSegLen - 1;
                        if (var_s0_2 > 0) {
loop_10:
                            if (gTextLayoutW < trackComputeLen(arg1, 0, var_s0_2)) {
                                var_s0_2 -= 1;
                                if (var_s0_2 <= 0) {

                                } else {
                                    goto loop_10;
                                }
                            }
                        }
                        goto block_17;
                    }
                    var_s1 = (u16) gTrackSegLen;
                    gTrackSegLen = var_s0;
                    var_s0_2 = var_s0 + 1;
                } else {
                    goto block_14;
                }
            } else {
block_14:
                var_s0_2 = (u16) gTrackSegLen - 1;
                if (var_s0_2 > 0) {
loop_15:
                    if (gTextLayoutW < trackComputeLen(arg1, 0, var_s0_2)) {
                        var_s0_2 -= 1;
                        if (var_s0_2 > 0) {
                            goto loop_15;
                        }
                    }
                }
block_17:
                var_s1 = (u16) gTrackSegLen;
                gTrackSegLen = var_s0_2;
            }
            rdpTextLayout(arg0, arg1, 1);
            gTextCurX = gTextLayoutX;
            if ((gTextCurY + gGlyphSize.unk0) >= 0x100) {
                var_v0 = 0xFF;
            } else {
                var_v0 = (u16) gTextCurY + gGlyphSize.unk2;
            }
            gTextCurY = var_v0;
            if (var_s0_2 < (s32) var_s1) {
                var_a0 = (var_s0_2 * 0x10) + arg1;
                do {
                    var_s0_2 += 1;
                    temp_v0 = (((u16) gTrackSegLen & 0xFFFF) * 0x10) + arg1;
                    temp_v0->unk0 = (s32) var_a0->unk0;
                    temp_v0->unk4 = (s32) var_a0->unk4;
                    temp_v0->unk8 = (s32) var_a0->unk8;
                    temp_v0->unkC = (s32) var_a0->unkC;
                    var_a0 += 0x10;
                    gTrackSegLen = (u16) gTrackSegLen + 1;
                } while (var_s0_2 < (s32) var_s1);
            }
            goto loop_2;
        }
    }
}
