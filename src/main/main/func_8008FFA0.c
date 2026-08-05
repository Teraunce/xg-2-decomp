#include "ultra64.h"
char *func_8008FFA0(Unk *arg0, s32 arg1, s32 arg2) {
    Unk *sp = (Unk*)0;
    s32 sp4;
    s32 sp0;
    s32 temp_v1;

    sp0 = (s32)0 /* implicit $v0 from caller */;
    temp_v1 = arg1 - (arg2 * (s32)0 /* implicit $v0 from caller */);
    sp4 = temp_v1;
    if ((s32)0 /* implicit $v0 from caller */ < 0) {
        sp0 = (s32)0 /* implicit $v0 from caller */;
        sp4 = temp_v1;
        if (temp_v1 > 0) {
            sp4 = temp_v1 - arg2;
            sp0 = (s32)0 /* implicit $v0 from caller */ + 1;
        }
    }
    arg0->unk0 = (s32) sp->unk0;
    arg0->unk4 = (s32) sp->unk4;
    return arg0;
}
