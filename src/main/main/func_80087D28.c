#include "ultra64.h"
void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
s32 osSendMesg(Unk*, s32, s32);                         /* extern */
extern s32 D_80096370;
extern s32 D_8018AD08;
extern s32 D_8018AD10;

void __siInit(void) {
    D_80096370 = 1;
    osCreateMesgQueue(&D_8018AD10, &D_8018AD08, 1);
    osSendMesg(&D_8018AD10, 0, 0);
}
