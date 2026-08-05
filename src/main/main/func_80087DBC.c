#include "ultra64.h"
void osSendMesg(void *, int, int);
extern int D_8018AD10;

void __siUnlock(void) {
    osSendMesg(&D_8018AD10, 0, 0);
}
