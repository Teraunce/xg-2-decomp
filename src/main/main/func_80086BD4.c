#include "ultra64.h"
s32 sfxIsBusy(void);
void osSpSetStatus(s32);                                 /* extern */
extern s32 D_A4040010;

void osSpTaskStart(s32 arg0) {
    if (sfxIsBusy() != 0) {
        do {

        } while (sfxIsBusy() != 0);
    }
    osSpSetStatus(0x125);
}

s32 sfxIsBusy(void) {
    return 0;
}
