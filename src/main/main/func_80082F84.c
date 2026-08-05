#include "ultra64.h"
s32 audioHeapAlloc(s32, s32, s32, s32, s32);               /* extern */
void audioNodeInit(Unk*, s32, s32, s32);              /* extern */
extern s32 func_80085068;
extern s32 func_80085154;

void func_80082F84(Unk *arg0, s32 arg1) {
    audioNodeInit(arg0, &func_80085154, &func_80085068, 1);
    arg0->unk14 = audioHeapAlloc(0, 0, arg1, 1, 0x20);
    arg0->unk24 = 1;
    arg0->unk30 = 0;
    arg0->unk1C = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk20 = 0.0f;
    arg0->unk18 = 1.0f;
}
