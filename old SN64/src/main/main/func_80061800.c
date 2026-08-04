#include "ultra64.h"
void func_80063878(u16);                               /* extern */
u16 func_80063B0C(s32);                               /* extern */
extern s32 D_80092B74;
extern u16 D_80092B78;

s32 func_80061800(s32 arg0) {
    s32 var_s0;
    u16 temp_v0;

    var_s0 = arg0;
    if (var_s0 != 0x656E554B) {
        var_s0 = 0x656E554B;
    }
    D_80092B74 = 0;
    if (D_80092B78 != 0) {
        func_80063878(D_80092B78);
    }
    temp_v0 = func_80063B0C(0x4E);
    D_80092B78 = temp_v0;
    if (temp_v0 & 0xFFFF) {
        D_80092B74 = var_s0;
        return 1;
    }
    return 0;
}

s32 func_80061884(void) {
    return D_80092B74;
}
