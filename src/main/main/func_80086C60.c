#include "ultra64.h"
extern s32 DP_CMD_START;

s32 osSpSetPc(s32 arg0, s32 arg1) {
    if (!(arg1 & 1)) {
        return -1;
    }
    DP_CMD_START = arg0;
    return 0;
}
