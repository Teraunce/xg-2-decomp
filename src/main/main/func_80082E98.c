#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x14];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_arg0;

void func_80084EF8(void *, void *, void *, s32);
extern s32 func_80085FB8;
extern s32 func_80085FEC;

void func_80082E98(UnkStruct_arg0 *arg0) {
    func_80084EF8(arg0, &func_80085FEC, &func_80085FB8, 3);
    arg0->unk14 = 0;
    arg0->unk18 = 1;
}
