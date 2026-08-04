#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8007D238 (initial). */

s32 func_8007C484(void **);                           /* extern */
s32 func_8007C584(void **, void *);                   /* extern */
char *func_8007C5CC(void **);                       /* extern */
s32 func_8007C5DC();                                  /* extern */
s32 func_8007C768();                                /* extern */
s32 func_8007C788(s32);                               /* extern */
extern Unk *D_800952A8;
extern Unk *D_800952B0;

void func_8007D0E8(Unk *arg0) {
    s32 temp_s0;
    u16 temp_s1;
    void **temp_t0;

    temp_s0 = func_8007C768();
    temp_s1 = arg0->unk10;
    if (temp_s1 != 1) {
        if (temp_s1 == 8) {
            arg0->unk10 = 2U;
            func_8007C584(&D_800952A8, arg0);
        }
    } else {
        temp_t0 = arg0->unk8;
        if ((temp_t0 == NULL) || ((void*)temp_t0 == (void*)&D_800952A8)) {
            arg0->unk10 = 2U;
            func_8007C584(&D_800952A8, arg0);
        } else {
            arg0->unk10 = 8U;
            func_8007C584(arg0->unk8, arg0);
            func_8007C584(&D_800952A8, func_8007C5CC(arg0->unk8));
        }
    }
    if (D_800952B0 == NULL) {
        func_8007C5DC();
    } else if (D_800952B0->unk4 < D_800952A8->unk4) {
        D_800952B0->unk10 = 2;
        func_8007C484(&D_800952A8);
    }
    func_8007C788(temp_s0);
}

void func_8007D238(Unk *arg0) {

}
