#include "ultra64.h"
u8 *fontGetCharWidth(u16, s32 *, s32);                   /* extern */
extern Unk gTextCharAdv;
extern s32 gTextBaseX;

s32 fontStringWidth(u16 *arg0) {
    s32 sp10;
    s32 temp_s0;
    s32 var_s0;
    s32 var_v0;
    u16 *var_s1;
    u32 var_v0_2;
    u8 *temp_v0;

    var_s1 = arg0;
    var_s0 = 0;
    if (*var_s1 != 0) {
loop_2:
        temp_v0 = fontGetCharWidth(*var_s1, &sp10, 0);
        if (temp_v0 != NULL) {
            var_v0_2 = (u32) (*temp_v0 * sp10) >> 0x10;
        } else {
            var_v0_2 = ((s32) gTextBaseX / 4) + 6;
        }
        temp_s0 = var_s0 + var_v0_2;
        var_s1 += 2;
        var_v0 = temp_s0 & 0xFFFF;
        if (*var_s1 != 0) {
            var_s0 = temp_s0 + gTextCharAdv.unk2;
            goto loop_2;
        }
    } else {
        var_v0 = 0 & 0xFFFF;
    }
    return var_v0;
}

void copyU16Array(u16 *arg0, u16 *arg1) {
    u16 *var_a0;
    u16 *var_a1;
    u16 var_v0;

    var_a0 = arg0;
    var_a1 = arg1;
    if (var_a1 != NULL) {
        var_v0 = *var_a1;
        if (var_v0 != 0) {
            do {
                var_a1 += 2;
                *var_a0 = var_v0;
                var_v0 = *var_a1;
                var_a0 += 2;
            } while (var_v0 != 0);
        }
    }
    *var_a0 = 0;
}
