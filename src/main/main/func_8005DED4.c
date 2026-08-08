#include "ultra64.h"
void sfxPlaySpatial(f32, f32, s32, s32, f32, s32);      /* extern */
extern f32 gSfxSpatialDefDist;

void sfxPlaySpatialDef(f32 arg4, f32 arg5, s32 arg6, s32 arg7) {
    sfxPlaySpatial(arg4, arg5, arg6, arg7, gSfxSpatialDefDist, 0x10000);
}
