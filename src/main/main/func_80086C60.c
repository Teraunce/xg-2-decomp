#include "ultra64.h"
extern s32 D_A4080000;

s32 osSpSetPc(s32 arg0, s32 arg1) {
    if (!(arg1 & 1)) {
        return -1;
    }
    D_A4080000 = arg0;
    return 0;
}
