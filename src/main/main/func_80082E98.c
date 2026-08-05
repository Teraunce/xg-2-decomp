#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x14];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} UnkStruct_arg0;

void audioNodeInit(void *, void *, void *, s32);
extern s32 audioNodeSetProp;
extern s32 func_80085FEC;

void func_80082E98(UnkStruct_arg0 *arg0) {
    audioNodeInit(arg0, &func_80085FEC, &audioNodeSetProp, 3);
    arg0->unk14 = 0;
    arg0->unk18 = 1;
}
