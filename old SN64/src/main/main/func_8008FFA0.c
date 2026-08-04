#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
char *func_8008FFA0(Unk *arg0, s32 arg1, s32 arg2) {
    Unk *sp = (Unk*)0;
    s32 sp4;
    s32 sp0;
    s32 temp_v1;

    sp0 = (s32)M2C_ERROR(/* Read from unset register $v0 */);
    temp_v1 = arg1 - (arg2 * (s32)M2C_ERROR(/* Read from unset register $v0 */));
    sp4 = temp_v1;
    if ((s32)M2C_ERROR(/* Read from unset register $v0 */) < 0) {
        sp0 = (s32)M2C_ERROR(/* Read from unset register $v0 */);
        sp4 = temp_v1;
        if (temp_v1 > 0) {
            sp4 = temp_v1 - arg2;
            sp0 = (s32)M2C_ERROR(/* Read from unset register $v0 */) + 1;
        }
    }
    arg0->unk0 = (s32) sp->unk0;
    arg0->unk4 = (s32) sp->unk4;
    return arg0;
}
