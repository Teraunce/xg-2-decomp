#include "ultra64.h"
s32 handlerGetResult(void *);                               /* extern */
extern s32 D_800E412C;
extern Unk D_801887D0;

s32 handlerPostCmd(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    *(s32 *)(((D_801887D0.unk160 + 1) * 0x2C) + &D_801887D0) = 0xA;
    (((D_801887D0.unk160 + 1) * 0x2C) + &D_801887D0)->unk4 = arg1;
    (((D_801887D0.unk160 + 1) * 0x2C) + &D_801887D0)->unk8 = arg0;
    (((D_801887D0.unk160 + 1) * 0x2C) + &D_801887D0)->unkC = arg2;
    (((D_801887D0.unk160 + 1) * 0x2C) + &D_801887D0)->unk10 = arg3;
    (((D_801887D0.unk160 + 1) * 0x2C) + &D_801887D0)->unk14 = arg4;
    (((D_801887D0.unk160 + 1) * 0x2C) + &D_801887D0)->unk1C = arg5;
    (((D_801887D0.unk160 + 1) * 0x2C) + &D_801887D0)->unk20 = arg6;
    (((D_801887D0.unk160 + 1) * 0x2C) + &D_801887D0)->unk28 = -1;
    D_801887D0.unk160 = (s32) (D_801887D0.unk160 + 1);
    handlerGetResult(&D_800E412C);
    return (((D_801887D0.unk160 + 1) * 0x2C) + &D_801887D0)->unk28;
}
