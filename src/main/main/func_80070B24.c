#include "ultra64.h"
void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);        /* extern */
void func_8007D0E8(Unk*);                               /* extern */
extern s32 D_801875C0;
extern s32 D_80188770;
extern s32 D_80188774;
extern s32 D_80188780;
extern s32 D_801887A0;
extern s32 D_801887B8;
extern Unk D_801887D0;
extern s32 func_80070B0C;

void func_80070B24(s32 arg0) {
    D_80188770 = arg0;
    osCreateMesgQueue(&D_801887A0, &D_80188780, 8);
    osCreateMesgQueue(&D_801887B8, &D_80188774, 1);
    osCreateThread(&D_801875C0, 5, &func_80070B0C, 0, &D_80188770, 5);
    D_801887D0.unk16C = 1;
    D_801887D0.unk160 = -1;
    func_8007D0E8(&D_801875C0);
}
