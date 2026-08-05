#include "ultra64.h"
void func_8007BD08(OSThread*, OSId, u32, s32, u32, OSPri);          /* extern */
void func_8007C9E8();                                  /* extern */
void func_8007D0E8(Unk*);                               /* extern */
extern s32 D_8016DBD0;
extern s32 D_8016DC10;
extern s32 D_801786B8;
extern s32 func_8004E0F8;

void func_8004E094(void) {
    func_8007C9E8();
    D_801786B8 = 0;
    func_8007BD08(&D_8016DC10, 1, &func_8004E0F8, 0, &D_8016DBD0, 0xA);
    func_8007D0E8(&D_8016DC10);
}
