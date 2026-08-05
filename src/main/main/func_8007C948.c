#include "ultra64.h"
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
s32 __osGetCount();                                /* static */
extern s32 D_80189A88;
extern u32 D_80189A8C;
extern s32 D_80189A90;

s32 osGetTime(void) {
    s32 sp34;
    s32 sp30;
    u32 sp2C;
    s32 sp28;
    s32 temp_s0;

    temp_s0 = osDisableInt();
    sp34 = __osGetCount();
    sp30 = sp34 - D_80189A90;
    sp2C = D_80189A8C;
    sp28 = D_80189A88;
    osRestoreInt(temp_s0);
    return ((u32) (sp30 + sp2C) < sp2C) + sp28;
}

/*
 * __osGetCount — read COP0 Count register (hardware cycle counter).
 * Uses `mfc0 $v0, $9` — not expressible in standard C.
 */
s32 __osGetCount(void) {
    /* mfc0 $v0, $9 — read COP0 Count */
    return 0;
}
