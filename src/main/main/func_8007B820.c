#include "ultra64.h"
void guMtxF2L(char*, char*);                          /* extern */
void guMtxIdent(char*);                               /* extern */
extern f32 gEulerScaleConst;

void guTranslateF(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    s32 sp28[16];

    guMtxIdent(&sp28);
    sp58 = arg1;
    sp5C = arg2;
    sp60 = arg3;
    guMtxF2L(&sp28, arg0);
}

void mtxEulerScaleF(void);  /* forward: GETTER_NOJR fallthrough */
void mtxEulerScaleFGetter(f32 arg1, s32 arg2, s32 arg3) {
    mtxEulerScaleF();  /* GETTER_NOJR: loads gEulerScaleConst into $fv0, scales $fa0, falls into mtxEulerScaleF */
}
