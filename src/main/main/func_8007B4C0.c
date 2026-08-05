#include "ultra64.h"
void func_8007A758(char*, char*);                          /* extern */
void func_8007B368(void *, f32, f32);                       /* extern */

void func_8007B4C0(f32 arg1, s32 arg0) {
    s32 sp18[16];

    func_8007B368(&sp18, arg0, arg1);
    func_8007A758(&sp18, arg0);
}
