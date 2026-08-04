#include "ultra64.h"
s32 func_8007CD08(Unk*, s32*, s32);                         /* extern */
s32 func_80087C78(s32, s32);                          /* extern */
s32 func_80087D78();                                  /* extern */
void func_80087DBC();                                  /* extern */
void func_80088310(s32);                                 /* extern */
extern s32 D_8018AD28;
extern u8 D_8018AD68;

s32 func_80087BC8(s32 arg0) {
    s32 sp1C;
    s32 temp_v0;

    sp1C = 0;
    func_80087D78();
    if (D_8018AD68 != 0) {
        func_80088310(0);
        sp1C = func_80087C78(1, &D_8018AD28);
        func_8007CD08(arg0, 0, 1);
    }
    temp_v0 = func_80087C78(0, &D_8018AD28);
    sp1C = temp_v0;
    D_8018AD68 = 0;
    func_80087DBC();
    return temp_v0;
}
