#include "ultra64.h"
void sfxPlaySpatialDef(f32, f32, s32, s32);                 /* extern */

void sfxEntityPlayDef(Unk *arg0, s32 arg1) {
    sfxPlaySpatialDef(arg0->unk39C, arg0->unk3A0, arg1, arg0->unk568);
}
