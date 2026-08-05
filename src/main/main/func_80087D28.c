#include "ultra64.h"
void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
s32 func_8007CE48(Unk*, s32, s32);                         /* extern */
extern s32 D_80096370;
extern s32 D_8018AD08;
extern s32 D_8018AD10;

void func_80087D28(void) {
    D_80096370 = 1;
    osCreateMesgQueue(&D_8018AD10, &D_8018AD08, 1);
    func_8007CE48(&D_8018AD10, 0, 0);
}
