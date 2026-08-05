#include "ultra64.h"
void func_8007A758(char*, char*);                          /* extern */
s32 func_8007A910(void *, s32);                          /* extern */
void func_8007AA68(char*, f32*, char*);                     /* extern */

void func_8007AC38(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp98[16];
    s32 sp58[16];
    s32 sp18[16];

    func_8007A910(&sp98, arg0);
    func_8007A910(&sp58, arg1);
    func_8007AA68(&sp98, &sp58, &sp18);
    func_8007A758(&sp18, arg2);
}
