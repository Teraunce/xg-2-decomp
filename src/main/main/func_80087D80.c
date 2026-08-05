#include "ultra64.h"
s32 func_8007CD08(Unk*, s32*, s32);                       /* extern */
void func_80087D28();                                  /* extern */
extern s32 D_8018AD10;

void func_80087D80(void) {
    s32 sp1C;

    if ((s32)0 /* implicit $t6 from caller */ == 0) {
        func_80087D28();
    }
    func_8007CD08(&D_8018AD10, &sp1C, 1);
}
