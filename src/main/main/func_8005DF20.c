#include "ultra64.h"
s32 sfxQueueCmd(s16, f32, s32, s8, s32);           /* extern */
s32 sfxComputeSpatial(f32, f32, f32 *, s32 *, s32 *, s32 *, s32); /* extern */

void sfxPlaySpatial(f32 arg4, f32 arg5, s32 arg6, s32 arg7, f32 arg8, s32 arg9) {
    s32 sp34;
    s32 sp30;

    sp30 = 0x40;
    sp34 = 0;
    if (sfxComputeSpatial(arg4, arg5, &arg8, &arg9, &sp30, &sp34, arg7) != 0) {
        sfxQueueCmd(arg6, arg8, arg9, sp30, sp34);
    }
}
