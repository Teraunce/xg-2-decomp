#include "ultra64.h"
void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
s32 func_8007CE48(Unk*, s32, s32);                         /* extern */
extern s32 D_800964B0;
extern s32 D_8018D308;
extern s32 D_8018D310;

void func_8008E458(void) {
    D_800964B0 = 1;
    osCreateMesgQueue(&D_8018D310, &D_8018D308, 1);
    func_8007CE48(&D_8018D310, 0, 0);
}
