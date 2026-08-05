#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8008E3B8 (initial). */

s32 func_8007C484(void *);                               /* extern */
s32 func_8007C768();                                /* extern */
s32 func_8007C788(s32);                               /* extern */
extern s32 D_800952A8;
extern Unk *D_800952B0;
extern s32 D_A4600010;

void func_8008E368(void) {
    s32 temp_s0;

    temp_s0 = func_8007C768();
    D_800952B0->unk10 = 2;
    func_8007C484(&D_800952A8);
    func_8007C788(temp_s0);
}

void func_8008E3B8(void) {

}
