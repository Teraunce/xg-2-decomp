#include "ultra64.h"
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad04[0x10];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 pad18[0x10];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8 pad2C[0x10];
    /* 0x3C */ s32 unk3C;
} UnkStruct_arg0;

void func_8007A858(char *);                         /* extern */

void func_8007B508(UnkStruct_arg0 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    func_8007A858(arg0);
    arg0->unk0 = arg1;
    arg0->unk14 = arg2;
    arg0->unk3C = 1.0f;
    arg0->unk28 = arg3;
}

void func_8007B55C(s32 arg1, s32 arg2, s32 arg3) {

}
