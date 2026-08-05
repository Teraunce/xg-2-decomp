#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x3C];
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
} UnkStruct_arg0;

void func_8007E734(void**, s32, s32);                  /* extern */
extern f64 D_8004CEA8;

void func_80082758(UnkStruct_arg0 *arg0, s8 arg1) {
    s8 sp28;
    s32 sp24;
    s16 sp20;

    sp20 = 8;
    sp28 = arg1;
    sp24 = (arg0->unk3C * 0x30) + arg0->unk40;
    func_8007E734(arg0 + 0x14, &sp20, 0);
}

void func_800827B8(void) {

}

s32 func_800827C0(UnkStruct_arg0 *arg0, s32 arg1) {
    return (s32) (f32) (((f64) ((f32) arg1 * (f32) arg0->unk44) / D_8004CEA8) + 0.5) & ~0xF;
}
