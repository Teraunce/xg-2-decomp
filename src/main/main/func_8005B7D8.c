#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of viRenderSync (initial). */

void audioSetupCopySample(Unk*, s32, s32);                       /* extern */
void audioInitDecodeTable();                                  /* extern */
extern s16 D_8017DF3E;
extern s8 D_8017DF40;
extern char *D_8017DF44;
extern s32 D_8017DF4C;
extern s16 D_8017DF52;
extern s16 D_8017DF54;
extern s16 D_8017DF56;
extern s32 D_8017DF58;
extern s32 D_8017EF98;

void audioSampleInit(s32 arg0) {
    s32 var_a0;
    s8 *var_v1;

    D_8017DF44 = &D_8017EF98;
    audioSetupCopySample(&D_8017EF98, arg0, -1);
    audioInitDecodeTable();
    var_a0 = 0xFC3;
    var_v1 = &D_8017DF58 + 0xFC3;
    D_8017DF3E = 0;
    D_8017DF40 = 0;
    D_8017DF4C = 0;
    do {
        *var_v1 = 0;
        var_a0 -= 1;
        var_v1 -= 1;
    } while (var_a0 >= 0);
    D_8017DF56 = 0xFC4;
    D_8017DF52 = 0;
    D_8017DF54 = 0;
}

s16 viRenderSync(void) {
    fmvDecodeFrame(0);
    return D_8017DF52;
}
