#include "ultra64.h"
s32 handlerGetResult(void *);                               /* extern */
extern s32 gSfxEffectTableA;
extern Unk gHandlerCtx;

s32 handlerPostCmd(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    *(s32 *)(((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx) = 0xA;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk4 = arg1;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk8 = arg0;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unkC = arg2;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk10 = arg3;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk14 = arg4;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk1C = arg5;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk20 = arg6;
    (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk28 = -1;
    gHandlerCtx.unk160 = (s32) (gHandlerCtx.unk160 + 1);
    handlerGetResult(&gSfxEffectTableA);
    return (((gHandlerCtx.unk160 + 1) * 0x2C) + &gHandlerCtx)->unk28;
}
