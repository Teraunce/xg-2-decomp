#include "ultra64.h"
void func_8007A758(char*, char*);                          /* extern */
void func_8007A858(char*);                               /* extern */

void func_8007A8E0(s32 arg0) {
    s32 sp18[16];

    func_8007A858(&sp18);
    func_8007A758(&sp18, arg0);
}

f32 func_8007A910(void) {
    return 65536.0f;
}
