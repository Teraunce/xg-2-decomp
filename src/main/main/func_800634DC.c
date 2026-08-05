#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8006364C (initial). */

s32 func_80061894(s32);                               /* extern */
void func_80065224(void**);                               /* extern */
void func_80065274(void**);                               /* extern */
void func_80065370(void**, s32);                            /* extern */
void func_80066574(s32, s32, s32);                    /* extern */
extern s32 D_8004C050;
extern s32 D_8004C058;
extern s32 D_80173CC0;
extern s32 D_801823C4;
extern s32 D_801823C8;

void func_800634DC(void) {
    char *var_a1;
    s32 var_a3;
    s32 temp_t2;

    func_80065224(&D_80173CC0);
    if (D_801823C4 != 0) {
        func_80065370(&D_80173CC0, 0);
        func_80061894(0x48);
        var_a1 = &D_8004C050;
        var_a3 = 0x10;
    } else {
        temp_t2 = func_80061894(0x69);
        var_a1 = &D_8004C058;
        if ((D_801823C8 * 3) < 0) {

        }
        var_a3 = 5;
    }
    func_80066574(var_a1, 0, var_a3);
    func_80065274(&D_80173CC0);
}

void func_8006364C(Unk *arg0) {
    arg0->unkC00;
}
