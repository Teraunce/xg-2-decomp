#include "ultra64.h"
s32 func_80061894(s32);                               /* extern */
void func_80062D98(void*, void*);                            /* extern */
void func_80062F1C(s32, s32, s32, s32, s32);                   /* extern */
void func_80065618(u16*, u16*);                          /* extern */
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
    func_80065618(&D_80182038, func_80061894(0xC6));
    func_80065618(&D_80182188, func_80061894(0xC7));
    func_80065618(&D_80181F90, func_80061894(0xC8));
    func_80065618(&D_801820B8, func_80061894(0xED));
    func_80065618(&D_80181E50, func_80061894(0xCB));
    func_80065618(&D_801821C8, func_80061894(0xCF));
    func_80065618(&D_80182290, func_80061894(0x13E));
    func_80065618(&D_80182168, func_80061894(0xB8));
    func_80065618(&D_80182230, func_80061894(0x64));
    func_80065618(&D_80182258, func_80061894(0xC9));
    func_80065618(&D_801821F0, func_80061894(0x13B));
    func_80065618(&D_80181F10, func_80061894(0x13C));
    func_80065618(&D_80181F50, func_80061894(0xCA));
    func_80065618(&D_801822B0, func_80061894(0x13D));
    func_80062F1C(3, 4, 0, 0x100, 0);
    func_80062D98(&D_80092BA0, 0);
}
