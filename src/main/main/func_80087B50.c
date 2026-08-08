#include "ultra64.h"
s32 isUnaligned(s32 arg0) {
    if (arg0 & 3) {
        return 1;
    }
    return 0;
}
