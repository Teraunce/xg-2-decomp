#include "ultra64.h"
void audioClearNode();                                  /* extern */
extern s32 gPendingFlushFlag;

void pendingFlushClear(void) {
    if ((s32)0 /* implicit $t6 from caller */ != 0) {
        audioClearNode();
        gPendingFlushFlag = 0;
    }
}

void audioSynthSetup(void);  /* forward: GETTER_NOJR fallthrough */
void audioSynthSetupGetter(void) {
    audioSynthSetup();  /* GETTER_NOJR: loads *D_800952D0 into $t6, falls into audioSynthSetup */
}
