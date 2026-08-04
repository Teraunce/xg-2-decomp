#include "ultra64.h"
void func_80074F08(s32*, s32);                          /* extern */
s32 func_80074F40(s32*);                             /* extern */

void func_800752E8(s32 arg0, s32 arg1) {
    s32 temp_s0;
    s32 temp_s2;

    temp_s0 = arg0 & ~3;
    temp_s2 = (~arg0 & 3) * 8;
    func_80074F08(temp_s0, (func_80074F40(temp_s0) & ~(0xFF << temp_s2)) | ((arg1 & 0xFF) << temp_s2));
}
