#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of geomNodeDispatchGetter (initial). */

void audioGeomNodeInit(Unk*, Unk*, void*);                         /* extern */
s32 audioNoteWrite(Unk*, s32, s32);                       /* extern */
s32 audioNodeSetValue(s32*, s32, s32);                       /* extern */
extern f32 gAudioRateD;
extern f32 gAudioRateC;
extern s32 gAiClock;

s32 audioVoiceGeomInit(Unk *arg0, s16 arg1, s32 arg2, s32 arg3) {
    s32 temp_a2;
    s32 temp_s1;

    temp_s1 = arg1 * 0x4C;
    audioGeomNodeInit(arg0->unk34 + temp_s1 + 0x20, arg2, arg3);
    temp_a2 = arg0->unk34 + temp_s1;
    audioNodeSetValue(temp_a2 + 0x20, 1, temp_a2);
    audioNoteWrite(arg0->unk30, 2, arg0->unk34 + temp_s1 + 0x20);
    return arg0->unk34 + temp_s1 + 0x20;
}

f32 audioSemitoneRatio(s32 arg0) {
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_t7;
    s32 var_a0;

    var_a0 = arg0;
    var_fv1 = 1.0f;
    if (var_a0 >= 0) {
        var_fv0 = gAudioRateD;
    } else {
        var_fv0 = gAudioRateC;
        var_a0 = -var_a0;
    }
    if (var_a0 != 0) {
        do {
            temp_t7 = var_a0 >> 1;
            if (var_a0 & 1) {
                var_fv1 *= var_fv0;
            }
            var_fv0 *= var_fv0;
            var_a0 = temp_t7;
        } while (temp_t7 != 0);
    }
    return var_fv1;
}

void geomNodeDispatchGetter(Unk *arg0, Unk *arg1, void *arg2) {
    audioGeomNodeInit(arg0, arg1, arg2);  /* GETTER_NOJR: preloads D_80095288→$t6 and (f32)arg0→$ft2, falls through */
}
