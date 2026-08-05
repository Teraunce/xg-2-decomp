#include "ultra64.h"
void sfxPlaySpatial(f32, f32, s32, s32, f32, s32);       /* extern */

void func_8005E04C(Unk *arg0, s32 arg1, s32 arg2, s32 arg3) {
    sfxPlaySpatial(arg0->unk39C, arg0->unk3A0, arg1, arg0->unk568, arg2, arg3);
}
