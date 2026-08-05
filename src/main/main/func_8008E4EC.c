#include "ultra64.h"
void osSendMesg(void *, int, int);
extern int D_8018D310;

void func_8008E4EC(void) {
    osSendMesg(&D_8018D310, 0, 0);
}
