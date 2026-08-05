#include "ultra64.h"
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
void func_8008CEB8(s32, u32 *);                          /* extern */
void func_8008EAB8(s32, s32);                           /* extern */
extern char *D_8009649C;
extern char *D_8018C208;
extern s8 D_8018C20C;
extern s8 D_8018C20D;
extern s8 D_8018C20E;
extern s8 D_8018C210;
extern s8 D_8018C211;
extern s32 D_8018C214;
extern s8 D_8018C28C;
extern s8 D_8018C28D;
extern s8 D_8018C28E;
extern s8 D_8018C290;
extern s32 D_8018C294;

void **osEPiGetDomainInfo(void) {
    u32 sp1C;
    s32 sp18;
    s32 temp_v0;

    sp1C = 0;
    if ((s32)0 /* implicit $t6 from caller */ == 0xB0000000) {

    } else {
        D_8018C20C = 0;
        D_8018C214 = 0xB0000000;
        func_8008CEB8(0, &sp1C);
        D_8018C20D = sp1C & 0xFF;
        D_8018C210 = (sp1C >> 8) & 0xFF;
        D_8018C20E = (sp1C >> 0x10) & 0xF;
        D_8018C20E = (sp1C >> 0x14) & 0xF;
        D_8018C211 = 0;
        func_8008EAB8(&D_8018C208 + 0x14, 0x60);
        temp_v0 = osDisableInt();
        D_8018C208 = D_8009649C;
        sp18 = temp_v0;
        D_8009649C = &D_8018C208;
        osRestoreInt(sp18);
    }
    return &D_8018C208;
}

void func_8008D4A8(void) {
    D_8018C28C = 2;
    D_8018C294 = 0xA5000000;
    D_8018C28D = 3;
    D_8018C290 = 6;
    D_8018C28E = 6;
    D_8018C28E = 2;
}
