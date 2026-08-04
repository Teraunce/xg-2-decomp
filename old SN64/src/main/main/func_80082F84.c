#include "ultra64.h"
s32 func_8007FD48(s32, s32, s32, s32, s32);               /* extern */
void func_80084EF8(Unk*, s32, s32, s32);              /* extern */
extern s32 func_80085068;
extern s32 func_80085154;

void func_80082F84(Unk *arg0, s32 arg1) {
    func_80084EF8(arg0, &func_80085154, &func_80085068, 1);
    arg0->unk14 = func_8007FD48(0, 0, arg1, 1, 0x20);
    arg0->unk24 = 1;
    arg0->unk30 = 0;
    arg0->unk1C = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk20 = 0.0f;
    arg0->unk18 = 1.0f;
}
