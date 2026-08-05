#include "ultra64.h"
s32 func_8004D4A8(s32);                               /* extern */
extern s32 D_8017C7F0;
extern s32 D_8017C8A0;

void func_8004EC54(void) {
    s32 temp_v0;

    temp_v0 = func_8004D4A8(0xFA00);
    D_8017C8A0 = temp_v0;
    D_8017C7F0 = temp_v0;
}
