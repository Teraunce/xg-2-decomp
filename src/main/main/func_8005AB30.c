#include "ultra64.h"
s32 func_8007CD08(Unk*, s32*, s32);                       /* extern */
extern s32 D_8016DF70;

void func_8005AB30(void) {
    s32 sp10;
    s32 temp_v0;
    Unk *temp_s0;

    if ((s32)0 /* implicit $v0 from caller */ > 0) {
        temp_s0 = (s32)0 /* implicit $v1 from caller */;
        do {
            func_8007CD08(&D_8016DF70, &sp10, 1);
            temp_v0 = temp_s0->unk0 /* FIXME: was ->unk-3208 */ - 1;
            temp_s0->unk0 /* FIXME: was ->unk-3208 */ = temp_v0;
        } while (temp_v0 > 0);
    }
}
