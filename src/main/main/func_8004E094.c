#include "ultra64.h"
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);          /* extern */
void osInitialize();                                  /* extern */
void func_8007D0E8(Unk*);                               /* extern */
extern s32 D_8016DBD0;
extern s32 D_8016DC10;
extern s32 D_801786B8;
extern s32 gameMainThread;

void gameInit(void) {
    osInitialize();
    D_801786B8 = 0;
    osCreateThread(&D_8016DC10, 1, &gameMainThread, 0, &D_8016DBD0, 0xA);
    func_8007D0E8(&D_8016DC10);
}
