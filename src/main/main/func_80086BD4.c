#include "ultra64.h"
s32 sfxIsBusy(void);
void osSpSetStatus(s32);                                 /* extern */
extern s32 SP_STATUS_REG;

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
