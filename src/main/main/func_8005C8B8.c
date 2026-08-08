#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of audioQueueDispatchGetter (initial). */

void audioSetCallback(s32);                                 /* extern */
extern s32 gAudioStatus;
extern s32 D_80092804;
extern s32 D_80092818;
extern s32 D_8009281C;
extern s32 D_80092824;

void audioResetCallback(void) {
    audioSetCallback(-1);
}

void audioSetTrack(s32 arg0) {
    D_80092804 = arg0;
    D_80092824 = 1;
}

void audioSetRates(s32 arg0, s32 arg1) {
    s32 temp_a0;
    s32 temp_a2;
    s32 var_a0;
    s32 var_a1;
    s32 var_v0;
    s32 var_v0_2;

    var_a0 = arg0;
    var_a1 = arg1;
    D_80092818 = 0x10000;
    temp_a2 = var_a0 > 0x10000;
    var_v0 = var_a0;
    if (temp_a2 != 0) {
        var_v0 = 0x10000;
    }
    if (var_v0 >= 2) {
        if (temp_a2 != 0) {
            var_a0 = 0x10000;
        }
        D_80092818 = 0x10000 / var_a0;
    }
    D_8009281C = 0x10000;
    temp_a0 = var_a1 > 0x10000;
    var_v0_2 = var_a1;
    if (temp_a0 != 0) {
        var_v0_2 = 0x10000;
    }
    if (var_v0_2 >= 2) {
        if (temp_a0 != 0) {
            var_a1 = 0x10000;
        }
        D_8009281C = 0x10000 / var_a1;
    }
}

void audioQueueDispatch(void);  /* forward: GETTER_NOJR fallthrough */
void audioQueueDispatchGetter(void) {
    audioQueueDispatch();
}
