#include "ultra64.h"
s32 func_8007CD08(Unk*, s32*, s32);                       /* extern */
void func_8008E458();                                  /* extern */
extern s32 D_8018D310;

void func_8008E4B0(void) {
    s32 sp1C;

    if ((s32)0 /* implicit $t6 from caller */ == 0) {
        func_8008E458();
    }
    func_8007CD08(&D_8018D310, &sp1C, 1);
}
