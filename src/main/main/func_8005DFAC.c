#include "ultra64.h"
void sfxComputeSpatial(f32, f32, s32, s32, f32, f32, s32, s32, s32, s32, s32); /* extern */

void sfxEntitySpatial(Unk *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    sfxComputeSpatial(arg0->unk0, arg0->unk4, arg0->unk8, arg0->unk398, arg0->unk39C, arg0->unk3A0, arg1, arg2, arg3, arg4, arg0->unk568);
}
