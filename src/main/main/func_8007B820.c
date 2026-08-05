#include "ultra64.h"
void func_8007A758(char*, char*);                          /* extern */
void func_8007A858(char*);                               /* extern */
extern f32 D_8004C8E8;

void func_8007B820(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    s32 sp28[16];

    func_8007A858(&sp28);
    sp58 = arg1;
    sp5C = arg2;
    sp60 = arg3;
    func_8007A758(&sp28, arg0);
}

void func_8007B878(f32 arg1, s32 arg2, s32 arg3) {

}
