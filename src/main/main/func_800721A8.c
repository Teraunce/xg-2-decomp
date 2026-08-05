#include "ultra64.h"
void func_80070454(s32, Unk*);                       /* extern */
s32 func_80070F50(s32, s32, s32, s32, s32, s32, s32);     /* extern */
void func_80071EA4(s32, s32);                          /* extern */
s32 func_8008A288(Unk*, u16, s32, s32, s32); /* extern */
s32 func_8008B088(void *, u16, s32, s32, s32, s32*); /* extern */
extern s32 D_8018894C;
extern Unk D_80188B5C;

void func_800721A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp48;
    s32 sp20;
    s32 var_s5;
    Unk *temp_s0;
    char *temp_s1;
    char *temp_s2;
    char *temp_s3;

    /* Flowgraph is not reducible, falling back to gotos-only mode. */
    temp_s0 = (arg2 * 0x2C) + &D_80188B5C;
    if (temp_s0->unk0 == 0) {
        goto block_3;
    }
    if (arg3 == 0) {
        goto block_4;
    }
    func_80070454(temp_s0 + 0x1A, &sp20);
    var_s5 = 1;
    if (func_80070F50(0x38, arg1, 0x39, 0x31, 0, &sp20, 0) <= 0) {
        goto block_5;
    }
block_3:
    *(s32*)((char*)&D_80188B5C - 0x22C) = (s32) (*(s32*)((char*)&D_80188B5C - 0x22C) - 1);
    return;
block_4:
    var_s5 = 1;
block_5:
    temp_s2 = (arg1 * 0x68) + &D_8018894C;
    temp_s3 = temp_s0 + 0x1A;
    temp_s1 = temp_s0 + 0x16;
    if (func_8008A288(temp_s2, temp_s0->unk14, temp_s0->unk10, temp_s3, temp_s1) != 0) {
        goto block_7;
    }
    if (func_8008B088(temp_s2, temp_s0->unk14, temp_s0->unk10, temp_s3, temp_s1, &sp48) != 0) {
        goto block_8;
    }
block_7:
    var_s5 = 0;
    if (func_80070F50(0x3B, arg1, 0x52, 0x31, 0, 0, 0) == 0) {
        goto block_4;
    }
block_8:
    if (var_s5 == 0) {
        goto block_10;
    }
    func_80070F50(0x3A, arg1, 0xB9, 0, 0, 0, 0);
block_10:
    func_80071EA4(arg0, arg1);
    return;
}
