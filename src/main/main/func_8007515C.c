#include "ultra64.h"
s32 func_80074F40(s32*);                             /* extern */
s32 func_80074FC4(s32);                             /* extern */
void func_80075120(s32, s32);                          /* extern */

void func_8007515C(s32 arg0, s32 arg1, u32 arg2) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s1_3;
    s32 var_a0;
    s32 var_s1;
    s32 var_s3;
    s32 var_v0;
    s32 var_v0_2;
    u32 temp_v0;
    u32 var_s2;

    /* Flowgraph is not reducible, falling back to gotos-only mode. */
    var_s3 = arg0;
    var_s1 = arg1;
    var_s2 = arg2;
    if (var_s2 == 0) {
        goto block_6;
    }
    var_v0 = var_s3 & 3;
loop_2:
    temp_a0 = var_s3;
    if (var_v0 == 0) {
        goto block_6;
    }
    var_s3 += 1;
    temp_a0_2 = var_s1;
    var_s1 += 1;
    func_80075120(temp_a0_2, func_80074FC4(temp_a0) & 0xFF);
    var_s2 -= 1;
    var_v0 = var_s3 & 3;
    if (var_s2 != 0) {
        goto loop_2;
    }
    var_v0_2 = var_s2 < 4U;
    goto block_7;
block_5:
    temp_v0 = func_80074F40(var_s3);
    temp_s1 = var_s1 + 1;
    func_80075120(var_s1, temp_v0 >> 0x18);
    temp_s1_2 = temp_s1 + 1;
    func_80075120(temp_s1, (temp_v0 >> 0x10) & 0xFF);
    temp_s1_3 = temp_s1_2 + 1;
    func_80075120(temp_s1_2, (temp_v0 >> 8) & 0xFF);
    var_s1 = temp_s1_3 + 1;
    func_80075120(temp_s1_3, temp_v0 & 0xFF);
    var_s3 += 4;
    var_s2 -= 4;
block_6:
    var_v0_2 = var_s2 < 4U;
block_7:
    if (var_v0_2 == 0) {
        goto block_5;
    }
    var_a0 = var_s3;
    if (var_s2 == 0) {
        goto block_10;
    }
loop_9:
    var_s3 += 1;
    temp_a0_3 = var_s1;
    var_s1 += 1;
    func_80075120(temp_a0_3, func_80074FC4(var_a0) & 0xFF);
    var_s2 -= 1;
    var_a0 = var_s3;
    if (var_s2 != 0) {
        goto loop_9;
    }
block_10:
    return;
}
