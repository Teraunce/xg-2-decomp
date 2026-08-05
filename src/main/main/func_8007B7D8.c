#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x30];
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} UnkStruct_arg0;

void guMtxIdent(char *);                         /* extern */

void func_8007B7D8(UnkStruct_arg0 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    guMtxIdent(arg0);
    arg0->unk30 = arg1;
    arg0->unk34 = arg2;
    arg0->unk38 = arg3;
}
