#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
u8 func_8007DC58(s32, s32);                            /* extern */

s32 func_8007DD1C(void) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_t1;

    temp_v0 = func_8007DC58((s32)M2C_ERROR(/* Read from unset register $t2 */), (s32)M2C_ERROR(/* Read from unset register $t3 */));
    var_t1 = temp_v0;
    if (temp_v0 & 0x80) {
        do {
            temp_v0_2 = func_8007DC58((s32)M2C_ERROR(/* Read from unset register $t2 */), (s32)M2C_ERROR(/* Read from unset register $t3 */));
            var_t1 = ((s32)M2C_ERROR(/* Read from unset register $t1 */) << 7) + (temp_v0_2 & 0x7F);
        } while (temp_v0_2 & 0x80);
    }
    return var_t1;
}
