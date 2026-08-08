#include "ultra64.h"
extern s32 gPhysMemBase;
extern s32 PI_STATUS_REG;

s32 osEPiRawWriteIo(Unk *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 & 3) {
        do {

        } while (PI_STATUS_REG & 3);
    }
    *(s32*)(s32)(arg0->unkC | arg1 | (s32) &gPhysMemBase) = arg2;
    return 0;
}
