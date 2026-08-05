#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
s32 func_8007CD08(Unk*, s32*, s32);                       /* extern */
extern s32 D_8016DF70;

void func_8005AB30(void) {
    s32 sp10;
    s32 temp_v0;
    Unk *temp_s0;

    if ((s32)M2C_ERROR(/* Read from unset register $v0 */) > 0) {
        temp_s0 = (s32)M2C_ERROR(/* Read from unset register $v1 */);
        do {
            func_8007CD08(&D_8016DF70, &sp10, 1);
            temp_v0 = temp_s0->unk0 /* FIXME: was ->unk-3208 */ - 1;
            temp_s0->unk0 /* FIXME: was ->unk-3208 */ = temp_v0;
        } while (temp_v0 > 0);
    }
}
