#include "ultra64.h"
#include "mtx.h"
void guMtxIdent(char *);                         /* extern */

void guScaleF(Matrix4x4 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    guMtxIdent((char *)arg0);
    arg0->unk0 = arg1;
    arg0->unk14 = arg2;
    arg0->unk3C = 1.0f;
    arg0->unk28 = arg3;
}

void guScale(void);  /* forward: GETTER_NOJR fallthrough */
void guScaleGetter(s32 arg1, s32 arg2, s32 arg3) {
    guScale();  /* GETTER_NOJR: mtc1 $a1/$a2/$a3 to $fa0/$fa1/$ft4, falls into guScale */
}
