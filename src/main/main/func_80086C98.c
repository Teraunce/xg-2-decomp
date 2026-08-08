#include "ultra64.h"
s32 osVirtualToPhysical(u32);                             /* extern */
s32 sfxIsBusy();                                /* extern */
extern s32 SP_MEM_ADDR;
extern s32 SP_DRAM_ADDR;
extern s32 SP_RD_LEN;
extern s32 SP_WR_LEN;

s32 osSpRawStartDma(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (sfxIsBusy() != 0) {
        return -1;
    }
    SP_MEM_ADDR = arg1;
    SP_DRAM_ADDR = osVirtualToPhysical(arg2);
    if (arg0 == 0) {
        SP_WR_LEN = arg3 - 1;
    } else {
        SP_RD_LEN = arg3 - 1;
    }
    return 0;
}
