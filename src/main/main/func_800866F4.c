#include "ultra64.h"
extern s32 gAiClock;
extern s32 AI_CONTROL;
extern s32 AI_DACRATE;
extern s32 AI_BITRATE;

s32 osAiSetFrequency(void) {
    s32 var_a2;
    u32 temp_a1;

    /* arg_t6: implicit integer in $t6 from caller; arg_f8: implicit integer in $ft2/$f8 from caller */
    temp_a1 = (u32) (((f32) 0 /* arg_t6 */ / (f32) 0 /* arg_f8 */) + 0.5f);
    if (temp_a1 < 0x84U) {
        return -1;
    }
    var_a2 = (temp_a1 / 66U) & 0xFF;
    if (var_a2 >= 0x11) {
        var_a2 = 0x10;
    }
    AI_DACRATE = temp_a1 - 1;
    AI_BITRATE = var_a2 - 1;
    AI_CONTROL = 1;
    return (s32) gAiClock / (s32) temp_a1;
}
