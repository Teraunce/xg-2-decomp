#include "ultra64.h"
s32 contPakChecksum(s32 arg0, u16 *arg1, u16 *arg2) {
    u16 sp6;
    u32 sp0;
    u16 temp_t9;
    u32 temp_t7;

    sp6 = 0;
    *arg2 = 0;
    *arg1 = *arg2;
    sp0 = 0;
    do {
        temp_t9 = *(u16*)(s32)(arg0 + sp0);
        sp6 = temp_t9;
        *arg1 += temp_t9;
        *arg2 += ~sp6;
        temp_t7 = sp0 + 2;
        sp0 = temp_t7;
    } while (temp_t7 < 0x1CU);
    return 0;
}
