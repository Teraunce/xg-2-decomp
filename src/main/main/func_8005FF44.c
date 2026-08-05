#include "ultra64.h"
s32 sfxMapId(s32);                               /* extern */
void func_80062D98(void*, void*);                            /* extern */
void func_80062F1C(s32, s32, s32, s32, s32);                   /* extern */
void copyU16Array(u16*, u16*);                          /* extern */
extern s32 gRaceCtrl;
extern s32 D_80092BA0;
extern s32 D_80181E50;
extern s32 D_80181F10;
extern s32 D_80181F50;
extern s32 D_80181F90;
extern s32 D_80182038;
extern s32 D_801820B8;
extern s32 D_80182168;
extern s32 D_80182188;
extern s32 D_801821C8;
extern s32 D_801821F0;
extern s32 D_80182230;
extern s32 D_80182258;
extern s32 D_80182290;
extern s32 D_801822B0;

void func_8005FF44(s32 arg0) {
    gRaceCtrl = arg0;
    copyU16Array(&D_80182038, sfxMapId(0xC6));
    copyU16Array(&D_80182188, sfxMapId(0xC7));
    copyU16Array(&D_80181F90, sfxMapId(0xC8));
    copyU16Array(&D_801820B8, sfxMapId(0xED));
    copyU16Array(&D_80181E50, sfxMapId(0xCB));
    copyU16Array(&D_801821C8, sfxMapId(0xCF));
    copyU16Array(&D_80182290, sfxMapId(0x13E));
    copyU16Array(&D_80182168, sfxMapId(0xB8));
    copyU16Array(&D_80182230, sfxMapId(0x64));
    copyU16Array(&D_80182258, sfxMapId(0xC9));
    copyU16Array(&D_801821F0, sfxMapId(0x13B));
    copyU16Array(&D_80181F10, sfxMapId(0x13C));
    copyU16Array(&D_80181F50, sfxMapId(0xCA));
    copyU16Array(&D_801822B0, sfxMapId(0x13D));
    func_80062F1C(3, 4, 0, 0x100, 0);
    func_80062D98(&D_80092BA0, 0);
}
