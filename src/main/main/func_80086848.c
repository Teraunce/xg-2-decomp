#include "ultra64.h"
s32 func_800868F8(void);
s32 func_8007D688(u32);                             /* extern */
extern u8 D_800955B0;
extern s32 D_A4500000;
extern s32 D_A4500004;
extern s32 D_A450000C;

s32 func_80086848(s32 arg0, s32 arg1) {
    s32 sp1C;

    sp1C = arg0;
    if (D_800955B0 != 0) {
        sp1C = arg0 - 0x2000;
    }
    if (((arg0 + arg1) & 0x3FFF) == 0x2000) {
        D_800955B0 = 1;
    } else {
        D_800955B0 = 0;
    }
    if (func_800868F8() != 0) {
        return -1;
    }
    D_A4500000 = func_8007D688(sp1C);
    D_A4500004 = arg1;
    return 0;
}

s32 func_800868F8(void) {

}
