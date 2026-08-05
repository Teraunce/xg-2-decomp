#include "ultra64.h"
s32 getCOP0Status();                                /* extern */
void setCOP0Status();                              /* extern */

s32 intDisable(void) {
    s32 temp_v0;

    temp_v0 = getCOP0Status();
    setCOP0Status();
    return temp_v0 & 1;
}
