#include "ultra64.h"
s32 func_80074FA8();                                  /* extern */
s32 func_80076154();                                /* extern */
void func_80076160();                              /* extern */
extern s32 D_80188E40;

void func_80074ED8(s32 arg0) {
    func_80076160(func_80076154() | arg0);
}

void func_80074F08(s32 *arg0, s32 arg1) {
    if (*(s32 *)0xA4600010 & 3) {
        do {

        } while (*(s32 *)0xA4600010 & 3);
    }
    *arg0 = arg1;
}

s32 func_80074F40(s32 *arg0) {
    if (*(s32 *)0xA4600010 & 3) {
        do {

        } while (*(s32 *)0xA4600010 & 3);
    }
    return *arg0;
}

void func_80074F7C(void) {
    D_80188E40 = 0;
    func_80074FA8();
}

/* -------------------------------------------------------------------------
 * func_80074F8C — PI DMA busy-wait counter.
 *
 * Increments D_80188E40 each iteration and spins until D_80188E40 >= arg0.
 * The branch-to-self pattern (bnez func_80074F8C) caused m2c to fail;
 * translated here as a simple do-while.
 * ------------------------------------------------------------------------- */
void func_80074F8C(s32 arg0) {
    do {
        D_80188E40++;
    } while (D_80188E40 < arg0);
}
