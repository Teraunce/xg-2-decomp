#include "ultra64.h"
void func_8005A978(Unk *);                                  /* extern */
extern s32 D_8017CDF8;

void func_8005AA64(Unk *arg0, s32 arg1, s32 arg2) {
    arg0->unk0 = arg1;
    arg0->unk4 = arg2;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk10 = 0;
    D_8017CDF8 = 0;
    func_8005A978(arg0);
}
