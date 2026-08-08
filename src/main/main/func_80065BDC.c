#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of sfxGetVolLevel (initial). */

u16 renderCurveStrip(void**, Unk*, u32, s16, s32, u32);   /* extern */
s32 gfxAddPoint(s32, s32, s16, s16, s32);        /* extern */
s32 trackComputeLen(s32, s16, s16);                   /* extern */
extern s16 gTrackSegLen;
extern u16 gTextCurX;
extern s16 gTextCurY;
extern Unk gTextCharAdv;
extern s16 gTextClipH;
extern s16 gTextLayoutW;
extern u16 gTextLayoutX;
extern s16 gTextClipY;
extern u8 gTextAlignFlags;
extern s32 gTextVisible;
extern s32 gTextBaseX;

void rdpTextLayout(s32 arg0, u8 **arg1, s32 arg2) {
    s16 *var_v1_2;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_v1;
    s32 var_a0;
    s32 var_s2;
    s32 var_s4;
    s32 var_s4_2;
    s32 var_s4_3;
    s32 var_s6;
    s32 var_s7;
    s32 var_v0_3;
    u16 *var_v0_4;
    u16 var_v0;
    u16 var_v0_2;
    u32 temp_v0;
    u32 var_v1;
    u8 **var_s0;
    u8 **var_s0_2;
    u8 **var_v1_3;

    var_s6 = trackComputeLen(arg1, 0, gTrackSegLen);
    if ((u16) gTrackSegLen != 0) {
        if ((gTextCurY >= (gTextClipY + gTextClipH)) || (gTextCurY >= 0xFF)) {
            gTrackSegLen = 0;
            return;
        }
        if ((arg2 == 0) || (var_a0 = 0, ((gTextAlignFlags & 6) != 6))) {
            temp_v1 = gTextAlignFlags & 6;
            if (temp_v1 == 4) {
                gTextCurX = (gTextLayoutX + (u16) gTextLayoutW) - var_s6;
            } else if (temp_v1 == 0) {
                temp_v0 = gTextLayoutW - var_s6;
                gTextCurX = gTextLayoutX + ((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1);
            }
            var_s4 = 0;
            if ((u16) gTrackSegLen != 0) {
                var_s0 = arg1;
                do {
                    if (((Unk *)var_s0)->unk0 != 0) {
                        if ((gTextVisible != 0) && (gfxAddPoint(((Unk *)var_s0)->unk0, ((Unk *)var_s0)->unk8, (s16) gTextCurX, gTextCurY, ((Unk *)var_s0)->unkC) != 0)) {
                            if ((((Unk *)var_s0)->unk4 != 0) && (gfxAddPoint(((Unk *)var_s0)->unk4, ((Unk *)var_s0)->unk8, (s16) gTextCurX, gTextCurY, ((Unk *)var_s0)->unkC) == 0)) {
                                renderCurveStrip(arg0, ((Unk *)var_s0)->unk4, ((Unk *)var_s0)->unk8, (s16) gTextCurX, (s32) gTextCurY, ((Unk *)var_s0)->unkC);
                            }
                            var_v0 = gTextCurX;
                            var_v1 = (u32) (*(u8*)(s32)((Unk *)var_s0)->unk0 * ((Unk *)var_s0)->unk8) >> 0x10;
                            goto block_26;
                        }
                        temp_s1 = renderCurveStrip(arg0, ((Unk *)var_s0)->unk0, ((Unk *)var_s0)->unk8, (s16) gTextCurX, (s32) gTextCurY, ((Unk *)var_s0)->unkC) & 0xFFFF;
                        if (((Unk *)var_s0)->unk4 != 0) {
                            renderCurveStrip(arg0, ((Unk *)var_s0)->unk4, ((Unk *)var_s0)->unk8, (s16) gTextCurX, (s32) gTextCurY, ((Unk *)var_s0)->unkC);
                        }
                        var_v0_2 = gTextCurX + temp_s1;
                    } else {
                        var_v0_3 = gTextBaseX;
                        var_v1 = gTextCurX + 6;
                        if (var_v0_3 < 0) {
                            var_v0_3 += 3;
                        }
                        var_v0 = (u16) (var_v0_3 >> 2);
block_26:
                        var_v0_2 = var_v1 + var_v0;
                    }
                    gTextCurX = var_v0_2;
                    var_s0 += 0x10;
                    var_s4 += 1;
                    gTextCurX += gTextCharAdv.unk2;
                } while (var_s4 < (s32) (u16) gTrackSegLen);
            }
            var_v0_4 = (u16 *)0x80180000;
            if (gTextAlignFlags & 4) {
                var_v1_2 = (s16 *)0x80180000;
                goto block_55;
            }
        } else {
            var_s4_2 = 0;
            if ((u16) gTrackSegLen != 0) {
                var_v1_3 = arg1;
                do {
                    if (*var_v1_3 == NULL) {
                        var_a0 += 1;
                    }
                    var_s4_2 += 1;
                    var_v1_3 += 0x10;
                } while (var_s4_2 < (s32) (u16) gTrackSegLen);
            }
            if (var_a0 > 0) {
                var_s7 = (s32) ((s32) (gTextLayoutW - var_s6) / 4) / var_a0;
                var_s6 += var_s7 * var_a0;
            } else {
                var_s7 = 0;
            }
            var_s4_3 = 0;
            if ((u16) gTrackSegLen != 0) {
                var_s0_2 = arg1;
                do {
                    var_s2 = 0;
                    if ((u16) gTrackSegLen >= 2U) {
                        var_s2 = (s32) ((gTextLayoutW - var_s6) * var_s4_3) / (s32) ((u16) gTrackSegLen - 1);
                    }
                    if (((Unk *)var_s0_2)->unk0 != 0) {
                        if ((gTextVisible != 0) && (gfxAddPoint(((Unk *)var_s0_2)->unk0, ((Unk *)var_s0_2)->unk8, (s16) (gTextCurX + var_s2), gTextCurY, ((Unk *)var_s0_2)->unkC) != 0)) {
                            if ((((Unk *)var_s0_2)->unk4 != 0) && (gfxAddPoint(((Unk *)var_s0_2)->unk4, ((Unk *)var_s0_2)->unk8, (s16) (gTextCurX + var_s2), gTextCurY, ((Unk *)var_s0_2)->unkC) == 0)) {
                                renderCurveStrip(arg0, ((Unk *)var_s0_2)->unk4, ((Unk *)var_s0_2)->unk8, (s16) (gTextCurX + var_s2), (s32) gTextCurY, ((Unk *)var_s0_2)->unkC);
                            }
                            gTextCurX += (u32) (*(u8*)(s32)((Unk *)var_s0_2)->unk0 * ((Unk *)var_s0_2)->unk8) >> 0x10;
                        } else {
                            temp_s1_2 = renderCurveStrip(arg0, ((Unk *)var_s0_2)->unk0, ((Unk *)var_s0_2)->unk8, (s16) (gTextCurX + var_s2), (s32) gTextCurY, ((Unk *)var_s0_2)->unkC) & 0xFFFF;
                            if (((Unk *)var_s0_2)->unk4 != 0) {
                                renderCurveStrip(arg0, ((Unk *)var_s0_2)->unk4, ((Unk *)var_s0_2)->unk8, (s16) (gTextCurX + var_s2), (s32) gTextCurY, ((Unk *)var_s0_2)->unkC);
                            }
                            gTextCurX += temp_s1_2;
                        }
                    } else {
                        gTextCurX += ((s32) gTextBaseX / 4) + (var_s7 + 6);
                    }
                    var_s0_2 += 0x10;
                    var_s4_3 += 1;
                    gTextCurX += gTextCharAdv.unk2;
                } while (var_s4_3 < (s32) (u16) gTrackSegLen);
            }
            var_v0_4 = &gTextLayoutX;
            var_v1_2 = &gTextLayoutW;
block_55:
            gTextCurX = *var_v0_4 + (u16) *var_v1_2;
        }
        gTrackSegLen = 0;
    }
}

u8 sfxGetVolLevel(void) {
    return gTextAlignFlags;
}
