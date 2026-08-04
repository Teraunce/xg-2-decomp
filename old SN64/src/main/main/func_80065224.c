#include "ultra64.h"
void func_80063C08();                                  /* extern */
extern s32 D_800930A8;
extern s32 D_801823F4;
extern s32 D_80182404;

void func_80065224(void **arg0) {
    Unk *temp_v0;

    temp_v0 = *arg0;
    *arg0 = temp_v0 + 8;
    temp_v0->unk0 = 0xDE000000;
    temp_v0->unk4 = &D_800930A8;
    func_80063C08();
    D_801823F4 = 0;
    D_80182404 = -1;
}
