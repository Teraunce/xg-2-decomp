#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
s32 func_80086904(s32 arg0) {
    if (arg0 & (s32)M2C_ERROR(/* Read from unset register $at */)) {
        return 1;
    }
    return 0;
}
