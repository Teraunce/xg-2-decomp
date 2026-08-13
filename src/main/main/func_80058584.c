#include "ultra64.h"
#include "mtx.h"
s32 vec3Normalize(f32 *, f32 *, f32 *);               /* extern */
void vec3Cross(Unk*, Unk*, Unk*);               /* extern */
extern f32 gGeomParamI;

void mtxSetFromVectorsNeg(Matrix4x4 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp58;
    f32 sp54;
    f32 sp50;

    sp70 = -arg1;
    sp60 = -arg4;
    sp64 = -arg5;
    sp68 = -arg6;
    sp74 = -arg2;
    sp78 = -arg3;
    vec3Cross(&sp70, &sp60, &sp50);
    vec3Cross(&sp70, &sp50, &sp60);
    vec3Normalize(&sp50, &sp54, &sp58);
    vec3Normalize(&sp60, &sp64, &sp68);
    vec3Normalize(&sp70, &sp74, &sp78);
    arg0->unk0 = sp50;
    arg0->unk10 = sp54;
    arg0->unk30 = 0;
    arg0->unk20 = sp58;
    arg0->unk4 = sp60;
    arg0->unk14 = sp64;
    arg0->unk34 = 0;
    arg0->unk24 = sp68;
    arg0->unk8 = sp70;
    arg0->unk18 = sp74;
    arg0->unk38 = 0;
    arg0->unkC = 0;
    arg0->unk1C = 0;
    arg0->unk2C = 0;
    arg0->unk3C = (f32) gGeomParamI;
    arg0->unk28 = sp78;
}
