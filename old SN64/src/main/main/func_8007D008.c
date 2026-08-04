#include "ultra64.h"
s32 func_8007C484(void **);                           /* extern */
s32 func_8007C584(s32, void *);                       /* extern */
s32 func_8007C768();                                /* extern */
s32 func_8007C788(s32);                               /* extern */
void func_8007D238(Unk *);                            /* extern */
extern Unk *D_800952A8;
extern Unk *D_800952B0;

void func_8007D008(Unk *arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = func_8007C768();
    if (arg0 == NULL) {
        arg0 = D_800952B0;
    }
    if (arg0->unk4 != arg1) {
        arg0->unk4 = arg1;
        if ((arg0 != D_800952B0) && (arg0->unk10 != 1)) {
            func_8007D238(arg0->unk8);
            func_8007C584(arg0->unk8, arg0);
        }
        if (D_800952B0->unk4 < D_800952A8->unk4) {
            D_800952B0->unk10 = 2;
            func_8007C484(&D_800952A8);
        }
    }
    func_8007C788(temp_s0);
}
