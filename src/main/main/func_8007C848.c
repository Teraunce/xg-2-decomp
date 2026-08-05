#include "ultra64.h"
s32 func_8007C5DC();                                  /* extern */
s32 func_8007C768();                                /* extern */
s32 func_8007C788(s32);                               /* extern */
void func_8007D238(Unk *);                            /* extern */
extern Unk *D_800952AC;
extern char *D_800952B0;

void func_8007C848(Unk *arg0) {
    s32 temp_s0;
    Unk *var_s1;
    char *var_s2;

    temp_s0 = func_8007C768();
    if (arg0 == NULL) {
        arg0 = D_800952B0;
    } else if (arg0->unk10 != 1) {
        func_8007D238(arg0->unk8);
    }
    if (D_800952AC == arg0) {
        D_800952AC = D_800952AC->unkC;
    } else {
        var_s1 = D_800952AC;
        var_s2 = var_s1->unkC;
        if (var_s2 != NULL) {
loop_7:
            if ((void*)var_s2 == (void*)arg0) {
                var_s1->unkC = (s32) arg0->unkC;
            } else {
                var_s1 = var_s2;
                var_s2 = var_s1->unkC;
                if (var_s2 != NULL) {
                    goto loop_7;
                }
            }
        }
    }
    if ((void*)arg0 == (void*)D_800952B0) {
        func_8007C5DC();
    }
    func_8007C788(temp_s0);
}
