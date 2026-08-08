#include "ultra64.h"
void osSendMesg(void *, int, int);
extern int D_8018D310;

void __piUnlock(void) {
    osSendMesg(&D_8018D310, 0, 0);
}
