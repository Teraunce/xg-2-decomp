#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_80086C58 (initial). */

extern s32 D_A4040010;

s32 func_80086C20(s32 arg0) {
    if (arg0 & 0x1C) {
        return 1;
    }
    return 0;
}

void func_80086C48(s32 arg0) {
    D_A4040010 = arg0;
}

void func_80086C58(void) {

}
