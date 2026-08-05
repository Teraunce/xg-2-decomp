#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8008E408 (initial). */

extern s32 D_A0000000;
extern s32 D_A4600010;

s32 func_8008E3C0(Unk *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    if (arg3 & 3) {
        do {

        } while (D_A4600010 & 3);
    }
    *arg2 = *(s32*)(s32)(arg0->unkC | arg1 | (s32) &D_A0000000);
    return 0;
}

s32 func_8008E410(void);  /* forward: GETTER_NOJR fallthrough */
void func_8008E408(void) {
    return func_8008E410();
}
