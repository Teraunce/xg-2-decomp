#include "ultra64.h"
extern s32 D_80095288;
extern s32 D_A4500008;
extern s32 D_A4500010;
extern s32 D_A4500014;

s32 func_800866F4(void) {
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
    D_A4500010 = temp_a1 - 1;
    D_A4500014 = var_a2 - 1;
    D_A4500008 = 1;
    return (s32) D_80095288 / (s32) temp_a1;
}
