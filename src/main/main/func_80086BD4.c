#include "ultra64.h"
s32 func_80086C18(void);
void osSpSetStatus(s32);                                 /* extern */
extern s32 D_A4040010;

void osSpTaskStart(s32 arg0) {
    if (func_80086C18() != 0) {
        do {

        } while (func_80086C18() != 0);
    }
    osSpSetStatus(0x125);
}

s32 func_80086C18(void) {
    return 0;
}
