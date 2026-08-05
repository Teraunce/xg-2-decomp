#include "ultra64.h"
void sfxPlay(u16);                               /* extern */
u16 func_80063B0C(s32);                               /* extern */
extern s32 gLocale;
extern u16 gLocaleIdx;

s32 func_80061800(s32 arg0) {
    s32 var_s0;
    u16 temp_v0;

    var_s0 = arg0;
    if (var_s0 != 0x656E554B) {
        var_s0 = 0x656E554B;
    }
    gLocale = 0;
    if (gLocaleIdx != 0) {
        sfxPlay(gLocaleIdx);
    }
    temp_v0 = func_80063B0C(0x4E);
    gLocaleIdx = temp_v0;
    if (temp_v0 & 0xFFFF) {
        gLocale = var_s0;
        return 1;
    }
    return 0;
}

s32 func_80061884(void) {
    return gLocale;
}
