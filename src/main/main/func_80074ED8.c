#include "ultra64.h"
s32 func_80074FA8();                                  /* extern */
s32 getCOP0Status();                                /* extern */
void setCOP0Status();                              /* extern */
extern s32 gContPakWaitCnt;

void intRestore(s32 arg0) {
    setCOP0Status(getCOP0Status() | arg0);
}

void __osPiRawWriteIo(s32 *arg0, s32 arg1) {
    if (*(s32 *)0xA4600010 & 3) {
        do {

        } while (*(s32 *)0xA4600010 & 3);
    }
    *arg0 = arg1;
}

s32 __osPiRawReadIo(s32 *arg0) {
    if (*(s32 *)0xA4600010 & 3) {
        do {

        } while (*(s32 *)0xA4600010 & 3);
    }
    return *arg0;
}

void __osPiResetCount(void) {
    gContPakWaitCnt = 0;
    func_80074FA8();
}

/* -------------------------------------------------------------------------
 * __osPiWaitForCount — PI DMA busy-wait counter.
 *
 * Increments gContPakWaitCnt each iteration and spins until gContPakWaitCnt >= arg0.
 * The branch-to-self pattern (bnez __osPiWaitForCount) caused m2c to fail;
 * translated here as a simple do-while.
 * ------------------------------------------------------------------------- */
void __osPiWaitForCount(s32 arg0) {
    do {
        gContPakWaitCnt++;
    } while (gContPakWaitCnt < arg0);
}
