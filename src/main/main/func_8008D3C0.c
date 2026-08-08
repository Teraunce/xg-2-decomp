#include "ultra64.h"
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
void osEPiRawReadIoCart(s32, u32 *);                          /* extern */
void bzero(s32, s32);                           /* extern */
extern char *gSramDmaHead;
extern char *gSramDmaNode;
extern s8 gSramCmdByte;
extern s8 gSramAddrLo;
extern s8 gSramVersion;
extern s8 gSramAddrMid;
extern s8 gSramAddrHi;
extern s32 gSramBase;
extern s8 gSramLatInit;
extern s8 gSramPgsInit;
extern s8 gSramState;
extern s8 gSramPwdInit;
extern s32 gSramMmioBase;

void **osEPiGetDomainInfo(void) {
    u32 sp1C;
    s32 sp18;
    s32 temp_v0;

    sp1C = 0;
    if ((s32)0 /* implicit $t6 from caller */ == 0xB0000000) {

    } else {
        gSramCmdByte = 0;
        gSramBase = 0xB0000000;
        osEPiRawReadIoCart(0, &sp1C);
        gSramAddrLo = sp1C & 0xFF;
        gSramAddrMid = (sp1C >> 8) & 0xFF;
        gSramVersion = (sp1C >> 0x10) & 0xF;
        gSramVersion = (sp1C >> 0x14) & 0xF;
        gSramAddrHi = 0;
        bzero(&gSramDmaNode + 0x14, 0x60);
        temp_v0 = osDisableInt();
        gSramDmaNode = gSramDmaHead;
        sp18 = temp_v0;
        gSramDmaHead = &gSramDmaNode;
        osRestoreInt(sp18);
    }
    return &gSramDmaNode;
}

void func_8008D4A8(void) {
    gSramLatInit = 2;
    gSramMmioBase = 0xA5000000;
    gSramPgsInit = 3;
    gSramPwdInit = 6;
    gSramState = 6;
    gSramState = 2;
}
