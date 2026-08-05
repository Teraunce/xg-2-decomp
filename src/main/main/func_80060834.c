#include "ultra64.h"
void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);        /* extern */
void osStartThread(Unk*);                               /* extern */
extern s32 gLineTexPtr;
extern s32 D_80092CAC;
extern s32 D_80174730;
extern s32 D_80178450;
extern s32 D_80178458;
extern s32 D_8017C808;
extern Unk D_80181E40;
extern Unk *D_801821E8;
extern s32 func_800602A0;

void func_80060834(s32 arg0) {
    osCreateMesgQueue(&D_80174730, &D_8017C808, 0x20);
    D_80181E40.unk0 = arg0;
    D_80181E40.unk4 = &D_80174730;
    osCreateThread(&D_80178458, 5, &func_800602A0, &D_80181E40, &D_80178450, 8);
    osStartThread(&D_80178458);
}

void gfxAddLineTex(s32 arg1, s8 arg2, s8 arg3, u16 arg4, u16 arg5, u16 arg6) {
    Unk *var_v1;
    u32 var_a0;
    Unk *temp_v0;
    Unk *temp_v0_2;

    if (D_80092CAC != 0) {
        var_a0 = 0;
        var_v1 = D_801821E8;
        do {
            *(s32 *)var_v1 = 0;
            var_a0 += 1;
            var_v1 += 0x10;
        } while (var_a0 < 0x20U);
        D_80092CAC = 0;
    }
    temp_v0 = (gLineTexPtr * 0x10) + D_801821E8;
    temp_v0->unk0 = arg1;
    temp_v0->unkA = arg2;
    ((gLineTexPtr * 0x10) + D_801821E8)->unkB = arg3;
    temp_v0_2 = (gLineTexPtr * 0x10) + D_801821E8;
    temp_v0_2->unk4 = arg4;
    temp_v0_2->unk6 = arg5;
    temp_v0_2->unk8 = arg6;
}
