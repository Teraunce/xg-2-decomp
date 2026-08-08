#include "ultra64.h"
extern s32 D_A0000000;
extern s32 D_A4600010;

s32 osEPiRawWriteIo(Unk *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 & 3) {
        do {

        } while (D_A4600010 & 3);
    }
    *(s32*)(s32)(arg0->unkC | arg1 | (s32) &D_A0000000) = arg2;
    return 0;
}
