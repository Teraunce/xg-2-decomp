#include "ultra64.h"
s32 handlerGetResult(void *);                               /* extern */
extern s32 gSfxEffectTableB;
extern Unk gHandlerCtx;

s32 handlerPostSfxCmd(s32 arg0, s32 arg1) {
    *(s32 *)(((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx) = 0xB;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk4 = arg0;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk8 = arg1;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk28 = -1;
    gHandlerCtx.unk160 = (s32) (gHandlerCtx.unk160 + 1);
    handlerGetResult(&gSfxEffectTableB);
    return (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk28;
}

void func_80071200(s32 arg1) {
    *(s32 *)(((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx) = 3;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk4 = arg1;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk28 = -1;
    gHandlerCtx.unk160 = (s32) (gHandlerCtx.unk160 + 1);
}

void func_8007128C(s32 arg1, s32 arg2, s32 arg3) {
    *(s32 *)(((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx) = 4;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk4 = arg1;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk8 = arg2;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unkC = arg3;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk28 = -1;
    gHandlerCtx.unk160 = (s32) (gHandlerCtx.unk160 + 1);
}
