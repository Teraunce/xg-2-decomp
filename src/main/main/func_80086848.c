#include "ultra64.h"
s32 func_800868F8(void);
s32 osVirtualToPhysical(u32);                             /* extern */
extern u8 gAiDmaWrap;
extern s32 AI_DRAM_ADDR;
extern s32 AI_LEN;
extern s32 AI_STATUS;

s32 osAiRawStartDma(s32 arg0, s32 arg1) {
    s32 sp1C;

    sp1C = arg0;
    if (gAiDmaWrap != 0) {
        sp1C = arg0 - 0x2000;
    }
    if (((arg0 + arg1) & 0x3FFF) == 0x2000) {
        gAiDmaWrap = 1;
    } else {
        gAiDmaWrap = 0;
    }
    if (func_800868F8() != 0) {
        return -1;
    }
    AI_DRAM_ADDR = osVirtualToPhysical(sp1C);
    AI_LEN = arg1;
    return 0;
}

s32 func_800868F8(void) {

}
