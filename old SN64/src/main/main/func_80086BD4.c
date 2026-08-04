#include "ultra64.h"
s32 func_80086C18(void);
void func_80086C48(s32);                                 /* extern */
extern s32 D_A4040010;

void func_80086BD4(s32 arg0) {
    if (func_80086C18() != 0) {
        do {

        } while (func_80086C18() != 0);
    }
    func_80086C48(0x125);
}

s32 func_80086C18(void) {
    return 0;
}
