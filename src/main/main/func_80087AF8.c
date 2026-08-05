#include "ultra64.h"
s32 func_80087B48(void);                                /* static */
extern s32 D_A0000000;
extern s32 D_A4800018;

s32 osEPiRawReadIo(s32 arg0, s32 *arg1) {
    if (func_80087B48() != 0) {
        return -1;
    }
    *arg1 = *(s32*)(s32)(arg0 | (s32) &D_A0000000);
    return 0;
}

s32 func_80087B48(void) {

}
