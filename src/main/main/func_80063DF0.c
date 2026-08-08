#include "ultra64.h"
s32 sfxFreeBlock(s32);                               /* extern */
extern s32 gFontRange;
extern s32 gFontTable;
extern s32 gTextVertBuf;
extern s32 gTextGlyphCoords;
extern s32 gTrackColorKey;
extern s32 gSfxPitchVal;
extern s32 gSfxFilterVal;
extern s32 gTextCharAdv;
extern s32 gGlyphSize;
extern u32 gTextIndent;
extern s32 gTextVisible;
extern u32 gTextBaseX;

void sfxBufAlloc(void) {
    gTextVertBuf = sfxFreeBlock(0x1800);
    gTextGlyphCoords = sfxFreeBlock(0x300);
}

void sfxFrameBegin(void) {

}

void sfxSetPitch(s32 arg0) {
    gSfxPitchVal = arg0 & 0xFF;
    gFontRange = 0;
    gFontTable = 0;
}

void sfxSetFreq(s32 arg0) {
    s32 temp_v1;
    u32 temp_a0;
    u32 temp_a0_2;
    u32 temp_v0;

    temp_a0 = arg0 & 0xFF;
    gTextBaseX = temp_a0;
    temp_a0_2 = temp_a0 >> 3;
    gTextCharAdv = -2;
    temp_v1 = temp_a0_2 < 4U;
    if (temp_v1 != 0) {
        if ((s32) temp_a0_2 >= 2) {
            if (temp_v1 != 0) {
                gTextIndent = temp_a0_2;
            } else {
                goto block_5;
            }
        } else {
            gTextIndent = 1;
        }
    } else {
block_5:
        gTextIndent = 3;
    }
    temp_v0 = arg0 & 0xFF;
    gGlyphSize = temp_v0 + (temp_v0 >> 1);
    gFontRange = 0;
    gFontTable = 0;
}

void func_80063ED0(s8 arg0) {
    gTextCharAdv = (s32) arg0;
}

void func_80063EE4(s32 arg0) {
    gGlyphSize = arg0 & 0xFF;
}

void sfxSetFilter(s32 arg0) {
    gSfxFilterVal = arg0 | 0xFF000000;
    gTrackColorKey = 0xFF00FF;
}

void sfxSetState(s32 arg0) {
    gTextVisible = arg0;
}

s32 sfxComputeFreqOffset(Unk *arg0) {
    s32 var_a0;
    s32 var_a0_2;
    u8 temp_a1;

    temp_a1 = arg0->unk1;
    if ((s32) temp_a1 < (s32) gTextBaseX) {
        var_a0_2 = (gTextBaseX - temp_a1) * 2;
        if (arg0->unk0 != gSfxPitchVal) {
            var_a0_2 += 0x100;
        }
        return var_a0_2;
    }
    var_a0 = temp_a1 - gTextBaseX;
    if (arg0->unk0 != gSfxPitchVal) {
        var_a0 += 0x100;
    }
    return var_a0;
}
