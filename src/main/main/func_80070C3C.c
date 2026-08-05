#include "ultra64.h"
s32 func_8006216C(void *);                             /* extern */
void func_80070BCC(s32, s32);                        /* extern */
extern s32 D_80093EE4;

void func_80070C3C(s32 arg0, s32 arg1) {
    if (func_8006216C(&D_80093EE4) == 0) {
        func_80070BCC(1, arg1);
    }
}
