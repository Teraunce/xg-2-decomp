#include "ultra64.h"
#include "mtx.h"
void guMtxIdent(char *);                         /* extern */

void mtxIdentSetPos(Matrix4x4 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    guMtxIdent((char *)arg0);
    arg0->unk30 = arg1;
    arg0->unk34 = arg2;
    arg0->unk38 = arg3;
}
