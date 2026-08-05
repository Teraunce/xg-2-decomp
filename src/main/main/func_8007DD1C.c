#include "ultra64.h"
u8 func_8007DC58(s32, s32);                            /* extern */

s32 func_8007DD1C(void) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_t1;

    temp_v0 = func_8007DC58((s32)0 /* implicit $t2 from caller */, (s32)0 /* implicit $t3 from caller */);
    var_t1 = temp_v0;
    if (temp_v0 & 0x80) {
        do {
            temp_v0_2 = func_8007DC58((s32)0 /* implicit $t2 from caller */, (s32)0 /* implicit $t3 from caller */);
            var_t1 = ((s32)var_t1 /* loop feedback: previous var_t1 value in $t1 */ << 7) + (temp_v0_2 & 0x7F);
        } while (temp_v0_2 & 0x80);
    }
    return var_t1;
}
