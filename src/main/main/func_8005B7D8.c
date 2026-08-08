#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of viRenderSync (initial). */

void audioSetupCopySample(Unk*, s32, s32);                       /* extern */
void audioInitDecodeTable();                                  /* extern */
extern s16 gSfxDecodeState;
extern s8 gSfxDecodePending;
extern char *gSfxDecodeDst;
extern s32 gSfxCooldown;
extern s16 gSfxDecodedCount;
extern s16 gSfxDecodeIdx;
extern s16 gSfxDecodeSize;
extern s32 gSfxDecodeBufData;
extern s32 gSfxDecodeDstBuf;

void audioSampleInit(s32 arg0) {
    s32 var_a0;
    s8 *var_v1;

    gSfxDecodeDst = &gSfxDecodeDstBuf;
    audioSetupCopySample(&gSfxDecodeDstBuf, arg0, -1);
    audioInitDecodeTable();
    var_a0 = 0xFC3;
    var_v1 = &gSfxDecodeBufData + 0xFC3;
    gSfxDecodeState = 0;
    gSfxDecodePending = 0;
    gSfxCooldown = 0;
    do {
        *var_v1 = 0;
        var_a0 -= 1;
        var_v1 -= 1;
    } while (var_a0 >= 0);
    gSfxDecodeSize = 0xFC4;
    gSfxDecodedCount = 0;
    gSfxDecodeIdx = 0;
}

s16 viRenderSync(void) {
    fmvDecodeFrame(0);
    return gSfxDecodedCount;
}
