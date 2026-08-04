#include "ultra64.h"
void func_8007BA98(u32, s32);                            /* extern */
void func_8007BC28(u32, s32);                            /* extern */
s32 func_8007D688(u32);                             /* extern */
s32 func_80087B48();                                /* extern */
extern s32 D_A4800000;
extern s32 D_A4800004;
extern s32 D_A4800010;

s32 func_80087C78(s32 arg0, s32 arg1) {
    if (func_80087B48() != 0) {
        return -1;
    }
    if (arg0 == 1) {
        func_8007BC28(arg1, 0x40);
    }
    D_A4800000 = func_8007D688(arg1);
    if (arg0 == 0) {
        D_A4800004 = 0x1FC007C0;
    } else {
        D_A4800010 = 0x1FC007C0;
    }
    if (arg0 == 0) {
        func_8007BA98(arg1, 0x40);
    }
    return 0;
}
