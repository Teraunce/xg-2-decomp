#include "ultra64.h"
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x02 */ s32 unk2;
    /* 0x04 */ s32 unk4;
    /* 0x06 */ s32 unk6;
    /* 0x0A */ u8 pad0A[0x2E];
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ u8 pad44[0xC];
    /* 0x50 */ f32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0x24];
    /* 0x80 */ s32 unk80;
} UnkStruct_arg1;

s16 trackNodeFindNearestGetter(f32, f32, s32);                   /* extern */
extern f32 D_8004BBB8;
extern f32 D_8004BBBC;

void entitySlotReset(UnkStruct_arg0 *arg0, UnkStruct_arg1 *arg1, s32 arg2) {
    s16 var_v0;

    if (arg2 != 0) {
        var_v0 = trackNodeFindNearestGetter(arg0->unk0, arg0->unk4, arg0->unk8);
    } else {
        var_v0 = arg1->unk4;
    }
    arg1->unk4 = var_v0;
    arg1->unk6 = -1;
    arg1->unk2 = 0;
    arg1->unk80 = 0;
    arg1->unk0 = -1;
    arg1->unk38 = 0;
    arg1->unk3C = 0;
    arg1->unk54 = 0;
    arg1->unk58 = 0;
    arg1->unk40 = (f32) D_8004BBB8;
    arg1->unk50 = (f32) D_8004BBBC;
}
